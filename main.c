#include <ncurses.h>
#include "character.h"

int main(){
    WINDOW *my_win;
    t_mage mage;
    int row,col, ch;
    int centerx, centery;

    initscr();			/* Inicia o modo curses */
    cbreak();		    	/* Buffer de linha desativado, passe tudo para mim  */
    keypad(stdscr, TRUE);		/* Eu preciso daquele F1 bacana	*/
    noecho();
    curs_set( false );
    getmaxyx(stdscr,row,col);

    centerx = row/2;
    centery = (col/2)-1;

    mage = init_mage(centerx, centery);

    mvprintw(mage.x, mage.y, "%s", mage.icon);

    refresh();	


    
    while((ch = getch()) != KEY_F(1)){
        
        switch(ch){
            case KEY_LEFT:
                clear();
                // printw("entrei");
                mage.y--;
                mvprintw(mage.x, mage.y, "%s", mage.icon);
                break;
            
            case KEY_UP:
                clear();
                // printw("entrei");
                mage.x--;
                mvprintw(mage.x, mage.y, "%s", mage.icon);
                break;

            case KEY_DOWN:
                clear();
                // printw("entrei");
                mage.x++;
                mvprintw(mage.x, mage.y, "%s", mage.icon);
                break;
            
            case KEY_RIGHT:
                clear();
                // printw("entrei");
                mage.y++;
                mvprintw(mage.x, mage.y, "%s", mage.icon);
                break;
        }

        refresh();
    }
    
    refresh();

    getch();			
	

  return 0;
}
