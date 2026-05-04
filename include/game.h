#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <math.h>

//-------------------------------------------------------------------------
//  Defines
//-------------------------------------------------------------------------

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define SPRITE_SCALE 4.0f
#define SPRITE_TINT (Color){255, 255, 255, 255}

#define PLAYER_SPEED 2
#define PLAYER_DAMAGE 15

#define SKELETON_SPEED 2
#define SKELETON_DAMAGE 10

#define MAX_LEVELS 5
#define MAX_ENTITIES 25
#define MAX_TEXTURES 50

//-------------------------------------------------------------------------
//  Structs
//-------------------------------------------------------------------------

typedef struct {
    Vector2 position;
    int type;
    bool facingRight;
    Texture2D texture;
    float scale;
    bool active;
    float visionRange;
    float interactRange;
    int speed;
    int maxHealth;
    int health;
    bool equipped;
    int damage;
    bool canAttack;
    int attackCooldown;
    bool attacking;
    int attackFrames;
    bool canBlock;
    int blockCooldown;
    bool blocking;
    int blockFrames;
    Color tint;
} Entity;

typedef struct {
    const int (*tileLayout)[30];
    int border[4];
    Vector2 playerSpawn;
    int entityCount;
    int inactiveEntities;
    Vector2 (*entitySpawns)[MAX_ENTITIES];
} Level;

typedef struct {
    Texture2D right;
    Texture2D left;
    Texture2D rightEquip;
    Texture2D leftEquip;
    Texture2D rightAttack;
    Texture2D leftAttack;
    Texture2D rightAttackSwing;
    Texture2D leftAttackSwing;
    Texture2D rightBlock;
    Texture2D leftBlock;
} PlayerTextures;

typedef struct {
    Texture2D right;
    Texture2D left;
    Texture2D rightAttack;
    Texture2D leftAttack;
    Texture2D rightAttackSwing;
    Texture2D leftAttackSwing;
    Texture2D rightBlock;
    Texture2D leftBlock;
} EntityTextures;

typedef struct {
    // Game State
    bool victory;
    bool paused;

    // Level
    int currentLevelNum;
    Level *currentLevel;
    Level levels[MAX_LEVELS];

    // Player
    Entity player;
    PlayerTextures playerTextures;

    // Entities
    Entity entities[MAX_LEVELS][MAX_ENTITIES];
    EntityTextures entityTextures[MAX_LEVELS];

    // GUI
    bool displayLegend;
    bool debug;
    int transition;
    int transitionFrames;

    // Textures
    Texture2D texture;
    Texture2D legend;
    Texture2D legendClosed;
    Texture2D tileTextures[MAX_TEXTURES];

    // Sounds
    Sound swordSound;
    Sound equipSound;

} Global;

//-------------------------------------------------------------------------
//  Global Variables Struct
//-------------------------------------------------------------------------

extern Global g;

//-------------------------------------------------------------------------
//  Function Declarations
//-------------------------------------------------------------------------

void InitGame(void);
void UpdateGame(void);
void DrawGame(void);
void RunFrame(void);
void UnloadGame(void);

#include "player.h"
#include "entity.h"
#include "layouts.h"
#include "utils.h"

#endif