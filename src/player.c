//-------------------------------------------------------------------------
//  Includes
//-------------------------------------------------------------------------

#include "game.h"

//-------------------------------------------------------------------------
//  Player Functions
//-------------------------------------------------------------------------

// Player Movement

void PlayerMove(Entity *player, Level *level) {
    // Player Speed
    if (IsKeyDown(KEY_LEFT_SHIFT) && !player->blocking) {
        player->speed = 3;
    } else if (IsKeyDown(KEY_LEFT_CONTROL) || player->blocking) {
        player->speed = 1;
    } else {
        player->speed = 2;
    }

    // Player Movement
    // Moving Up
    bool movingUp = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP);
    bool borderUp = player->position.y >= (0 + level->border[0]);

    if (movingUp && borderUp) player->position.y -= player->speed;

    // Moving Left
    bool movingLeft = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
    bool borderLeft = player->position.x >= (0 + level->border[2]);

    if (movingLeft) {
        player->facingRight = false;
        if (borderLeft) player->position.x -= player->speed;
    }

    // Moving Down
    bool movingDown = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN);
    bool borderDown = player->position.y <= (1080 - level->border[1]);

    if (movingDown && borderDown) player->position.y += player->speed;

    // Moving Right
    bool movingRight = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);
    bool borderRight = player->position.x <= (1920 - level->border[3]);

    if (movingRight) {
        player->facingRight = true;
        if (borderRight) player->position.x += player->speed;
    }
}

// Player Equip

void PlayerEquip(Entity *player) {
    if (IsKeyPressed(KEY_E)) {
        player->attacking = false;
        player->blocking = false;
        player->equipped = !player->equipped;
        SetSoundPitch(g.equipSound, 0.75f);
        PlaySound(g.equipSound);
    }
}

// Player Attack

void PlayerAttack(Entity *entity) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && entity->equipped && !entity->blocking && !entity->attacking && entity->attackCooldown == 0) {
        entity->attacking = true;
        entity->attackFrames = 15;
        entity->attackCooldown = 30;
        SetSoundPitch(g.swordSound, 1.5f);
        PlaySound(g.swordSound);

        int inRange = 0;
        for (int i = 0; i < g.levels[g.currentLevelNum].entityCount; i++) {
            if (CalculateDistance(entity->position, g.entities[g.currentLevelNum][i].position) <= entity->interactRange) inRange += 1;
        }

        if (inRange > 0) {
            int oldDamage = entity->damage;
            entity->damage = ceil(entity->damage / inRange);

            for (int i = 0; i < g.levels[g.currentLevelNum].entityCount; i++) {
                if (CalculateDistance(entity->position, g.entities[g.currentLevelNum][i].position) <= entity->interactRange) DamageTarget(&g.entities[g.currentLevelNum][i], &g.player, &g.levels[g.currentLevelNum]);
            }

            entity->damage = oldDamage;
        }

    }

    if (entity->attackFrames >= 5) {
        for (int i = 0; i < g.levels[g.currentLevelNum].entityCount; i++) {
            if (CalculateDistance(entity->position, g.entities[g.currentLevelNum][i].position) <= entity->interactRange) g.entities[g.currentLevelNum][i].tint = (Color){211, 32, 32, 255};
        }
    } else {
        for (int i = 0; i < g.levels[g.currentLevelNum].entityCount; i++) {
            g.entities[g.currentLevelNum][i].tint = SPRITE_TINT;
        }
    }

    if (entity->attackFrames > 0) entity->attackFrames--; else entity->attacking = false;
    if (entity->attackCooldown > 0) entity->attackCooldown--;
}

void PlayerSprite(Entity *entity) {
    if (entity->equipped) {
        if (entity->attacking) {
            if (entity->attackFrames >= 10) entity->texture = entity->facingRight ? g.playerTextures.rightAttackSwing : g.playerTextures.leftAttackSwing;
            else entity->texture = entity->facingRight ? g.playerTextures.rightAttack : g.playerTextures.leftAttack;

        } else if (entity->blocking) {
            entity->texture = entity->facingRight ? g.playerTextures.rightBlock : g.playerTextures.leftBlock;

        } else entity->texture = entity->facingRight ? g.playerTextures.rightEquip : g.playerTextures.leftEquip;

    } else entity->texture = entity->facingRight ? g.playerTextures.right : g.playerTextures.left;
}

// Master Function

void UpdatePlayer(void) {
    PlayerMove(&g.player, g.currentLevel);
    PlayerEquip(&g.player);
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) EntityBlock(&g.player);
    if (g.player.blockFrames > 0) g.player.blockFrames--; else g.player.blocking = false;
    if (g.player.blockCooldown > 0) g.player.blockCooldown--;

    PlayerAttack(&g.player);
    PlayerSprite(&g.player);
}

// By Seth C