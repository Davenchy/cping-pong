#include "../include/game/game.h"

void score_draw(const Score score) {
  const char *human_str = TextFormat("%u", score.human);
  const char *cpu_str = TextFormat("%u", score.cpu);
  int human_len = MeasureText(human_str, FONT_SIZE);
  int cpu_len = MeasureText(cpu_str, FONT_SIZE);

  DrawText(human_str, SCREEN_MID_X / 2 - human_len / 2,
           SCREEN_MID_Y - FONT_HALF_SIZE, FONT_SIZE, RAYWHITE);
  DrawText(cpu_str, SCREEN_WIDTH - SCREEN_MID_X / 2 - cpu_len / 2,
           SCREEN_MID_Y - FONT_HALF_SIZE, FONT_SIZE, RAYWHITE);
}
