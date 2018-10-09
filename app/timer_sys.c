/**************************************************************************
*
* Copyright (C) 2011 Steve Karg <skarg@users.sourceforge.net>
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
* Module Description:
* Generate a periodic timer tick for use by generic timers in the code.
*
*************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include "hardware.h"
#include "timer.h"
#include "debug.h"
#include "led.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/* counter for the various timers */
static volatile uint32_t Millisecond_Counter;
extern xQueueHandle    led_queue_hdl;

/*************************************************************************
* Description: Activate the LED
* Returns: nothing
* Notes: none
**************************************************************************/
static void timer_debug_on(
    void)
{
    //GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_SET);
}

/*************************************************************************
* Description: Activate the LED
* Returns: nothing
* Notes: none
**************************************************************************/
static void timer_debug_off(
    void)
{
    //GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_RESET);
}

/*************************************************************************
* Description: Toggle the state of the setup LED
* Returns: none
* Notes: none
*************************************************************************/
void timer_debug_toggle(
    void)
{
    static bool state = false;

    if (state) {
        timer_debug_off();
        state = false;
    } else {
        timer_debug_on();
        state = true;
    }
}

/*************************************************************************
* Description: returns the current millisecond count
* Returns: none
* Notes: none
*************************************************************************/
uint32_t timer_milliseconds(
    void)
{
    return Millisecond_Counter;
}

uint8_t timer_milliseconds_byte(
    void)
{
    return Millisecond_Counter;
}

/*************************************************************************
* Description: Timer setup for 1 millisecond timer
* Returns: none
* Notes: peripheral frequency defined in hardware.h
*************************************************************************/
void timer_init(
    void)
{
    

}

void vApplicationTickHook(void)
{
	Millisecond_Counter++;
	if(Millisecond_Counter%400==0){
		led_event_t event = LED_EVENT_LED_RUN;
		xQueueSendFromISR(led_queue_hdl,&event,0);
	}
}
