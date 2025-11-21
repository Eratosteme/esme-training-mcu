/* 
 * File:   MCP9700.c
 * Author: Esme Sudria
 */

#include "MCP9700.h"
#include "ADC.h" // Utilise votre driver ADC existant

// Timeout pour la conversion (en ms)
#define TEMP_ADC_TIMEOUT_MS  10U

void MCP9700_Init(void)
{
    // L'initialisation hardware est faite par ADC_vidInitialize() dans le main
}

int16_t MCP9700_GetDeciCelsius(void)
{
    uint16_t adcRawVal = 0;
    ADC_tenuStatus status;
    
    // Appel de votre fonction ADC qui lit le canal défini dans ADC_cfg.h
    status = ADC_enuGetRawValue(&adcRawVal, TEMP_ADC_TIMEOUT_MS);
    
    if(status != ADC_eSTATUS_OK)
    {
        return -9999; // Code d'erreur
    }

    // CALCUL DE TEMPERATURE (Optimisé sans float)
    
    // 1. Conversion ADC -> mV
    // V = (raw * Vref) / 1024
    uint32_t voltage_mV = ((uint32_t)adcRawVal * MCP9700_VREF_MV) / MCP9700_ADC_RESOLUTION;

    // 2. Conversion mV -> Température (Deci-degrés)
    // Formule MCP9700 : Vout = Tc * 10mV + 500mV
    // Tc = (Vout - 500) / 10
    // On veut des dixièmes de degrés : T_deci = Tc * 10
    // Donc T_deci = Vout - 500
    
    int32_t temp_deciC = (int32_t)voltage_mV - (int32_t)MCP9700_OFFSET_MV;
    
    return (int16_t)temp_deciC;
}