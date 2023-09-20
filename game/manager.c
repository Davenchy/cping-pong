#include "../include/game/game.h"
#include <raylib.h>

void draw_board() {
	ClearBackground(BLACK);
  DrawLine(SCREEN_MID_X, 0, SCREEN_MID_X, SCREEN_HEIGHT, WHITE);
  DrawCircleLines(SCREEN_MID_X, SCREEN_MID_Y, BALL_RADIUS * 8, WHITE);
}

void controller_human(Paddle *human_paddle) {
    /* control human paddle using keyboard k, j buttons */
  if (IsKeyDown(KEY_J))
    human_paddle->vel += PADDLE_SPEED;
  if (IsKeyDown(KEY_K))
    human_paddle->vel -= PADDLE_SPEED;
}

void controller_cpu(Paddle *cpu_paddle, int ball_y) {
  /* control CPU paddle using ball's position */
  int diff = ball_y - cpu_paddle->rect.y - (int)(PADDLE_HEIGHT / 2);
  cpu_paddle->vel += diff > 0 ? PADDLE_SPEED : -PADDLE_SPEED;
}

void controller_cpu_adv(Game *game) {
  static float timer = 0;
  Ball *ball = &game->ball;
  Paddle *cpu_paddle = &game->cpu_paddle;
  Vector2 ball_pos = ball->pos;

  /* control CPU paddle using ball's position */
  int dir = 0;
  int dest = ABS(cpu_paddle->rect.x - ball_pos.x);

  if ((int)(timer / 10) % 2 == 0)
    dest = 0;

  if (dest > SCREEN_MID_X) {
    dir = SCREEN_MID_Y - cpu_paddle->rect.y - (int)(PADDLE_HEIGHT / 2);
    if (ABS(dir) <= 1)
      dir = 0;
  } else {
    dir = ball_pos.y - cpu_paddle->rect.y - (int)(PADDLE_HEIGHT / 2);
  }

  if (dir)
    cpu_paddle->vel += dir > 1 ? PADDLE_SPEED : - PADDLE_SPEED;

  timer += GetFrameTime();
}

void game_management(Game *game) {
  Ball *ball = &game->ball;
  Score *score = &game->score;
  Rectangle human_rect = game->human_paddle.rect;
  Rectangle cpu_rect = game->cpu_paddle.rect;

    /* update ball->direction on collision with top/bottom walls */
  if (ball->pos.y - BALL_RADIUS < 0 ||
      ball->pos.y + BALL_RADIUS > SCREEN_HEIGHT)
    ball->vel.y *= -1;

  /* update cpu score */
  if (ball->pos.x < 0) {
    ball->pos.x = SCREEN_MID_X;
    ball->vel.x *= -1;
    score->cpu++;
  }

  /* update human score */
  if (ball->pos.x > SCREEN_WIDTH) {
    ball->pos.x = SCREEN_MID_X;
    ball->vel.x *= -1;
    score->human++;
  }

  /* check human paddle collision with the ball */
  if (CheckCollisionCircleRec(ball->pos, BALL_RADIUS, human_rect))
    ball->vel.x *= -1;
  /* check cpu paddle collision with the ball */
  if (CheckCollisionCircleRec(ball->pos, BALL_RADIUS, cpu_rect))
    ball->vel.x *= -1;
}
