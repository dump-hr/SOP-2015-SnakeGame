#include <iostream>
#include <string>
#include <conio.h>
#include <time.h>

using namespace std;

bool IsRunning();
bool IsSnakeElement(int);
bool IsCharacterInputed();

void PrintMap();
void InitializeGame();
void InitializeMap();
void InitializeBorders();
void InitializeSnake();
void WaitForNSeconds(double);

char GetCharacterFromInput();
void ChangeDirection(char);
void Move(int, int);
void UpdateSnakePosition();
void GenerateFood();
void Update();
void ClearScreen();
char GetElementValue(int);
void PrintCenteredText(string);
void PrintCharacterNTimes(char, int);

const int mapWidth = 20;
const int mapHeight = 20;
const int mapSize = mapWidth * mapHeight;
int map[mapHeight][mapWidth];
int headXPosition;
int headYPosition;
int direction;
int snakeLength = 3;
bool running = true;

const int emptySpaceId = 0;
const int borderId = -1;
const int foodId = -2;
const int initialSnakeLength = 3;

int main()
{
    InitializeGame();

    while (IsRunning())
    {
        if (IsCharacterInputed())
        {
            ChangeDirection(GetCharacterFromInput());
        }
        Update();
        PrintMap();
        WaitForNSeconds(0.5);
    }

    PrintCenteredText("Game over!");
    PrintCenteredText("Your score is: " + to_string(snakeLength - initialSnakeLength));

    return 0;
}


void InitializeGame()
{
    srand(time(NULL));
    InitializeBorders();
    InitializeSnake();
    direction = 0;
    GenerateFood();
}
void InitializeMap()
{
    InitializeBorders();
    InitializeSnake();
    GenerateFood();
}
void InitializeBorders()
{
    for (int y = 0; y < mapHeight; y++)
    {
        bool isFirstOrLastLine = y == 0 || y == mapHeight - 1;
        if (isFirstOrLastLine)
        {
            for (int x = 0; x < mapWidth; x++)
                map[y][x] = borderId;
        }
        else
        {
            map[y][0] = borderId;
            map[y][mapWidth - 1] = borderId;
        }
    }
}
void InitializeSnake()
{
    headXPosition = mapWidth / 2;
    headYPosition = mapHeight / 2;

    for (int headElementIndex = 0; headElementIndex < snakeLength; headElementIndex++)
        map[headXPosition][headYPosition + headElementIndex] = snakeLength - headElementIndex;
}

bool IsRunning()
{
    return running;
}

bool IsSnakeElement(int element)
{
    return element > 0;
}
bool IsSnakeHead(int element)
{
    return element == map[headYPosition][headXPosition];
}

bool IsCharacterInputed()
{
    return kbhit();
}

void ClearScreen()
{
    system("cls");
}
void PrintMap()
{
    ClearScreen();

    for (int x = 0; x < mapWidth; x++)
    {
        for (int y = 0; y < mapHeight; y++)
        {
            cout << GetElementValue(map[y][x]);
        }
        cout << endl;
    }
}


void WaitForNSeconds(double seconds)
{
    _sleep(seconds * 1000);
}

char GetCharacterFromInput()
{
    return getch();
}

void ChangeDirection(char key)
{
    switch (key)
    {
    case 'w': if (direction != 2) direction = 0; break;
    case 'd': if (direction != 3) direction = 1; break;
    case 's': if (direction != 0) direction = 2; break;
    case 'a': if (direction != 1) direction = 3; break;
    }
}

void Move(int dx, int dy)
{
    int newXPosition = headXPosition + dx;
    int newYPosition = headYPosition + dy;

    if (map[newYPosition][newXPosition] == foodId)
    {
        map[newYPosition][newXPosition] = snakeLength + 1;
        snakeLength++;
        GenerateFood();
    }
    else if (map[newYPosition][newXPosition] == emptySpaceId)
    {
        map[newYPosition][newXPosition] = snakeLength + 1;
        UpdateSnakePosition();
    }
    else if (map[newYPosition][newXPosition] == borderId || IsSnakeElement(map[newYPosition][newXPosition]))
    {
        running = false;
    }

    headXPosition = newXPosition;
    headYPosition = newYPosition;
}

void UpdateSnakePosition()
{
    for (int x = 0; x < mapWidth; x++)
    {
        for (int y = 0; y < mapHeight; y++)
        {
            if (IsSnakeElement(map[y][x]))
            {
                map[y][x]--;
            }
        }
    }
}

void GenerateFood()
{
    int x = 0, y = 0;
    do {
        x = rand() % (mapWidth - 2) + 1;
        y = rand() % (mapHeight - 2) + 1;
    } while (map[y][x] != 0);
    map[y][x] = foodId;
}

void Update()
{
    switch (direction)
    {
    case 0: Move(-1, 0); break;
    case 1: Move(0, 1);  break;
    case 2: Move(1, 0);  break;
    case 3: Move(0, -1); break;
    }
}

char GetElementValue(int element)
{
    if (IsSnakeHead(element))
    {
        return 'O';
    }
    if (IsSnakeElement(element))
    {
        return 'o';
    }

    switch (element)
    {
    case borderId: return '#';
    case foodId: return '*';
    }
}

void PrintCenteredText(string text)
{
    int numberOfSpacesOnLeft = (mapWidth - text.length()) / 2;
    PrintCharacterNTimes(' ', numberOfSpacesOnLeft);
    cout << text << endl;
}

void PrintCharacterNTimes(char character, int n)
{
    for (int i = 0; i < n; i++)
        cout << character;
}
