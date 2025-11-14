/* 
 * File:   MCP9700.h
 * Author: mperr
 *
 * Created on 14 novembre 2025, 13:39
 */

#ifndef MCP9700_H
#define	MCP9700_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MCP9700_OFFSET_MV   500U  // Offset en mV (0°C)
#define MCP9700_SCALE_MV_C  10U   // Sensibilité : 10mV/°C

// Prototype des fonctions
void MCP9700_Init(void);
uint16_t MCP9700_ReadRaw(void);
float MCP9700_ConvertToCelsius(uint16_t adcValue);

#ifdef	__cplusplus
}
#endif

#endif	/* MCP9700_H */

