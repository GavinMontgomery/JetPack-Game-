#ifndef BACKGROUND_H
#define BACKGROUND_H

extern float SPEED;

struct backGround
{
    float x;
    float y;
    float velX;
    float velY;
    int dirX;
    int dirY;

    int width;
    int height;

    ALLEGRO_BITMAP * image;
};

void initBackGround(struct backGround *back, float x, float y, float velX, float velY, int width, int height, int dirX, int dirY, ALLEGRO_BITMAP * image);
void updateBackGround(struct backGround *back, struct obstacle obstacle[]);
void drawBackGround(struct backGround *back);

#endif // BACKGROUND_H
