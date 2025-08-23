#include "raylib.h"
#include "raymath.h"
#include <vector>

void drawBall(float x, float y, float r) {
    DrawCircleV(Vector2{x,y},r, BLUE); 
}

void updateBall(float &x, float &y, float &velX, float &velY, float r ) {
    x += velX;
    y += velY;
    if (y <= 0) velY *= -1;
    if (x <= 0 || x >= 800) velX *= -1;
}

void drawPaddle(float x, float y, float width, float height) {
    DrawRectangleRec(Rectangle{ x, y, width, height },RED);
}

void updatePaddle(float &x, float vel ) {
    if (IsKeyDown(KEY_RIGHT)) x += vel; 
    if (IsKeyDown(KEY_LEFT))  x -= vel; 
}

int main() {
    InitWindow(800, 600, "Breakout Game - OOP Demo");
    SetTargetFPS(60);

    float ballX = 300, ballY = 300, ballVelocityX = 4;
    float ballVelocityY = -4, ballRadius = 8 ;
    
    float paddleX = 150, paddleY = 550;
    float paddleWidth = 100, paddleHeight = 20, paddleSpeed = 7;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        updateBall(ballX, ballY, ballVelocityX, ballVelocityY, ballRadius);
        updatePaddle(paddleX, paddleSpeed);

        if (CheckCollisionRecs( 
            Rectangle{ballX - ballRadius, ballY- ballRadius, 
                      ballRadius * 2, ballRadius * 2},
            Rectangle{paddleX, paddleY,paddleWidth, paddleHeight}) )

            ballVelocityY *= -1;
        drawBall(ballX, ballY, ballRadius);
        drawPaddle(paddleX, paddleY, paddleWidth, paddleHeight);
    

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
