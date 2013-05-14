#ifndef PICLIST_H
#define PICLIST_H

extern struct list * root; ///!!!

struct list
{
    struct list * next;
    struct list * prev;
    ALLEGRO_BITMAP * image;
};

void addToList(ALLEGRO_BITMAP * image);

#endif // PICLIST_H
