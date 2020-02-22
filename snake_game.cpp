#include<iostream>
#include<vector>
#include<conio.h>
using namespace std;

const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY;
vector<int> tailX(100, -1), tailY(100, -1);
int tail_len;
bool gameOver;
int score;
enum Direction {STOP=0, LEFT, RIGHT, UP, DOWN};
Direction dir;

void setup(){
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    tailX.clear();
    tailY.clear();
    tail_len = 0;
}

void draw(){
    system("cls");

    for(int i=0; i<width; i++)
        cout << "=";
    cout << endl;

    for(int j=0; j<height; j++){
        for(int i=0; i<width+1; i++){
            if(i == 0 || i == width) cout << "|";
            else if(i == x && j == y) cout << "O";
            else if(i == fruitX && j == fruitY) cout << "*";
            else{
                bool tail_print = false;
                for(int t=0; t<tail_len; t++){
                    if(i == tailX[t] && j == tailY[t]){
                        cout << "o";
                        tail_print = true;
                    }
                }
                if(!tail_print) cout << " ";
            }
        }
        cout << endl;
    }

    for(int i=0; i<width; i++)
        cout << "=";
    cout << endl;
    cout << "\nScore: " << score << endl;
}

void input(){
    if(_kbhit()){
        switch(_getch()){
            case 'H':
                dir = UP;
                break;
            case 'K':
                dir = LEFT;
                break;
            case 'P':
                dir = DOWN;
                break;
            case 'M':
                dir = RIGHT;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void logic(){
    for(int i=tail_len-1; i>0; i--){
        tailX[i] = tailX[i-1];
        tailY[i] = tailY[i-1];
    }
    tailX[0] = x;
    tailY[0] = y;
    
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

    for(int i=0; i<tail_len; i++){
        if(x == tailX[i] && y == tailY[i]) gameOver = true;
    }

    if(x == fruitX && y == fruitY){
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;

        tail_len++;
    }

    if(x >= width) x=1;
    if(x <= 0) x = width-1;
    if(y >= height) y=1;
    if(y < 0) y = height-1;
}

int Play(){
    setup();
    while(!gameOver){
        draw();
        input();
        logic();
    }
    return score;
}

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