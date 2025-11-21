/* 
 * File:   MCP9700.h
 * Author: Esme Sudria
 */

#ifndef MCP9700_H
#define	MCP9700_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

/* CONFIGURATION */
// Tension de référence ADC (généralement 3300mV ou 5000mV sur votre carte)
#define MCP9700_VREF_MV         3300U   

// Résolution ADC du PIC18F47Q10 (10 bits)
#define MCP9700_ADC_RESOLUTION  1024U   

/* CARACTERISTIQUES CAPTEUR */
#define MCP9700_OFFSET_MV       500U    // 500mV à 0°C
// Pente : 10mV par °C

/* PROTOTYPES */
void MCP9700_Init(void);

/**
 * @brief Lit la température et retourne des dixièmes de degrés.
 * @return Ex: 235 pour 23.5°C. Retourne -9999 en cas d'erreur.
 */
int16_t MCP9700_GetDeciCelsius(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MCP9700_H */