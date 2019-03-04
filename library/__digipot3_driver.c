/*
    __digipot3_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__digipot3_driver.h"
#include "__digipot3_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __DIGIPOT3_DRV_I2C__
static uint8_t _slaveAddress;
#endif

const uint8_t _DIGIPOT3_DO_NOTHING_COMM = 0x00;
const uint8_t _DIGIPOT3_RESTORE_EEMEM_TO_RDAC_COMM = 0x01;
const uint8_t _DIGIPOT3_STORE_RDAC_TO_EEMEM_COMM = 0x02;
const uint8_t _DIGIPOT3_DECREMENT_RDAC_6DB_COMM = 0x04;
const uint8_t _DIGIPOT3_DECREMENT_RDAC_ONESTEP_COMM = 0x06;
const uint8_t _DIGIPOT3_RESTORE_RDAC_WITH_EEMEM_COMM = 0x08;
const uint8_t _DIGIPOT3_INCREMENT_RDAC_6DB_COMM = 0x0C;
const uint8_t _DIGIPOT3_INCREMENT_RDAC_ONESTEP_COMM = 0x0E;

const uint8_t _DIGIPOT3_RDAC_EEMEM_LOC = 0x00;
const uint8_t _DIGIPOT3_O1_O2_EEMEM_LOC = 0x01;
const uint8_t _DIGIPOT3_USER1_EEMEM_LOC = 0x02;
const uint8_t _DIGIPOT3_USER2_EEMEM_LOC = 0x03;
const uint8_t _DIGIPOT3_USER3_EEMEM_LOC = 0x04;
const uint8_t _DIGIPOT3_USER4_EEMEM_LOC = 0x05;
const uint8_t _DIGIPOT3_USER5_EEMEM_LOC = 0x06;
const uint8_t _DIGIPOT3_USER6_EEMEM_LOC = 0x07;
const uint8_t _DIGIPOT3_USER7_EEMEM_LOC = 0x08;
const uint8_t _DIGIPOT3_USER8_EEMEM_LOC = 0x09;
const uint8_t _DIGIPOT3_USER9_EEMEM_LOC = 0x0A;
const uint8_t _DIGIPOT3_USER10_EEMEM_LOC = 0x0B;
const uint8_t _DIGIPOT3_USER11_EEMEM_LOC = 0x0C;
const uint8_t _DIGIPOT3_USER12_EEMEM_LOC = 0x0D;
const uint8_t _DIGIPOT3_USER13_EEMEM_LOC = 0x0E;
const uint8_t _DIGIPOT3_USER14_EEMEM_LOC = 0x0F;

const uint16_t _DIGIPOT3_ZERO_SCALE = 0x0000;
const uint16_t _DIGIPOT3_QUARTER_SCALE = 0x0100;
const uint16_t _DIGIPOT3_HALF_SCALE = 0x0200;
const uint16_t _DIGIPOT3_THREE_QUARTERS_SCALE = 0x0300;
const uint16_t _DIGIPOT3_FULL_SCALE = 0x03FF;

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

uint8_t digipot3_checkCommand( uint8_t commandCheck );

/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

uint8_t digipot3_checkCommand( uint8_t commandCheck )
{
    switch (commandCheck)
    {
        case 0x00 :
        {
            return 0;
        }
        case 0x01 :
        {
            return 0;
        }
        case 0x02 :
        {
            return 0;
        }
        case 0x04 :
        {
            return 0;
        }
        case 0x05 :
        {
            return 0;
        }
        case 0x06 :
        {
            return 0;
        }
        case 0x07 :
        {
            return 0;
        }
        case 0x08 :
        {
            return 0;
        }
        case 0x0C :
        {
            return 0;
        }
        case 0x0D :
        {
            return 0;
        }
        case 0x0E :
        {
            return 0;
        }
        case 0x0F :
        {
            return 0;
        }
        default :
        {
            return 1;
        }
    }
}

/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __DIGIPOT3_DRV_SPI__

void digipot3_spiDriverInit(T_DIGIPOT3_P gpioObj, T_DIGIPOT3_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    hal_gpio_csSet( 1 );
}

#endif
#ifdef   __DIGIPOT3_DRV_I2C__

void digipot3_i2cDriverInit(T_DIGIPOT3_P gpioObj, T_DIGIPOT3_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __DIGIPOT3_DRV_UART__

void digipot3_uartDriverInit(T_DIGIPOT3_P gpioObj, T_DIGIPOT3_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif

/* ----------------------------------------------------------- IMPLEMENTATION */

uint8_t digipot3_sendCommand( uint8_t commandByte )
{
    uint8_t tmp[ 3 ] = { 0 };

    if (digipot3_checkCommand( commandByte ))
        return 1;
        
    tmp[ 0 ] = commandByte << 4;
    while (!digipot3_checkDataReady());
    
    hal_gpio_csSet( 0 );
    hal_spiWrite( tmp, 3 );
    hal_gpio_csSet( 1 );
    Delay_1ms();
    
    if (commandByte == 0x01)
    {
        tmp[ 0 ] = 0x00;
        while (!digipot3_checkDataReady());
        
        hal_gpio_csSet( 0 );
        hal_spiWrite( tmp, 3 );
        hal_gpio_csSet( 1 );
        Delay_1ms();
    }
    
    return 0;
}

uint8_t digipot3_storeEEMEM( uint8_t location_address, uint16_t transfer_data )
{
    uint8_t tmp[ 3 ] = { 0 };
    
    if ((location_address < 0x01) || (location_address > 0x0F))
        return 1;
        
    tmp[ 0 ] = 0x30 | location_address;
    tmp[ 1 ] = transfer_data >> 8;
    tmp[ 2 ] = transfer_data;
    while (!digipot3_checkDataReady());
    
    hal_gpio_csSet( 0 );
    hal_spiWrite( tmp, 3 );
    hal_gpio_csSet( 1 );
    Delay_1ms();
    
    return 0;
}

uint8_t digipot3_readEEMEM( uint8_t location_address, uint16_t *dataOut )
{
    uint8_t tmp[ 3 ] = { 0 };
    uint16_t temp = 0;
    
    if (location_address > 0x0F)
        return 1;

    tmp[ 0 ] = 0x90 | location_address;
    while (!digipot3_checkDataReady());
    
    hal_gpio_csSet( 0 );
    hal_spiWrite( tmp, 3 );
    hal_gpio_csSet( 1 );
    Delay_1ms();
    
    while (!digipot3_checkDataReady());

    hal_gpio_csSet( 0 );
    hal_spiRead( tmp, 3 );
    hal_gpio_csSet( 1 );
    Delay_1ms();
    
    temp = tmp[ 1 ];
    temp <<= 8;
    temp |= tmp[ 2 ];
    *dataOut = temp;
    
    return 0;
}

uint8_t digipot3_writeDAC( uint16_t valueDAC )
{
    uint8_t tmp[ 3 ] = { 0 };
    
    if (valueDAC > 0x03FF)
        return 1;
        
    tmp[ 0 ] = 0xB0;
    tmp[ 1 ] = valueDAC >> 8;
    tmp[ 2 ] = valueDAC;
    while (!digipot3_checkDataReady());
    
    hal_gpio_csSet( 0 );
    hal_spiWrite( tmp, 3 );
    hal_gpio_csSet( 1 );
    Delay_1ms();

    return 0;
}

void digipot3_readDAC( uint16_t *dataOut )
{
    uint8_t tmp[ 3 ] = { 0 };
    uint16_t temp = 0;
    
    tmp[ 0 ] = 0xA0;
    while (!digipot3_checkDataReady());
    
    hal_gpio_csSet( 0 );
    hal_spiWrite( tmp, 3 );
    hal_gpio_csSet( 1 );
    Delay_1ms();
    
    while (!digipot3_checkDataReady());

    hal_gpio_csSet( 0 );
    hal_spiRead( tmp, 3 );
    hal_gpio_csSet( 1 );
    Delay_1ms();
    
    temp = tmp[ 1 ];
    temp <<= 8;
    temp |= tmp[ 2 ];
    *dataOut = temp;
}

uint8_t digipot3_checkDataReady( void )
{
    if (hal_gpio_intGet())
        return 1;
    else
        return 0;
}

/* -------------------------------------------------------------------------- */
/*
  __digipot3_driver.c

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