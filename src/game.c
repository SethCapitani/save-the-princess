//-------------------------------------------------------------------------
//  Includes
//-------------------------------------------------------------------------

#include "game.h"

//-------------------------------------------------------------------------
//  Initialise Global Struct
//-------------------------------------------------------------------------

Global g = {0};

//-------------------------------------------------------------------------
//  Function Defintions
//-------------------------------------------------------------------------

void InitGame(void) {

    //-------------------------------------------------------------------------
    //  Initialise Textures & Sounds
    //-------------------------------------------------------------------------

    // PoP Logo
    g.texture = LoadTexture("src/resources/pop_logo.png");

    // Player Textures
    g.playerTextures.right = LoadTexture("resources/textures/sprites/knight_right.png");
    g.playerTextures.left = LoadTexture("resources/textures/sprites/knight_left.png");
    g.playerTextures.rightEquip = LoadTexture("resources/textures/sprites/knight_right_equip.png");
    g.playerTextures.leftEquip = LoadTexture("resources/textures/sprites/knight_left_equip.png");
    g.playerTextures.rightAttackSwing = LoadTexture("resources/textures/sprites/knight_right_attack_swing.png");
    g.playerTextures.leftAttackSwing = LoadTexture("resources/textures/sprites/knight_left_attack_swing.png");
    g.playerTextures.rightAttack = LoadTexture("resources/textures/sprites/knight_right_attack.png");
    g.playerTextures.leftAttack = LoadTexture("resources/textures/sprites/knight_left_attack.png");
    g.playerTextures.rightBlock = LoadTexture("resources/textures/sprites/knight_right_block.png");
    g.playerTextures.leftBlock = LoadTexture("resources/textures/sprites/knight_left_block.png");

    // Slime Textures
    g.entityTextures[0].right = LoadTexture("resources/textures/sprites/slime_right.png");
    g.entityTextures[0].left = LoadTexture("resources/textures/sprites/slime_left.png");

    // Skeleton Textures
    g.entityTextures[1].right = LoadTexture("resources/textures/sprites/skeleton_right.png");
    g.entityTextures[1].left = LoadTexture("resources/textures/sprites/skeleton_left.png");
    g.entityTextures[1].rightAttack = LoadTexture("resources/textures/sprites/skeleton_right_attack.png");
    g.entityTextures[1].leftAttack = LoadTexture("resources/textures/sprites/skeleton_right_attack.png");
    g.entityTextures[1].rightAttackSwing = LoadTexture("resources/textures/sprites/skeleton_right_attack_swing.png");
    g.entityTextures[1].leftAttackSwing = LoadTexture("resources/textures/sprites/skeleton_left_attack_swing.png");

    // GUI Textures
    g.legend = LoadTexture("resources/textures/legend.png");
    g.legendClosed = LoadTexture("resources/textures/legend_closed.png");

    // Sounds
    g.swordSound = LoadSound("resources/sounds/sword_swoosh.ogg");
    g.equipSound = LoadSound("resources/sounds/equip.ogg");

    SetSoundVolume(g.swordSound, 0.5f);
    SetSoundVolume(g.equipSound, 1.0f);

    // Tile Textures
    g.tileTextures[0] = LoadTexture("resources/textures/tiles/basalt.png");
    g.tileTextures[1] = LoadTexture("resources/textures/tiles/lava_middle.png");
    g.tileTextures[2] = LoadTexture("resources/textures/tiles/lava_top.png");
    g.tileTextures[3] = LoadTexture("resources/textures/tiles/lava_bottom.png");
    g.tileTextures[4] = LoadTexture("resources/textures/tiles/basalt_spawn.png");
    g.tileTextures[5] = LoadTexture("resources/textures/tiles/sky.png");
    g.tileTextures[6] = LoadTexture("resources/textures/tiles/sky_grass.png");
    g.tileTextures[7] = LoadTexture("resources/textures/tiles/grass.png");
    g.tileTextures[8] = LoadTexture("resources/textures/tiles/cloud.png");
    g.tileTextures[9] = LoadTexture("resources/textures/tiles/dungeon_floor.png");
    g.tileTextures[10] = LoadTexture("resources/textures/tiles/dungeon_wall.png");
    g.tileTextures[11] = LoadTexture("resources/textures/tiles/dungeon_floor_bottom.png");
    g.tileTextures[12] = LoadTexture("resources/textures/tiles/dungeon_acid.png");
    g.tileTextures[13] = LoadTexture("resources/textures/tiles/dungeon_acid_top.png");
    g.tileTextures[14] = LoadTexture("resources/textures/tiles/dungeon_light.png");
    g.tileTextures[15] = LoadTexture("resources/textures/tiles/courtyard_ground.png");
    g.tileTextures[16] = LoadTexture("resources/textures/tiles/courtyard_ground_bottom.png");
    g.tileTextures[17] = LoadTexture("resources/textures/tiles/courtyard_wall.png");
    g.tileTextures[18] = LoadTexture("resources/textures/tiles/courtyard_wall_light.png");
    g.tileTextures[19] = LoadTexture("resources/textures/tiles/courtyard_pit_top.png");
    g.tileTextures[20] = LoadTexture("resources/textures/tiles/courtyard_pit.png");

    //-------------------------------------------------------------------------
    //  Initialise Levels
    //-------------------------------------------------------------------------

    // Entities Spawn Locations
    Vector2 zeroEntitySpawns[MAX_ENTITIES];
    zeroEntitySpawns[0] = (Vector2){SCREEN_WIDTH/2,SCREEN_HEIGHT/2 + 150};

    Vector2 oneEntitySpawns[MAX_ENTITIES];
    oneEntitySpawns[0] = (Vector2){500,SCREEN_HEIGHT/2};
    oneEntitySpawns[1] = (Vector2){1350,SCREEN_HEIGHT/2};
    oneEntitySpawns[2] = (Vector2){900,SCREEN_HEIGHT/2-150};
    oneEntitySpawns[3] = (Vector2){900,SCREEN_HEIGHT/2+150};
    oneEntitySpawns[4] = (Vector2){1550,SCREEN_HEIGHT/2-150};
    oneEntitySpawns[5] = (Vector2){1550,SCREEN_HEIGHT/2+150};

    Vector2 twoEntitySpawns[MAX_ENTITIES];
    twoEntitySpawns[0] = (Vector2){0,0};

    Vector2 threeEntitySpawns[MAX_ENTITIES];
    threeEntitySpawns[0] = (Vector2){0,0};

    // Level 0 - Menu
    g.levels[0].tileLayout = zeroLayout;
    g.levels[0].border[0] = 500;
    g.levels[0].border[1] = 30;
    g.levels[0].border[2] = 0;
    g.levels[0].border[3] = 0;
    g.levels[0].playerSpawn = (Vector2){96, (SCREEN_HEIGHT/2)};
    g.levels[0].entityCount = 1;
    g.levels[0].inactiveEntities = 0;
    g.levels[0].entitySpawns = &zeroEntitySpawns;

    // Level 1 - The Bridge
    g.levels[1].tileLayout = oneLayout;
    g.levels[1].border[0] = 256;
    g.levels[1].border[1] = 265;
    g.levels[1].border[2] = 0;
    g.levels[1].border[3] = 0;
    g.levels[1].playerSpawn = (Vector2){96, (SCREEN_HEIGHT/2)};
    g.levels[1].entityCount = 6;
    g.levels[1].inactiveEntities = 0;
    g.levels[1].entitySpawns = &oneEntitySpawns;

    // Level 2 - The Dungeon
    g.levels[2].tileLayout = twoLayout;
    g.levels[2].border[0] = 192;
    g.levels[2].border[1] = 395;
    g.levels[2].border[2] = 0;
    g.levels[2].border[3] = 0;
    g.levels[2].playerSpawn = (Vector2){96, (SCREEN_HEIGHT/2)};
    g.levels[2].entityCount = 0;
    g.levels[2].inactiveEntities = 0;
    g.levels[2].entitySpawns = &twoEntitySpawns;

    // Level 3 - The Courtyard
    g.levels[3].tileLayout = threeLayout;
    g.levels[3].border[0] = 192;
    g.levels[3].border[1] = 395;
    g.levels[3].border[2] = 0;
    g.levels[3].border[3] = 0;
    g.levels[3].playerSpawn = (Vector2){96, (SCREEN_HEIGHT/2)};
    g.levels[3].entityCount = 0;
    g.levels[3].inactiveEntities = 0;
    g.levels[3].entitySpawns = &threeEntitySpawns;

    // Level 4 - The Spire


    g.currentLevel = &g.levels[g.currentLevelNum];

    //-------------------------------------------------------------------------
    //  Initialise Player
    //-------------------------------------------------------------------------

    g.player.position = g.levels[0].playerSpawn;
    g.player.type = 0;
    g.player.facingRight = true;
    g.player.texture = g.playerTextures.right;
    g.player.scale = SPRITE_SCALE;
    g.player.active = true;
    g.player.visionRange = 120.0f;
    g.player.interactRange = 60.0f;
    g.player.speed = 2;
    g.player.maxHealth = 100;
    g.player.health = g.player.maxHealth;
    g.player.equipped = false;
    g.player.damage = 15;
    g.player.attackCooldown = 0;
    g.player.attacking = false;
    g.player.attackFrames = 0;
    g.player.blockCooldown = 0;
    g.player.blocking = false;
    g.player.blockFrames = 0;
    g.player.tint = SPRITE_TINT;

    //-------------------------------------------------------------------------
    //  Initialise Entities
    //-------------------------------------------------------------------------

    // Initialise Slime(s)
    for (int i = 0; i < g.levels[0].entityCount; i++) {
        g.entities[0][i].position = zeroEntitySpawns[i];
        g.entities[0][i].type = 1;
        g.entities[0][i].facingRight = false;
        g.entities[0][i].texture = g.entityTextures[0].left;
        g.entities[0][i].scale = SPRITE_SCALE;
        g.entities[0][i].active = true;
        g.entities[0][i].visionRange = 100.0f;
        g.entities[0][i].interactRange = 40.0f;
        g.entities[0][i].speed = 1;
        g.entities[0][i].maxHealth = 20;
        g.entities[0][i].health = g.entities[0][i].maxHealth;
        g.entities[0][i].equipped = true;
        g.entities[0][i].damage = 5;
        g.entities[0][i].canAttack = true;
        g.entities[0][i].attackCooldown = 30;
        g.entities[0][i].attacking = false;
        g.entities[0][i].attackFrames = 10;
        g.entities[0][i].canBlock = false;
        g.entities[0][i].tint = SPRITE_TINT;
    }

    // Initialise Skeleton(s)
    for (int i = 0; i < g.levels[1].entityCount; i++) {
        g.entities[1][i].position = oneEntitySpawns[i];
        g.entities[1][i].type = 1;
        g.entities[1][i].facingRight = false;
        g.entities[1][i].texture = g.entityTextures[1].left;
        g.entities[1][i].scale = SPRITE_SCALE;
        g.entities[1][i].active = true;
        g.entities[1][i].visionRange = 192.0f;
        g.entities[1][i].interactRange = 60.0f;
        g.entities[1][i].speed = 2;
        g.entities[1][i].maxHealth = 60;
        g.entities[1][i].health = g.entities[1][i].maxHealth;
        g.entities[1][i].equipped = true;
        g.entities[1][i].damage = 5;
        g.entities[1][i].canAttack = true;
        g.entities[1][i].attackCooldown = 30;
        g.entities[1][i].attacking = false;
        g.entities[1][i].attackFrames = 0;
        g.entities[1][i].canBlock = false;
        g.entities[1][i].tint = SPRITE_TINT;
    }
}

void UpdateGame(void) {

    //-------------------------------------------------------------------------
    //  Update Level
    //-------------------------------------------------------------------------

    if (IsKeyPressed(KEY_F) && g.levels[g.currentLevelNum].entityCount == g.levels[g.currentLevelNum].inactiveEntities) { // runs every frame until level num switched
        g.transitionFrames = 510;
        g.transition = 0;
    }

    if (g.transitionFrames == 220) {
        g.currentLevelNum++;
        g.currentLevel = &g.levels[g.currentLevelNum];

        g.player.position = g.levels[g.currentLevelNum].playerSpawn;
    }

    //-------------------------------------------------------------------------
    //  Update Player
    //-------------------------------------------------------------------------

    UpdatePlayer();

    //-------------------------------------------------------------------------
    //  Update Entities
    //-------------------------------------------------------------------------

    UpdateEntities();

    //-------------------------------------------------------------------------
    //  Update GUI
    //-------------------------------------------------------------------------

    UpdateGui();

}

void DrawGame(void) {

    BeginDrawing();
    ClearBackground(BLACK);

    // Draw Map Tiles
    for (int r = 0; r < 17; r++) {
        for (int c = 0; c < 30; c++) {
            Vector2 position = { c * 64, r * 64 };
            Texture2D texture = g.tileTextures[g.levels[g.currentLevelNum].tileLayout[r][c] - 1];
            DrawTextureEx(texture, position, 0.0f, SPRITE_SCALE, SPRITE_TINT);
        }
    }

    // Draw Player
    DrawSprite(&g.player, g.debug);

    // Draw Entities
    for (int i = 0; i < g.levels[g.currentLevelNum].entityCount; i++) {
        DrawSprite(&g.entities[g.currentLevelNum][i], g.debug);
    }

    // Draw GUI

    if (g.displayLegend) DrawTextureEx(g.legend, (Vector2){10, 10}, 0.0f, SPRITE_SCALE, SPRITE_TINT); else DrawTextureEx(g.legendClosed, (Vector2){10, 10}, 0.0f, SPRITE_SCALE, SPRITE_TINT);

    if (g.transitionFrames > 0) {
        Transition(&g.transitionFrames, &g.transition);
    }

    EndDrawing();

}

void RunFrame(void) {
    UpdateGame();
    DrawGame();
}

void UnloadGame(void) {

    // Unload PoP Texture
    UnloadTexture(g.texture);

    // Unload Player Textures
    UnloadTexture(g.playerTextures.right);
    UnloadTexture(g.playerTextures.left);
    UnloadTexture(g.playerTextures.rightEquip);
    UnloadTexture(g.playerTextures.leftEquip);
    UnloadTexture(g.playerTextures.rightAttackSwing);
    UnloadTexture(g.playerTextures.leftAttackSwing);
    UnloadTexture(g.playerTextures.rightAttack);
    UnloadTexture(g.playerTextures.leftAttack);
    UnloadTexture(g.playerTextures.rightBlock);
    UnloadTexture(g.playerTextures.leftBlock);

    // Unload Entity Textures
    for (int i = 0; i < MAX_LEVELS; i++) {
        if (g.entityTextures[i].right.id != 0)               UnloadTexture(g.entityTextures[i].right);
        if (g.entityTextures[i].left.id != 0)                UnloadTexture(g.entityTextures[i].left);
        if (g.entityTextures[i].rightAttack.id != 0)         UnloadTexture(g.entityTextures[i].rightAttack);
        if (g.entityTextures[i].leftAttack.id != 0)          UnloadTexture(g.entityTextures[i].leftAttack);
        if (g.entityTextures[i].rightAttackSwing.id != 0)    UnloadTexture(g.entityTextures[i].rightAttackSwing);
        if (g.entityTextures[i].leftAttackSwing.id != 0)     UnloadTexture(g.entityTextures[i].leftAttackSwing);
        if (g.entityTextures[i].rightBlock.id != 0)          UnloadTexture(g.entityTextures[i].rightBlock);
        if (g.entityTextures[i].leftBlock.id != 0)           UnloadTexture(g.entityTextures[i].leftBlock);
    }

    // Unload GUI Textures
    UnloadTexture(g.legend);
    UnloadTexture(g.legendClosed);

    // Unload Tile Textures
    for (int i = 0; i < MAX_TEXTURES; i++) {
        UnloadTexture(g.tileTextures[i]);
    }

    // Unload Sounds
    UnloadSound(g.swordSound);
    UnloadSound(g.equipSound);

}

// By Seth C