/*
 * main.c
 *
 *  Created on: 02-Jun-2016
 *      Author: sreev
 */

#include "msp430.h"


#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "portmacro.h"
#include "timers.h"

#define LED_PORT_OUT P1OUT
#define LED_1        BIT0

static void vRegTestTask( void *pvParameters );


void main ( void )
{
	WDTCTL = WDTPW + WDTHOLD;		// Stop watchdog timer
	P6DIR |= BIT5;					// Set P1.0 to output direction
	P6OUT ^= BIT5;				// Toggle P1.0 using exclusive-OR

	xTaskCreate( vRegTestTask, "test", configMINIMAL_STACK_SIZE, NULL, 0, NULL );

	/* Start the scheduler. */
	vTaskStartScheduler();
	while(1);
}

static void vRegTestTask( void *pvParameters )
{
	while(1)
	{
		vTaskDelay(1000);
		P6OUT ^= BIT5;				// Toggle P1.0 using exclusive-OR
	}
}


void vApplicationTickHook( void )
{
static unsigned long ulCounter = 0;

	/* Is it time to toggle the LED again? */
	ulCounter++;

	/* Just periodically toggle an LED to show that the tick interrupt is
	running.  Note that this access LED_PORT_OUT in a non-atomic way, so tasks
	that access the same port must do so from a critical section. */
	if( ( ulCounter & 0xff ) == 0 )
	{
		if( ( LED_PORT_OUT & LED_1 ) == 0 )
		{
			LED_PORT_OUT |= LED_1;
		}
		else
		{
			LED_PORT_OUT &= ~LED_1;
		}
	}
}
/*-----------------------------------------------------------*/

/* The MSP430X port uses this callback function to configure its tick interrupt.
This allows the application to choose the tick interrupt source.
configTICK_VECTOR must also be set in FreeRTOSConfig.h to the correct
interrupt vector for the chosen tick interrupt source.  This implementation of
vApplicationSetupTimerInterrupt() generates the tick from timer A0, so in this
case configTICK_VECTOR is set to TIMER0_A0_VECTOR. */
void vApplicationSetupTimerInterrupt( void )
{
const unsigned short usACLK_Frequency_Hz = 32768;

	/* Ensure the timer is stopped. */
	TA0CTL = 0;

	/* Run the timer from the ACLK. */
	TA0CTL = TASSEL_1;

	/* Clear everything to start with. */
	TA0CTL |= TACLR;

	/* Set the compare match value according to the tick rate we want. */
	TA0CCR0 = usACLK_Frequency_Hz / configTICK_RATE_HZ;

	/* Enable the interrupts. */
	TA0CCTL0 = CCIE;

	/* Start up clean. */
	TA0CTL |= TACLR;

	/* Up mode. */
	TA0CTL |= MC_1;
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* Called on each iteration of the idle task.  In this case the idle task
	just enters a low(ish) power mode. */
	__bis_SR_register( LPM1_bits + GIE );
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues or
	semaphores. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pxTask;
	( void ) pcTaskName;

	/* Run time stack overflow checking is performed if
	configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/



