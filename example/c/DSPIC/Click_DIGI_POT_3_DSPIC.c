/*
Example for DIGI_POT_3 Click

    Date          : Apr 2018.
    Author        : Nemanja Medakovic

Test configuration dsPIC :
    
    MCU                : P33FJ256GP710A
    Dev. Board         : EasyPIC Fusion v7
    dsPIC Compiler ver : v7.0.1.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes peripherals and pins.
- Application Initialization - Initializes SPI driver and restores the wiper position value from
  EEMEM (non volatile) memory to the DAC register, if this value does not already exist in the DAC register.
- Application Task - (code snippet) - Increments the wiper position by 6dB every 2 seconds. When wiper position
  reaches the desired value (0x0200), then the wiper position be decremented by 6dB every 2 seconds, until position 
  value reaches the new desired value (0x0002). After that the new position value will be stored to the EEMEM memory,
  if that value does not already exist in the EEMEM memory.

*/

#include "Click_DIGI_POT_3_types.h"
#include "Click_DIGI_POT_3_config.h"

uint16_t digitalValue;
uint16_t eememValue;
char text[ 50 ] = { 0 };

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_AN_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_OUTPUT );

    mikrobus_spiInit( _MIKROBUS1, &_DIGIPOT3_SPI_CFG[0] );

    mikrobus_logInit( _LOG_USBUART_A, 9600 );
    mikrobus_logWrite( "Initializing...", _LOG_LINE );

    Delay_ms( 100 );
}

void applicationInit()
{
    digipot3_spiDriverInit( (T_DIGIPOT3_P)&_MIKROBUS1_GPIO, (T_DIGIPOT3_P)&_MIKROBUS1_SPI );
    Delay_ms( 200 );
    
    digipot3_readDAC( &digitalValue );
    digipot3_readEEMEM( _DIGIPOT3_RDAC_EEMEM_LOC, &eememValue );
    
    if ( eememValue != digitalValue )
    {
        digipot3_sendCommand( _DIGIPOT3_RESTORE_EEMEM_TO_RDAC_COMM );
    }
    
    mikrobus_logWrite( "DIGI POT 3 is initialized", _LOG_LINE );
    mikrobus_logWrite( "", _LOG_LINE );
    Delay_ms( 200 );
}

void applicationTask()
{
    while (digitalValue < 0x0200)
    {
        digipot3_sendCommand( _DIGIPOT3_INCREMENT_RDAC_6DB_COMM );
        digipot3_readDAC( &digitalValue );
        WordToStr( digitalValue, text );
        mikrobus_logWrite( "DAC value is: ", _LOG_TEXT );
        mikrobus_logWrite( text, _LOG_LINE );
        Delay_ms( 2000 );
    }

    while (digitalValue > 0x0002)
    {
        digipot3_sendCommand( _DIGIPOT3_DECREMENT_RDAC_6DB_COMM );
        digipot3_readDAC( &digitalValue );
        WordToStr( digitalValue, text );
        mikrobus_logWrite( "DAC value is: ", _LOG_TEXT );
        mikrobus_logWrite( text, _LOG_LINE );
        Delay_ms( 2000 );
    }

    if (eememValue != digitalValue)
    {
        digipot3_sendCommand( _DIGIPOT3_STORE_RDAC_TO_EEMEM_COMM );
        eememValue = digitalValue;
    }
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
        applicationTask();
    }
}
