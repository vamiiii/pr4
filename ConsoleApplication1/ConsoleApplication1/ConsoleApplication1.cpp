#include <iostream>
#include <conio.h>
#include <windows.h>

const int width = 10;
const int height = 10;
bool GameOver = false;
bool GameWin = false;
int foodX, foodY;
int metka = 0;

struct SnakeNode {
public:
    int x, y;
    SnakeNode* next;
    SnakeNode(int startX, int startY) : x(startX), y(startY), next(nullptr) {}
};

class Snake {
public:
    SnakeNode* head=nullptr;
    SnakeNode* tail=nullptr;
    char dvi='d';

    Snake() {};

    Snake(int startX, int startY)
    {
        head = new SnakeNode{ startX,startY};
        tail = head;
    }

    void genFood() {
        foodX = rand() % (width-2)+1;
        foodY = rand() % (height-2)+1;

        while (Game(foodX, foodY))
        {
            foodX = rand() % (width - 2) + 1;
            foodY = rand() % (height - 2) + 1;
        }
    }

    void move() {
        int newX = head->x;
        int newY = head->y;

        if (_kbhit())
        {
            int key = _getch();
            if (key == 87 || key == 119 )
            {
                if (dvi !='s')
                {
                    dvi = 'w';
                }
            }
            else if (key == 65 || key == 97)
            {
                if (dvi != 'd')
                {
                    dvi = 'a';
                }
            }
            else if (key == 83 || key == 115)
            {
                if (dvi != 'w')
                {
                    dvi = 's';
                }
            }
            else if (key == 68 || key == 100)
            {
                if (dvi != 'a')
                {
                    dvi = 'd';
                }
            }
        }

        switch (dvi) {
        case 'w': newY--; break;
        case 's': newY++; break;
        case 'a': newX--; break;
        case 'd': newX++; break;
        }

        if(Game(newX,newY))
        {
            GameOver = true;
            return;
        }

        if (newX==foodX && newY == foodY)
        {
            SnakeNode* newHead = new SnakeNode(newX, newY);
            newHead->next = head;
            head = newHead;
            metka++;
            if (metka==100)
            {
                GameWin = true;
                return;
            }
            genFood();
        }
        else
        {
            SnakeNode* newHead = new SnakeNode(newX, newY);
            newHead->next = head;
            head = newHead;

            SnakeNode* temp = head;
            while (temp->next != tail) { temp = temp->next; }
            delete tail;
            tail = temp;
            tail->next = nullptr;

        }
    }

    bool Game(int x, int y)
    {
        if (x < 1 || x >= width-1 || y < 1 || y >= height-1)
        {
            GameOver = true;
            return true;
        }
        SnakeNode* current = head;
        while (current != nullptr)
        {
            if (current->x == x && current->y == y)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void draw() {
        system("cls");

        for (int i = 0; i < width; ++i) {
            std::cout << '#';
        }
        std::cout << std::endl;

        for (int i = 1; i < height - 1; ++i) {
            for (int j = 0; j < width; ++j) {
                if (j == 0 || j == width - 1) {
                    std::cout << '#'; 
                }
                else if (i == head->y && j == head->x) {
                    std::cout << 'O'; 
                }
                else if (i == foodY && j == foodX) {
                    std::cout << '*'; 
                }
                else {
                    bool isBodyPart = false;
                    SnakeNode* current = head->next;
                    while (current != nullptr) {
                        if (current->x == j && current->y == i) {
                            std::cout << 'o';
                            isBodyPart = true;
                            break;
                        }
                        current = current->next;
                    }
                    if (!isBodyPart) {
                        std::cout << '.';
                    }
                }
            }
            std::cout << std::endl;
        }

        for (int i = 0; i < width; ++i) {
            std::cout << '#';
        }
        std::cout << std::endl;
    }

};

int main()
{
    setlocale(0, "rus");
    Snake g;
    g.head = new SnakeNode(width / 2, height / 2);
    g.tail = g.head;
    g.genFood();
    while(!GameOver || !GameWin)
    {
        g.move();
        g.draw();
        Sleep(1000);
    }
    if (GameWin == true)
    {
        std::cout << "Game Win!";
        return 0;
    }
    std::cout << "Game Over!";
    return 0;
}

