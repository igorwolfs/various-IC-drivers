/*************************************************************************************
 Title	:   Analog Devices AD9833 DDS Wave Generator Library for STM32 Using HAL Libraries
 Author:    Bardia Alikhan Afshar <bardia.a.afshar@gmail.com>  
 Software:  IAR Embedded Workbench for ARM
 Hardware:  Any STM32 device
*************************************************************************************/
#include "driver_ad9833.h"
#include "main.h"

// -------------------------------- Functions --------------------------------

// ------------------------------------------------ Sets Wave Frequency & Phase (In Degree) In PHASE0 & FREQ0 Registers

// ------------------------------------------------ Initializing AD9833
void AD9833_SetWave(uint16_t WaveType,float FRQ,float Phase){
    // ---------- Tuning Word for Phase ( 0 - 360 Degree )
    if(Phase<0)Phase=0; // Changing Phase Value to Positive
    if(Phase>360)Phase=360; // Maximum value For Phase (In Degree)
    uint32_t phaseVal  = ((int)(Phase*(4096/360))) | 0XC000;  // 4096/360 = 11.37 change per Degree for Register And using 0xC000 which is Phase 0 Register Address
    
    // ** Tuning word for Frequency
    long freq=0;
    freq=(int)(((FRQ * pow(2,28))/FMCLK)+1); // Tuning Word
    uint16_t FRQHW=(int)((freq & 0xFFFC000) >> 14); // FREQ MSB
    uint16_t FRQLW=(int)(freq & 0x3FFF);  // FREQ LSB 
    FRQLW |= 0x4000;
    FRQHW |= 0x4000; 

    // ** WRITE 
    // WAVE-TYPE
    HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
    if (HAL_SPI_Transmit(&hspi2, &WaveType, 1, 10) != HAL_OK) {
        Error_Handler();
    }
    HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);

    HAL_Delay(1);

    // WAVE CONFIGURATION
    uint16_t SpiTxBuff[5] = {0x2100, // Control register 
        FRQLW, // Frequency register LSB
        FRQHW, // Frequency register MSB
        phaseVal, // Phase register
        0x2000}; // Exit reset
    HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
    if (HAL_SPI_Transmit(&hspi2, &SpiTxBuff[0], 5, 10) != HAL_OK) {
        Error_Handler();
    }
    HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);

    // WAVE-TYPE
    HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
    if (HAL_SPI_Transmit(&hspi2, &WaveType, 1, 10) != HAL_OK) {
        Error_Handler();
    }
    HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);
    return;
}