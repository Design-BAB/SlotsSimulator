//Author: Design-BAB
//Date: 6/16/2026
//Description: Slot game

#include "raylib.h"
#include <ctime>
#include <iostream>
#include <stdio.h>

using std::string;

const int WINDOW_X = 480;
const int WINDOW_Y = 272;


class GameState {
    public:
        int coins;
        int results[3];
        string message;
        int whichRoll;
        bool selectingNow;
        bool isOver;
        int frames;

    GameState(){
        this->coins = 25;
        this->results[0] = 0;
        this->results[1] = 0;
        this->results[2] = 0;
        this->message = "Welcome to the game! Press X to roll!";
        this->whichRoll = 0;
        this-> selectingNow = false;
        this->isOver = false;
        this->frames = 0;
    }
};


void pullLever(GameState& yourGame){
    yourGame.message = "Let's roll! Press x to pull the lever.";
    if (yourGame.selectingNow == false){
        yourGame.selectingNow = true;
    } else if (yourGame.whichRoll == 2 && yourGame.selectingNow == true) {
        yourGame.coins--;  // cost to pull
        // all match!
        if (yourGame.results[0] == yourGame.results[1] && yourGame.results[1] == yourGame.results[2]) {
            if (yourGame.results[0] == 5 || yourGame.results[0] == 6)
                yourGame.coins += 10;
            else{
                yourGame.message = "You got all of them to match! Won 5 coins!";
                yourGame.coins += 5;
                //close single match
            }
        } else if (yourGame.results[0] == yourGame.results[1] || yourGame.results[1] == yourGame.results[2]) {
            yourGame.coins += 3;
            yourGame.message = "You have one match! You won 3 coins!";
            //just the first and third one only
        } else if (yourGame.results[0] == yourGame.results[2]) {
            yourGame.coins += 1;
            yourGame.message = "So close... coin has been returned.";
        }
        if (yourGame.coins == 0) {
            yourGame.isOver = true;
        }
        yourGame.selectingNow = false;
        yourGame.whichRoll = 0;
    } else if (yourGame.whichRoll < 3 && yourGame.selectingNow == true) {
        yourGame.selectingNow = false;
        if (yourGame.whichRoll < 3){
        yourGame.whichRoll++;
        }
    }
}


void getInput(GameState& yourGame) {
    if (IsKeyPressed(KEY_X)) {
        pullLever(yourGame);
    }
}

void update(GameState& yourGame) {
    yourGame.frames++;
    if (yourGame.selectingNow && yourGame.frames % 7 == 0) {
        if (yourGame.results[yourGame.whichRoll] < 3){
            yourGame.results[yourGame.whichRoll]++;
        } else {
        yourGame.results[yourGame.whichRoll] = 0;
        }
    }
}

void draw(GameState& yourGame, Texture2D emojis[4]){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(emojis[yourGame.results[0]], WINDOW_X*.20 - emojis[0].width/2, WINDOW_Y/2 - emojis[0].height/2, WHITE);
    DrawTexture(emojis[yourGame.results[1]], WINDOW_X/2 - emojis[0].width/2, WINDOW_Y/2 - emojis[0].height/2, WHITE);
    DrawTexture(emojis[yourGame.results[2]], WINDOW_X*.80 - emojis[0].width/2, WINDOW_Y/2 - emojis[0].height/2, WHITE);
    DrawText(yourGame.message.c_str(), 25, 25, 20, DARKGRAY);
    //this is to convert from int to C-style string
    char str[16];
    sprintf(str, "%d", yourGame.coins);
    DrawText(str, WINDOW_X-25, WINDOW_Y-25, 20, DARKGRAY);
    EndDrawing();
}


int main() {
    //creating variables
    GameState yourGame;

    //Initializing the window
    InitWindow(WINDOW_X, WINDOW_Y, "Slots Game");
    SetTargetFPS(60);

    //loading slot symbols
    //Texture2D texture = LoadTexture("assets/Cherries.bmp");
    Texture2D emojis[4];
    emojis[0] = LoadTexture("assets/Cherries.bmp");
    emojis[1] = LoadTexture("assets/Orange.bmp");
    emojis[2] = LoadTexture("assets/Grapes.bmp");
    emojis[3] = LoadTexture("assets/Bell.bmp");

    //dealing with random
    SetRandomSeed(time(NULL));

    while (!WindowShouldClose()) {
        if (yourGame.isOver == false){
            getInput(yourGame);
            update(yourGame);
        }
        draw(yourGame, emojis);
    }
    //A nessesary De-initialize step
    for (auto symbol : emojis) {
    UnloadTexture(symbol);
    }
    CloseWindow();
    return 0;
}
