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
 * File:   timers.h
 * Author: jacques Deschênes
 * Description:  timers management module.
 * Created on 22 février 2014, 16:10
 */

#ifndef TIMERS_H
#define	TIMERS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "hardwareProfile.h"

#define MAX_TIMERS 8     // number of available timers
#define TIMER_SINGLE 0   // timer mode single shot
#define TIMER_REPEAT 1   // timer mode repeatable

    /* prototype function for timer callback*/
    typedef void *timer_handler_t(void);

    /* timers_init() initialise timers module
     *  parameters:
     *     ticks_per_second is the number of time
     *     the interrupt will be called
     *     the interrupt service routine is used to
     *     control timers and maintain a ticks counter.
     */
    void timers_init(unsigned ticks_per_second);

    /* create_timer() create a new timer
     * parameters:
     *     - delay is the timer period in multiple of
     *       of the basic timer periiod. (i.e. 1/ticks_per_second)
     *
     *     - repeat a timer maybe repeatable or single shot. Once a single shot
             as triggered it is stopped and must be restarted manually using "start_timer()
     *       this argument may have values TIMER_SINGLE. TIMER_REPEAT
     *
     *     - handler is the function that is called when the timer event is triggered.
     *  A timer is created suspended start_timer() must be call to start it.
     *  The function return the timer identifier or -1 if no timer available.
     *  This function can be called more than one time but ticks is reset to zero
     *  each time and timers are all destroyed.
     */
    int create_timer(unsigned delay, unsigned repeat, timer_handler_t *handler);

    /* stop_timer() suspend timer but keep it alive.
     * parameters:
     *      - timer_id  is the value returned by create_timer()
     */
    void stop_timer(int timer_id);

    /* start_timer() start a suspended timer.
     * parameters:
     *      timer_id is the value returned by create_timer() 
     */
    void start_timer(int timer_id);

    /* update_timer() update timer delay
     * parameters:
     *      timer_id is the value returned by create_timer()
     *      new_delay  new timer delay in basic timer units.
     */
    void update_timer(int timer_id, unsigned new_delay);

    /* destroy_timer() destroy a previously created timer
     * parameters:
     *      timer_id is the value returned by create_timer()
     */
    void destroy_timer(int timer_id);

    /* sys_ticks() return the number of ticks since module initialization */
    unsigned long sys_ticks();

#ifdef	__cplusplus
}
#endif

#endif	/* TIMERS_H */

