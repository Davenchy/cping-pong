#include "include/game/game.h"
#include <raylib.h>

void main_loop() {
  Game game;

  /* initialise objects */
  ball_init(&game.ball, -1, 1);
  paddle_init(
      &game.human_paddle,
      (Vector2){PADDLE_PADDING, (int)(SCREEN_MID_Y - PADDLE_HEIGHT / 2)});
  paddle_init(
      &game.cpu_paddle,
      (Vector2){SCREEN_WIDTH - PADDLE_PADDING - PADDLE_WIDTH, SCREEN_MID_Y});

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    /* update objects */
    ball_update(&game.ball);
    paddle_update(&game.human_paddle);
    paddle_update(&game.cpu_paddle);

    controller_human(&game.human_paddle);
    // controller_cpu(&game.cpu_paddle, game.ball.pos.y);
    controller_cpu_adv(&game);

    game_management(&game);

    /* draw objects */
    BeginDrawing();

    draw_board();

    ball_draw(&game.ball);

    paddle_draw(game.human_paddle);
    paddle_draw(game.cpu_paddle);
    score_draw(game.score);

    EndDrawing();
  }

  CloseWindow();
}

int main() {
  main_loop();
  return 0;
}
