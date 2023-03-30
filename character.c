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

    aux->status.life = 10;
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
    t_enemy *aux = NULL;
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
    t_enemy *aux = enemy;

    while(aux != NULL){
        X = abs(mage->x - aux->x);
        Y = abs(mage->y - aux->y);

        if(X < Y){
            enemy_y = aux->y;

            Y1 = abs(mage->y - ++enemy_y);
            Y2 = abs(mage->y - --enemy_y);

            if(Y1 < Y2)
                aux->y++;
            else
                aux->y--;

        }else{

            enemy_x = aux->x;

            X1 = abs(mage->x - ++enemy_x);
            X2 = abs(mage->x - --enemy_x);

            if(X1 < X2)
                aux->x++;
            else
                aux->x--;
        }

        aux = aux->next;
    }
}

t_enemy *remove_enemy(t_enemy *enemy, t_enemy *enemy_q){
    t_enemy *aux = enemy_q;

    while (aux != enemy)
        aux = aux->next;
    
    if(aux->next == NULL && aux->prev == NULL){
        enemy_q->next = NULL;
        enemy_q->prev = NULL;
        enemy_q = NULL;
        enemy=NULL;
    }
    
    else if(aux->next == NULL && aux->prev != NULL){
        aux->prev->next = NULL;
    }
    else if(aux->next != NULL && aux->prev == NULL){
        aux->next->prev = NULL;
    }else{
        aux->next->prev = aux->prev;
        aux->prev->next = aux->next;
    }


    free(aux);
    aux = NULL;

    return enemy_q;
}

void detect_collision(t_enemy *enemy, t_mage* mage){
    t_enemy *aux = enemy;

    while(aux != NULL){
        if(abs(mage->y - aux->y) <= 1 && aux->x == mage->x){
            mage->status.life = (mage->status.life - (aux->status.attack - mage->status.defense));
            aux->status.life = (aux->status.life - (mage->status.attack - aux->status.defense));

            aux->x++;
            aux->x++;
            mage->x--;
            mage->x--;

            if(aux->status.life <= 0){
                // printw("enemy life: %d", aux->status.life);
                enemy = remove_enemy(aux, enemy);
            }

            // printw("ENEMY: %p __ aux->next: %p", enemy, aux->next);
        }

        aux = aux->next;
    }
}

void print_status(t_mage* mage, int col){
    mvprintw(0, col-28, "LIFE: %d", mage->status.life);
    mvprintw(0, col-5, "ATTACK: %d", mage->status.attack);
    mvprintw(0, col+18, "DEFENSE: %d", mage->status.defense);
}

// RETURN 0 -> CONTINUE GAME
// RETURN 1 -> PLAYER LOSE
// RETURN 2 -> PLAYER WIN
int game_is_over(t_enemy *enemy, t_mage* mage){
    // printw("ENEMY N: %p __ ENEMY P: %p", enemy->next, enemy->prev);

    if(mage->status.life <= 0)
        return 1;
    
    if(enemy->next == NULL && enemy->prev == NULL && enemy->status.life <= 0)
        return 2;
    
    return 0;
}

void end_game(int* status,int *x,int *y){
    clear();

    if(*status == 1){
        mvprintw(*x, *y-9, "YOU ARE A LOSER!!!");
    }

    else if(*status == 2)
        mvprintw(*x, *y-9, "YOU ARE A WINNER!!!");
}
