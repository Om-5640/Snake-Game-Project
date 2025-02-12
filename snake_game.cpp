#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm> 

using namespace std;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class SnakeGame {
private:
    bool gameOver;
    int width, height;
    int x, y, foodX, foodY, score;
    int speed;
    int level;
    char foodType;
    Direction dir;
    vector<pair<int, int>> snake;
    vector<pair<int, int>> obstacles;

    
    bool hasPortals;
    vector<pair<int, int>> portals;  

public:
    SnakeGame() : gameOver(false), score(0), dir(STOP), hasPortals(false) {}

    void setupGame() {
        cout << "Enter Grid Height: ";
        cin >> height;
        cout << "Enter Grid Width: ";
        cin >> width;

        cout << "Choose difficulty level:\n";
        cout << "1 -(Easy)\n2 -(Medium)\n3 -(Hard)\n";
        cout << "Enter level: ";
        cin >> level;

        if (level == 1) speed = 110;
        else if (level == 2) speed = 70;
        else if (level == 3) speed = 40;
        else speed = 110;  

        resetGame();
    }

    
    bool portalCollides(int px, int py) {
        for (auto part : snake) {
            if (px == part.first && py == part.second)
                return true;
        }
        for (auto obs : obstacles) {
            if (px == obs.first && py == obs.second)
                return true;
        }
        for (auto port : portals) {
            if (px == port.first && py == port.second)
                return true;
        }
        return false;
    }

   
    void generatePortals() {
        portals.clear();
        for (int i = 0; i < 2; i++) {
            int portalX, portalY;
            do {
                portalX = rand() % width;
                portalY = rand() % height;
            } while ((portalX == x && portalY == y) ||  
                     portalCollides(portalX, portalY) || 
                     (portalX == foodX && portalY == foodY));
            portals.push_back({portalX, portalY});
        }
    }

    void resetGame() {
        system("cls");
        gameOver = false;
        score = 0;
        dir = STOP;
        x = width / 2;
        y = height / 2;
        snake.clear();
        
        snake.push_back({x, y});
        snake.push_back({x - 1, y});
        
        obstacles.clear();
        generateObstacles();

        
        char portalChoice;
        cout << "Do you want to enable teleportation portals? (y/n): ";
        cin >> portalChoice;
        if (portalChoice == 'y' || portalChoice == 'Y') {
            hasPortals = true;
            generatePortals();
        } else {
            hasPortals = false;
            portals.clear();
        }

        spawnFood();
    }

    void generateObstacles() {
        int numObstacles = (width * height) / (level == 1 ? 70 : (level == 2 ? 60 : 40));

        for (int i = 0; i < numObstacles; i++) {
            int obsX, obsY;
            do {
                obsX = rand() % width;
                obsY = rand() % height;
            } while ((obsX == x && obsY == y) || (obsX == foodX && obsY == foodY));
            obstacles.push_back({obsX, obsY});
        }
    }

   
    void spawnFood() {
        do {
            foodX = rand() % width;
            foodY = rand() % height;
        } while (foodCollides());

        int foodChance = rand() % 100;
        
        foodType = (foodChance < 70) ? 'F' : (foodChance < 90) ? 'S' : 'M';
    }

    
    bool foodCollides() {
        for (auto part : snake) {
            if (foodX == part.first && foodY == part.second)
                return true;
        }
        for (auto obs : obstacles) {
            if (foodX == obs.first && foodY == obs.second)
                return true;
        }
        if (hasPortals) {
            for (auto port : portals) {
                if (foodX == port.first && foodY == port.second)
                    return true;
            }
        }
        return false;
    }

    void gotoxy(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void hideCursor() {
        CONSOLE_CURSOR_INFO cursorInfo;
        cursorInfo.dwSize = 100;
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    }

    void draw() {
        gotoxy(0, 0); 

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
            buffer[part.second + 1][part.first + 1] = 'o';
        }
       
        buffer[y + 1][x + 1] = 'O';

        
        buffer[foodY + 1][foodX + 1] = foodType;

        
        for (auto obs : obstacles) {
            buffer[obs.second + 1][obs.first + 1] = 'X';
        }

       
        if (hasPortals) {
            for (auto port : portals) {
                buffer[port.second + 1][port.first + 1] = 'O';
            }
        }

        
        for (const auto& line : buffer) {
            cout << line << endl;
        }

        cout << "Score: " << score << "  (F = +10, S = +30, M = +50)" << endl;
    }

    void input() {
        if (_kbhit()) {
            char key = _getch();

            
            if (key == -32) {
                key = _getch();
                switch (key) {
                    case 72: if (dir != DOWN) dir = UP; break;
                    case 80: if (dir != UP) dir = DOWN; break;
                    case 75: if (dir != RIGHT) dir = LEFT; break;
                    case 77: if (dir != LEFT) dir = RIGHT; break;
                }
            } else {
                switch (key) {
                    case 'a': if (dir != RIGHT) dir = LEFT; break;
                    case 'd': if (dir != LEFT) dir = RIGHT; break;
                    case 'w': if (dir != DOWN) dir = UP; break;
                    case 's': if (dir != UP) dir = DOWN; break;
                    case 'x': gameOver = true; break;
                }
            }
        }
    }

    void logic() {
        if (dir == STOP) return;

        
        snake.insert(snake.begin(), {x, y});

        
        if (x == foodX && y == foodY) {
            int growth = 1;  
            if (foodType == 'F') {
                score += 10;
                growth = 1;
            } else if (foodType == 'S') {
                score += 30;
                growth = 3;
            } else if (foodType == 'M') {
                score += 50;
                growth = 5;
            }
            
            for (int i = 0; i < growth - 1; i++) {
                snake.push_back(snake.back());
            }
            spawnFood();
        } else {
            snake.pop_back();
        }

        
        switch (dir) {
            case LEFT:  x--; break;
            case RIGHT: x++; break;
            case UP:    y--; break;
            case DOWN:  y++; break;
            default: break;
        }

       
        if (hasPortals) {
            for (size_t i = 0; i < portals.size(); i++) {
                if (x == portals[i].first && y == portals[i].second) {
                    
                    int other = (i == 0) ? 1 : 0;
                    x = portals[other].first;
                    y = portals[other].second;
                    break;
                }
            }
        }

       
        if (x < 0 || x >= width || y < 0 || y >= height) {
            gameOver = true;
            return;
        }

        
        for (size_t i = 1; i < snake.size(); i++) {
            if (snake[i].first == x && snake[i].second == y) {
                gameOver = true;
                return;
            }
        }

        
        for (auto obs : obstacles) {
            if (x == obs.first && y == obs.second) {
                gameOver = true;
                return;
            }
        }
    }

    void run() {
        int maxx = 0;
        setupGame();
        while (true) {
            while (!gameOver) {
                draw();
                input();
                logic();
                Sleep(speed);
            }
            maxx = max(maxx, score);
            
            cout << "Game Over! Your adventure has ended. \n";
            cout << "Your score: " << score << "\nMax Score: " << maxx << endl;
            string choice;
            cout << "Press 'r' to restart or any other key to exit: ";
            cin >> choice;
            
            if (choice == "r" || choice == "R") {
                setupGame();
            } else {
                cout << " Game Over! Your adventure has ended. \n";
                break;
            }
        }
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));
    SnakeGame game;
    game.run();
    return 0;
}
