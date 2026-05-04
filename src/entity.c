//-------------------------------------------------------------------------
//  Includes
//-------------------------------------------------------------------------

#include "game.h"

//-------------------------------------------------------------------------
//  Entity Functions
//-------------------------------------------------------------------------

// Draws entity sprites

void DrawSprite(Entity *sprite, bool debug) {
    float ratio = (float)sprite->health / (float)sprite->maxHealth;
    int healthWidth = (int)(ratio * 100);

    DrawTextureEx(sprite->texture, (Vector2){sprite->position.x - 64, sprite->position.y - 64}, 0.0f, sprite->scale, sprite->tint);
    DrawRectangle((sprite->position.x - 50), (sprite->position.y - 64), 100, 12, (Color){211, 32, 32, 255});
    DrawRectangle((sprite->position.x - 50), (sprite->position.y - 64), healthWidth, 12, (Color){49, 212, 32, 255});
    DrawRectangleLinesEx((Rectangle){(sprite->position.x - 54), (sprite->position.y - 68), 108, 20}, 4.0f, (Color){34, 32, 52, 255});

    // Debugging

    if (debug) {
        DrawRectangleLines((sprite->position.x - 64), (sprite->position.y - 64), 128, 128, (Color){000, 000, 255, 255});    // Sprite Outline
        DrawCircleLines(sprite->position.x, sprite->position.y, sprite->visionRange, (Color){000, 255, 000, 255});          // Vision Range
        DrawCircleLines(sprite->position.x, sprite->position.y, sprite->interactRange, (Color){255, 000, 000, 255});        // Attack Range
    }
}

// Controls damage

void DamageTarget(Entity *target, Entity *source, Level *counter) {
    if (target->blocking == false) target->health -= source->damage;

    if (target->health <= 0) {
        target->health = 0;
        target->position = (Vector2){-50,-50};
        target->active = false;

        if (target->type == 1) counter->inactiveEntities++;
    }
}

void EntityBlock(Entity *entity) {
    if (entity->equipped && !entity->attacking && !entity->blocking && entity->blockCooldown == 0) {
        entity->blocking = true;
        entity->blockFrames = 150;
        entity->blockCooldown = 450;
        SetSoundPitch(g.swordSound, 0.25f);
        PlaySound(g.swordSound); 

        entity->health += 15;
        if (entity->health > entity->maxHealth) entity->health = entity->maxHealth;
    }
}

void EntityAttack(Entity *entity) {
    if (CalculateDistance(entity->position, g.player.position) <= entity->interactRange && entity->equipped && !entity->blocking && !entity->attacking && entity->attackCooldown == 0) {
        entity->attacking = true;
        entity->attackFrames = 15;
        entity->attackCooldown = 30;
        SetSoundPitch(g.swordSound, 1.5f);
        PlaySound(g.swordSound);
    }

    if (entity->attackFrames == 15) {
        if (CalculateDistance(entity->position, g.player.position) <= entity->interactRange) {
            DamageTarget(&g.player, entity, &g.levels[g.currentLevelNum]);
        }
    }

    if (entity->attackFrames >= 5) {
        g.player.tint = (Color){211, 32, 32, 255};
    } else {
        g.player.tint = SPRITE_TINT;
    }

    if (entity->attackFrames > 0) entity->attackFrames--; else entity->attacking = false;
    if (entity->attackCooldown > 0) entity->attackCooldown--;
}

void EntitySprite(Entity *entity) {
    if (CalculateDistance(g.player.position, entity->position) <= entity->visionRange) {
        entity->facingRight = g.player.position.x > entity->position.x;
    }

    if (entity->attacking && g.entityTextures[g.currentLevelNum].rightAttack.id != 0) {
        if (entity->attackFrames >= 10 && g.entityTextures[g.currentLevelNum].rightAttackSwing.id != 0) {
            entity->texture = entity->facingRight ? g.entityTextures[g.currentLevelNum].rightAttackSwing : g.entityTextures[g.currentLevelNum].leftAttackSwing;
        }
        else {
            entity->texture = entity->facingRight ? g.entityTextures[g.currentLevelNum].rightAttack : g.entityTextures[g.currentLevelNum].leftAttack;
        }

    } else if (entity->blocking && g.entityTextures[g.currentLevelNum].rightBlock.id != 0) {
        entity->texture = entity->facingRight ? g.entityTextures[g.currentLevelNum].rightBlock : g.entityTextures[g.currentLevelNum].leftBlock;

    } else {
        entity->texture = entity->facingRight ? g.entityTextures[g.currentLevelNum].right : g.entityTextures[g.currentLevelNum].left;
    }
}

void UpdateEntities(void) {
    for (int i = 0; i < g.levels[g.currentLevelNum].entityCount; i++) {
        if (g.entities[g.currentLevelNum][i].active == true) g.entities[g.currentLevelNum][i].position = CalculateNewPosition(g.player.position, &g.entities[g.currentLevelNum][i]);

        if (g.entities[g.currentLevelNum][i].canBlock && g.entities[g.currentLevelNum][i].health < 20) EntityBlock(&g.entities[g.currentLevelNum][i]);
        if (g.entities[g.currentLevelNum][i].blockFrames > 0) g.entities[g.currentLevelNum][i].blockFrames--; else g.entities[g.currentLevelNum][i].blocking = false;
        if (g.entities[g.currentLevelNum][i].blockCooldown > 0) g.entities[g.currentLevelNum][i].blockCooldown--;

        if (g.entities[g.currentLevelNum][i].canAttack) EntityAttack(&g.entities[g.currentLevelNum][i]);

        EntitySprite(&g.entities[g.currentLevelNum][i]);
    }
}

// By Seth C