/*
 * RF24HALSTM32HAL.h
 *
 *  Created on: 9 лип. 2021 р.
 *      Author: xeedj
 */

#pragma once

#include "spi.h"
#include "gpio.h"

#include "RF24HAL.h"

class RF24HALSTM32HAL: public RF24HAL {
	GPIO_TypeDef *csn_port;
	uint16_t csn_pin;
	GPIO_TypeDef *ce_port;
	uint16_t ce_pin;
	SPI_HandleTypeDef* hspi;
public:
	RF24HALSTM32HAL(GPIO_TypeDef *csn_port, uint16_t csn_pin,
					GPIO_TypeDef *ce_port, uint16_t ce_pin,
					SPI_HandleTypeDef* hspi):  csn_port(csn_port), csn_pin(csn_pin), ce_port(ce_port), ce_pin(ce_pin), hspi(hspi) {

	};
	~RF24HALSTM32HAL() {};

	uint32_t millis() {
		return HAL_GetTick();
	};
	void delay(uint16_t ms) {
		HAL_Delay(ms);
	};
	void delayMicroseconds(uint16_t us) {
		HAL_Delay(1);
	};
	void csn(int mode) {
		  if(mode)
		  {
			  HAL_GPIO_WritePin(csn_port, csn_pin, GPIO_PinState::GPIO_PIN_SET);
		  }
		  else
		  {
			  HAL_GPIO_WritePin(csn_port, csn_pin, GPIO_PinState::GPIO_PIN_RESET);
		  }
	};
	void ce(int level) {
		  if(level)
		  {
			  HAL_GPIO_WritePin(ce_port, ce_pin, GPIO_PinState::GPIO_PIN_SET);
		  }
		  else
		  {
			  HAL_GPIO_WritePin(ce_port, ce_pin, GPIO_PinState::GPIO_PIN_RESET);
		  }
	};
	uint8_t spi_transfer(uint8_t tx) {
		uint8_t rx = 0;
		if (HAL_SPI_TransmitReceive(hspi, &tx, &rx, sizeof(uint8_t), 1000) != HAL_OK) {
			exit(-1);
		};
		return rx;
	};
	void hal_init() {

	};
};

