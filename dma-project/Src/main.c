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

u32 arr1[100] = {4, 5, 5, 8, 7, 9, 9, 6};		/* 4 5 5 8 7 9 9 6 0000. */
u32 arr2[100] = {0};

void DMA2_Stream0_IRQHandler(void){
	for(u8 i = 0; i < 8; i++){
		if(arr1[i] == arr2[i]){
			GPIO_WritePin('A', i, HIGH);
		}
	}
}

void dma_stream0_init(void){
	streamCofig_dtype stream0_config;

	stream0_config.dest_address 						= (u32)arr2;
	stream0_config.src_address 							= (u32)arr1;
	stream0_config.circular_mode 						= DISABLE;
	stream0_config.channel_number 						= 0;
	stream0_config.burst.memory_beats 					= SINGLE_TRANSFER;
	stream0_config.burst.peripheral_beats 				= SINGLE_TRANSFER;
	stream0_config.direct_mode 							= DIRECT_MODE_DISABLED;
	stream0_config.fifo_threshold 						= FULL;
	stream0_config.flow_controller 						= DMA_FLOW_CONTROLLER;
	stream0_config.memory_ptr_mode 						= INCREMENT;
	stream0_config.peripheral_ptr_mode 					= INCREMENT;
	stream0_config.memory_size 							= FOUR_BYTES;
	stream0_config.peripheral_size 						= FOUR_BYTES;
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
	DMA_voidConfigureStream(DMA2, 0, &stream0_config);
	NVIC_voidEnableInterrupt(_DMA2_STREAM2_VECTOR_IRQ);
	DMA_voidStartTransfer(DMA2, 0);
}


int main(void) {
	GPIO_Init('A', P0, OUTPUT, PUSH_PULL, NO_PULLING);
	GPIO_Init('A', P1, OUTPUT, PUSH_PULL, NO_PULLING);
	GPIO_Init('A', P2, OUTPUT, PUSH_PULL, NO_PULLING);
	GPIO_Init('A', P3, OUTPUT, PUSH_PULL, NO_PULLING);
	GPIO_Init('A', P4, OUTPUT, PUSH_PULL, NO_PULLING);
	GPIO_Init('A', P5, OUTPUT, PUSH_PULL, NO_PULLING);
	GPIO_Init('A', P6, OUTPUT, PUSH_PULL, NO_PULLING);
	GPIO_Init('A', P7, OUTPUT, PUSH_PULL, NO_PULLING);

	dma_stream0_init();



	while (1) {

	}
	return 0;
}
