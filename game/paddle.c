#include "../include/game/game.h"

void paddle_init(Paddle *paddle, Vector2 pos) {
	paddle->rect.x = pos.x;
	paddle->rect.y = pos.y;
	paddle->rect.width = PADDLE_WIDTH;
	paddle->rect.height = PADDLE_HEIGHT;
	paddle->vel = 0;
}

void paddle_update(Paddle *paddle) {
  /* limit the velocity of the paddle */
  if (paddle->vel > PADDLE_MAX_VEL)
    paddle->vel = PADDLE_MAX_VEL;
  if (paddle->vel < -PADDLE_MAX_VEL)
    paddle->vel = -PADDLE_MAX_VEL;

  /* update the paddle position */
  paddle->rect.y += paddle->vel;
  /* apply drag force on the paddle, to force it to stop or slow down */
  paddle->vel *= 0.85;

  /* force the paddle to stay inside the window */
  if (paddle->rect.y < 0)
    paddle->rect.y = 0;
  if (paddle->rect.y + PADDLE_HEIGHT > SCREEN_HEIGHT)
    paddle->rect.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
}

void paddle_draw(const Paddle paddle) {
  DrawRectangleLines(paddle.rect.x, paddle.rect.y, paddle.rect.width,
                     paddle.rect.height, RAYWHITE);
}
