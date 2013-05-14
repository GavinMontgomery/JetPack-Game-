#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "picList.h"

struct list * root = NULL;
struct list * prev = NULL;

void addToList(ALLEGRO_BITMAP * image)
{
    struct list * tmp = (struct list *)malloc(sizeof(struct list));

    if(root)
    {
        prev -> next = tmp;
        tmp -> next = NULL;
        tmp -> prev = prev;
        tmp -> image = image;
        prev = tmp;
    }
    else
    {
        tmp -> next = NULL;
        tmp -> prev = NULL;
        tmp -> image = image;
        root = tmp;
        prev = root;
    }
}
