#include <ncurses.h>

int main(){
    WINDOW *my_win;
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

    mvprintw(centerx, centery, "|0|");

    refresh();	


    
    while((ch = getch()) != KEY_F(1)){
        
        switch(ch){
            case KEY_LEFT:
                clear();
                // printw("entrei");
                centery--;
                mvprintw(centerx, centery, "|0|");
                break;
            
            case KEY_UP:
                clear();
                // printw("entrei");
                centerx--;
                mvprintw(centerx, centery, "|0|");
                break;

            case KEY_DOWN:
                clear();
                // printw("entrei");
                centerx++;
                mvprintw(centerx, centery, "|0|");
                break;
            
            case KEY_RIGHT:
                clear();
                // printw("entrei");
                centery++;
                mvprintw(centerx, centery, "|0|");
                break;
        }

        refresh();
    }
    
    refresh();

    getch();			
	

  return 0;
}
