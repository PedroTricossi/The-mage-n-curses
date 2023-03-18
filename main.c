#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "character.h"

int main(){
    WINDOW *my_win = NULL;
    t_mage mage;
    t_enemy *enemies = NULL;
    int row, col, ch;
    int centerx, centery;

    initscr();			/* Inicia o modo curses */
    cbreak();		    	/* Buffer de linha desativado, passe tudo para mim  */
    keypad(stdscr, TRUE);		/* Eu preciso daquele F1 bacana	*/
    noecho();
    curs_set( false );
    srand(time(NULL));
    getmaxyx(stdscr,row,col);

    centerx = row/2;
    centery = (col/2)-1;

    mage = init_mage(centerx, centery);

    enemies = init_enemies(row, col, enemies);

    show_map(&mage, enemies);

    print_status(&mage, centery);

    refresh();	

    while((ch = getch()) != KEY_F(1)){
      move_character(ch, &mage);
      move_enemy(enemies, &mage);
      detect_collision(enemies,&mage);

      show_map(&mage, enemies);
      print_status(&mage, centery);
    }
    
    getch();
	
  return 0;
}
