/* 
 * File:   prelab.c
 * Author: juane
 *
 * Created on 4 de abril de 2022, 05:36 PM
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>
#include <stdint.h>
/*------------------------------------------------------------------------------
 * CONSTANTES 
 ------------------------------------------------------------------------------*/
//#define _tmr0_value 60
#define BOTON PORTBbits.RB0     
#define BOTON1 PORTBbits.RB1     

void setup(void);

void __interrupt() isr (void){
    if(INTCONbits.RBIF){           
        if(!BOTON){                
            PORTC++;               
        }
        INTCONbits.RBIF = 0;    
        
        if(!BOTON1){                
            PORTC--;                 
        }
        
        INTCONbits.RBIF = 0;    
    }
    if(INTCONbits.T0IF){
        PORTD++;
        INTCONbits.T0IF = 0;
        TMR0 = 207;
    }
    return;
}

/*------------------------------------------------------------------------------
 * CICLO PRINCIPAL
 ------------------------------------------------------------------------------*/
void main(void) {
    setup();                        
    while(1){

    }
    return;
}

/*------------------------------------------------------------------------------
 * CONFIGURACION 
 ------------------------------------------------------------------------------*/
void setup(void){
    
    ANSEL = 0;
    ANSELH = 0b00000000;        
    
    TRISC = 0x00;               
    PORTC = 0;                  
    
    TRISB = 0b0011;     
    
    TRISD = 0x00;
    PORTD = 0;
    
    OPTION_REGbits.nRBPU = 0;   
    WPUB = 0b0011;         
    
    INTCONbits.GIE = 1;         
    INTCONbits.RBIE = 1;        
    IOCBbits.IOCB0 = 1;         
    IOCBbits.IOCB1 = 1;         
    INTCONbits.RBIF = 0;  
    
    OSCCONbits.IRCF = 0b011;
    OSCCONbits.SCS = 1;
    
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.T0SE = 0;
    OPTION_REGbits.PSA = 0;
    
    OPTION_REGbits.PS = 0b111;
    TMR0 = 207;
    INTCONbits.T0IF = 0;
    INTCONbits.T0IE = 1;
    
    return;
    
}
