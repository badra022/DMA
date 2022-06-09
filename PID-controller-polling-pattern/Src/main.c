/************************************************************/
/*********** Author		: Ahmed Mohamed Badra	*************/
/*********** Date		: 7/6/2022				*************/
/*********** Version	: V01					*************/
/************************************************************/
#include "main.h"



/***************************************Global variables*******************************************/
u8 dutyCycle = 0;

/**************************************Forward declaration******************************************/
void pid_controller(u8 temperature);
void TC72_poller(void);
void setup_spi_configs(void);
void setup_pwm_configs(void);
void start_tc72_polling(void);

/****************************************Entry Point*******************************************/
int main(void) {
	RCC_initSystemClock();
	setup_spi_configs();
	setup_pwm_configs();
	start_tc72_polling();

	while (1) {

	}
	return 0;
}





/**************************************Application setup fucntions************************************/
void setup_spi_configs(void){
	SPI_VidInit();
	GPIO_Init('A', P5, ALTERNATE_FUN, PUSH_PULL, NO_PULLING);
	GPIO_Init('A', P6, ALTERNATE_FUN, PUSH_PULL, NO_PULLING);
	GPIO_Init('A', P7, ALTERNATE_FUN, PUSH_PULL, NO_PULLING);
	GPIO_setAlternateFunction('A', P5, AF5);
	GPIO_setAlternateFunction('A', P6, AF5);
	GPIO_setAlternateFunction('A', P7, AF5);
}

void start_tc72_polling(void){
	/* enable TIM clock */
	RCC_voidEnableClock(RCC_APB1, _TIM2_RCC_ID);
	/* setup the TIM2 configs */
	TIM_voidInit(TIM2, DOWNCOUNTING, RCC_u32GetSystemClock() / 1000);		// 1 ms periodic
	/* enable TIM2 NVIC interrupt */
	NVIC_voidEnableInterrupt(_TIM2_VECTOR_IRQ);
	/* set the callback function that will be called inside the interrupt */
	TIM_voidSetCallBackFunction(TIM2, TC72_Poll);

	TC72_SetPollingTime(500);		// 500 ms periodic polling
	/* start TIM2 */
	TIM_voidStartTimer(TIM2);
	TC72_StartPolling();
}

void setup_pwm_configs(void){

	RCC_voidEnableClock(RCC_APB1, _TIM3_RCC_ID);
	PWM_INIT(TIM3, 3, 1, dutyCycle, RCC_u32GetSystemClock() / 100);		// 100HZ pwm output on TIM3_CH3 with preset duty cycle
	GPIO_Init('B', P0, ALTERNATE_FUN, PUSH_PULL, NO_PULLING);
	GPIO_setAlternateFunction('B', P0, AF2);
	PWM_START_TIMER(TIM3);				// start pwm
}

void TC72_poller(void){
	u8 temperature = SPI1_VidSendDataU8(0);
	temperature = 10;
	pid_controller(temperature);
}

void pid_controller(u8 temperature){
	static u32 err_integrated = 0;

	if(temperature <= 30){
		s8 err = 30 - temperature;
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
