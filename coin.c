#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "jetpack.h"
#include "coin.h"

void initCoin(struct coin coin[], int size, ALLEGRO_BITMAP * image)
{
    int i;
    for(i = 0; i < size; i++)
    {
        coin[i].ID = OBSTACLE;
        coin[i].life = false;
        coin[i].speed = 5;
        coin[i].width = al_get_bitmap_width(image);
        coin[i].height = al_get_bitmap_height(image);
        coin[i].image = image;
    }
}
void startCoins(struct coin coin[], int size)
{
    int random = rand() % (HEIGHT - 60); ///zmienic
    if(!coin[3].life && rand() % 500 == 0)
    {
        int j;
        for(j = 0; j < size; j++)
        {
            coin[j].speed = SPEED;
        }
        int i = 0;
        for(i = 0; i < size; i++)
        {
            coin[i].life = true;
            coin[i].x = WIDTH + i * coin[i].width;
            coin[i].y = random;
        }
    }
}

void coinCollect(struct jetPack *JP, struct coin coin[], int coinSize)
{
   int i;
   for(i = 0; i < coinSize; i++)
   {
       if(coin[i].life)
       {
           if(JP -> y + JP -> height> coin[i].y &&
              JP -> y < coin[i].y + coin[i].height &&
              JP -> x + JP -> width > coin[i].x &&
              JP -> x < coin[i].x + coin[i].width)
           {
               coin[i].life = false;
               JP -> score++;
           }
       }
   }
}

void updateCoin(struct coin coin[], int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        if(coin[i].life)
        {
            coin[i].x -= coin[i].speed;
        }
        if(coin[i].x < 0 - coin[i].width)
        {
            coin[i].life = false;
        }
    }
}
void drawCoins(struct coin coin[], int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        if(coin[i].life)
        {
            al_draw_bitmap(coin[i].image, coin[i].x, coin[i].y, 0);
        }
    }
}
