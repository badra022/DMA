/************************************************************/
/*********** Author		: Ahmed Mohamed Badra	*************/
/*********** Date		: 7/6/2022				*************/
/*********** Version	: V01					*************/
/************************************************************/
#include "main.h"



/***************************************Global variables*******************************************/
u8 dutyCycle = 0;
u8 average_temperature = 0;

/**************************************Forward declaration******************************************/
void pid_controller_500ms(void);
void setup_tc72_configs(void);
void setup_pwm_configs(void);
void pid_controller_accept(u8 data);
void setup_tc72_manageData_task_50ms(void);
void setup_pid_controller_task_500ms(void);

/****************************************Entry Point*******************************************/
int main(void) {
	RCC_initSystemClock();
	setup_tc72_configs();
	setup_pwm_configs();
	setup_tc72_manageData_task_50ms();
	setup_pid_controller_task_500ms();

	while (1) {

	}
	return 0;
}





/**************************************Application setup fucntions************************************/
void setup_tc72_configs(void){
	/* init TC72 device that is based on the SPI1 peripheral */
	TC72_init();

	/* setting MISO, MOSI and CLK pins as alternate function for SPI usage */
	GPIO_Init('A', P5, ALTERNATE_FUN, PUSH_PULL, NO_PULLING);
	GPIO_Init('A', P6, ALTERNATE_FUN, PUSH_PULL, NO_PULLING);
	GPIO_Init('A', P7, ALTERNATE_FUN, PUSH_PULL, NO_PULLING);
	GPIO_setAlternateFunction('A', P5, AF5);
	GPIO_setAlternateFunction('A', P6, AF5);
	GPIO_setAlternateFunction('A', P7, AF5);
}

void setup_tc72_manageData_task_50ms(void){
	/* enable TIM clock */
	RCC_voidEnableClock(RCC_APB1, _TIM2_RCC_ID);
	/* setup the TIM2 configs */
	TIM_voidInit(TIM2, DOWNCOUNTING, RCC_u32GetSystemClock() / 20);		// 50 ms periodic
	/* enable TIM2 NVIC interrupt */
	NVIC_voidEnableInterrupt(_TIM2_VECTOR_IRQ);
	/* set the callback function that will be called inside the interrupt */
	TIM_voidSetCallBackFunction(TIM2, TC72_manageData);
	/* start TIM2 */
	TIM_voidStartTimer(TIM2);
}

void setup_pid_controller_task_500ms(void){
	/* enable TIM clock */
	RCC_voidEnableClock(RCC_APB1, _TIM3_RCC_ID);
	/* setup the TIM3 configs */
	TIM_voidInit(TIM3, DOWNCOUNTING, RCC_u32GetSystemClock() / 2);		// 500 ms periodic
	/* enable TIM3 NVIC interrupt */
	NVIC_voidEnableInterrupt(_TIM3_VECTOR_IRQ);
	/* set the callback function that will be called inside the interrupt */
	TIM_voidSetCallBackFunction(TIM3, pid_controller_500ms);
	/* start TIM3 */
	TIM_voidStartTimer(TIM3);

	/* subscribe to TC72 average temperature data */
	TC72_subscribe(pid_controller_accept);
}

void setup_pwm_configs(void){

	RCC_voidEnableClock(RCC_APB1, _TIM3_RCC_ID);
	PWM_INIT(TIM3, 3, 1, dutyCycle, RCC_u32GetSystemClock() / 100);		// 100HZ pwm output on TIM3_CH3 with preset duty cycle
	GPIO_Init('B', P0, ALTERNATE_FUN, PUSH_PULL, NO_PULLING);
	GPIO_setAlternateFunction('B', P0, AF2);
	PWM_START_TIMER(TIM3);				// start pwm
}

void pid_controller_accept(u8 data){
	average_temperature = data;
}

void pid_controller_500ms(void){
	static u32 err_integrated = 0;

	if(average_temperature <= 30){
		s8 err = 30 - average_temperature;
		err_integrated += err;
		u8 signal = (u8)((0.1 * err + 0.01 * err_integrated) * 100);
		if(signal >= 73){			// if reached max
			PWM_ChangeDutycycle(TIM3, 3, 73);
		}
		else{
			PWM_ChangeDutycycle(TIM3, 3, signal);
		}
	}
	else{
		err_integrated = 0;
		PWM_ChangeDutycycle(TIM3, 3, 0);		// heater off
	}
}
