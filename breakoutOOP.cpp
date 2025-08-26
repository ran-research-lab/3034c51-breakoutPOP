#include "raylib.h"
#include "raymath.h"
#include <vector>


class Ball {
protected:
    float x, y, velX, velY, radius;
public:
    Ball() {
        x = rand() % 600 + 100;
        y = rand() % 200 + 100;
        velX = 4;
        velY = 6;
        radius = 10;
    }
    Ball(float xx, float yy, float vvelX, float vvelY, float rradius) {
        x = xx;
        y = yy;
        velX = vvelX;
        velY = vvelY;
        radius = rradius;
    }
    void update() {
        x += velX;
        y += velY;
        if (y <= 0) bounce();
        if (x <= 0 || x >= 800) velX *= -1;
    }
    void draw() const {
        DrawCircleV(Vector2{x,y},radius, BLUE); 
    }
    float getX() const {return x; }
    float getY() const {return y; }
    float getRadius() const {return radius; }
    void bounce() { velY = -velY; }

};


class Fireball : public Ball {
private:
    bool grow = true;
public:
void update() {
    if (grow ) radius++;
    else radius--;
    if (radius < 5 || radius > 15) grow = !grow;
    x += velX;
    y += velY;
    if (y <= 0) bounce();
    if (x <= 0 || x >= 800) velX *= -1;
}

};



class Paddle {
private:
//data members
    float x, y, width, height, speed;
public:
// member functions or methods
    Paddle(float xx, float yy, float wwidth, float hheight, float sspeed ) : x(xx), y(yy), width(wwidth), height(hheight), speed(sspeed) {}
    void update() {
        if (IsKeyDown(KEY_RIGHT)) x += speed; 
        if (IsKeyDown(KEY_LEFT))  x -= speed; 
    }
    void draw() const { DrawRectangleRec(Rectangle{ x, y, width, height },GREEN); }
    float getX() const { return x;}
    float getY() const { return y;}
    float getWidth() const { return width;}
    float getHeight() const { return height;}



};



// void drawPaddle(float x, float y, float width, float height) {
//     DrawRectangleRec(Rectangle{ x, y, width, height },RED);
// }

// void updatePaddle(float &x, float vel ) {
//     if (IsKeyDown(KEY_RIGHT)) x += vel; 
//     if (IsKeyDown(KEY_LEFT))  x -= vel; 
// }
using namespace std;
int main() {
    InitWindow(800, 600, "Breakout Game - OOP Demo");
    SetTargetFPS(60);

    srand(time(NULL));
    vector<Fireball> v(5);

    //Ball b(100, 100, 5, -5, 25);

    Paddle p(150, 550, 100, 20, 7);

    // float paddleX = 150, paddleY = 550;
    // float paddleWidth = 100, paddleHeight = 20, paddleSpeed = 7;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        for (auto &e: v) e.update();
        p.update();

        for(auto &e: v) {
            if (CheckCollisionRecs( 
                Rectangle{e.getX() - e.getRadius(), e.getY()- e.getRadius(), 
                        e.getRadius() * 2, e.getRadius() * 2},
                Rectangle{p.getX(), p.getY(),p.getWidth(), p.getHeight()}) ) {

                e.bounce();
            }
        }

        for (auto e: v) e.draw();
        p.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
