# coding for embedded

> This repository contains projects implemented in coding for embedded course at cairo university supervised by valeo egypt


## DMA array transfer

We implemented a full functional DMA Proxy driver to configure the peripheral and start transfer

```c
void DMA_voidInit(DMA_dtype* DMA_ptr);
```
This API starts the clock of the selected DMA peripheral.

```c
void DMA_voidStartTransfer(DMA_dtype* DMA_ptr, u8 stream_idx);
```
This API starts data transfer in the ```stream_idx``` selected in the DMA peripheral ```DMA_ptr``` selected

```c
ErrorStatus DMA_voidConfigureStream(DMA_dtype* DMA_ptr, u8 stream_idx, streamCofig_dtype* streamConfig_ptr);
```
This API configure the selected stream in the selected DMA peripheral using struct of configurations passed to the function.

```c
transferState_dtype DMA_transferState(DMA_dtype* DMA_ptr, u8 stream_idx);
```
This API returns the current status of the transfer in the selected (DMA, stream).

### Usage example

```c

char str1[100] = "hello world!";
char str2[100] = "";

void DMA2_Stream0_IRQHandler(void){
	USART1_voidSendString((u8*)str2);
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
```

## PID-controller-observer-pattern

This is an example applying observer pattern for reading average temperature from TC72 digital sensor using SPI interface and notifying the client which is the PID controller to accomodate the heater pwm signal to conserve 30 degree celicius.

## PID-controller-polling-pattern

This is an example applying polling pattern for reading temperature from TC72 digital sensor using SPI interface Periodically and handling it using the PID controller to accomodate the heater pwm signal to conserve 30 degree celicius.


## press-counting-rtos

Thins is an example applying binary semaphore for preventing shared resource corruption between two tasks having the same priority and executed at the same time using round robin. The rtos used here is [**bartos**](https://github.com/badra022/bartos), developed it myself from scratch.

## toggle-led-gpt-based

We implemented General purpose timers proxy driver in this project and used it to schedule a periodic task that toggles a led each specific period of time, timers 2,3,4 and 5 are supported for this driver.