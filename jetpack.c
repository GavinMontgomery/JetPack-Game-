#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "picList.h"
#include "jetpack.h"

void drawPack(struct jetPack *JP, struct list *LS)
{
    al_draw_bitmap(LS -> image, JP -> x, JP -> y, 0);
}
void movePack(struct jetPack *JP)
{
    JP -> y += JP -> speed;
    if(JP -> y < JP -> topBound){ JP -> y = JP -> topBound; }
    if(JP -> y > HEIGHT - JP -> height){ JP -> y = HEIGHT - JP -> height; }
}
void initPack(struct jetPack *JP, ALLEGRO_BITMAP * image)
{
    JP -> x = 100;
    JP -> topBound = 0;
    JP -> y = HEIGHT/2;
    JP -> accel = 0.08;
    JP -> ID = PLAYER;
    JP -> distance = 0;
    JP -> lives = 3;
    JP -> speed = 0;
    JP -> image = image;
    JP -> width = al_get_bitmap_width(image);
    JP -> height = al_get_bitmap_height(image);
    JP -> score = 1000;
}
void speedUpPack(struct jetPack *JP)
{
    JP -> speed -= JP -> accel;
}
void slowDownPack(struct jetPack *JP)
{
    JP -> speed += GRAVITY;
}

void packFlyUp(struct jetPack *JP)
{
    if(JP -> y != JP -> topBound)
    {
        speedUpPack(JP);
        movePack(JP);
    }
    else
    {
        JP -> speed = 0;
    }

    if(JP -> y != HEIGHT - JP -> height)
    {
        speedUpPack(JP);
        movePack(JP);
    }
    else
    {
        JP -> speed = 0;
    }

}

void packFlyDown(struct jetPack *JP)
{
    if(JP -> y != HEIGHT - JP -> height)
    {
        slowDownPack(JP);
        movePack(JP);
    }
    else
    {
        JP -> speed = 0;
    }
    if(JP -> y != JP -> topBound)
    {
        slowDownPack(JP);
        movePack(JP);
    }
    else
    {
        JP -> speed = 0;
    }
}


