/*
 * spi_config.h
 *
 *  Created on: Jun 7, 2022
 *      Author: Badra
 */

#ifndef INC_SPI_CONFIG_H_
#define INC_SPI_CONFIG_H_

#define SP1_STATUS          SPI_ENABLE

#define SPI1_CLOCK_MODE     SPI_MODE3

#define SPI1_MASTER_SLAVE   SPI_MASTER

#define SPI1_PRESCALLER     SPI_FPCLK_DIVIDED_BY_4

#define SPI1_DATA_ORDER     SPI_MSB_FIRST

#define SPI1_SS_MANAGE      HW_SLAVE_MANAGEMENT

#define SPI1_DATA_SIZE      SPI_8BIT_DATA

#define SPI1_INT_STATUS     SPI_INT_DISABLE

#endif /* INC_SPI_CONFIG_H_ */
