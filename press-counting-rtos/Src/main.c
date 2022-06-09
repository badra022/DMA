/************************************************************/
/*********** Author		: Ahmed Mohamed Badra	*************/
/*********** Date		: 8/6/2022				*************/
/*********** Version	: V01					*************/
/************************************************************/
#include "main.h"

/**********************************GLOBAL VARIABLES********************************/
semphrHandler_dtype semphr1 = NULL;
u8 inc_pressed = FALSE;
u8 dec_pressed = FALSE;
u8 curr_count = 0;


/**********************************FORWARD DECLARATION*****************************/
void setup_io_configs(void);

/********************************* OS TASKS ***************************************/

void pollButtons(void){
	while(1){
		if(BARTOS_semaphoreGet(semphr1, 0) == TRUE){
			do{
				inc_pressed = GPIO_ReadPin('A', P13);
				dec_pressed = GPIO_ReadPin('A', P14);
			}while(inc_pressed == FALSE && dec_pressed == FALSE);
			BARTOS_semaphorePut(semphr1);
		}
		else{
			/* There's an error getting the semaphore */
		}
	}
}

void svnSegmentDisplayTask(void){
	while(1){
		if(BARTOS_semaphoreGet(semphr1, 10) == TRUE){
			/* do some thing else */
			if(inc_pressed){
				curr_count++;
			}
			if(dec_pressed){
				curr_count--;
			}
			BARTOS_semaphorePut(semphr1);
		}
		else{
			/* couldn't acquire the semaphore for 10 ms, we do display the curr count and try acquiring the semaphore again */
			svn_segment_write(curr_count);
		}
	}
}



int main(void) {
	setup_io_configs();
	semphr1 = BARTOS_createBinarySemaphore();
	BARTOS_createTask(pollButtons, 2);
	BARTOS_createTask(svnSegmentDisplayTask, 2);
	svn_segment_write(curr_count);
	while (1) {

		/* start the rtos */
		BARTOS_start();
	}
	return 0;
}


/**********************************SETUP FUNCTIONS**********************************/
void setup_io_configs(void){
	/* setup I/O configs */
	GPIO_Init('A', P13, INPUT, PUSH_PULL, PULL_DOWN);
	GPIO_Init('A', P14, INPUT, PUSH_PULL, PULL_DOWN);
	svn_segment_init();		/* PA0...PA7 */
}
