/************************************************************/
/*********** Author		: Ahmed Mohamed Badra	*************/
/*********** Date		: 8/6/2022				*************/
/*********** Version	: V01					*************/
/************************************************************/
#include "main.h"

/**********************************FORWARD DECLARATION*****************************/
void setup_io_configs(void);

/********************************* OS TASKS ***************************************/
void toggleLed1(void){
	while(TRUE){
		GPIO_TogglePin('A', P0);
		BARTOS_delayTask(500);
	}
}

void toggleLed2(void){
	while(TRUE){
		GPIO_TogglePin('A', P1);
		BARTOS_delayTask(2000);
	}
}

void toggleLed3(void){
	while(TRUE){
		GPIO_TogglePin('A', P2);
		BARTOS_delayTask(5000);
	}
}

/***************************************** ENTRY POINT ***************************/
int main(void) {
	setup_io_configs();
	BARTOS_createTask(toggleLed1, 2);
	BARTOS_createTask(toggleLed2, 2);
	BARTOS_createTask(toggleLed3, 2);
	while (1) {

		/* start the rtos */
		BARTOS_start();
	}
	return 0;
}

/**********************************SETUP FUNCTIONS**********************************/
void setup_io_configs(void){
	/* setup I/O configs */
	GPIO_Init('A', P0, OUTPUT, PUSH_PULL, NO_PULLING);
	GPIO_Init('A', P1, OUTPUT, PUSH_PULL, NO_PULLING);
	GPIO_Init('A', P2, OUTPUT, PUSH_PULL, NO_PULLING);
}
