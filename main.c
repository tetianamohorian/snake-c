#include "world.h"
#include <stdlib.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "snake.h"


// This file contains functions for drawing the the game and changing the state

// Start is called one in the beginning
void* init_game(){
    // Allocate memory for the state
    struct state* st = calloc(1,(sizeof(struct state)));
    return st;
}

// The first event
// Initialize game state
// - borders
// - snake position
// - food position
void init_snake(struct event* world, struct state* st)
{
    int cy = world->height/2;
    int cx = world->width/2 - 5;
    for (int i = 0; i < 5; i++){
        st->snake = add_snake(st->snake,cx + i ,cy);
    }

    int h = world->height;
    int w = world->width;
    for (int i = 0; i < 5; i++){
        st->foodx[i] = rand() % w;
        st->foody[i] = rand() % h;
    }
    // Initial game vector
    st->sx = 1;
    st->sy = 0;
}

// Step is called in a loop once in interval.
// It should modify the state and draw it.
int world_event(struct event* w,void* game){
    // Get state pointer
    struct state* st = game;
    if (w->type == EVENT_START){
        // Called on beginning
        init_snake(w,st);
    }
    // Called on key press
    else if (w->type == EVENT_KEY){
        int key = w->key;
        // Modifies vector of snake movement
        if (key == KEY_RIGHT){
           st->sx = 1;
           st->sy = 0;
        }
        else if (key == KEY_LEFT){
            st->sx = -1;
            st->sy = 0;
        }
        else if (key == KEY_DOWN){
            st->sx = 0;
            st->sy = 1;
        }
        else if (key == KEY_UP){
            st->sx = 0;
            st->sy = -1;
        }
    }
    // Called on esc key
    else if (w->type == EVENT_ESC){
            // Non zero means finish the loop and stop the game.
            return 1;
    }
    // Called on interval timeout
    else if (w->type == EVENT_TIMEOUT){
        clear_screen();
        // Copy screen size
        st->width = w->width;
        st->height = w->height;
        // Change game state
        int r = step_state(st);
        char ms[200];
       // sprintf(ms,"r %d\n",r);
        set_message(ms,9,9);
	start_color();
    	init_pair(1, COLOR_BLUE, COLOR_GREEN);
        // Draw snake
        struct snake* sn = st->snake;

	clear_screen();
	int color_pair = 1;
        while (sn != NULL)
        {	   	
//	   attron(COLOR_PAIR(1));
	    	
   	   set_color_cell('O',sn->x,sn->y,COLOR_RED + color_pair, COLOR_BLACK);
	
  	   attroff(COLOR_PAIR(1));

    	   color_pair++;
	
	   
    	   if(color_pair > 7) 
	   {
        	color_pair = 1;
    	   }
           
            sn = sn->next;
        }
        // Draw food
        for (int i = 0 ; i < FOOD_COUNT; i++){
            if (st->foodx[i] >= 0 && st->foody[i] >= 0){
                set_color_cell('*',st->foodx[i],st->foody[i], COLOR_RED,COLOR_BLACK);
            }
        }

        // Stop the game

	int yMax, xMax;
    	getmaxyx(stdscr, yMax, xMax);

        if (r)
	{
	    clear_screen();
		
	    if(r == END_FOOD)
	    {
		mvprintw(20, (xMax-strlen("Congratulation! You won!"))/2, "Congratulation! You won!");	
	    }
	    else
	    {
		mvprintw(20, (xMax-strlen("Ooh! You lose!"))/2, "Ooh! You lose!");
	    }

	     mvprintw(21, (xMax-strlen("Do you want to play again?(yes - 1, no - 0)"))/2, "Do you want to play again?(yes - 1, no - 0)");
            // char message[] = "Koniec";
	
            // set_message(message,10,10);
	    
//	    clear_screen();
	    //clear_screen();	    
//initscr();
	    
	    //mvprintw(20, (xMax-strlen("Koniec"))/2, "Koniec");
	    //mvprintw(21, (xMax-strlen("Do you want to play again?(yes - 1, no - 0)"))/2, "Do you want to play again?(yes - 1, no - 0)");
//	    noecho();	
	    int ch = 0;


 	    do
            {
                ch = getch() - '0';
            }
    	    while (ch < 0 || ch > 1);

		switch(ch)
		{
	           case 1:
		   {
//			clear_screen();
//			initscr();
			endwin();
			start_world(init_game,world_event,free);
		   }
            	   break;
		   case 0 :
			flushinp();
			endwin();
			exit(0);
				
		   break;			
		}	
	    }		   		
	    //set_message(message,10,10);
//	    getch();
//	    timeout(5000);
//	    endwin();
//	    exit(0);
	    	    
	    return 0;	    
        }
    return 0;
}


int main(int argc, char** argv)
{
    initscr();
    noecho();    
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    
    mvprintw(10, (xMax-strlen("||||||  ||||    |||      |||      |||  ||  |||||| "))/2, "||||||  ||||    |||      |||      |||  ||  ||||||");
    attron(COLOR_PAIR(1));
    mvprintw(11, (xMax-strlen("|||     ||| ||| |||     || ||     ||| |||  |||    "))/2, "|||     ||| ||| |||     || ||     ||| |||  |||");
    attron(COLOR_PAIR(1));    
    mvprintw(12, (xMax-strlen("||||||  |||    ||||    |||||||    |||||    |||||| "))/2, "||||||  |||    ||||    |||||||    |||||    ||||||");
    attron(COLOR_PAIR(1));    
    mvprintw(13, (xMax-strlen("   |||  |||     |||   |||   |||   ||| |||  |||    "))/2, "   |||  |||     |||   |||   |||   ||| |||  |||");
    attron(COLOR_PAIR(1));    
    mvprintw(14, (xMax-strlen("||||||  |||     |||  |||     |||  ||| |||  |||||| "))/2, "||||||  |||     |||  |||     |||  ||| |||  ||||||");


    mvprintw(yMax/2+5, (xMax-strlen("Game menu"))/2, "Game menu");
    mvprintw(yMax/2+10, (xMax-strlen("1. Start new game"))/2,"1. Start new game");
    mvprintw(yMax/2+12, (xMax-strlen("2. Exit"))/2, "2. Exit"); 

  attroff(COLOR_PAIR(1));
  attroff(COLOR_PAIR(1));
  attroff(COLOR_PAIR(1)); 
  attroff(COLOR_PAIR(1));
  attroff(COLOR_PAIR(1));   

     
//    clear_screen();    
  
    int choice = 0;
    do 
    {
        choice = getch() - '0';
    } 
    while (choice < 1 || choice > 2);

    
    switch (choice) 
    {
        case 1:
	    endwin();
	    clear();	    
            start_world(init_game,world_event,free);
            break;
        case 2:
            endwin();
            break;
    }

        
    //start_world(init_game,world_event,free);
  	   
    struct snake* snake;
      
    return 0;
} 
