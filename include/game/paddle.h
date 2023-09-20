#ifndef __PADDLE_H__
#define __PADDLE_H__

#include <raylib.h>

#define PADDLE_HEIGHT 100
#define PADDLE_WIDTH 15
#define PADDLE_PADDING 10
#define PADDLE_SPEED 2
#define PADDLE_MAX_VEL 5

typedef struct Paddle {
  Rectangle rect;
  int vel;
} Paddle;

void paddle_init(Paddle *paddle, Vector2 pos);
void paddle_update(Paddle *paddle);
void paddle_draw(const Paddle paddle);

#endif
