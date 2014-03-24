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
 * File:   menus.h
 * Author: jacques Deschênes
 * Description: display 1 level text menu on screen, use paddle as input device.
 * Created on 24 mars 2014, 13:41
 */

#ifndef MENUS_H
#define	MENUS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <string.h>
#include "text_console/text_console.h"
#include "Hardware/controllers/SNES/snes_paddle.h"
#include "TVout/TVout.h"
#include "graphics/graphics.h"

    typedef struct menu_item{
       const char *text; // item caption
       int id;  // item id
       struct menu_item *next; // next item.
    }menu_item_t;

    typedef struct menu{
       const char *title;
       int items; // number of items
       menu_item_t *first; // first menu item
    }menu_t;

    /* menu_t *create_menu()
     * Description: create a new menu.
     * Arguments:
     *      - title  menu title caption
     *  return pointer to that menu or NULL if failed.
     */
    menu_t *create_menu(const char *title);

    /* menu_item_t* add_menu_item(const char *text, int id, int menuId)
     * Description: create a new menu item and add it to menu
     * Arguments:
     *      - *text  item caption text
     *      - id   unique identifier for this item
     *      - *menu pointer to parent menu
     *  return pointer to menu item or NULL if failed.
     */
    menu_item_t* add_menu_item(const char *text, int id, menu_t *menu);

    /* int run_menu(menu_t *menu, int x, int y);
     * Description: display menu and wait for selection.
     * Arguments:
     *      - *menu pointer  menu to display
     *      - x  text console column coordinate of menu title
     *      - y  text console line coordinate of menu title
     *      - paddle that control menu.
     * return id of selected item
     */
    int run_menu(menu_t *menu, int x, int y, int paddle);

    /* void destroy_menu(menu_t menu)
     * Description: destroy menu and all items in it.
     * Arguments:
     *      - *menu  pointer to menu
     */
    void destroy_menu(menu_t *menu);

#ifdef	__cplusplus
}
#endif

#endif	/* MENUS_H */

