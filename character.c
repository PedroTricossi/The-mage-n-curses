#include <ncurses.h>
#include <stdlib.h>

#include "character.h"

t_mage init_mage(int row, int col){
    t_mage aux;

    aux.x = row;
    aux.y = col;
    aux.icon = MAGE;

    aux.status.life = 100;
    aux.status.attack = 15;
    aux.status.defense = 10;

    return aux;
}

t_enemy *init_enemies(int row, int col, t_enemy *enemy){
    t_enemy *aux = NULL;
    t_enemy *iter = NULL;

    aux = (t_enemy *) malloc(sizeof(t_enemy));

    if(aux == NULL)
        exit(1);

    aux->icon = SIMPLE_ENEMY;
    aux->x = rand() % row;
    aux->y = rand() % col;
    aux->next = NULL;
    aux->prev = NULL;

    aux->status.life = 40;
    aux->status.attack = 50;
    aux->status.defense = 2;

    if(enemy == NULL)
        enemy = aux;
    else{
        iter = enemy;
        while (iter->next != NULL)
        {
            iter = iter->next;
        }

        iter->next = aux;
        aux->prev = iter;
    }

    return enemy;
}

void move_character(int ch, t_mage* mage){
    clear();
    switch(ch){
        case KEY_LEFT:
            mage->y--;
            break;
        
        case KEY_UP:
            mage->x--;
            break;

        case KEY_DOWN:
            mage->x++;
            break;
        
        case KEY_RIGHT:
            mage->y++;
            break;
    }
}

void show_map(t_mage* mage, t_enemy *enemy){
    t_enemy *aux;
    // printw("MAGO X: %d \nMAGO Y: %d \nENEMY X: %d \nENEMY Y: %d \n", mage->x, mage->y, enemy->x, enemy->y);
    mvprintw(mage->x, mage->y, "%s", mage->icon);

    aux = enemy;
    while (aux != NULL)
    {
        mvprintw(aux->x, aux->y, "%s", aux->icon);
        aux = aux->next;
    }

    refresh();
}

void move_enemy(t_enemy *enemy, t_mage* mage){
    int X, X1, X2, Y, Y1, Y2;
    int enemy_x, enemy_y;

    X = abs(mage->x - enemy->x);
    Y = abs(mage->y - enemy->y);

    if(X < Y){
        enemy_y = enemy->y;

        Y1 = abs(mage->y - ++enemy_y);
        Y2 = abs(mage->y - --enemy_y);

        if(Y1 < Y2)
            enemy->y++;
        else
            enemy->y--;

        return;
    }

    enemy_x = enemy->x;

    X1 = abs(mage->x - ++enemy_x);
    X2 = abs(mage->x - --enemy_x);

    if(X1 < X2)
        enemy->x++;
    else
        enemy->x--;
}


void detect_collision(t_enemy *enemy, t_mage* mage){
    if(abs(mage->y - enemy->y) <= 1 && enemy->x == mage->x){
        mage->status.life = (mage->status.life - (enemy->status.attack - mage->status.defense));
        enemy->status.life = (enemy->status.life - (mage->status.attack - enemy->status.defense));

        enemy->x++;
        enemy->x++;
        mage->x--;
        mage->x--;
    }
}

void print_status(t_mage* mage, int col){
        mvprintw(0, col-28, "LIFE: %d", mage->status.life);
        mvprintw(0, col-5, "ATTACK: %d", mage->status.attack);
        mvprintw(0, col+18, "DEFENSE: %d", mage->status.defense);
}

