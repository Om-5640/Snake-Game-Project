#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#ifdef _WIN32
    #include <conio.h>   // Windows keyboard input
    #include <windows.h> // Windows system commands
    #define CLEAR_SCREEN "cls"
    void sleep_ms(int ms) { Sleep(ms); }
#else
    #include <termios.h>
    #include <unistd.h>
    #define CLEAR_SCREEN "clear"
    void sleep_ms(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

    int _kbhit() {
        struct termios oldt, newt;
        int ch;
        int oldf;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);
        if (ch != EOF) {
            ungetc(ch, stdin);
            return 1;
        }
        return 0;
    }

    int _getch() {
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#endif

using namespace std;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class SnakeGame {
private:
    bool gameOver;
    const int width;
    const int height;
    int x, y, foodX, foodY, score;
    int speed, baseSpeed;
    Direction dir;
    vector<pair<int, int>> snake;
    vector<pair<int, int>> obstacles;
    vector<pair<int, int>> portals;
    bool hasObstacles, hasPortals;

public:
    SnakeGame(int w, int h) 
        : width(w), height(h), gameOver(false), score(0), dir(STOP), 
          hasObstacles(false), hasPortals(false) {}

    void selectDifficulty() {
        char choice;
        cout << "Select Difficulty - (E)asy, (M)edium, (H)ard: ";
        cin >> choice;

        if (choice == 'E' || choice == 'e') baseSpeed = 150;
        else if (choice == 'M' || choice == 'm') baseSpeed = 100;
        else baseSpeed = 60;

        speed = baseSpeed;
    }

    void resetGame() {
        gameOver = false;
        score = 0;
        dir = STOP;
        x = width / 2;
        y = height / 2;
        snake.clear();
        snake.push_back({x, y});
        foodX = rand() % width;
        foodY = rand() % height;
        obstacles.clear();
        portals.clear();

        selectDifficulty(); 

        char obstacleChoice;
        cout << "Do you want to enable obstacles? (y/n): ";
        cin >> obstacleChoice;
        hasObstacles = (obstacleChoice == 'y' || obstacleChoice == 'Y');

        if (hasObstacles) {
            int numObstacles = (width * height) / 60;
            for (int i = 0; i < numObstacles; i++) {
                int obsX, obsY;
                do {
                    obsX = rand() % width;
                    obsY = rand() % height;
                } while ((obsX == x && obsY == y) || (obsX == foodX && obsY == foodY));
                obstacles.push_back({obsX, obsY});
            }
        }

        char portalChoice;
        cout << "Do you want to enable teleportation portals? (y/n): ";
        cin >> portalChoice;
        hasPortals = (portalChoice == 'y' || portalChoice == 'Y');

        if (hasPortals) {
            for (int i = 0; i < 2; i++) {
                int portalX, portalY;
                do {
                    portalX = rand() % width;
                    portalY = rand() % height;
                } while ((portalX == x && portalY == y) || (portalX == foodX && portalY == foodY));
                portals.push_back({portalX, portalY});
            }
        }
    }

    void draw() {
        cout << "\033[H";  // Move cursor to top left without clearing the screen

        vector<string> buffer(height + 2, string(width + 2, ' '));

        for (int i = 0; i < width + 2; i++) {
            buffer[0][i] = '#';
            buffer[height + 1][i] = '#';
        }

        for (int i = 1; i <= height; i++) {
            buffer[i][0] = '#';
            buffer[i][width + 1] = '#';
        }

        for (auto part : snake) {
            buffer[part.second + 1][part.first + 1] = '*';
        }

        buffer[y + 1][x + 1] = '*';
        buffer[foodY + 1][foodX + 1] = 'F';

        for (auto obs : obstacles) {
            buffer[obs.second + 1][obs.first + 1] = '#';
        }

        if (hasPortals) {
            buffer[portals[0].second + 1][portals[0].first + 1] = 'O';
            buffer[portals[1].second + 1][portals[1].first + 1] = 'O';
        }

        for (const auto& line : buffer) {
            cout << line << endl;
        }

        cout << "Score: " << score << endl;
    }

    void input() {
        if (_kbhit()) {
            switch (_getch()) {
                case 'a': if (dir != RIGHT) dir = LEFT; break;
                case 'd': if (dir != LEFT) dir = RIGHT; break;
                case 'w': if (dir != DOWN) dir = UP; break;
                case 's': if (dir != UP) dir = DOWN; break;
                case 'x': gameOver = true; break;
            }
        }
    }

    void logic() {
        snake.insert(snake.begin(), {x, y});

        if (x == foodX && y == foodY) {
            score += 10;
            foodX = rand() % width;
            foodY = rand() % height;
        } else {
            snake.pop_back();
        }

        switch (dir) {
            case LEFT: x--; break;
            case RIGHT: x++; break;
            case UP: y--; break;
            case DOWN: y++; break;
        }

        if (x < 0 || x >= width || y < 0 || y >= height) {
            gameOver = true;
            return;
        }

        for (int i = 1; i < snake.size(); i++) {
            if (snake[i].first == x && snake[i].second == y) {
                gameOver = true;
                return;
            }
        }

        if (hasObstacles) {
            for (auto obs : obstacles) {
                if (x == obs.first && y == obs.second) {
                    gameOver = true;
                    return;
                }
            }
        }

        if (hasPortals && ((x == portals[0].first && y == portals[0].second) ||
                           (x == portals[1].first && y == portals[1].second))) {
            auto otherPortal = (x == portals[0].first && y == portals[0].second) ? portals[1] : portals[0];
            x = otherPortal.first;
            y = otherPortal.second;
        }
    }

    void run() {
        while (true) {
            resetGame();
            while (!gameOver) {
                draw();
                input();
                logic();
                sleep_ms(speed);
            }
            cout << "Game Over! Score: " << score << endl;
            char choice;
            cout << "Press 'R' to restart or any other key to exit: ";
            cin >> choice;
            if (choice != 'R' && choice != 'r') break;
        }
    }
};

int main() {
    srand(time(0));
    SnakeGame game(30, 20);
    game.run();
    return 0;
}
