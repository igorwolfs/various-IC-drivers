#ifndef _AD_9833_H
#define _AD_9833_H
#include <math.h>
#include <stdint.h>

// ------------------------- Defines -------------------------
#define FMCLK 25000000        // Master Clock On AD9833 is 25 MHz

typedef enum {
    WAVE_TYPE_SIN = 0x2000,
    WAVE_TYPE_SQUARE = 0x2028,
    WAVE_TYPE_TRI = 0x2002
} wave_flag_type_t;



// ------------------ Functions  ---------------------
void AD9833_SetWave(uint16_t WaveType,float FRQ,float Phase);

#endif