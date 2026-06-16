#include "raylib.h"
#include <ctime>
#include <iostream>
#include <stdio.h>

using std::string;

const int WINDOW_X = 480;
const int WINDOW_Y = 272;

struct GameState {
    int coins;
    string results;
    bool isOver;
};

void pullLever(GameState& yourGame, string emoji[4]){
    yourGame.results = "";
    int r1 = GetRandomValue(0, 3);
    int r2 = GetRandomValue(0, 3);
    int r3 = GetRandomValue(0, 3);

    yourGame.results = "[" + emoji[r1] + "|" + emoji[r2] + "|" + emoji[r3] + "]";
    yourGame.coins--;  // cost to pull
// all match!
    if (r1 == r2 && r2 == r3) {
        if (r1 == 5 || r1 == 6)
            yourGame.coins += 10;
        else
            yourGame.coins += 5;
            //close single match
    } else if (r1 == r2 || r2 == r3) {
        yourGame.coins += 3;
        //just the first and third one only
    } else if (r1 == r3) {
        yourGame.coins += 1;
    }

    if (yourGame.coins == 0)
        yourGame.isOver = true;
}


int main() {
    //creating variables
    GameState yourGame;
    yourGame.coins = 20;
    yourGame.results = "";
    yourGame.isOver = false;
    string emoji[] = {"Cherry", "Orange", "Grapes", "Bell"};

    //Initializing the window
    InitWindow(WINDOW_X, WINDOW_Y, "Raylib + Code::Blocks");
    SetTargetFPS(60);

    //dealing with random
    SetRandomSeed(time(NULL));
    int num = GetRandomValue(0, 3);

    //test
    pullLever(yourGame, emoji);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(yourGame.results.c_str(), 0, 0, 20, DARKGRAY);
        char str[20];
        sprintf(str, "%d", yourGame.coins);
        DrawText(str, 190, 200, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
