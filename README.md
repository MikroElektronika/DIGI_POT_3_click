![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# DIGI_POT_3 Click

- **CIC Prefix**  : DIGIPOT3
- **Author**      : Nemanja Medakovic
- **Verison**     : 1.0.0
- **Date**        : Apr 2018.

---

### Software Support

We provide a library for the DIGI_POT_3 Click on our [LibStock](https://libstock.mikroe.com/projects/view/2381/digi-pot-3-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

Library initializes and defines SPI driver and functions which execute the commands and determine the wiper position (DAC value).
Library has ability to store desired values in the non volatile EEMEM memory, and on that way user can save the data (desired values) 
after power down. After power up user can restore data from the non volatile EEMEM memory to the DAC register, which determines the wiper position.
For more details check documentation.

Key functions :

- ``` uint8_t digipot3_sendCommand( uint8_t commandByte ) ``` - Function executes the desired command.
- ``` uint8_t digipot3_storeEEMEM( uint8_t location_address, uint16_t transfer_data ) ``` - Function stores 16-bit data to the desired 
  EEMEM (non volatile) memory location.
- ``` uint8_t digipot3_writeDAC( uint16_t valueDAC ) ``` - Function writes 10-bit value to DAC register and determines the wiper position.
- ``` void digipot3_readDAC( uint16_t *dataOut ) ``` - Function reads 10-bit value from DAC register (wiper position).

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes peripherals and pins.
- Application Initialization - Initializes SPI driver and restores the wiper position value from
  EEMEM (non volatile) memory to the DAC register, if this value does not already exist in the DAC register.
- Application Task - (code snippet) - Increments the wiper position by 6dB every 2 seconds. When wiper position
  reaches the desired value (0x0200), then the wiper position be decremented by 6dB every 2 seconds, until position 
  value reaches the new desired value (0x0002). After that the new position value will be stored to the EEMEM memory,
  if that value does not already exist in the EEMEM memory.


```.c
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
```

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2381/digi-pot-3-click) page.

Other mikroE Libraries used in the example:

- Conversions
- SPI
- UART

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
