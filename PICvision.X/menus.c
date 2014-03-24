/*
* Copyright 2014, Jacques Deschênes
* This file is part of PICvision.
*
*     PICvision is free software: you can redistribute it and/or modify
*     it under the terms of the GNU General Public License as published by
*     the Free Software Foundation, either version 3 of the License, or
*     (at your option) any later version.
*
*     PICvision is distributed in the hope that it will be useful,
*     but WITHOUT ANY WARRANTY; without even the implied warranty of
*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*     GNU General Public License for more details.
*
*     You should have received a copy of the GNU General Public License
*     along with PICvision.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * File:   menus.c
 * Author: jacques Deschênes
 * Description: display text menu on screen, use paddle as input device.
 *            >>> use dynamic memory allocation, space must reserved for
 *            >>> heap in project properties
 * Created on 24 mars 2014, 13:41
 */

#include <stdlib.h>
#include "menus.h"

/* menu_t *create_menu()
 * Description: create a new menu.
 * Arguments:
 *      - *title  menu title text
 *  return pointer to that menu or NULL if failed.
 */
menu_t *create_menu(const char *title){
    menu_t *m;
    m=malloc(sizeof(menu_t));
    if (m){
        m->title=title;
        m->first=NULL;
        m->items=0;
    }
    return m;
}//f()

/* menu_item_t* add_menu_item(const char *text, int id, menut_t *menu)
 * Description: create a new menu item and add it to menu
 * Arguments:
 *      - text  item caption text
 *      - id   unique identifier for this item
 *      - *menu pointer to parent menu
 *  return pointer to item or NULL if failed.
 */
menu_item_t* add_menu_item(const char *text, int id, menu_t *menu){
    menu_item_t *item, *walk;
    item=malloc(sizeof(menu_item_t));
    if (item){
        item->id=id;
        item->text=text;
        item->next=NULL;
        if (!menu->first){
            menu->first=item;
            menu->items=1;
        }else{
            walk=menu->first;
            while (walk){
                if (!walk->next){
                    walk->next=item;
                    menu->items++;
                    break;
                }else{
                    walk=walk->next;
                }//if
            }//while
        }//if
    }//if
    return item;
}//f()

// display menu and hilite selected item
void display_menu(menu_t *menu,int x, int y, int selected){
    menu_item_t *walk;
    int count;

    count=0;
    set_curpos(x,y);
    invert_video();
    print(menu->title);
    normal_video();
    walk=menu->first;
    while (walk){
        set_curpos(x,y+2+count);
        if (count==selected){
            invert_video();
            print(walk->text);
            normal_video();
        }else{
            print(walk->text);
        }
        walk=walk->next;
        count++;
    }//while
}//f()


/* int run_menu(menu_t *menu, int x, int y, int pad);
 * Description: display menu and wait for selection.
 * Arguments:
 *      - *menu pointer  menu to display
 *      - x  text console column coordinate of menu title
 *      - y  text console line coordinate of menu title
 *      - paddle which gamepad control menu.
 * return id of selected item
 */
int run_menu(menu_t *menu, int x, int y, int paddle){
    int selected, loop;
    unsigned buttons;
    selected=0;
    loop=1;
    while (loop){
        display_menu(menu,x,y,selected);
        buttons=read_paddle(paddle);
        if ((buttons&SNES_UP)==SNES_UP){
            if (selected>0) selected--;
        }else if((buttons&SNES_DOWN)==SNES_DOWN){
            if (selected<(menu->items-1)) selected++;
        }else if ((buttons & SNES_SELECT)==SNES_SELECT){
            loop=0;
        }
        wait_n_frame(10);
    }

    int i;
    menu_item_t *walk;
    walk=menu->first;
    i=0;
    while(i<selected){
        walk=walk->next;
        i++;
    }
    return walk->id;
}//f()

// recursively free items list.
void free_item(menu_item_t *item){
    if (item->next) free_item(item->next);
    free(item);
}//f()

/* void destroy_menu(menu_t menu)
 * Description: destroy menu and all items in it.
 * Arguments:
 *      - *menu  pointer to menu
 */
void destroy_menu(menu_t *menu){
    free_item(menu->first);
    free(menu);
}//f()

