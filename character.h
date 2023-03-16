#ifndef __CHARACTER__
#define __CHARACTER__

#define MAGE "|0|"

typedef struct
{
    char* icon;
    int x, y;
}t_mage;

t_mage init_mage(int row, int col);


#endif