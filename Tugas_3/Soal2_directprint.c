/*
 * FreeRTOS Kernel V10.4.0
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

 /******************************************************************************
  * NOTE: Windows will not be running the FreeRTOS demo threads continuously, so
  * do not expect to get real time behaviour from the FreeRTOS Windows port, or
  * this demo application.  Also, the timing information in the FreeRTOS+Trace
  * logs have no meaningful units.  See the documentation page for the Windows
  * port for further information:
  * http://www.freertos.org/FreeRTOS-Windows-Simulator-Emulator-for-Visual-Studio-and-Eclipse-MingW.html
  *
  * NOTE 2:  This project provides two demo applications.  A simple blinky style
  * project, and a more comprehensive test and demo application.  The
  * mainCREATE_SIMPLE_BLINKY_DEMO_ONLY setting in main.c is used to select
  * between the two.  See the notes on using mainCREATE_SIMPLE_BLINKY_DEMO_ONLY
  * in main.c.  This file implements the simply blinky version.  Console output
  * is used in place of the normal LED toggling.
  *
  * NOTE 3:  This file only contains the source code that is specific to the
  * basic demo.  Generic functions, such FreeRTOS hook functions, are defined
  * in main.c.
  ******************************************************************************
  *
  * main_blinky() creates one queue and four tasks. It then starts the scheduler.
  *
  * The Queue Send Task 1, 2, and 3:
  * The queue send task is implemented by the prvQueueSendTask() functions in
  * this file.  It uses vTaskDelayUntil() to create a periodic task that sends
  * the value 100, 200, and 300 to the queue every 200, 900, and 1500 milliseconds 
  * (please read the notes above regarding the accuracy of timing under Windows).
  *
  *
  * Expected Behaviour:
  * - The queue send task writes to the queue every 200ms, 900ms, and 1500ms, 
  *   so every 200ms the queue receive task will output a message indicating 
  *   that data was received on the queue from the three queue send tasks.
  *
  * NOTE:  Console input and output relies on Windows system calls, which can
  * interfere with the execution of the FreeRTOS Windows port.  This demo only
  * uses Windows system call occasionally.  Heavier use of Windows system calls
  * can crash the port.
  */

/* Standard includes. */
#include <stdio.h>
#include <conio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/* Priorities at which the tasks are created. */
#define	mainQUEUE_SEND_TASK1_PRIORITY		( tskIDLE_PRIORITY + 1 )
#define	mainQUEUE_SEND_TASK2_PRIORITY		( tskIDLE_PRIORITY + 1 )
#define	mainQUEUE_SEND_TASK3_PRIORITY		( tskIDLE_PRIORITY + 1 )

// The rate at which data is sent to the queue.  The times are converted from
// milliseconds to ticks using the pdMS_TO_TICKS() macro. 
#define mainTASK1_SEND_FREQUENCY_MS			pdMS_TO_TICKS( 200UL )
#define mainTASK2_SEND_FREQUENCY_MS			pdMS_TO_TICKS( 900UL )
#define mainTASK3_SEND_FREQUENCY_MS			pdMS_TO_TICKS( 1500UL )

/*-----------------------------------------------------------*/

/*
  The tasks as described in the comments at the top of this file.
*/
static void prvQueueSendTask1(void* pvParameters);
static void prvQueueSendTask2(void* pvParameters);
static void prvQueueSendTask3(void* pvParameters);


/*** SEE THE COMMENTS AT THE TOP OF THIS FILE ***/
void main_blinky(void)
{
	xTaskCreate(prvQueueSendTask1, "TX1", configMINIMAL_STACK_SIZE, NULL, mainQUEUE_SEND_TASK1_PRIORITY, NULL);
	xTaskCreate(prvQueueSendTask2, "TX2", configMINIMAL_STACK_SIZE, NULL, mainQUEUE_SEND_TASK2_PRIORITY, NULL);
	xTaskCreate(prvQueueSendTask3, "TX3", configMINIMAL_STACK_SIZE, NULL, mainQUEUE_SEND_TASK3_PRIORITY, NULL);

	/* Start the tasks. */
	vTaskStartScheduler();

	/* If all is well, the scheduler will now be running, and the following
	line will never be reached.  If the following line does execute, then
	there was insufficient FreeRTOS heap memory available for the idle and/or
	timer tasks	to be created.  See the memory management section on the
	FreeRTOS web site for more details. */
	for (;; );
}

/*-----------------------------------------------------------*/

static void prvQueueSendTask1(void* pvParameters)
{
	TickType_t xNextWakeTime;
	const TickType_t xBlockTime = mainTASK1_SEND_FREQUENCY_MS;

	/* Prevent the compiler warning about the unused parameter. */
	(void)pvParameters;

	/* Initialise xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	for (;; )
	{
		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, pdMS_TO_TICKS() was used to
		convert a time specified in milliseconds into a time specified in ticks.
		While in the Blocked state this task will not consume any CPU time. */
		vTaskDelayUntil(&xNextWakeTime, xBlockTime);

		// print string
		printf("EL4121\r\n");
	}
}

/*-----------------------------------------------------------*/

static void prvQueueSendTask2(void* pvParameters)
{
	TickType_t xNextWakeTime;
	const TickType_t xBlockTime = mainTASK2_SEND_FREQUENCY_MS;

	/* Prevent the compiler warning about the unused parameter. */
	(void)pvParameters;

	/* Initialise xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	for (;; )
	{
		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, pdMS_TO_TICKS() was used to
		convert a time specified in milliseconds into a time specified in ticks.
		While in the Blocked state this task will not consume any CPU time. */
		vTaskDelayUntil(&xNextWakeTime, xBlockTime);

		// Print String
		printf("Perancangan Sistem Embedded 2020\r\n");
	}
}

/*-----------------------------------------------------------*/

static void prvQueueSendTask3(void* pvParameters)
{
	TickType_t xNextWakeTime;
	const TickType_t xBlockTime = mainTASK3_SEND_FREQUENCY_MS;

	/* Prevent the compiler warning about the unused parameter. */
	(void)pvParameters;

	/* Initialise xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	for (;; )
	{
		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, pdMS_TO_TICKS() was used to
		convert a time specified in milliseconds into a time specified in ticks.
		While in the Blocked state this task will not consume any CPU time. */
		vTaskDelayUntil(&xNextWakeTime, xBlockTime);

		//  Print String
		printf("Tugas #3 Pengenalan FreeRTOS\r\n");
	}
}

/*-----------------------------------------------------------*/