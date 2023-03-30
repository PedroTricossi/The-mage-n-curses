#ifndef __CHARACTER__
#define __CHARACTER__

#define MAGE "|0|"
#define SIMPLE_ENEMY "|X|"

typedef struct t_mage t_mage;
typedef struct t_enemy t_enemy;
typedef struct t_rpg t_rpg;

struct t_rpg
{
    int life;
    int attack;
    int defense;
};


struct t_mage
{
    char* icon;
    int x, y;
    t_rpg status;
};

struct t_enemy
{
    char* icon;
    int x, y;
    t_enemy *next;
    t_enemy *prev;
    t_rpg status;
};

t_mage init_mage(int row, int col);

t_enemy *init_enemies(int row, int col, t_enemy *enemy);

void show_map(t_mage* mage, t_enemy *enemy);

void print_status(t_mage* mage, int col);

void move_character(int ch, t_mage* mage);

void move_enemy(t_enemy *enemy, t_mage* mage);

void detect_collision(t_enemy *enemy, t_mage* mage);

int game_is_over(t_enemy *enemy, t_mage* mage);

void end_game(int* status,int *x,int *y);

#endif