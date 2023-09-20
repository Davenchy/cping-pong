#ifndef __BALL_H__
#define __BALL_H__

#include <raylib.h>

#define BALL_RADIUS 10
#define BALL_SPEED 6

typedef struct Ball {
  Vector2 pos;
  Vector2 vel;
} Ball;

void ball_init(Ball *ball, int x_dir, int y_dir);
void ball_update(Ball *ball);
void ball_draw(Ball *ball);

#endif
