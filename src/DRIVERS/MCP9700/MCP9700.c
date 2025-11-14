#include "MCP9700.h"
#include "adc_driver.h"  // Adapter selon ton code ADC

// Initialisation du capteur (ex : config ADC)
void MCP9700_Init(void)
{
    ADC_Init();
}

// Lecture brute du canal ADC
uint16_t MCP9700_ReadRaw(void)
{
    return ADC_ReadChannel(MCP9700_ADC_CHANNEL); // macro à définir dans le .h
}

// Conversion ADC -> temp en dixièmes de degré Celsius (°C x10)
// Pas de float : tout en entiers
int16_t MCP9700_ConvertToDeciCelsius(uint16_t adcValue)
{
    // Tension (mV) = adcValue * Vref_mV / resolution_ADC
    uint32_t voltage_mV = ((uint32_t)adcValue * MCP9700_VREF_MV) / MCP9700_ADC_RESOLUTION;
    // (temp * 10) = ((U_mv - offset) * 10) / scale
    int32_t temp_deciC = ((int32_t)voltage_mV - MCP9700_OFFSET_MV) * 10 / MCP9700_SCALE_MV_C;
    return (int16_t)temp_deciC;
}

