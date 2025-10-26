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
// #define SET_WAVE
// ------------------------------------------------ Initializing AD9833
void AD9833_SetWave(uint16_t WaveType, float FRQ, float Phase) {

    // Clamp Phase 0–360
    if (Phase < 0) Phase = 0;
    if (Phase > 360) Phase = 360;

    // ---- Frequency tuning word ----
    uint32_t freqWord = (uint32_t)((FRQ * pow(2, 28)) / FMCLK);

    uint16_t freqLSB = (uint16_t)(freqWord & 0x3FFF);
    uint16_t freqMSB = (uint16_t)((freqWord >> 14) & 0x3FFF);

    freqLSB |= 0x4000;  // FREQ0 write LSB
    freqMSB |= 0x4000;  // FREQ0 write MSB

    // ---- Phase tuning word ----
    uint16_t phaseWord = (uint16_t)((Phase * 4096.0) / 360.0);
    phaseWord |= 0xC000; // PHASE0 register address

    // ---- Control word sequence ----
    uint16_t controlReset = 0x2100; // Reset bit set
    uint16_t controlExit  = 0x2000; // Reset bit cleared

    // ---- SPI write sequence ----
    uint16_t words[] = {
        controlReset,
        freqLSB,
        freqMSB,
        phaseWord,
        controlExit
    };
    for (int i = 0; i < 5; i++) {
        HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
        if (HAL_SPI_Transmit(&hspi2, &words[i], 1, HAL_MAX_DELAY) != HAL_OK) {
            Error_Handler();
        }
        HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);
    }
    // HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
    // if (HAL_SPI_Transmit(&hspi2, (uint8_t*)words, sizeof(words), HAL_MAX_DELAY) != HAL_OK) {
    //     Error_Handler();
    // }
    // HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);

    // ---- Set waveform type ----
    HAL_Delay(1);
    /*
    HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
    if (HAL_SPI_Transmit(&hspi2, (uint8_t*)&WaveType, sizeof(WaveType), HAL_MAX_DELAY) != HAL_OK) {
        Error_Handler();
    }
    HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);
    */
}