#ifndef __SCORE_H__
#define __SCORE_H__

typedef struct Score {
  unsigned int human;
  unsigned int cpu;
} Score;

void score_draw(const Score score);

#endif
