#include <iostream>
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <cstdint>
#include <ctime>

const std::string_view RESET = "\033[0m";
const std::string_view BOW = "\033[30;47m";
const std::string_view WOB = "\033[37;40m";

constexpr std::uint8_t WIDTH = 60;
constexpr std::uint8_t HEIGHT = 20;

char generate()
{
    const char chars[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890";
    return chars[std::rand() % (sizeof(chars) - 1)];
}

void init(std::vector<std::vector<char>>& maze)
{
    for ( std::uint8_t i = 0; i < HEIGHT; ++i )
    {
        for ( std::uint8_t j = 0; j < WIDTH; ++j )
        {
            maze[i][j] = generate();
        }
    }
}

void display(const std::vector<std::vector<char>>& maze, std::uint8_t X, std::uint8_t Y)
{
    std::system("cls");
    for ( std::uint8_t i = 0; i < HEIGHT; ++i )
    {
        for ( std::uint8_t j = 0; j < WIDTH; ++j )
        {
            if ( i == Y && j == X )
            {
                std::cout << BOW << maze[i][j] << RESET; // selected
            }
            else
            {
                std::cout << WOB << maze[i][j] << RESET; // normal
            }
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::srand(static_cast<std::uint32_t>(std::time(NULL)));

    std::vector<std::vector<char>> maze(HEIGHT, std::vector<char>(WIDTH));
    init(maze);

    std::uint8_t X, Y = 0;
    char prev = maze[Y][X];

    while ( 1 )
    {
        display(maze, X, Y);

        int key = _getch();
        if ( key == 27 ) // esc
        {
            maze[Y][X] = prev;
            prev = maze[Y][X];
        }
        else if ( key == 224) // arrow keys
        {
            key = _getch();
            switch ( key )
            {
                case 72: // up
                    if ( Y > 0 )
                    {
                        prev = maze[Y][X];
                        --Y;
                        maze[Y][X] = generate();
                    }
                    break;
                case 80: // down
                    if ( Y < HEIGHT - 1 )
                    {
                        prev = maze[Y][X];
                        ++Y;
                        maze[Y][X] = generate();
                    }
                    break;
                case 75: // left
                    if ( X > 0 )
                    {
                        prev = maze[Y][X];
                        --X;
                        maze[Y][X] = generate();
                    }
                    break;
                case 77: // right
                    if ( X < WIDTH - 1 )
                    {
                        prev = maze[Y][X];
                        ++X;
                        maze[Y][X] = generate();
                    }
                    break;
            }
        }
        else // wasd
        {
            switch ( key )
            {
                case 'w':
                case 'W':
                    if ( Y > 0 )
                    {
                        prev = maze[Y][X];
                        --Y;
                        maze[Y][X] = generate();
                    }
                    break;
                case 's':
                case 'S':
                    if ( Y < HEIGHT - 1 )
                    {
                        prev = maze[Y][X];
                        ++Y;
                        maze[Y][X] = generate();
                    }
                    break;
                case 'a':
                case 'A':
                    if ( X > 0 )
                    {
                        prev = maze[Y][X];
                        --X;
                        maze[Y][X] = generate();
                    }
                    break;
                case 'd':
                case 'D':
                    if ( X < WIDTH - 1 )
                    {
                        prev = maze[Y][X];
                        ++X;
                        maze[Y][X] = generate();
                    }
                    break;
            }
        }
    }

    return 0;
}
