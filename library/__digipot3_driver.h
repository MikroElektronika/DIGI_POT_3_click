/*
    __digipot3_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __digipot3_driver.h
@brief    DIGI_POT_3 Driver
@mainpage DIGI_POT_3 Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   DIGIPOT3
@brief      DIGI_POT_3 Click Driver
@{

| Global Library Prefix | **DIGIPOT3** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Apr 2018.**      |
| Developer             | **Nemanja Medakovic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _DIGIPOT3_H_
#define _DIGIPOT3_H_

/** 
 * @macro T_DIGIPOT3_P
 * @brief Driver Abstract type 
 */
#define T_DIGIPOT3_P    const uint8_t*

/** @defgroup DIGIPOT3_COMPILE Compilation Config */              /** @{ */

   #define   __DIGIPOT3_DRV_SPI__                            /**<     @macro __DIGIPOT3_DRV_SPI__  @brief SPI driver selector */
//  #define   __DIGIPOT3_DRV_I2C__                            /**<     @macro __DIGIPOT3_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __DIGIPOT3_DRV_UART__                           /**<     @macro __DIGIPOT3_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup DIGIPOT3_VAR Variables */                           /** @{ */

/** Commands **/
extern const uint8_t _DIGIPOT3_DO_NOTHING_COMM;
extern const uint8_t _DIGIPOT3_RESTORE_EEMEM_TO_RDAC_COMM;
extern const uint8_t _DIGIPOT3_STORE_RDAC_TO_EEMEM_COMM;
extern const uint8_t _DIGIPOT3_DECREMENT_RDAC_6DB_COMM;
extern const uint8_t _DIGIPOT3_DECREMENT_RDAC_ONESTEP_COMM;
extern const uint8_t _DIGIPOT3_RESTORE_RDAC_WITH_EEMEM_COMM;
extern const uint8_t _DIGIPOT3_INCREMENT_RDAC_6DB_COMM;
extern const uint8_t _DIGIPOT3_INCREMENT_RDAC_ONESTEP_COMM;

/** Non volatile EEMEM memory locations **/
extern const uint8_t _DIGIPOT3_RDAC_EEMEM_LOC;
extern const uint8_t _DIGIPOT3_O1_O2_EEMEM_LOC;
extern const uint8_t _DIGIPOT3_USER1_EEMEM_LOC;
extern const uint8_t _DIGIPOT3_USER2_EEMEM_LOC;
extern const uint8_t _DIGIPOT3_USER3_EEMEM_LOC;
extern const uint8_t _DIGIPOT3_USER4_EEMEM_LOC;
extern const uint8_t _DIGIPOT3_USER5_EEMEM_LOC;
extern const uint8_t _DIGIPOT3_USER6_EEMEM_LOC;
extern const uint8_t _DIGIPOT3_USER7_EEMEM_LOC;
extern const uint8_t _DIGIPOT3_USER8_EEMEM_LOC;
extern const uint8_t _DIGIPOT3_USER9_EEMEM_LOC;
extern const uint8_t _DIGIPOT3_USER10_EEMEM_LOC;
extern const uint8_t _DIGIPOT3_USER11_EEMEM_LOC;
extern const uint8_t _DIGIPOT3_USER12_EEMEM_LOC;
extern const uint8_t _DIGIPOT3_USER13_EEMEM_LOC;
extern const uint8_t _DIGIPOT3_USER14_EEMEM_LOC;

/** DAC values which determine the wiper position **/
extern const uint16_t _DIGIPOT3_ZERO_SCALE;
extern const uint16_t _DIGIPOT3_QUARTER_SCALE;
extern const uint16_t _DIGIPOT3_HALF_SCALE;
extern const uint16_t _DIGIPOT3_THREE_QUARTERS_SCALE;
extern const uint16_t _DIGIPOT3_FULL_SCALE;

                                                                       /** @} */
/** @defgroup DIGIPOT3_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup DIGIPOT3_INIT Driver Initialization */              /** @{ */

#ifdef   __DIGIPOT3_DRV_SPI__
void digipot3_spiDriverInit(T_DIGIPOT3_P gpioObj, T_DIGIPOT3_P spiObj);
#endif
#ifdef   __DIGIPOT3_DRV_I2C__
void digipot3_i2cDriverInit(T_DIGIPOT3_P gpioObj, T_DIGIPOT3_P i2cObj, uint8_t slave);
#endif
#ifdef   __DIGIPOT3_DRV_UART__
void digipot3_uartDriverInit(T_DIGIPOT3_P gpioObj, T_DIGIPOT3_P uartObj);
#endif

                                                                       /** @} */
/** @defgroup DIGIPOT3_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Command Send function
 *
 * @param[in] commandByte      Command which be executed
 *
 * @return 0 - OK, 1 - Wrong command
 *
 * Function executes the desired command.
 */
uint8_t digipot3_sendCommand( uint8_t commandByte );

/**
 * @brief EEMEM Store function
 *
 * @param[in] location_address        EEMEM location where data be stored
 * @param[in] transfer_data           Data which be stored
 *
 * @return 0 - OK, 1 - Wrong EEMEM location
 *
 * Function stores 16-bit data to the desired EEMEM (non volatile) memory location.
 */
uint8_t digipot3_storeEEMEM( uint8_t location_address, uint16_t transfer_data );

/**
 * @brief EEMEM Read function
 *
 * @param[in] location_address       EEMEM location which from data be read
 * @param[out] dataOut               Buffer where data be stored
 *
 * @return 0 - OK, 1 - Wrong EEMEM location
 *
 * Function reads 16-bit data from the EEMEM (non volatile) memory location.
 */
uint8_t digipot3_readEEMEM( uint8_t location_address, uint16_t *dataOut );

/**
 * @brief DAC Write function
 *
 * @param[in] valueDAC      Determines the wiper position
 *
 * @return 0 - OK, 1 - DAC value is out of range
 *
 * Function writes 10-bit value to DAC register and determines the wiper position.
 */
uint8_t digipot3_writeDAC( uint16_t valueDAC );

/**
 * @brief DAC Read function
 *
 * @param[out] dataOut     Buffer where DAC value be stored
 *
 * Function reads 10-bit value from DAC register (wiper position).
 */
void digipot3_readDAC( uint16_t *dataOut );

/**
 * @brief Data Ready Check function
 *
 * @return 0 - Command is not executed (communication is busy), 1 - Command is executed
 *
 * Function checks is command executed or not.
 */
uint8_t digipot3_checkDataReady( void );

                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_DIGI_POT_3_STM.c
    @example Click_DIGI_POT_3_TIVA.c
    @example Click_DIGI_POT_3_CEC.c
    @example Click_DIGI_POT_3_KINETIS.c
    @example Click_DIGI_POT_3_MSP.c
    @example Click_DIGI_POT_3_PIC.c
    @example Click_DIGI_POT_3_PIC32.c
    @example Click_DIGI_POT_3_DSPIC.c
    @example Click_DIGI_POT_3_AVR.c
    @example Click_DIGI_POT_3_FT90x.c
    @example Click_DIGI_POT_3_STM.mbas
    @example Click_DIGI_POT_3_TIVA.mbas
    @example Click_DIGI_POT_3_CEC.mbas
    @example Click_DIGI_POT_3_KINETIS.mbas
    @example Click_DIGI_POT_3_MSP.mbas
    @example Click_DIGI_POT_3_PIC.mbas
    @example Click_DIGI_POT_3_PIC32.mbas
    @example Click_DIGI_POT_3_DSPIC.mbas
    @example Click_DIGI_POT_3_AVR.mbas
    @example Click_DIGI_POT_3_FT90x.mbas
    @example Click_DIGI_POT_3_STM.mpas
    @example Click_DIGI_POT_3_TIVA.mpas
    @example Click_DIGI_POT_3_CEC.mpas
    @example Click_DIGI_POT_3_KINETIS.mpas
    @example Click_DIGI_POT_3_MSP.mpas
    @example Click_DIGI_POT_3_PIC.mpas
    @example Click_DIGI_POT_3_PIC32.mpas
    @example Click_DIGI_POT_3_DSPIC.mpas
    @example Click_DIGI_POT_3_AVR.mpas
    @example Click_DIGI_POT_3_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __digipot3_driver.h

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */