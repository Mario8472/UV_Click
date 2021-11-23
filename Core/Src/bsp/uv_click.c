

/*********************************INCLUDES******************************************/
#include "bsp/uv_click.h"
#include <string.h>
/**********************GLOBAL VARIABLES AND CONSTANTS*******************************/


/****************************FORWARD DECLARATIONS***********************************/


/*********************************FUNCTIONS*****************************************/

/*
 * @brief  Enables ML8511 UV sensor and deselects MCP3201
 *
 * */
void UV_Click_Init()
{
	// Enable ML8511 UV sensor
	HAL_GPIO_WritePin(ML8511_ENABLE_PORT, ML8511_ENABLE_PIN, GPIO_PIN_SET);
	// Deselect MCP3201
	HAL_GPIO_WritePin(MCP3201_CHIP_SELECT_PORT, MCP3201_CHIP_SELECT_PIN, GPIO_PIN_SET);
}

/*
 * @brief  Reads and formats data from MCP3201
 * @param  hspi pointer to a SPI_HandleTypeDef structure that contains the configuration information for SPI module
 * @retval Formated raw data from MCP3201
 *
 * */
static uint16_t MCP3201_Get_ADC(SPI_HandleTypeDef *device)
{
	uint16_t result = 0;
	uint8_t received_buffer[2] = {0};

	HAL_GPIO_WritePin(MCP3201_CHIP_SELECT_PORT, MCP3201_CHIP_SELECT_PIN, GPIO_PIN_RESET);
	HAL_SPI_Receive(device, received_buffer, 2, 20);
	HAL_GPIO_WritePin(MCP3201_CHIP_SELECT_PORT, MCP3201_CHIP_SELECT_PIN, GPIO_PIN_SET);

	result = (received_buffer[0] & 0x1F) << 8;
	result = ((result | received_buffer[1]) >> 1);

	return result;
}

/*
 * @brief  Calculates UV intensity based on measured raw data
 * @param  hspi pointer to a SPI_HandleTypeDef structure that contains the configuration information for SPI module
 * @retval UV Intensity in mW/cm2
 *
 * */
float Get_UV_Value(SPI_HandleTypeDef *device)
{
	uint16_t adc_data = 0, average = 0;
	float mV = 0.0f, uv_value = 0.0f;

	for(uint8_t i = 0; i < 16; i++)
	{
		adc_data = MCP3201_Get_ADC(device);
		average += adc_data;
	}

	// result in mV
	mV = average >> 4;

	// result in mW/cm2 @ 365nm
	mV = mV / 1000; // convert mV to V
	uv_value = (0.1167 * mV) + 1.05; // Datasheet diagram page 4/8 approximation

	return uv_value;
}

/*
 * @brief  Sends UV Intensity Result on UART
 * @param  huart Pointer to a UART_HandleTypeDef structure that contains *
 *
 * */
void UART_Send_Data(float uv_data, UART_HandleTypeDef *port)
{
	char send_data[40];

	// Send UV Data
	sprintf(send_data,"UV intensity: %2.5f mW/cm2 \r\n", uv_data);
	HAL_UART_Transmit(port, (uint8_t*)send_data, strlen(send_data), 40);
}
