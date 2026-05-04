#ifndef ENTITY_H
#define ENTITY_H

void DrawSprite(Entity *sprite, bool debug);

void DamageTarget(Entity *target, Entity *source, Level *counter);

void EntityBlock(Entity *entity);

void EntityAttack(Entity *entity);

void EntitySprite(Entity *entity);

void UpdateEntities(void);

#endif