#include<iostream>
#include<vector>
#include<conio.h>
using namespace std;

const int width = 40;  //width and height of window
const int height = 20;
int x, y, fruitX, fruitY; //coordinates of snake head(x,y) and fruit(fruitX,fruitY)
vector<int> tailX(100, -1), tailY(100, -1); //array of coordinates of snake tail
int tail_len; //length of the tail
bool gameOver;
int score;
enum Direction {STOP=0, LEFT, RIGHT, UP, DOWN};
Direction dir;

//Initialize window and coordinates with setup() function
void setup(){
    gameOver = false;
    dir = STOP;
    x = width / 2;    //snake head in middle of the window when start
    y = height / 2;
    fruitX = rand() % width;  //fruit is placed at random coordinate in window
    fruitY = rand() % height;
    score = 0;
    tailX.clear();
    tailY.clear();
    tail_len = 0;
}

//draw the updated window after every move
void draw(){
    system("cls"); //clear previous window

    //draw the wall
    for(int i=0; i<width; i++)
        cout << "=";
    cout << endl;

    for(int j=0; j<height; j++){
        for(int i=0; i<width+1; i++){
            if(i == 0 || i == width) cout << "|";
            else if(i == x && j == y) cout << "O";    //draw the snake head
            else if(i == fruitX && j == fruitY) cout << "*";  //draw the fruit
            else{
                bool tail_print = false;
                //draw the tail coordinate
                for(int t=0; t<tail_len; t++){
                    if(i == tailX[t] && j == tailY[t]){
                        cout << "o";
                        tail_print = true;
                    }
                }
                if(!tail_print) cout << " "; //if nothing is drawn at (i,j) coord, then put blank space
            }
        }
        cout << endl;
    }
    
    //wall
    for(int i=0; i<width; i++)
        cout << "=";
    cout << endl;
    cout << "\nScore: " << score << endl; //print score below the game window
}

//take keyboard input to move
void input(){
    if(_kbhit()){    //if key is hit
        switch(_getch()){   //get charecter of the key
            case 'H':     //UP arrow
                dir = UP;
                break;
            case 'K':     //LEFT arrow
                dir = LEFT;
                break;
            case 'P':     //DOWN arrow
                dir = DOWN;
                break;
            case 'M':     //RIGHT arrow
                dir = RIGHT;
                break;
            case 'x':     //x key (to terminate game)
                gameOver = true;
                break;
        }
    }
}

//update head, tail and fruit coordinated according to move OR gameover if head hits tail
void logic(){
    //update tail
    for(int i=tail_len-1; i>0; i--){
        tailX[i] = tailX[i-1];
        tailY[i] = tailY[i-1];
    }
    tailX[0] = x;
    tailY[0] = y;
    
    //update head
    switch(dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    
    //Gameover if heaf hits tail
    for(int i=0; i<tail_len; i++){
        if(x == tailX[i] && y == tailY[i]) gameOver = true;
    }
    
    //place new fruit if head gets to the fruit and increase tail-length
    if(x == fruitX && y == fruitY){
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;

        tail_len++;
    }
    
    //if head goes thriugh one wall then pass it through apposite wall
    if(x >= width) x=1;
    if(x <= 0) x = width-1;
    if(y >= height) y=1;
    if(y < 0) y = height-1;
}

//function runs every time player wants to play
int Play(){
    setup();
    while(!gameOver){
        draw();
        input();
        logic();
    }
    return score;
}

//Driver code
int main(){
    int high_score = 0;

    while(1){
        high_score = max(high_score, Play());
        cout << "Highest: " << high_score << "\n\n";

        char ch;
        cout << "Play again? [y/n]: ";
        cin >> ch;

        if(ch == 'n') break;
    }
    return 0;
}
