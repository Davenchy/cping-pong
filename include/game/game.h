#ifndef __GAME_H__
#define __GAME_H__

#include "../utils.h"
#include "ball.h"
#include "paddle.h"
#include "score.h"
#include <raylib.h>

#define GAME_TITLE "CPingPong"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

#define SCREEN_MID_X (int)(SCREEN_WIDTH / 2)
#define SCREEN_MID_Y (int)(SCREEN_HEIGHT / 2)

#define FONT_SIZE 130
#define FONT_HALF_SIZE (int)(FONT_SIZE / 2)

typedef struct {
  Ball ball;
  Paddle human_paddle;
  Paddle cpu_paddle;
  Score score;
} Game;

void draw_board();
void controller_human(Paddle *human_paddle);
void controller_cpu(Paddle *cpu_paddle, int ball_y);
void controller_cpu_adv(Game *game);
void game_management(Game *game);

#endif
