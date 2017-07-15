//******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "user.h"          /* User funct/params, such as InitApp */
#include "system.h"        /* System funct/params, like osc/peripheral config */

//#include "i2c_nino.h"          /* User funct/params, such as InitApp */
#include "nRF24L01P.h"
#include "spi.h"
#include "i2c.h"

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */

uint8_t wdata[2] = {0x06, 0x00 }; //temp. measurement, heated disabled, 11 bit resoluton
//uint8_t wdata[2] = {0x02, 0x00 }; //temp. measurement, heater disabled, 14 bit resolution
//uint8_t wdata[2] = {0x22, 0x00 }; //temp. measurement, heater enabled, 14 bit resolution
uint8_t rdata[2] = { 0x00, 0x00};
uint8_t data[3];

//interrupt service routine isr
void interrupt isr(void)
{
    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */       
       
        if (IOCAFbits.IOCAF0 & INTCONbits.IOCIF){               
            INTCONbits.IOCIE = 0;           // Disable interrupt on change             
            IOCAFbits.IOCAF0 = 0;                                   
                                    
            // AD pretvorba
            signed int ctemp;
            FVRCON = 0b01100000;        //enable internal temp indicator, 4Vt high range,
            //configure ADC
            ADCON1 = 0b11000000;     //right justified, Fosc/4, Vref- is VSS, Vref+ is VDD
            ADCON0 = 0b01110101;   //select temp module
            ADCON0bits.GO = 1;
         
            while(1)
            {       
                if (ADCON0bits.GO_nDONE)
                {
                   
                    //ctemp = (ADRESH << 8) | ADRESL;  
                    data[0] = ADRESL;
                    data[1] = ADRESH;
                    break;
                    
                }             
            }           
            data[2]=1; //ID
            // slanje podataka
            CE = 0;
            SPI_init();
            nRF_Setup();                       
            FlushTXRX();
            WriteRegister(NRF_STATUS,0x70);         // Reset status register            
             __delay_ms(2);        
            CE = 1; //bez ovog
            WritePayload(3, data); 
            __delay_us(202);  // 130 us + Ttransmit???
            FlushTXRX();            
            WriteRegister(NRF_CONFIG, 0x00);        // turn off module
            __delay_ms(5);                            
                        
            // LED indikacija
            REDLED = 1;
            __delay_ms(10);
            REDLED = 0;
            __delay_ms(10);                        
            
            // Interrupt enable
            INTCONbits.IOCIE = 1;           // Enable interrupt on change  
            SLEEP();
        }
}

  

