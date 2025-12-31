
// 
// 
// Game Name : The Culebrita game (a snake game version) 
// Written by : Alejandro Marchesini 
// Date : Starting date 4/5/2023   Ending date : 4/24/2023
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //
// Instructions :                                                                                   //
// The game consists on moving the Snake in order to eat the food so the Snake can grow.           //
// However, the snake can grow too much, and that will make the game harder.                       //
// Try to not eat your own tail. If you do, you will die!                                           //
// Bonus: You can go through the Borders of the game board (You will reappear in a different place)./ 
//                                                                                                   //
// Use the Key Letters "W" to Move up, "A" to Move left, "S" to Move down,                           //
//"D" to Move left, or "Q" to Quit the game.                                                       //
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// 


#include "graphics.h"
#include <string>
#include <random>
#include <iostream>
#include <fstream>

using namespace std;


// --------- Variables to display Welcome screen ---------
const int BACKGROUND_COLOR = BROWN;
const int TEXT_COLOR = BLACK;


// --------- Main Maze Size ---------
const int MAX_SIZE = 100;
const int TAIL_LENGTH = 1000;

const int WINDOW_X = 800;
const int WINDOW_Y = 725;




// --------- Maze Locations ----------
struct MazeLocations
{
    int x;
    int y;
};

enum MazeContent { EMPTY, WALL, FOOD, SNAKE, CACTUS };

// --------- Variables for Drawing a maze ----------
int gBoxSize = 25;
int gBoxOffsetX = 15;
int gBoxOffsetY = 15;

// ----------- Random devices to create the food ---------
random_device myEngineX;
uniform_int_distribution<int> randomIntX(2, 23);

random_device myEngineY;
uniform_int_distribution<int> randomIntY(1, 36);

// Functions prototypes.
void welcomeScreen();
void drawBox(int x, int y, int color);
void playAgainDisplay();
void ControlsDisplay();
void keepTrackofScore(int);

int main()
{
    bool keepGoing = true;
    bool playAgain = true; // Keep playing the game loop.
    char keyPressed;

    // ---------- Variables for keeping track of the score ---------
    int playerScore = 0;
    char scoreKeeper[20]; // string array

    // ---------- Variables for objects ----------
    static int WALL_COLOR = YELLOW;
    static int EMPTY_COLOR = BLACK;
    static int SNAKE_COLOR = LIGHTGRAY;
    static int FOOD_COLOR = LIGHTRED;
    static int CACTUS_COLOR = GREEN;

    // ---------- Creating Variables for the Snake ---------
    MazeLocations snake = { 1, 1 };
    MazeLocations prevSnake[TAIL_LENGTH] = { 1,1 };
    MazeLocations velSnake = { 0,0 };

    // --------- Creating Varibales for the Food ---------
    MazeLocations food = { 799,799 };
    MazeLocations prevFood = { 799,799 };

    // -------- Open a Window and Display the game name  ---------
    initwindow(1000, 725, (char*)"The Culebrita Game (a version of the Snake Game)", 10, 10);
    welcomeScreen();


    // --------- Variables needed to read the Filename for the Maze ----------
    ifstream inputFile;
    string filename = "Main Maze Game.txt";
    int numColumns;
    int numRows;


    // --------- Array for the creation of the Maze.---------
    MazeContent maze1[MAX_SIZE][MAX_SIZE];




    // ---------- Main "Play Again" loop ----------

    do {

        // ---------- Reset the location of the variables again -----------
        snake = { 1, 1 };
        velSnake = { 0,0 };
        food = { 799,799 };
        prevFood = { 799,799 };
        playerScore = 0;

        // ---------- Opening and Creating the Maze ----------

        inputFile.open(filename); // Opening the File.

        if (!inputFile) // Valid the input name of the File. 
        {

            cout << " Error opening the file. " << filename << ".txt" << endl;
            exit(1);// Check if the File is opening or not.
        }

        cleardevice();

        // ---------- Displaying the Instructions of the Game ---------
        ControlsDisplay();

        // --------- Set the screen score since the begining ----------

        sprintf_s(scoreKeeper, "Score: %d", 0);

        setcolor(TEXT_COLOR);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(500, 570, &scoreKeeper[0]);


        // ----------- Read the File to Display the game. -----------

        inputFile >> numColumns >> numRows;

        // Calculate box size and offset, based on size of maze
        gBoxSize = ((WINDOW_X > WINDOW_Y ? WINDOW_X : WINDOW_Y) - 100) /
            (numRows > numColumns ? numRows : numColumns);
        gBoxOffsetX = (WINDOW_X - ((numColumns)*gBoxSize)) / 10;
        gBoxOffsetY = (WINDOW_Y - ((numRows)*gBoxSize)) / 10;

        // ---------- Read What it is inside the Maze and display ----------
        setlinestyle(SOLID_LINE, 0, 1);

        for (int y = 0; y < numRows; y++) {
            for (int x = 0; x < numColumns; x++) {
                char nextChar;
                inputFile >> nextChar;
                if (nextChar == 'X' || nextChar == 'x')
                {
                    maze1[x][y] = WALL;
                    drawBox(x, y, WALL_COLOR);
                }
                else if (nextChar == 'F' || nextChar == 'f')
                {
                    maze1[x][y] = FOOD;
                    drawBox(x, y, FOOD_COLOR);
                }
                else if (nextChar == 'c' || nextChar == 'C')
                {
                    maze1[x][y] = CACTUS;
                    drawBox(x, y, CACTUS_COLOR);
                }
                else
                {
                    // Anything else is blank
                    maze1[x][y] = EMPTY;
                    drawBox(x, y, EMPTY_COLOR);
                }
            }
        }
        inputFile.close();// Closing the file.


        // ---------- Filling up the previous Locations ---------
        for (int count = 0; count < TAIL_LENGTH; count++)
        {
            prevSnake[count] = { 1, 1 };
        }

        // ------------ Main "Keep Going" loop -------------
        int snakeLength = 3; // Lenght of The Snake
        keepGoing = true;

        while (keepGoing)
        {

            // ---------- Adding the tail for the Snake -------- 
            prevSnake[0].x = snake.x;
            prevSnake[0].y = snake.y;

            for (int count = snakeLength; count >= 1; count--)
            {
                prevSnake[count] = prevSnake[count - 1];
            }

            // ---------- Moving Snake ----------
            snake.x += velSnake.x;
            snake.y += velSnake.y;

            // ---------- Not getting over the borders of the MAze ---------
            if (snake.y == 0)
            {
                snake.y = 36;
            }
            if (snake.y == 37)
            {
                snake.y = 1;
            }
            if (snake.x == 0)
            {
                snake.x = 23;
            }
            if (snake.x == 24)
            {
                snake.x = 1;
            }

            // ---------- If the Snake touches itself, The game will end --------- 
            if (maze1[snake.x][snake.y] == SNAKE)
            {
                keepGoing = false;
            }

            // ---------- If the Snake touches a Cactus, The game will end ---------
            if (maze1[snake.x][snake.y] == CACTUS)
            {
                keepGoing = false;
            }

            // ---------- If the Snakes eats the Food, create a new one in a random Location---------- 
            if (maze1[snake.x][snake.y] == FOOD)
            {
                do
                {
                    food.x = randomIntX(myEngineX);
                    food.y = randomIntY(myEngineY);

                } while (maze1[food.x][food.y] != EMPTY);

                maze1[food.x][food.y] = FOOD;
                snakeLength += 3;
                keepTrackofScore(playerScore += 50); // The player will get 100 points every time the snakes eats one food.
            }

            // ----------- Check to see if a key has been pressed -----------
            if (kbhit()) {
                keyPressed = getch();

                // Key Q or ESC pressed
                if (keyPressed == 'q' || keyPressed == 'Q' || keyPressed == 0x1b)
                {
                    keepGoing = false;
                }
                // Moving player.

                if ((keyPressed == 's' || keyPressed == 'S') && (velSnake.y != -1))
                {
                    velSnake.x = 0;
                    velSnake.y = 1;// s or S -- down
                }
                if ((keyPressed == 'w' || keyPressed == 'W') && (velSnake.y != 1))
                {
                    velSnake.x = 0;
                    velSnake.y = -1; // w or W -- up 
                }
                if ((keyPressed == 'a' || keyPressed == 'A') && (velSnake.x != 1))
                {
                    velSnake.x = -1;
                    velSnake.y = 0; // a or A -- left 
                }
                if ((keyPressed == 'd' || keyPressed == 'D') && (velSnake.x != -1))
                {
                    velSnake.x = 1;
                    velSnake.y = 0; // d or D -- right
                }


            } // end if(kbhit)

            // --------- Creating and Drawing Food, Snake --------
            drawBox(prevSnake[snakeLength].x, prevSnake[snakeLength].y, EMPTY_COLOR);
            drawBox(snake.x, snake.y, SNAKE_COLOR);

            drawBox(prevFood.x, prevFood.y, SNAKE_COLOR);
            drawBox(food.x, food.y, FOOD_COLOR);

            // ----------- Put in the information in the Maze --------- 
            maze1[snake.x][snake.y] = SNAKE;
            maze1[prevSnake[snakeLength].x][prevSnake[snakeLength].y] = EMPTY;

            // ----------- Check to see if a mouse was clicked ------------
            if (ismouseclick(WM_LBUTTONUP))
            {
                int mouseX, mouseY;
                getmouseclick(WM_LBUTTONUP, mouseX, mouseY);
            } // end if(mouse clicked)

            delay(100); // How Fast the game will Run 
        } // end while(keepGoing)
        // Game has ended

        playAgainDisplay();// Display "Game Over" and Ask Play Again.

        // --------- Pressed "y" or "Y" to play again ---------

        keyPressed = getch();
        if (keyPressed == 'y' || keyPressed == 'Y')
        {
            welcomeScreen();
        }
        else
        {
            playAgain = false;
        }


    } while (playAgain == true); // Main "Play Again" loop

    return 0;
} // ---------- end main() ----------


// --------- Functions Declarations for the Game ---------

// ---------- Display Welcome Screen ----------
void welcomeScreen()
{
    setbkcolor(BACKGROUND_COLOR);
    cleardevice();

    setcolor(TEXT_COLOR);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(10, 100, (char*)"Press any key to begin... ");

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 5);
    outtextxy(35, 275, (char*)" 'The Culebrita Game' ");

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(240, 325, (char*)" (a version of the Snake Game) ");

    // ---------- Display Instructions --------- 
    setcolor(TEXT_COLOR);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(10, 500, (char*)" Game Instructions:");

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(10, 530, (char*)" Move the Snake and eat as much food as possible to get points.");

    outtextxy(10, 560, (char*)" The Snake will grow each time eats food (RED). ");

    outtextxy(10, 590, (char*)" However, if the snake (GRAY) eats its own tail, or a cactus (GREEN),");

    outtextxy(10, 620, (char*)" YOU WILL DIE!!");

    outtextxy(10, 650, (char*)" BONUS: Try to go through the walls, you won't die.");


    getch();
    cleardevice();
}

// ---------- Display the Play again Info ----------
void playAgainDisplay()
{

    setcolor(TEXT_COLOR);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(500, 600, (char*)"Game Over... ");

    // --------- Ask Play Again ----------
    setcolor(TEXT_COLOR);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(500, 630, (char*)"Would you like to play again?");

    setcolor(TEXT_COLOR);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(500, 660, (char*)"(Press Y/N)");

    getch(); // Double touch a key letter, just in case after the player lost touches a key word accidentally. 
}

// ------------ Display the information for the Controls of the Game ---------
void ControlsDisplay()
{
    setcolor(TEXT_COLOR);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(500, 10, (char*)"Game Controls: ");

    // Key Letter Q
    setcolor(TEXT_COLOR);
    setlinestyle(DASHED_LINE, 0, 1);
    rectangle(590, 70, 650, 130);

    setcolor(TEXT_COLOR);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 4);
    outtextxy(601, 85, (char*)"Q");

    // Key Letter W
    setcolor(TEXT_COLOR);
    setlinestyle(DASHED_LINE, 0, 1);
    rectangle(730, 70, 790, 130);

    setcolor(TEXT_COLOR);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 4);
    outtextxy(738, 85, (char*)"W");

    // Key Letter A
    setcolor(TEXT_COLOR);
    setlinestyle(DASHED_LINE, 0, 1);
    rectangle(660, 140, 720, 200);

    setcolor(TEXT_COLOR);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 4);
    outtextxy(675, 155, (char*)"A");

    // Key Letter S
    setcolor(TEXT_COLOR);
    setlinestyle(DASHED_LINE, 0, 1);
    rectangle(730, 140, 790, 200);

    setcolor(TEXT_COLOR);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 4);
    outtextxy(745, 155, (char*)"S");

    // Key Letter D
    setcolor(TEXT_COLOR);
    setlinestyle(DASHED_LINE, 0, 1);
    rectangle(800, 140, 860, 200);

    setcolor(TEXT_COLOR);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 4);
    outtextxy(815, 155, (char*)"D");

    // Chart with the Instructions
    setcolor(TEXT_COLOR);
    setlinestyle(DASHED_LINE, 0, 1);
    rectangle(500, 270, 975, 510);

    setcolor(TEXT_COLOR);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(580, 320, (char*)"W -------- Move UP.");

    outtextxy(580, 350, (char*)"A -------- Move LEFT.");

    outtextxy(580, 380, (char*)"S -------- Move DOWN.");

    outtextxy(580, 410, (char*)"D -------- Move RIGHT.");

    outtextxy(580, 440, (char*)"Q -------- QUIT the Game.");
}

// ---------- Keep the Track of the Score and Display it --------
void keepTrackofScore(int trackOfScore)
{
    char scoreKeeper[20];

    sprintf_s(scoreKeeper, "Score: %d", trackOfScore);

    setcolor(TEXT_COLOR);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(500, 570, &scoreKeeper[0]);
}

// ----------- Draw the boxes inside the Maze for Moving --------
void drawBox(int mazeX, int mazeY, int color)
{
    int screenX = mazeX * gBoxSize + gBoxOffsetX;
    int screenY = mazeY * gBoxSize + gBoxOffsetY;

    setcolor(color);
    setfillstyle(SOLID_FILL, color);

    bar(screenX, screenY, screenX + gBoxSize, screenY + gBoxSize);

    if (gBoxSize > 15) {
        setcolor(BLACK);
        rectangle(screenX, screenY, screenX + gBoxSize, screenY + gBoxSize);
    }
}













