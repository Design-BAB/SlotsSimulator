//Author: Design-BAB
//Date: 6/18/2026
//Description: Slot game simulator

#include "raylib.h"
#include <ctime>
#include <iostream>
#include <stdio.h>

using std::string;

const int WINDOW_X = 480;
const int WINDOW_Y = 272;


class GameState {
    public:
        string message;
        int coins;
        int results[3];
        int stoppedReels;
        int frames;
        int flashingCount;
        int rollSpeed;
        bool reelSpinning[3];
        bool roundActive;
        bool finalResult;
        bool drawResults;
        bool justStarted;
        bool isOver;

    GameState(){
        this->message = "Welcome to the game! Press X to roll!";
        this->coins = 25;
        this->results[0] = 0;
        this->results[1] = 0;
        this->results[2] = 0;
        this->stoppedReels = 0;
        this->frames = 0;
        // flashingCount starts at 1 to avoid triggering % 7 == 0 on the first frame
        this->flashingCount = 1;
        //this is a variable because later in the game, it should get harder to roll
        this->rollSpeed = 9;
        this->reelSpinning[0] = false;
        this->reelSpinning[1] = false;
        this->reelSpinning[2] = false;
        this->roundActive = false;
        //for the flashing animation
        this->finalResult = false;
        this->drawResults = true;
        //for the welcome mssage
        this->justStarted = true;
        this->isOver = false;
    }
};


void finalizeRound(GameState& yourGame) {
    // all match!
    if (yourGame.results[0] == yourGame.results[1] && yourGame.results[1] == yourGame.results[2]) {
        if (yourGame.results[0] == 5 || yourGame.results[0] == 6)
            yourGame.coins += 10;
        else{
            yourGame.message = "You got all of them to match! Won 5 coins!";
            yourGame.coins += 5;
        }
    //result for a 2 symbols next to eachother to be the same.
    } else if (yourGame.results[0] == yourGame.results[1] || yourGame.results[1] == yourGame.results[2]) {
        yourGame.coins += 3;
        yourGame.message = "You have one match! You won 3 coins!";
    } else if (yourGame.results[0] == yourGame.results[2]) {
        yourGame.coins += 1;
        yourGame.message = "So close... coin has been returned.";
    } else {
        yourGame.message = "No match this round. Press X to roll again.";
    }

    if (yourGame.coins == 0) {
        yourGame.isOver = true;
    }

    yourGame.roundActive = false;
    yourGame.finalResult = true;
    yourGame.drawResults = true;
}

void startRound(GameState& yourGame){
    yourGame.coins--;  // cost to pull
    yourGame.message = "Reels spinning! Press O to stop each reel.";
    yourGame.roundActive = true;
    yourGame.reelSpinning[0] = true;
    yourGame.reelSpinning[1] = true;
    yourGame.reelSpinning[2] = true;
    yourGame.stoppedReels = 0;
    yourGame.finalResult = false;
}

void stopNextReel(GameState& yourGame) {
    //saftey protection
    if (!yourGame.roundActive || yourGame.stoppedReels >= 3) {
        return;
    }
    yourGame.reelSpinning[yourGame.stoppedReels] = false;
    yourGame.stoppedReels++;

    if (yourGame.stoppedReels < 3) {
        yourGame.message = "Press O to stop the next reel.";
    } else {
        finalizeRound(yourGame);
    }
}

void getInput(GameState& yourGame) {
    //pulling leaver
    if (IsKeyPressed(KEY_X) && !yourGame.roundActive) {
        startRound(yourGame);
    }
    //pressing the button for each roll
    if (IsKeyPressed(KEY_O) && yourGame.roundActive) {
        stopNextReel(yourGame);
    }

}

void update(GameState& yourGame) {
    yourGame.frames++;
    //before we start the round
    if (!yourGame.roundActive && !yourGame.finalResult && yourGame.frames > 36000){
        yourGame.message = "Press x to pull the lever to start the round.";
    }
    //when we are rolling
    if (yourGame.roundActive){
    if (yourGame.frames % yourGame.rollSpeed == 0 && yourGame.reelSpinning[1] == true) {
        for (int i = 0; i < 3; i++) {
            if (yourGame.reelSpinning[i] == false) {
                continue;
            }
            if (yourGame.results[i] < 3){
                yourGame.results[i]++;
            } else {
                yourGame.results[i] = 0;
            }
        }
        //gotta spin faster for that last roll.
    } else if (yourGame.frames % 7 == 0 && yourGame.reelSpinning[1] == false) {
        if (yourGame.results[2] < 3){
            yourGame.results[2]++;
        } else {
            yourGame.results[2] = 0;
        }
    }
    }
    //after the results are shown, we do a flashing animation
    if (yourGame.finalResult){
        if (yourGame.finalResult && yourGame.flashingCount % 7 == 0) {
            if (yourGame.drawResults == true) {
                yourGame.drawResults = false;
            } else {
                yourGame.drawResults = true;
            }
            if (yourGame.flashingCount % 28 == 0) {
                yourGame.finalResult = false;
                yourGame.drawResults = true;
                yourGame.flashingCount = 0;
            }
        }
        yourGame.flashingCount++;
        //since we are in the final results, we will also check to see if we can
        //increase difficulty
        if (yourGame.coins > 63) {
            yourGame.rollSpeed = 4;
        }
    }

}

void draw(GameState& yourGame, Texture2D emojis[4], Texture2D coinImg){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText(yourGame.message.c_str(), 25, 25, 20, DARKGRAY);
    if (yourGame.drawResults){
        DrawTexture(emojis[yourGame.results[0]], WINDOW_X*.20 - emojis[0].width/2, WINDOW_Y/2 - emojis[0].height/2, WHITE);
        DrawTexture(emojis[yourGame.results[1]], WINDOW_X/2 - emojis[0].width/2, WINDOW_Y/2 - emojis[0].height/2, WHITE);
        DrawTexture(emojis[yourGame.results[2]], WINDOW_X*.80 - emojis[0].width/2, WINDOW_Y/2 - emojis[0].height/2, WHITE);
    }
    DrawTexture(coinImg, WINDOW_X-50, WINDOW_Y-30, WHITE);
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

    auto coinImg = LoadTexture("assets/coin.png");

    //dealing with random
    SetRandomSeed(time(NULL));

    while (!WindowShouldClose()) {
        if (yourGame.isOver == false){
            getInput(yourGame);
            update(yourGame);
        }
        draw(yourGame, emojis, coinImg);
    }
    //A nessesary De-initialize step
    for (auto symbol : emojis) {
    UnloadTexture(symbol);
    }
    UnloadTexture(coinImg);
    CloseWindow();
    return 0;
}
