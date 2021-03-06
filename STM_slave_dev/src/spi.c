#include <spi.h>
#include <gpio.h>

uint8_t i = 0;


/*==============================================================================*/
/*==============================================================================*/
/* Function configurates and initializes SPI Peripheral
   - STM32F4 is slave device in this case
   - input argument = none
   - return value = none
   In this configuration pin PB4 is used as MISO line beacuse there were some
   problems with pin PA7 (this problem is probably device specific) */
void SPI_1_Init(void){

  SPI_InitTypeDef SPIx_InitStruct;
  GPIO_InitTypeDef GPIO_Spi;

  gpio_led_state(LED3_ORANGE_ID, 1);

  /* Peripheral Clock Enabe ---------------------------------------------------*/
  // Enable SPI Clock
  // Enable GPIO clock for MOSI, MISO and NSS GPIO
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);


  /* GPIO Configuration for SPI -----------------------------------------------*/

  // Configuration of desired pins
  GPIO_Spi.GPIO_Mode = GPIO_Mode_AF;
  GPIO_Spi.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Spi.GPIO_OType = GPIO_OType_PP;
  GPIO_Spi.GPIO_PuPd = GPIO_PuPd_UP;

  // SPI SCK Pin
  GPIO_Spi.GPIO_Pin = GPIO_Pin_5;
  GPIO_Init(GPIOA, &GPIO_Spi);

  // SPI MOSI Pin
  GPIO_Spi.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOA, &GPIO_Spi);

  // SPI MISO Pin
  GPIO_Spi.GPIO_Pin = GPIO_Pin_4;
  GPIO_Init(GPIOB, &GPIO_Spi);

  // SPI SS pin
  GPIO_Spi.GPIO_Pin = GPIO_Pin_4;
  GPIO_Spi.GPIO_Mode = GPIO_Mode_IN;
  GPIO_Spi.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Spi.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_Spi);

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

  /* SPI Configuration --------------------------------------------------------*/

  // reset to default configuration
  SPI_I2S_DeInit(SPI1);

  // configure SPI
  SPIx_InitStruct.SPI_Mode = SPI_Mode_Slave;
  SPIx_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPIx_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  SPIx_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
  SPIx_InitStruct.SPI_DataSize = SPI_DataSize_8b;
  SPIx_InitStruct.SPI_CPOL = SPI_CPOL_High;
  SPIx_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
  SPIx_InitStruct.SPI_NSS = SPI_NSS_Soft;

  SPI_Init( SPI1, &SPIx_InitStruct);

  SPI_BiDirectionalLineConfig(SPI1, SPI_Direction_1Line_Rx | SPI_Direction_1Line_Tx );

  // enable SPI
  SPI_Cmd( SPI1, ENABLE);

  return;
}



/*==============================================================================*/
/*==============================================================================*/
/* Function for sending data over SPI peripheral when device is asserted
   - input argument: SPI peripheral to be used
   - return value  : none */
void SPIx_Send(SPI_TypeDef* SPI_x){
  uint16_t recv;


  if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4 ))
  {

    i++;
    if(i==255){
      i=0;
    }
    // while(SPI_I2S_GetFlagStatus(SPI_x, SPI_I2S_FLAG_BSY));
    gpio_led_state(LED5_RED_ID, 1);
    while (!SPI_I2S_GetFlagStatus(SPI_x, SPI_I2S_FLAG_TXE ));
    recv = SPI_I2S_ReceiveData(SPI_x);
      SPI_I2S_SendData( SPI_x, (uint8_t) i );
      SPI_I2S_ClearFlag(SPI_x, SPI_I2S_FLAG_TXE);

    // }
  }

  else{
    gpio_led_state(LED5_RED_ID, 0);
  }

  return;
}



/*==============================================================================*/
/*==============================================================================*/
/* Function for reading data from SPI peripheral when device is asserted.
   - input argument: SPI peripheral to be used
   - return value  : received data */
uint8_t SPIx_Read(SPI_TypeDef* SPI_x){

  uint16_t recv;

  //check nss
  if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4 )){

    if (SPI_I2S_GetFlagStatus(SPI_x, SPI_I2S_FLAG_RXNE )){
      recv = SPI_I2S_ReceiveData(SPI_x);
      // clear status flag
      // SPI_I2S_ClearFlag(SPI_x, SPI_I2S_FLAG_RXNE);
      if ((recv) == 0xbc){
        gpio_led_state(LED6_BLUE_ID, 1);
      }
      else{
        gpio_led_state(LED6_BLUE_ID, 0);
      }
    }
  }
  return recv;
}
