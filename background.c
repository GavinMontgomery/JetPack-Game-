#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "obstacle.h"
#include "background.h"

void initBackGround(struct backGround *back, float x, float y, float velX, float velY, int width, int height, int dirX, int dirY, ALLEGRO_BITMAP * image)
{
    back -> x = x;
    back -> y = y;
    back -> velX = velX;
    back -> velY = velY;
    back -> dirX = dirX;
    back -> dirY = dirY;
    back -> width = width;
    back -> height = height;
    back -> image = image;
}

void updateBackGround(struct backGround *back, struct obstacle obstacle[])
{
    //back->x += obstacle[0].speed * back->dirX;///
    back->x -= SPEED;
    if(back -> x + back -> width <= 0)
    {
        back -> x = 0;
    }
}
void drawBackGround(struct backGround *back)
{
    al_draw_bitmap(back -> image, back -> x, back -> y, 0);

    if(back -> x + back -> width < WIDTH)
    {
        al_draw_bitmap(back -> image, back -> x + back -> width, back -> y, 0);
    }
}
