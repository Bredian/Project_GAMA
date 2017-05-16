// This file has been prepared for Doxygen automatic documentation generation.
/*! \file ********************************************************************
*
* Atmel Corporation
*
* File              : USI_TWI_Slave.c
* Compiler          : IAR EWAAVR 4.11A
* Revision          : $Revision: 1.14 $
* Date              : $Date: Friday, December 09, 2005 17:25:38 UTC $
* Updated by        : $Author: jtyssoe $
*
* Support mail      : avr@atmel.com
*
* Supported devices : All device with USI module can be used.
*
* AppNote           : AVR312 - Using the USI module as a I2C slave
*
* Description       : Functions for USI_TWI_receiver and USI_TWI_transmitter.
*
*
****************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "USI_TWI_Slave.h"

/*! Static Variables
 */

static unsigned char TWI_slaveAddress;
static volatile unsigned char USI_TWI_Overflow_State;


/*! Local variables
 */
static uint8_t TWI_RxBuf;
static volatile uint8_t TWI_RxState;

static uint8_t TWI_TxBuf;
static volatile uint8_t TWI_TxState;

/*! \brief Flushes the TWI buffers
 */
void Flush_TWI_Buffers(void)
{
    TWI_RxBuf = 0;
    TWI_RxState = 0;
    TWI_TxBuf = 0;
    TWI_TxState = 0;
}

//********** USI_TWI functions **********//

/*! \brief
 * Initialise USI for TWI Slave mode.
 */
void USI_TWI_Slave_Initialise( unsigned char TWI_ownAddress )
{
  Flush_TWI_Buffers();

  TWI_slaveAddress = TWI_ownAddress;

  PORT_USI |=  (1<<PORT_USI_SCL);                                 // Set SCL high
  PORT_USI |=  (1<<PORT_USI_SDA);                                 // Set SDA high
  DDR_USI  |=  (1<<PORT_USI_SCL);                                 // Set SCL as output
  DDR_USI  &= ~(1<<PORT_USI_SDA);                                 // Set SDA as input
  USICR    =  (1<<USISIE)|(0<<USIOIE)|                            // Enable Start Condition Interrupt. Disable Overflow Interrupt.
              (1<<USIWM1)|(0<<USIWM0)|                            // Set USI in Two-wire mode. No USI Counter overflow prior
                                                                  // to first Start Condition (potentail failure)
              (1<<USICS1)|(0<<USICS0)|(0<<USICLK)|                // Shift Register Clock Source = External, positive edge
              (0<<USITC);
  USISR    = 0xF0;                                                // Clear all flags and reset overflow counter
}


/*! \brief Puts data in the transmission buffer, Waits if buffer is full.
*/
void USI_TWI_Transmit_Byte( unsigned char data )
{
    TWI_TxBuf = data;                                 // Store data in buffer.
    TWI_TxState = 1;                                  // Data in buffer.
    return;
}

/*! \brief Returns a byte from the receive buffer. Waits if buffer is empty.
 */
unsigned char USI_TWI_Receive_Byte( void )
{
    return TWI_RxBuf;                                // Return data from the buffer.
}

/*! \brief Check if there is data in the receive buffer.
 */
unsigned char USI_TWI_Data_In_Receive_Buffer( void )
{
    return ( TWI_RxState );                 // Return 0 (FALSE) if the receive buffer is empty.
}

/*! \brief Usi start condition ISR
 * Detects the USI_TWI Start Condition and intialises the USI
 * for reception of the "TWI Address" packet.
 */

ISR(USI_START_VECTOR)
{
    unsigned char tmpUSISR;                                         // Temporary variable to store volatile
    tmpUSISR = USISR;                                               // Not necessary, but prevents warnings
// Set default starting conditions for new TWI package
    USI_TWI_Overflow_State = USI_SLAVE_CHECK_ADDRESS;
    DDR_USI  &= ~(1<<PORT_USI_SDA);                                 // Set SDA as input
    while ( (PIN_USI & (1<<PORT_USI_SCL)) & !(tmpUSISR & (1<<USIPF)) );   // Wait for SCL to go low to ensure the "Start Condition" has completed.
                                                                       // If a Stop condition arises then leave the interrupt to prevent waiting forever.
    USICR   =   (1<<USISIE)|(1<<USIOIE)|                            // Enable Overflow and Start Condition Interrupt. (Keep StartCondInt to detect RESTART)
                (1<<USIWM1)|(1<<USIWM0)|                            // Set USI in Two-wire mode.
                (1<<USICS1)|(0<<USICS0)|(0<<USICLK)|                // Shift Register Clock Source = External, positive edge
                (0<<USITC);
    USISR  =    (1<<USI_START_COND_INT)|(1<<USIOIF)|(1<<USIPF)|(1<<USIDC)|      // Clear flags
                (0x0<<USICNT0);                                     // Set USI to sample 8 bits i.e. count 16 external pin toggles.
}


/*! \brief USI counter overflow ISR
 * Handels all the comunication. Is disabled only when waiting
 * for new Start Condition.
 */

ISR(USI_OVERFLOW_VECTOR)
{
  unsigned char tmpUSIDR;


  switch (USI_TWI_Overflow_State)
  {
    // ---------- Address mode ----------
    // Check address and send ACK (and next USI_SLAVE_SEND_DATA) if OK, else reset USI.
    case USI_SLAVE_CHECK_ADDRESS:
      if ((USIDR == 0) || (( USIDR>>1 ) == TWI_slaveAddress))
      {
        if ( USIDR & 0x01 )
          USI_TWI_Overflow_State = USI_SLAVE_SEND_DATA;
        else
          USI_TWI_Overflow_State = USI_SLAVE_REQUEST_DATA;
          SET_USI_TO_SEND_ACK();
      }
      else
      {
        SET_USI_TO_TWI_START_CONDITION_MODE();
      }
      break;

    // ----- Master write data mode ------
    // Check reply and goto USI_SLAVE_SEND_DATA if OK, else reset USI.
    case USI_SLAVE_CHECK_REPLY_FROM_SEND_DATA:
      if ( USIDR ) // If NACK, the master does not want more data.
      {
        SET_USI_TO_TWI_START_CONDITION_MODE();
        return;
      }
      // From here we just drop straight into USI_SLAVE_SEND_DATA if the master sent an ACK

    // Copy data from buffer to USIDR and set USI to shift byte. Next USI_SLAVE_REQUEST_REPLY_FROM_SEND_DATA
    case USI_SLAVE_SEND_DATA:

      // Get data from Buffer
      //~ tmpTxTail = TWI_TxTail;           // Not necessary, but prevents warnings
      if ( TWI_TxState )
      {
        USIDR = TWI_TxBuf;
        TWI_TxState = 0;
      }
      else // If the buffer is empty then:
      {
          SET_USI_TO_TWI_START_CONDITION_MODE();
          return;
      }
      USI_TWI_Overflow_State = USI_SLAVE_REQUEST_REPLY_FROM_SEND_DATA;
      SET_USI_TO_SEND_DATA();
      break;

    // Set USI to sample reply from master. Next USI_SLAVE_CHECK_REPLY_FROM_SEND_DATA
    case USI_SLAVE_REQUEST_REPLY_FROM_SEND_DATA:
      USI_TWI_Overflow_State = USI_SLAVE_CHECK_REPLY_FROM_SEND_DATA;
      SET_USI_TO_READ_ACK();
      break;

    // ----- Master read data mode ------
    // Set USI to sample data from master. Next USI_SLAVE_GET_DATA_AND_SEND_ACK.
    case USI_SLAVE_REQUEST_DATA:
      USI_TWI_Overflow_State = USI_SLAVE_GET_DATA_AND_SEND_ACK;
      SET_USI_TO_READ_DATA();
      break;

    // Copy data from USIDR and send ACK. Next USI_SLAVE_REQUEST_DATA
    case USI_SLAVE_GET_DATA_AND_SEND_ACK:
      // Put data into Buffer
      tmpUSIDR = USIDR;             // Not necessary, but prevents warnings
      TWI_RxBuf = tmpUSIDR;
      TWI_RxState = 1;

      USI_TWI_Overflow_State = USI_SLAVE_REQUEST_DATA;
      SET_USI_TO_SEND_ACK();
      break;
  }
}
