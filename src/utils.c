//-------------------------------------------------------------------------
//  Includes
//-------------------------------------------------------------------------

#include "game.h"

//-------------------------------------------------------------------------
//  Utility Functions
//-------------------------------------------------------------------------

// Calculates the distance between an origin and the target

double CalculateDistance(Vector2 target, Vector2 origin) {
    float dx = origin.x - target.x;
    float dy = origin.y - target.y;

    return sqrt(dx * dx + dy * dy);
}

// Calculates a new position for an origin moving towards the target

Vector2 CalculateNewPosition(Vector2 target, Entity *origin) {
    float dx = origin->position.x - target.x;
    float dy = origin->position.y - target.y;

    float distance = sqrt(dx * dx + dy * dy);

    if (distance <= origin->visionRange && origin->interactRange <= distance) {
        float new_x = origin->position.x - (dx / distance) * origin->speed;
        float new_y = origin->position.y - (dy / distance) * origin->speed;
        return (Vector2){new_x, new_y};
    }

    return origin->position;
}

// Window Transition

void Transition(int *transitionFrames, int *transition) {
        if (*transitionFrames >= 220 && *transitionFrames <= 290) {
            *transition = 255;
            DrawRectangle(0, 0, 1920, 1080, (Color){0, 0, 0, *transition});
        } else if (*transitionFrames > 290) {
            *transition += 5;
            DrawRectangle(0, 0, 1920, 1080, (Color){0, 0, 0, *transition});
        } else {
            *transition -= 5;
            DrawRectangle(0, 0, 1920, 1080, (Color){0, 0, 0, *transition});
        }
        *transitionFrames -= 5;
}

// Gui

void UpdateGui(void) {
    if (IsKeyPressed(KEY_SLASH)) g.debug = !g.debug;
    if (IsKeyPressed(KEY_L)) g.displayLegend = !g.displayLegend;
}

// By Seth C

