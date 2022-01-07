/************************************************************/
/*********** Author		: Ahmed Mohamed Badra	*************/
/*********** Date		: 4/1/2021				*************/
/*********** Version	: V01					*************/
/************************************************************/
#include "STD_types.h"
#include "MATH_macros.h"

#include "gpio.h"
#include "nvic.h"
#include "dma.h"
#include "uart.h"

char str1[100] = "hello world!";
char str2[100] = "";

void DMA2_Stream0_IRQHandler(void){
	USART1_voidSendString((u8*)str2);
}

void init_uart1_comm(void){

	/* setup RX, Tx pins */
	GPIO_Init('A', P9, ALTERNATE_FUN, PUSH_PULL, NO_PULLING);
	GPIO_setAlternateFunction('A', P9, AF7);

	/* create configurations instance for USART1 */

	uartConfig_dtype Uart1_config;

	Uart1_config.parity.enable = 					DISABLE;
	Uart1_config.parity.type = 						EVEN;
	Uart1_config.over_eight = 						DISABLE;
	Uart1_config.clock_phase = 						FIRST_CLOCK;
	Uart1_config.clock_polarity = 					STEADY_LOW;
	Uart1_config.clock_synch = 						DISABLE;
	Uart1_config.parity_error_interrupt = 			DISABLE;
	Uart1_config.receive_complete_interrupt = 		DISABLE;
	Uart1_config.receiver =							DISABLE;
	Uart1_config.stopBit = 							HALF_STOP_BIT;
	Uart1_config.word_length = 						EIGHT;
	Uart1_config.transmission_complete_interrupt = 	DISABLE;
	Uart1_config.transmitter = 						ENABLE;

	/* initiate the USART1 */
	USART1_voidInit(&Uart1_config);
}


void dma_stream0_init(void){

	/* create configurations instance for stream x */
	streamCofig_dtype stream0_config;

	stream0_config.dest_address 						= (u32)str2;
	stream0_config.src_address 							= (u32)str1;
	stream0_config.circular_mode 						= DISABLE;
	stream0_config.channel_number 						= 0;
	stream0_config.burst.memory_beats 					= SINGLE_TRANSFER;
	stream0_config.burst.peripheral_beats 				= SINGLE_TRANSFER;
	stream0_config.direct_mode 							= DIRECT_MODE_DISABLED;
	stream0_config.fifo_threshold 						= FULL;
	stream0_config.flow_controller 						= DMA_FLOW_CONTROLLER;
	stream0_config.memory_ptr_mode 						= INCREMENT;
	stream0_config.peripheral_ptr_mode 					= INCREMENT;
	stream0_config.memory_size 							= ONE_BYTE;
	stream0_config.peripheral_size 						= ONE_BYTE;
	stream0_config.number_of_transactions 				= 100;
	stream0_config.stream_priority 						= VERY_HIGH_PRIORITY;
	stream0_config.transfer_direction 					= MEMORY_TO_MEMORY;
	stream0_config.transfer_error_interrupt_enable 		= DISABLE;
	stream0_config.direct_mode_error_interrupt_enable 	= DISABLE;
	stream0_config.fifo_error_interrupt_enable 			= DISABLE;
	stream0_config.half_transfer_interrupt_enable 		= DISABLE;
	stream0_config.transfer_error_interrupt_enable		= DISABLE;
	stream0_config.transfer_interrupt_enable 			= ENABLE;

	DMA_voidInit(DMA2);
	ErrorStatus state = DMA_voidConfigureStream(DMA2, 0, &stream0_config);

	if(state == ERROR){
		/* WRONG CONFIGURATIONS, rechoose the configurations */
		/* set a warning LED for debugging */
		GPIO_Init('A', P0, OUTPUT, PUSH_PULL, NO_PULLING);
		GPIO_WritePin('A', P0, HIGH);
	}

	/* enable NVIC inturrupt for the stream */
	NVIC_voidEnableInterrupt(_DMA2_STREAM2_VECTOR_IRQ);

	/* start transfer operation in the stream */
	DMA_voidStartTransfer(DMA2, 0);
}


int main(void) {
	/* setup UART1 */
	init_uart1_comm();

	/* setup DMA2_STREAM2 and begin transmission */
	dma_stream0_init();

	while (1) {

	}
	return 0;
}
