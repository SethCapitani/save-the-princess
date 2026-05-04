//=========================================================================
//
//  Name - Save The Princess
//
//  Game developed by Seth Capitani
//
//  This game is made in C and uses the raylib library.
//
//=========================================================================

#include "game.h"

//-------------------------------------------------------------------------
//  Main
//-------------------------------------------------------------------------

int main(void) {
    // Initialise Window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Save The Princess");
    InitAudioDevice();

    // Initiaslise Game
    InitGame();
    SetTargetFPS(60);

    // Game Loop
    while (!WindowShouldClose()) {
        RunFrame();
    }

    // Unload Game
    UnloadGame();
    CloseWindow();

    return 0;

}

// By Seth C