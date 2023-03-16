#include "character.h"

t_mage init_mage(int row, int col){
    t_mage aux;

    aux.x = row;
    aux.y = col;
    aux.icon = MAGE;

    return aux;
}