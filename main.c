None selected 

Skip to content
Using Gmail with screen readers

1 of 20,637
(no subject)
Inbox

MIN A ZAW
Attachments
10:07 AM (3 minutes ago)
to ZHIQIAN, me


 One attachment
  •  Scanned by Gmail
/* ************************************************************************** */
/** Create a DELAY based on a Timer1 interrupt                                */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
#include "config_bits.h"
#include "hardware.h"
#include <plib.h>



int main(void)
{
    // Initialize Basys MX3 IO hardware DO NOT MODIFY
    Hardware_Setup();        
    
    // Enable multi-vector interrupts DO NOT MODIFY
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);  // Do only once
    INTEnableInterrupts();   // Do as needed for global interrupt control
    __asm__ __volatile__(
            
            
            
/* ************************************************************************** */         
    /* Begin INITIAL subroutine code */            
            /* begin HARDWARE setup */ 
                // use a register for a rollover parameter
                        "li $s2, 0  \n\t"

                // initialize PORTA and PORTC as output
                        "la $s0, TRISACLR   \n\t"
                        "li $t0, 0b0000000000000011  \n\t"
                        "sw  $t0, 0($s0) \n\t"        

                        "la $s0, TRISCCLR   \n\t"
                        "li $t0, 0b0000000000001000  \n\t"
                        "sw  $t0, 0($s0) \n\t" 

                // output low at pins of PORTA and PORTC   
                        "la $s0, PORTACLR   \n\t"
                        "li $t0, 0b0000000000000011  \n\t"
                        "sw  $t0, 0($s0) \n\t"         

                        "la $s0, PORTCCLR   \n\t"
                        "li $t0, 0b0000000000001000  \n\t"
                        "sw  $t0, 0($s0) \n\t" 
            /* end HARDWARE setup */ 

            /* begin TIMER1 setup */ 
                // configure Timer1 control register bits
                // NOTE: Bus clock is running at (10 MHz)
                    //----- Write your code starting here
                        "la   $s0, T1CON              \n\t"
                        "li   $t0, 0x9030             \n\t"
                        "sw   $t0, 0($s0)             \n\t"

                        "la   $s0, TMR1               \n\t"
                        "sw   $zero, 0($s0)           \n\t"
            

                // Set Timer1 roll over period to 0.5 sec
                // NOTE: Timer1 clock is running at (bus clock freq.)/prescale
                    //----- Write your code starting here
                        "la   $s0, PR1                \n\t"
                        //"li   $t0, 6666666              \n\t"
                        "li   $t0, 39062              \n\t"
                        //"li   $t0, 19531              \n\t"
                        "sw   $t0, 0($s0)             \n\t"
            
            
            /* end TIMER1 setup */ 
            
            /* begin INTERRUPT setup */
                // enable timer 1 interrupt               
                    //----- Write your code starting here
                        "la   $s0, IEC0SET            \n\t"
                        "li   $t0, 0x0010             \n\t"
                        "sw   $t0, 0($s0)             \n\t"
            
            
                // set up the timer interrupt with a priority of 2 
                    //----- Write your code starting here
                        "la   $s0, IPC1SET            \n\t"
                        "li   $t0, 0x0008             \n\t"
                        "sw   $t0, 0($s0)             \n\t"
            
            
            /* end INTERRUPT setup */
    /* end INITIAL subroutine code */            
/* ************************************************************************** */
                   
            
            
/* ************************************************************************** */            
    /* begin MAIN loop */  
          "MainLoop:  \n\t"       
            
            // inner loop waiting for rollover
                //----- Write your code starting here
                    "WaitRoll:                      \n\t"
                    "beq  $s2, $zero, WaitRoll      \n\t"
                    "nop                            \n\t"  
            
            
            // set rollover parameter in register to value 0            
                    "li $s2, 0  \n\t"

            // toggle pin LED0 to test delay functionality by inspection                               
                    "la $s0, PORTAINV   \n\t"
                    "li $t0, 0b000000000000001  \n\t"
                    "sw  $t0, 0($s0) \n\t" 
 
            // toggle pin RC3 of PORTC to measure delay using oscilloscope                 
                    "la $s0, PORTCINV   \n\t"
                    "li $t0, 0b000000000001000  \n\t"
                    "sw  $t0, 0($s0) \n\t" 
        
           
        "j MainLoop \n\t"
    /* end MAIN loop  */              
/* ************************************************************************** */
              
              
    );            
    return (EXIT_FAILURE);  // System has failed if this line is reached
} 

/*  ********************************************
 * Interrupt service routine (ISR) for TIMER1 interrupt.
 * Used to create a delay.
 * The LED1 is toggled and the variable $s2 is set
 * each time the interrupt is triggered by TIMER1 roll over.
 * The Timer 1 interrupt flag must be reset.
 * *******************************************************/
void __ISR(_TIMER_1_VECTOR, IPL2SOFT) Timer1Handler(void)
{__asm__ __volatile__(
            
        
/* ************************************************************************** */
    /* begin ISR code */ 
        
    // set rollover flag parameter value 1
       "li $s2, 1  \n\t"

    // toggle LED1 to signal interrupt service
       "la $s0, PORTAINV   \n\t"
       "li $t0, 0b0000000000000010  \n\t"
       "sw  $t0, 0($s0) \n\t"         
            
    // clear TIMER1 interrupt FLAG              
        //----- Write your code starting here
       "la   $s0, IFS0CLR                  \n\t"
       "li   $t0, 0x0010                   \n\t"
       "sw   $t0, 0($s0)                   \n\t" 
        
        
        
    /* end ISR code */ 
/* ************************************************************************** */
        
    );
}
//END OF PROGRAM
lab4 done.txt
Displaying lab4 done.txt.
