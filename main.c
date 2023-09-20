#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

#define SCREEN_VMID (int)(SCREEN_WIDTH / 2)
#define SCREEN_HMID (int)(SCREEN_HEIGHT / 2)

#define FONT_SIZE 130
#define FONT_HALF_SIZE (int)(FONT_SIZE / 2)

#define PADDLE_HEIGHT 100
#define PADDLE_WIDTH 15
#define PADDLE_PADDING 10
#define PADDLE_SPEED 2
#define PADDLE_MAX_VEL 5

#define BALL_RADIUS 10
#define BALL_SPEED 6

typedef struct Ball {
  Vector2 pos;
  Vector2 vel;
} Ball;

typedef struct Paddle {
  Rectangle rect;
  int vel;
} Paddle;

typedef struct Score {
  unsigned int human;
  unsigned int cpu;
} Score;

void update_ball(Ball *ball, Score *score, Rectangle human_rect,
                 Rectangle cpu_rect) {
  /* update ball position */
  ball->pos.x += ball->vel.x;
  ball->pos.y += ball->vel.y;

  /* update ball->direction on collision with top/bottom walls */
  if (ball->pos.y - BALL_RADIUS < 0 ||
      ball->pos.y + BALL_RADIUS > SCREEN_HEIGHT)
    ball->vel.y *= -1;

  /* update cpu score */
  if (ball->pos.x < 0) {
    ball->pos.x = SCREEN_VMID;
    ball->vel.x *= -1;
    score->cpu++;
  }

  /* update human score */
  if (ball->pos.x > SCREEN_WIDTH) {
    ball->pos.x = SCREEN_VMID;
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

void update_paddle(Paddle *paddle) {
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

void update_human_paddle_velocity(Paddle *human_paddle) {
  /* control human paddle using keyboard k, j buttons */
  if (IsKeyDown(KEY_J))
    human_paddle->vel += PADDLE_SPEED;
  if (IsKeyDown(KEY_K))
    human_paddle->vel -= PADDLE_SPEED;
}

void update_cpu_paddle_velocity(Paddle *cpu_paddle, unsigned int ball_y) {
  /* control cpu paddle using ball's position */
  int diff = ball_y - cpu_paddle->rect.y - (int)(PADDLE_HEIGHT / 2);
  cpu_paddle->vel += diff > 0 ? PADDLE_SPEED : -PADDLE_SPEED;
}

void draw_paddle(const Paddle *paddle) {
  DrawRectangleLines(paddle->rect.x, paddle->rect.y, paddle->rect.width,
                     paddle->rect.height, RAYWHITE);
}

void draw_score(const Score *score) {
  const char *human_str = TextFormat("%u", score->human);
  const char *cpu_str = TextFormat("%u", score->cpu);
  int human_len = MeasureText(human_str, FONT_SIZE);
  int cpu_len = MeasureText(cpu_str, FONT_SIZE);

  DrawText(human_str, SCREEN_VMID / 2 - human_len / 2,
           SCREEN_HMID - FONT_HALF_SIZE, FONT_SIZE, RAYWHITE);
  DrawText(cpu_str, SCREEN_WIDTH - SCREEN_VMID / 2 - cpu_len / 2,
           SCREEN_HMID - FONT_HALF_SIZE, FONT_SIZE, RAYWHITE);
}

void main_loop() {
  Score score = (Score){0, 0};
  Ball ball = (Ball){{SCREEN_HMID, SCREEN_VMID}, {-BALL_SPEED, BALL_SPEED}};
  Paddle human_paddle = (Paddle){
      (Rectangle){PADDLE_PADDING, SCREEN_VMID - (int)(PADDLE_HEIGHT / 2),
                  PADDLE_WIDTH, PADDLE_HEIGHT},
      0};
  Paddle cpu_paddle =
      (Paddle){(Rectangle){SCREEN_WIDTH - PADDLE_WIDTH - PADDLE_PADDING,
                           SCREEN_VMID - (int)(PADDLE_HEIGHT / 2), PADDLE_WIDTH,
                           PADDLE_HEIGHT},
               0};

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CPingPong");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    /* Draw ground */
    DrawLine(SCREEN_VMID, 0, SCREEN_VMID, SCREEN_HEIGHT, WHITE);
    DrawCircleLines(SCREEN_VMID, SCREEN_HMID, BALL_RADIUS * 8, WHITE);

    /* Draw ball */
    DrawCircle(ball.pos.x, ball.pos.y, BALL_RADIUS, RED);

    draw_paddle(&human_paddle);
    draw_paddle(&cpu_paddle);
    draw_score(&score);

    update_ball(&ball, &score, human_paddle.rect, cpu_paddle.rect);

    update_human_paddle_velocity(&human_paddle);
    update_cpu_paddle_velocity(&cpu_paddle, ball.pos.y);

    update_paddle(&human_paddle);
    update_paddle(&cpu_paddle);

    EndDrawing();
  }

  CloseWindow();
}

int main() {
  main_loop();
  return 0;
}
