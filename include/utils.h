#ifndef UTILS_H
#define UTILS_H

double CalculateDistance(Vector2 playerPosition, Vector2 enemyPosition);

Vector2 CalculateNewPosition(Vector2 playerPosition, Entity *entity);

void Transition(int *transitionFrames, int *transition);

void UpdateGui(void);

#endif