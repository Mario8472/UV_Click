#ifndef uv_click_H_
#define uv_click_H_

/*********************************INCLUDES******************************************/
#include "stm32f4xx_hal.h"


/**********************************DEFINES******************************************/
#define ML8511_ENABLE_PORT						GPIOE
#define MCP3201_CHIP_SELECT_PORT				GPIOB
#define ML8511_ENABLE_PIN						GPIO_PIN_10
#define MCP3201_CHIP_SELECT_PIN					GPIO_PIN_12

/*********************************STRUCTURES****************************************/


/******************************EXTERN VARIABLES*************************************/


/****************************FUNCTION PROTOTYPES************************************/
void UV_Click_Init();
float Get_UV_Value(SPI_HandleTypeDef *device);
void UART_Send_Data(float uv_data, UART_HandleTypeDef *port);

#endif /* uv_click_H_ */
