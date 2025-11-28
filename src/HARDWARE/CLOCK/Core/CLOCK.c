/**
 ***********************************************************************************************************************
 * Company: Esme Sudria
 * Project: Projet Esme
 *
 ***********************************************************************************************************************
 * @file      CLOCK.c
 *
 * @brief     CLOCK Hardware core part
 * @details   All CONFIG bits must be placed in device_config.c.
 *            This module only configures the oscillator at runtime.
 *
 ***********************************************************************************************************************
 */

#include "CLOCK.h"

void CLOCK_vidInitialize(void)
{
    /* IMPORTANT :
     * Tous les #pragma config sont SUPPRIMÉS.
     * Le choix de RSTOSC = EXTOSC est fait dans device_config.c uniquement.
     */

#if (CLOCK_CONFIG_HFINTOSC_MHZ == 1)

    /* Sélection du diviseur pour obtenir 1 MHz */
    OSCCON1bits.NDIV = 0b0110;   // 64 ? 1 MHz

#elif (CLOCK_CONFIG_HFINTOSC_MHZ == 64)

    /* Configuration du diviseur en fonction de la fréquence FOSC choisie */
#if   (CLOCK_CONFIG_FOSC_FREQUENCY_MHZ == CLOCK_FOSC_FREQUENCY_01MHZ)
    OSCCON1bits.NDIV = 0b0110;
#elif (CLOCK_CONFIG_FOSC_FREQUENCY_MHZ == CLOCK_FOSC_FREQUENCY_02MHZ)
    OSCCON1bits.NDIV = 0b0101;
#elif (CLOCK_CONFIG_FOSC_FREQUENCY_MHZ == CLOCK_FOSC_FREQUENCY_04MHZ)
    OSCCON1bits.NDIV = 0b0100;
#elif (CLOCK_CONFIG_FOSC_FREQUENCY_MHZ == CLOCK_FOSC_FREQUENCY_08MHZ)
    OSCCON1bits.NDIV = 0b0013;
#elif (CLOCK_CONFIG_FOSC_FREQUENCY_MHZ == CLOCK_FOSC_FREQUENCY_16MHZ)
    OSCCON1bits.NDIV = 0b0010;
#elif (CLOCK_CONFIG_FOSC_FREQUENCY_MHZ == CLOCK_FOSC_FREQUENCY_32MHZ)
    OSCCON1bits.NDIV = 0b0001;
#elif (CLOCK_CONFIG_FOSC_FREQUENCY_MHZ == CLOCK_FOSC_FREQUENCY_64MHZ)
    OSCCON1bits.NDIV = 0b0000;
#else
#error Wrong value for the config "CLOCK_CONFIG_FOSC_FREQUENCY_MHZ"
#endif

#else
#error CLOCK_CONFIG_HFINTOSC_MHZ must be 1 or 64
#endif
}