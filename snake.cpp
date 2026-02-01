#include <iostream>
#include <deque>
#include <conio.h>
#include <windows.h>
using namespace std;
void SetupConsole() {
    SetConsoleOutputCP(CP_UTF8);
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);
}

struct Point { int x, y; };
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
class SnakeGame {
    int width, height, score;
    Point food;
    deque<Point> snake;
    Direction dir;
    bool gameOver;
public:
    SnakeGame() : width(30), height(15), score(0), gameOver(false), dir(STOP) {
        snake.push_front({width / 2, height / 2});
        food = { rand() % width, rand() % height };
    }
    void ShowMenu() {
        system("cls");
        cout << "\n\n\n\t  ==========================";
        cout << "\n\t     S N A K E   G A M E";
        cout << "\n\t  ==========================";
        cout << "\n\n\t   Press ANY KEY to Start";
        cout << "\n\t   Use W, A, S, D to move";
        _getch();
    }
    void Draw() {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
        cout << "\n    SCORE: " << score << "  |  Press 'X' to Quit\n";
        cout << "  ╔";
        for (int i = 0; i < width; i++) cout << "═";
        cout << "╗" << endl;
        for (int y = 0; y < height; y++) {
            cout << "  ║";
            for (int x = 0; x < width; x++) {
                bool isBody = false;
                if (x == snake.front().x && y == snake.front().y) {
                    cout << "O";
                    isBody = true;
                } else {
                    for (size_t i = 1; i < snake.size(); i++) {
                        if (snake[i].x == x && snake[i].y == y) {
                            cout << "o";
                            isBody = true;
                            break;
                        }
                    }
                }
                if (!isBody) {
                    if (x == food.x && y == food.y) cout << "★"; // Food
                    else cout << " ";
                }
            }
            cout << "║" << endl;
        }
        cout << "  ╚";
        for (int i = 0; i < width; i++) cout << "═";
        cout << "╝" << endl;
    }
    void Input() {
        if (_kbhit()) {
            switch (_getch()) {
                case 'a': case 'A': if(dir != RIGHT) dir = LEFT; break;
                case 'd': case 'D': if(dir != LEFT) dir = RIGHT; break;
                case 'w': case 'W': if(dir != DOWN) dir = UP; break;
                case 's': case 'S': if(dir != UP) dir = DOWN; break;
                case 'x': case 'X': gameOver = true; break;
            }
        }
    }
    void Logic() {
        if (dir == STOP) return;
        Point head = snake.front();
        if (dir == LEFT) head.x--;
        else if (dir == RIGHT) head.x++;
        else if (dir == UP) head.y--;
        else if (dir == DOWN) head.y++;
        if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height) gameOver = true;
        for (auto s : snake) if (s.x == head.x && s.y == head.y) gameOver = true;
        snake.push_front(head);
        if (head.x == food.x && head.y == food.y) {
            score += 10;
            food = { rand() % width, rand() % height };
        } else {
            snake.pop_back();
        }
    }
    void Run() {
        ShowMenu();
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            Sleep(70);
        }
        system("cls");
        cout << "\n\n   GAME OVER!";
        cout << "\n   Final Score: " << score << "\n\n";
        Sleep(2000);
    }
};
int main() {
    SetupConsole();
    SnakeGame game;
    game.Run();
    return 0;
}
