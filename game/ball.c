#include "../include/game/game.h"

void ball_init(Ball *ball, int x_dir, int y_dir) {
	/* set ball position */
	ball->pos.x = SCREEN_MID_X;
	ball->pos.y = SCREEN_MID_Y;

	/* set ball initial velocity direction */
	if (x_dir)
		ball->vel.x = (x_dir < 0 ? -1 : 1) * BALL_SPEED;
	if (y_dir)
		ball->vel.y = (y_dir < 0 ? -1 : 1) * BALL_SPEED;
}

void ball_draw(Ball *ball) {
	DrawCircle(ball->pos.x, ball->pos.y, BALL_RADIUS, RED);
}

void ball_update(Ball *ball) {
  /* update ball position */
  ball->pos.x += ball->vel.x;
  ball->pos.y += ball->vel.y;
}
