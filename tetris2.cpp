#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <sstream>
#include <algorithm>

using namespace std;

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

const int WIDTH = 10;
const int HEIGHT = 20;

vector<vector<vector<int>>> tetrominoes = {
    {{1, 1, 1, 1}},
    {{1, 1}, {1, 1}},
    {{0, 1, 0}, {1, 1, 1}},
    {{1, 1, 0}, {0, 1, 1}},
    {{0, 1, 1}, {1, 1, 0}},
    {{1, 0, 0}, {1, 1, 1}},
    {{0, 0, 1}, {1, 1, 1}}
};

class Tetris {
private:
    vector<vector<int>> grid;
    int score, level;
    int fallInterval;
    pair<int, int> pos;
    vector<vector<int>> currentPiece;
    int currentColor;
    HANDLE hConsole;
    bool gameOver;
    vector<string> colors;

    vector<vector<int>> nextPiece;
    int nextColor;

    void generateNextPiece() {
        int index = rand() % tetrominoes.size();
        nextPiece = tetrominoes[index];
        nextColor = index;
    }

public:
    Tetris() : gameOver(false) {
        grid = vector<vector<int>>(HEIGHT, vector<int>(WIDTH, -1));
        score = 0;
        level = 1;
        fallInterval = 500;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(hConsole, &cursorInfo);

        colors = {"🟦", "🟨", "🟪", "🟩", "🟥", "🟫", "🟧"};

        generateNextPiece();
        spawnPiece();
    }

    void spawnPiece() {
        currentPiece = nextPiece;
        currentColor = nextColor;
        pos.first = 0;
        pos.second = WIDTH / 2 - (int)currentPiece[0].size() / 2;
        generateNextPiece();
        if (!isValidMove(pos.first, pos.second, currentPiece)) {
            gameOver = true;
            Beep(400, 500);
        }
    }

    bool isValidMove(int newRow, int newCol, const vector<vector<int>> &piece) {
        for (int i = 0; i < piece.size(); i++) {
            for (int j = 0; j < piece[i].size(); j++) {
                if (piece[i][j]) {
                    int r = newRow + i, c = newCol + j;
                    if (r < 0 || r >= HEIGHT || c < 0 || c >= WIDTH || grid[r][c] != -1)
                        return false;
                }
            }
        }
        return true;
    }

    vector<vector<int>> rotatePieceMatrix(const vector<vector<int>> &piece) {
        int rows = piece.size(), cols = piece[0].size();
        vector<vector<int>> rotated(cols, vector<int>(rows, 0));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                rotated[j][rows - 1 - i] = piece[i][j];
            }
        }
        return rotated;
    }

    void rotatePiece() {
        vector<vector<int>> rotated = rotatePieceMatrix(currentPiece);
        int newWidth = rotated[0].size();
        int newHeight = rotated.size();
        int newCol = pos.second;
        int newRow = pos.first;
        if (newCol + newWidth > WIDTH)
            newCol = WIDTH - newWidth;
        if (newCol < 0)
            newCol = 0;
        if (newRow + newHeight > HEIGHT)
            newRow = HEIGHT - newHeight;
        if (newRow < 0)
            newRow = 0;
        if (isValidMove(newRow, newCol, rotated)) {
            pos.first = newRow;
            pos.second = newCol;
            currentPiece = rotated;
            Beep(500, 100);
        }
    }

    void movePiece(int dx) {
        if (isValidMove(pos.first, pos.second + dx, currentPiece)) {
            pos.second += dx;
            Beep(300, 50);
        }
    }

    bool moveDown() {
        if (isValidMove(pos.first + 1, pos.second, currentPiece)) {
            pos.first++;
            return true;
        }
        return false;
    }

    void dropPiece() {
        while (isValidMove(pos.first + 1, pos.second, currentPiece))
            pos.first++;
        Beep(600, 100);
    }

    void lockPiece() {
        for (int i = 0; i < currentPiece.size(); i++) {
            for (int j = 0; j < currentPiece[i].size(); j++) {
                if (currentPiece[i][j] && pos.first + i >= 0)
                    grid[pos.first + i][pos.second + j] = currentColor;
            }
        }
        clearLines();
        spawnPiece();
    }

    void clearLines() {
        int linesCleared = 0;
        for (int i = HEIGHT - 1; i >= 0; i--) {
            bool full = true;
            for (int j = 0; j < WIDTH; j++) {
                if (grid[i][j] == -1) {
                    full = false;
                    break;
                }
            }
            if (full) {
                linesCleared++;
                grid.erase(grid.begin() + i);
                grid.insert(grid.begin(), vector<int>(WIDTH, -1));
                i++;
                Beep(800, 100);
            }
        }
        score += linesCleared * 100;
        if (score >= level * 500) {
            level++;
            fallInterval = max(50, fallInterval - 50);
            Beep(1000, 150);
        }
    }

    bool isGameOver() {
        return gameOver;
    }

    void render() {
        pair<int, int> ghostPos = pos;
        while (isValidMove(ghostPos.first + 1, ghostPos.second, currentPiece))
            ghostPos.first++;

        ostringstream frame;
        frame << "+";
        for (int j = 0; j < WIDTH * 2; j++)
            frame << "-";
        frame << "+\n";

        for (int i = 0; i < HEIGHT; i++) {
            frame << "|";
            for (int j = 0; j < WIDTH; j++) {
                bool activeCell = false;
                bool ghostCell = false;
                int cellColor = -1;
                for (int pi = 0; pi < currentPiece.size(); pi++) {
                    for (int pj = 0; pj < currentPiece[pi].size(); pj++) {
                        if (currentPiece[pi][pj]) {
                            if (pos.first + pi == i && pos.second + pj == j) {
                                activeCell = true;
                                cellColor = currentColor;
                            }
                            if (ghostPos.first + pi == i && ghostPos.second + pj == j)
                                ghostCell = true;
                        }
                    }
                }
                if (activeCell)
                    frame << colors[cellColor];
                else if (grid[i][j] != -1)
                    frame << colors[grid[i][j]];
                else if (ghostCell)
                    frame << "\033[2m" << colors[currentColor] << "\033[22m";
                else
                    frame << "\033[48;5;235m  \033[0m";
            }
            frame << "|\n";
        }
        frame << "+";
        for (int j = 0; j < WIDTH * 2; j++)
            frame << "-";
        frame << "+\n";

        frame << "Score: " << score << "  Level: " << level << "\n";

        frame << "\nNext Piece:\n";
        if (!nextPiece.empty()) {
            frame << "+";
            for (int j = 0; j < nextPiece[0].size() * 2; j++)
                frame << "-";
            frame << "+\n";
            for (int i = 0; i < nextPiece.size(); i++) {
                frame << "|";
                for (int j = 0; j < nextPiece[i].size(); j++) {
                    if (nextPiece[i][j])
                        frame << colors[nextColor];
                    else
                        frame << "  ";
                }
                frame << "|\n";
            }
            frame << "+";
            for (int j = 0; j < nextPiece[0].size() * 2; j++)
                frame << "-";
            frame << "+\n";
        }

        SetConsoleCursorPosition(hConsole, {0, 0});
        cout << frame.str();
    }

    void processInput() {
        if (_kbhit()) {
            char key = _getch();
            if (key == 0 || key == -32) {
                key = _getch();
                if (key == 75)
                    movePiece(-1);
                else if (key == 77)
                    movePiece(1);
                else if (key == 80) {
                    if (!moveDown())
                        lockPiece();
                }
                else if (key == 72)
                    rotatePiece();
            }
            else if (key == 27) {
                exit(0);
            }
            else if (key == 32) {
                dropPiece();
                lockPiece();
            }
        }
    }

    void play() {
        DWORD lastFall = GetTickCount();
        const int frameDelay = 16;
        while (!isGameOver()) {
            processInput();
            DWORD now = GetTickCount();
            if (now - lastFall >= (DWORD)fallInterval) {
                if (!moveDown())
                    lockPiece();
                lastFall = now;
            }
            render();
            Sleep(frameDelay);
        }
        render();
        cout << "\nGame Over! Final Score: " << score << "\n";
    }
};

int main() {
    srand((unsigned int)time(0));
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    char choice;
    do {
        Tetris game;
        game.play();
        cout << "\nGame Over! Press R to restart, ESC to exit...";
        while (true) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 'r' || key == 'R') {
                    choice = 'r';
                    break;
                }
                else if (key == 27) {
                    choice = 27;
                    break;
                }
            }
        }
    } while (choice == 'r');

    return 0;
}

