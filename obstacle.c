#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "obstacle.h"
#include "jetpack.h"

void drawObstacle(struct obstacle obstacle[], int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        if(obstacle[i].life)
        {
            al_draw_filled_rectangle(obstacle[i].x, obstacle[i].y, obstacle[i].x + obstacle[i].width, obstacle[i].y + obstacle[i].height, al_map_rgb(24,120,4));
        }
    }
}

void initObstacle(struct obstacle obstacle[], int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        obstacle[i].ID = OBSTACLE;
        obstacle[i].life = false;
        obstacle[i].speed = 5;
        obstacle[i].width = 30;
        obstacle[i].height = 200;
    }
}

void startObstacle(struct obstacle obstacle[], int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        if(!obstacle[i].life)
        {
            if(WIDTH - obstacle[LAST].x > 300){
                if(rand() % 500 == 0)
                {
                    obstacle[i].life = true;
                    SPEED += 0.5;

                    int j;
                    for(j = 0; j < size; j++)
                    {
                        obstacle[j].speed = SPEED;
                    }

                    obstacle[i].x = WIDTH;
                    obstacle[i].y = rand() % (HEIGHT - obstacle[i].height);

                    LAST = i;
                }
            }else
            {
                if(!START_OBS)
                {
                    if(rand() % 500 == 0)
                    {
                        obstacle[i].life = true;
                        SPEED += 0.5;

                        int j;
                        for(j = 0; j < size; j++)
                        {
                            obstacle[j].speed = SPEED;
                        }

                        obstacle[i].x = WIDTH;
                        obstacle[i].y = rand() % (HEIGHT - obstacle[i].height);

                        LAST = i;
                        START_OBS = true;

                    }
                }
            }
        }
    }
}

void updateObstacle(struct obstacle obstacle[], int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        if(obstacle[i].life)
        {
            obstacle[i].x -= obstacle[i].speed;
        }
        if(obstacle[i].x < 0 - obstacle[i].width)
        {
            obstacle[i].life = false;
        }
    }
}

void obstacleCollission(struct jetPack *JP, struct obstacle obstacle[], int obSize)
{
    int i;
   for(i = 0; i < obSize; i++)
   {
       if(obstacle[i].life)
       {
           if(JP -> y + JP -> height> obstacle[i].y &&
              JP -> y < obstacle[i].y + obstacle[i].height &&
              JP -> x + JP -> width > obstacle[i].x &&
              JP -> x < obstacle[i].x + obstacle[i].width)
           {
               obstacle[i].life = false;
               JP -> lives--;
           }
       }
   }
}


