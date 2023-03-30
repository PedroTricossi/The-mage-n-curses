#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "character.h"

int main(){
    t_mage mage;
    t_enemy *enemies = NULL;
    int row, col, ch;
    int centerx, centery;
    int endgame = 0;

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

    for(int i=0;i<rand() % 10;i++)
      enemies = init_enemies(row, col, enemies);

    show_map(&mage, enemies);

    print_status(&mage, centery);

    refresh();	

    while((ch = getch()) != KEY_F(1) && (endgame == 0)){
      move_character(ch, &mage);
      move_enemy(enemies, &mage);
      detect_collision(enemies,&mage);

      endgame = game_is_over(enemies, &mage);

      show_map(&mage, enemies);
      print_status(&mage, centery);
    }

    end_game(&endgame, &centerx, &centery);
    
    getch();
	
  return 0;
}
