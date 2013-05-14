#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "jetpack.h"
#include "obstacle.h"
#include "coin.h"
#include "picList.h"
#include "background.h"


//***GROBALS***
const int WIDTH = 750;
const int HEIGHT = 450;
const float GRAVITY = 0.06;
const int ANIM_DELAY = 3;
bool START_OBS = false;
float SPEED = 5;

enum KEYS{UP,SPACE};
bool keys[2] = {false, false};



int main()
{
    bool done = false;
    bool redraw = true;
    bool isGameOver = false;
    int NUM_OF_OBSTACLES = 3;
    int NUM_OF_COINS = 4;

    srand(time(NULL));

    /// *** INITALIZATION ***
    struct backGround BG;
    struct jetPack JP;
    struct obstacle obstacles[NUM_OF_OBSTACLES];
    struct coin coins[NUM_OF_COINS];

    const int FPS = 60;

    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_EVENT_QUEUE * event_queue = NULL; ///ev
    ALLEGRO_TIMER * timer = NULL;
    ALLEGRO_FONT * font18 = NULL;
    ALLEGRO_BITMAP * bgImage;
    ALLEGRO_BITMAP * characterImage; ///********************///
    ALLEGRO_BITMAP * coinImage;

    if(!al_init())
    {
        return false;
    }

    display = al_create_display(WIDTH, HEIGHT);

    if(!display)
    {
        return false;
    }

    al_init_primitives_addon();
    al_init_font_addon();
    al_init_image_addon();
    al_init_ttf_addon();
    al_install_keyboard();

    event_queue = al_create_event_queue(); ///ev
    timer = al_create_timer(1.0 / FPS);

    characterImage = al_load_bitmap("character.png"); //

    /**********/

    addToList(al_load_bitmap("character.png"));
    addToList(al_load_bitmap("character1.png"));
    addToList(al_load_bitmap("character2.png"));
    addToList(al_load_bitmap("character3.png"));
    addToList(al_load_bitmap("character4.png"));
    addToList(al_load_bitmap("character5.png"));

    struct list * currPic = root; ///

    /******/
    coinImage = al_load_bitmap("coin.png");

    initPack(&JP, characterImage); ///*****/// ZMIENIAN TUTAJ!!!!!!!!!!
    initCoin(coins, NUM_OF_COINS, coinImage);
    initObstacle(obstacles, NUM_OF_OBSTACLES);

    bgImage = al_load_bitmap("BG.png");


    initBackGround(&BG, 0, 0, 1, 0, WIDTH, HEIGHT, -1, 1, bgImage); ///

    font18 = al_load_font("arial.ttf", 18, 0);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));///ev
    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_start_timer(timer);



     int i = 0;
     int j = 0;
    while(!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER && !isGameOver)
        {
            redraw = true;
            JP.distance += obstacles[0].speed * 0.00026;
            if(keys[UP])
            {
                packFlyUp(&JP);
                if(currPic->next && ++i > ANIM_DELAY)
                {
                    currPic = currPic -> next; ///**********///
                    i = 0;
                }
            }
            else
            {
                packFlyDown(&JP);
                if(currPic->prev && ++j > ANIM_DELAY)
                {
                    currPic = currPic -> prev;  ///**********///
                    j = 0;
                }
            }

            if(!isGameOver)
            {
                startObstacle(obstacles, NUM_OF_OBSTACLES);
                startCoins(coins, NUM_OF_COINS);
                updateObstacle(obstacles, NUM_OF_OBSTACLES);
                updateCoin(coins, NUM_OF_COINS);
                obstacleCollission(&JP, obstacles, NUM_OF_OBSTACLES);
                coinCollect(&JP, coins, NUM_OF_COINS);
                updateBackGround(&BG, obstacles);

                if(JP.lives <= 0)
                {
                    isGameOver = true;
                }
            }
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
                    break;
                case ALLEGRO_KEY_UP:
                    keys[UP] = true;
                    break;
                case ALLEGRO_KEY_SPACE:
                    keys[SPACE] = true;
                    break;
            }
        }else if(ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    done = false;
                    break;
                case ALLEGRO_KEY_UP:
                    keys[UP] = false;
                    break;
                case ALLEGRO_KEY_SPACE:
                    keys[SPACE] = false;
                    break;
            }
        }
        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;
            if(!isGameOver)
            {
                drawBackGround(&BG);
                drawPack(&JP, currPic); ///ZMIANA
                drawObstacle(obstacles, NUM_OF_OBSTACLES);
                drawCoins(coins, NUM_OF_COINS);
                al_draw_textf(font18, al_map_rgb(140,170,80), 20, 20, 0, "Player has %i lifes", JP.lives);
                al_draw_textf(font18, al_map_rgb(140,10,80), 20, 50, 0, "Distance %.2f meters",JP.distance);
                al_draw_textf(font18, al_map_rgb(140,10,80), 20, 80, 0, "Score: %d coins",JP.score);
            }
            else
            {
                drawBackGround(&BG);
                drawPack(&JP, currPic); ///ZIANA
                drawObstacle(obstacles, NUM_OF_OBSTACLES);
                al_draw_textf(font18, al_map_rgb(60,10,80), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "GAME OVER");
                al_draw_textf(font18, al_map_rgb(60,10,80), WIDTH / 2, HEIGHT / 2 + 50, ALLEGRO_ALIGN_CENTER, "Distance %.2f meters",JP.distance);
                al_draw_textf(font18, al_map_rgb(140,10,80), WIDTH / 2, HEIGHT / 2 + 100, ALLEGRO_ALIGN_CENTER, "Score: %d coins",JP.score);
            }
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
    }
    al_destroy_bitmap(bgImage);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);

    return 0;
}



