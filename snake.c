#include "snake.h"
#include <stdlib.h>
struct snake* add_snake(struct snake* snake,int x,int y)
{
 	struct snake* head = calloc(1,sizeof(struct snake)); //vytvorí sa nový hadí prvok a pridelí sa mu dynamická pamäť
	
    //Nepodarilo calloc
	if(head == NULL)
	{
	   return NULL;
	}

    //Súradnice nového prvku
	head->x = x;
	head->y = y;

    // Smernik ďalšieho nového prvku hada sa nastaví na predchádzajúcu hlavu hada
	head->next = snake;

	return head;   
}

struct snake* remove_snake(struct snake* snake)
{
	if(snake == NULL || snake->next == NULL)
        {
           return NULL;
        }

    //Smernik na aktuálny prvok hada rovnajúci sa hlavičke;
	struct snake* this = snake;

	// sa používa na nájdenie prvku pred posledným prvkom hada
	while(this->next->next != NULL)
	{
		this = this->next;
	}

	free(this->next); //posledný prvok hada sa uvoľní pomocou funkcie free (sa uvoľní dinamicku pamät')
	this->next = NULL;

	return snake;		 	  
}

void free_snake(struct snake* sn)
{
    struct snake* head = calloc(1,sizeof(struct snake)); // Dynamické prideľovanie pamäte 

    struct snake* this = head;

    while (this != NULL) 
    {
        struct snake* next = this->next;
        free(this); // uvoľnenie pamäťi
        this = next;
    }

    head = NULL; 
}

int is_snake(struct snake* snake,int x,int y)
{
    
    int k = 0;
    
    if(snake == NULL || snake->next == NULL)
    {
	k = 0;
	return k;
    }
		
    struct snake *this = snake;
    
    // či súradnice tohto uzla zodpovedajú prenášaným súradniciam x a y
    while(this != NULL)
    {
        if(this->x == x && this->y == y)
        {
           k = 1;           return k;

        }
        
        this = this->next;
        
   }
	 
   return 0;
 
}

int step_state(struct state* st)
{
    int nx = (st->snake->x + st->sx);
    int ny = (st->snake->y + st->sy);

//     add_snake(st->snake,nx,ny);
  //   remove_snake(st->snake);
    int i = 0, flag = 0, food = 0;


    // či sú prenášané súradnice x a y na hadovi
    if (is_snake(st->snake, nx, ny))
    {
        return END_SNAKE; 
    }


    while (i < FOOD_COUNT)
    {
        if(st->foodx[i] >= 0)
        {
            if (st->foodx[i] == nx && st->foody[i] == ny) //zodpovedajúce súradnice?
            {
                st->foodx[i] = -1; 
                st->foody[i] = -1;

                st->snake = add_snake(st->snake, nx, ny);

                flag = 1;

                break;
            }
        }

        i++;
    }

    if (flag == 0)
    {
        i = 0;

        while(i < FOOD_COUNT)
        {
            if (st->foodx[i] >= 0)
            {
                food = 1;
                break;
            }

            i++;
        }

        if (food == 0)
        {
            return END_FOOD;
        }

        st->snake = remove_snake(st->snake);
        st->snake = add_snake(st->snake, nx, ny);
    }

    if(nx <= 0 || nx >= st->width-1 || ny <= 0 || ny >= st->height-1)
    {
        return END_WALL;
    }

    return END_CONTINUE;
} 
