#ifndef OBSTACLE_H
#define OBSTACLE_H

extern const int WIDTH;
extern struct jetPack JP;
extern int distance;
extern float SPEED;

int LAST;
bool START_OBS;

struct obstacle{
    int ID;
    int x;
    int y;
    int width;
    int height;
    float speed;
    bool life;
};

void drawObstacle(struct obstacle obstacle[], int size);
void initObstacle(struct obstacle obstacle[], int size);
void startObstacle(struct obstacle obstacle[], int size);
void updateObstacle(struct obstacle obstacle[], int size);
void obstacleCollission(struct jetPack *JP, struct obstacle obstacle[], int obSize);


#endif // OBSTACLE_H
