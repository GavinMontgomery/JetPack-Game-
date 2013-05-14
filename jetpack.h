#ifndef JETPACK_H
#define JETPACK_H

extern const int HEIGHT;
extern const float GRAVITY;

enum IDS {PLAYER, OBSTACLE, COIN};

struct jetPack
{
    int ID;
    float x;
    float y;
    float distance;
    int lives;
    int topBound;
    int bottomBound;
    float speed;
    float accel;
    int width;
    int height;
    int score;
    ALLEGRO_BITMAP * image;
};

void drawPack(struct jetPack *JP, struct list * LS);
void movePack(struct jetPack *JP);
void initPack(struct jetPack *JP, ALLEGRO_BITMAP * image);


void speedUpPack(struct jetPack *JP);
void slowDownPack(struct jetPack *JP);

void packFlyUp(struct jetPack *JP);
void packFlyDown(struct jetPack *JP);

#endif // JETPACK_H
