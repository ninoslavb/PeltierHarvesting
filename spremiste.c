           //IRQ = 0;               // turn on sensor
            //__delay_ms(15); // device start up time
            //__delay_ms(75); // device start up time
            
              
            
            
      
                                      
        
           
            /*
            //IRQ = 1;
            LATCbits.LATC5 = 0;      
    
            INTCONbits.IOCIE = 1;           // Enable interrupt on change  
            IOCAPbits.IOCAP0 = 1;           // IOC , positive edge
            IOCAN = 0x00;
            INTCONbits.PEIE = 1;            // Enable Peripheral Interrupts
            INTCONbits.GIE  = 1;            // Enable Global interrupt   
            IOCAFbits.IOCAF0 = 0;           // clear IOC flag
            INTCONbits.IOCIF = 0;           // clear flag            */
            //SLEEP();
            //Sleep mode setup                
            //asm("CLRF PCLATH");
            //asm("GOTO 0x00");
              
        }      
}         
            
/*
if(INTCONbits.IOCIF)
    {
                  
        if (IOCAFbits.IOCAF0)           //RB7 interrupt on change
        {
             IOCAFbits.IOCAF0 = 0;           // clear IOC flag
           uint8_t data[2]={2,3};
            CE = 0;
            SPI_init();
            nRF_Setup(); 
             FlushTXRX();
        WriteRegister(NRF_STATUS,0x70);         // Reset status register
        __delay_ms(2);
        
        CE = 1; //bez ovog
        //__delay_us(150); // bez
       WritePayload(2, data); 
       __delay_us(202);  // 130 us + Ttransmit???
       //__delay_ms(5); 
       FlushTXRX();
        
      WriteRegister(NRF_CONFIG, 0x00);        // turn off module
      __delay_ms(5);                
      
     //INTCONbits.IOCIE = 0;           // Disable interrupt on change   
   
    
        }       
       
        
    }

*/


