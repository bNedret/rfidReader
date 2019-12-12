
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "dma.h"
#include "i2c.h"
#include "usart.h"
#include "usb.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "i2c-lcd.h"
#include "stdbool.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
#define BT_RECEIVE 32
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t		WriteData[12]="word three";
	uint8_t		name[12];
	uint8_t		surname[12];
	uint8_t recive[BT_RECEIVE];
	uint8_t del[BT_RECEIVE]= "";
	uint8_t send[2] = "AT";
	uint8_t dellim[] = " ";
	uint8_t del2 = 0xff;
	uint8_t * ptr1;
	uint8_t * ptr2;
	int	nameadd = 0;
	int surnameadd = 64;
	//int	raddMax = 32;
	//int raddMin = -1;
	int startadd = 48;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */


  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_USB_PCD_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_Delay(1000);
  lcd_init();
  lcd_send_string("SyStEm sTaRtInG");
  HAL_Delay(5000);
  lcd_send_cmd (0x01);

  HAL_Delay(100);
  while(EEPROM24XX_IsConnected()==false)
  	{
  		HAL_Delay(100);
  	}

  	//EEPROM24XX_Save(32,WriteData,strlen(WriteData));
  	EEPROM24XX_Load(nameadd,name,strlen(WriteData));
  	EEPROM24XX_Load(surnameadd,surname,strlen(WriteData));
  	HAL_Delay(100);
  	lcd_send_cmd (0x80);  // goto 1,1
  	lcd_send_string(name);
  	lcd_send_cmd (0xc0);
  	lcd_send_string(surname);
  	HAL_Delay (2000);  // wait for 2 sec

  	HAL_Delay (1000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin) == GPIO_PIN_SET){
		  configuration_mode();
	  }
	  else{
		  working_mode();
	  }

	  //Reading data from bluetooth
	  /*HAL_UART_Receive(&huart3, &recive, BT_RECEIVE, 1000);
	  if(strcmp(recive, "") != 0){

		  ptr1 =strtok(recive, dellim);
		  ptr2 = strtok(NULL, dellim);
		  EEPROM24XX_Save(nameadd,ptr1,strlen(ptr1));
		  EEPROM24XX_Save(surnameadd,ptr2,strlen(ptr2));
		  nameadd = nameadd +16;
		  surnameadd = surnameadd +16;
		  lcd_send_cmd (0x80);  // goto 1,1
		  lcd_send_string(ptr1);
		  lcd_send_cmd (0xc0);
		  lcd_send_string(ptr2);
		  HAL_Delay (2000);
		  lcd_send_cmd(0x01);
		  memcpy(recive, del, strlen(recive));
	  }*/

	  /*if (recive == '1'){
		  HAL_GPIO_WritePin(EXLED_GPIO_Port, EXLED_Pin, GPIO_PIN_SET);

	  }
	  else if (recive == '0'){
		  HAL_GPIO_WritePin(EXLED_GPIO_Port, EXLED_Pin, GPIO_PIN_RESET);

	  }*/

	  // Reading pin states: UP, DOWN and CALL
	  /*if (HAL_GPIO_ReadPin(GPIOA, BUTTON_UP_PIN_Pin) == GPIO_PIN_RESET){
		  HAL_GPIO_TogglePin(GPIOC, LED_PIN_Pin);
		  nameadd = nameadd + 16;
		  surnameadd = surnameadd + 16;
		  if(nameadd > 64){
			  nameadd = 0;
			  surnameadd = 64;
		  }
		  lcd_send_cmd (0x01);
		  EEPROM24XX_Load(nameadd,name,strlen(WriteData));
		  EEPROM24XX_Load(surnameadd,surname,strlen(WriteData));
		  HAL_Delay(100);
		  lcd_send_cmd (0x80);  // goto 1,1
		  lcd_send_string(name);
		  lcd_send_cmd (0xc0);
		  lcd_send_string(surname);
		  HAL_Delay (2000);  // wait for 2 sec
		    // clear the display
		  HAL_Delay (1000);

	  }
	  else if (HAL_GPIO_ReadPin(GPIOA, BUTTON_DOWN_PIN_Pin) == GPIO_PIN_RESET){
		  HAL_GPIO_TogglePin(GPIOC, LED_PIN_Pin);
		  nameadd = nameadd - 16;
		  surnameadd = surnameadd - 16;
		  if(nameadd < -1){
			  nameadd = 64;
			  surnameadd = 64*2;
		  }
		  lcd_send_cmd (0x01);
		  EEPROM24XX_Load(nameadd,name,strlen(WriteData));
		  EEPROM24XX_Load(surnameadd,surname,strlen(WriteData));
		  HAL_Delay(100);
		  lcd_send_cmd (0x80);  // goto 1,1
		  lcd_send_string(name);
		  lcd_send_cmd (0xc0);
		  lcd_send_string(surname);
		  HAL_Delay (2000);  // wait for 2 sec
		  //lcd_send_cmd (0x01);  // clear the display
		  HAL_Delay (1000);

	  }*/

	  /*for (int i = 0; i < 200; i++){
		  EEPROM24XX_Save(i, del2, strlen(del2));
	  }*/


  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
