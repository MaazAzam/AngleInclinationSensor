
//********************************************************************* 
//*                     	 Final Project                       	
//*                   	McMaster University                     	
//*                  	 2DP4 Microcontrollers                    	
//*                      	 Lab Section 06                       	
//*                  Maaz Azam azamm3 400069421           	      	
//*********************************************************************
//*********************************************************************
//*                          Description                             
//*                                                                                                            
//*********************************************************************
// Clock Speed of the Esduino is 6.25 MHz                          	//
//*********************************************************************
//*                            References                            
//* All Lectures & Tutorials
//* Application Note AN-1057
//* Project Specifications                                  	
//*********************************************************************
//*                       Compilation Notes                       	
//* Ensure project is cross-assembled under the Small memory model 	
//*********************************************************************
 
/*Include*/
#include <hidef.h>  	/* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "SCI.h"
 
/*Prototypes*/
void Lab4Delay1ms(unsigned int numTimes); //delay of 1ms
void OutCRLF(void); //prints new line in serial comm
void setClk(void); //sets clock speed to assigned speed
 
 /* DECLARE ALL YOUR GLOBAL VARIABLES BELOW*/
  /////////////////////////////////////////////////////
 
unsigned int counter;
unsigned short val;
unsigned int rem;
unsigned int divr;
unsigned int intang;
unsigned int mode;
unsigned int a;  

float arc;
float ang;	
 
float ref;
float zero;
float sens;
 
 	
 	
  /* DECLARE ALL YOUR GLOBAL VARIABLES ABOVE*/  
  /////////////////////////////////////////////////////
 
/* MAIN.C FOR LAB 4 YOU WILL NOT WRITE ANYTHING IN IT!!!!!!*/
void main(void) { 

  setClk();  	
 
 /* SET YOUR YOUR GLOBAL VARIABLES BELOW*/
  /////////////////////////////////////////////////////
  counter = 0;
  ref = 3.3;
  sens = 0.31;
  zero = 1.65;
  mode = 0;

 	
  /* SET YOUR YOUR GLOBAL VARIABLES ABOVE*/  
  /////////////////////////////////////////////////////
/* DECLARE ALL YOUR LOCAL VARIABLES BELOW*/
  /////////////////////////////////////////////////////
 
 
 	
  /* DECLARE ALL YOUR LOCAL VARIABLES ABOVE*/  
  /////////////////////////////////////////////////////
 	
  /* ESDUINO PORT CONFIGURATION BELOW (Don't Edit) */
  ///////////////////////////////////////////////////// 
  
  //ADC Configuration//
  
  ATDCTL1 = 0x2F;		// set for 10-bit ADC resolution
  ATDCTL3 = 0x88;		// right justified, one sample per sequence
	ATDCTL4 = 0x02;		// prescaler = 2; choose 1 MHz frequency for ATDCLK
	ATDCTL5 = 0x25;		// continuous conversion on channel 5 (assigned channel)

  //Set Ports

  DDR1AD = 0x1F; //configure AD ports 0-4, 6-7 as output pins
  DDR0AD = 0x0F; //configure AD ports 8-11 as output pins 
  DDRJ = 0xFF; //set all port J as output
  
/*
 * The next six assignment statements configure the Timer Input Capture                                          	     
 */       	
  TSCR1 = 0x90;	//Timer System Control Register 1
                	// TSCR1[7] = TEN:  Timer Enable (0-disable, 1-enable)
                	// TSCR1[6] = TSWAI:  Timer runs during WAI (0-enable, 1-disable)
                	// TSCR1[5] = TSFRZ:  Timer runs during WAI (0-enable, 1-disable)
                	// TSCR1[4] = TFFCA:  Timer Fast Flag Clear All (0-normal 1-read/write clears interrupt flags)
                	// TSCR1[3] = PRT:  Precision Timer (0-legacy, 1-precision)
                	// TSCR1[2:0] not used
 
  TSCR2 = 0x04;	//Timer System Control Register 2
                	// TSCR2[7] = TOI: Timer Overflow Interrupt Enable (0-inhibited, 1-hardware irq when TOF=1)
                	// TSCR2[6:3] not used
                	// TSCR2[2:0] = Timer Prescaler Select: See Table22-12 of MC9S12G Family Reference Manual r1.25 (set for bus/1)
 
                	
  TIOS = 0xFC; 	//Timer Input Capture or Output capture
                	//set TIC[0] and input (similar to DDR)
  PERT = 0x03; 	//Enable Pull-Up resistor on TIC[0] and TIC[1]
 
  TCTL3 = 0x00;	//TCTL3 & TCTL4 configure which edge(s) to capture
  TCTL4 = 0x0A;	//Configured for falling edge on TIC[0] (channel 0) and TIC[1] (channel 1)
 
/*
 * The next one assignment statement configures the Timer Interrupt Enable                                                  
 */       	
  
  TIE = 0x03;  	//Timer Interrupt Enable
 
/*
 * The next one assignment statement configures the ESDX to catch Interrupt Requests                                                  
 */       	
 
  SCI_Init(38400);
  SCI_OutString("Maaz Azam, 400069421");
  SCI_OutChar(CR);           

	EnableInterrupts; //CodeWarrior's method of enabling interrupts
  
   /////////////////////////////////////////////////////
  /*ESDUINO PORT CONFIGURATION ABOVE*/
 
	/* Esduino Loops Forever*/
  ////////////////////////////////////////////////////
  for(;;){
    
    if(counter == 0) {
      
    val = ATDDR0;
    //SCI_OutString("Analog Reading of Accelerometer: ");
    //SCI_OutUDec(val);
    //SCI_OutChar(CR);

    arc = (zero-((val*ref)/1024))/sens;
    
    if(arc >= 0 && arc <= 0.5) {
      
      ang = arc*60;
    } 
    
    else if(arc > 0.5 && arc <= 0.8) {
      
      ang = arc*65;
    } 
    
    else if(arc > 0.8 && arc <= 0.9) {
      
      ang = arc*69;
    } 
    
    else if(arc > 0.9 && arc <= 0.93) {
      
      ang = arc*72.1;
    } 
    
    else if(arc > 0.93 && arc <= 0.96) {
      
      ang = arc*76.1;
    }
    
    else if(arc > 0.96 && arc <= 0.985) {
      
      ang = arc*81;
    } 
    
    else if(arc > 0.985 && arc <= 0.9925) {
      
      ang = arc*83;
    }
    
    else if(arc > 0.9925 && arc <= 0.9975) {
      
      ang = arc*85;
    } 
    
    else if(arc > 0.9975) {
      
      ang = arc*89; 
    }
    
    
    intang = (int)ang;
    
    rem = intang%10;
    divr = intang/10;
    
    
    if(mode == 0) {
      
      PT1AD = rem;
      PT0AD = divr;
    }
  
    a = 0;
    
    if(mode == 1) {
    
      if(rem >= 5) {
        
        a = 1;
      }
      
      if(divr == 0) {
        
        PT1AD = a;
        PT0AD = 0;
      }
      
      if(divr == 1) {
        
        PT1AD = 1 + a*2;
        PT0AD = 0;
      }
      
      if(divr == 2) {
        
        PT1AD = 3 + a*4; 
        PT0AD = 0;
      }
      
      if(divr == 3) {
        
        PT1AD = 7 + a*8;
        PT0AD = 0;
      }
      
      if(divr == 4) {
        
        PT1AD = 15;
        PT0AD = a;
      }
      
      if(divr == 5) {
        
        PT1AD = 15;
        PT0AD = 1 + a*2;
      }
      
      if(divr == 6) {
        
        PT1AD = 15;
        PT0AD = 3 + a*4;
      }
      
      if(divr == 7) {
        
        PT1AD = 15;
        PT0AD = 7 + a*8;
      }
      
      if(divr == 8 && a == 1 || divr == 9) {
        
        PT1AD = 31;
        PT0AD = 15;
      }
    }
    
    //SCI_OutString("angle (in degrees): ");
    SCI_OutUDec(intang);
    SCI_OutChar(CR);
    Lab4Delay1ms(500);
    }
  }
}
 
  /* INTERRUPT SERIVE ROUTINES (ISRs) GO BELOW*/
  ///////////////////////////////////////////////////// 
 
/*
 * This is the Interrupt Service Routine for TIC channel 0 (Code Warrior has predefined the name for you as "Vtimch0"                                                   
 */       	
interrupt  VectorNumber_Vtimch0 void ISR_Vtimch0(void)
{
  /* DECLARE ALL YOUR LOCAL VARIABLES BELOW*/
  /////////////////////////////////////////////////////
  unsigned int temp; //DON'T EDIT THIS
 
 
  /* DECLARE ALL YOUR LOCAL VARIABLES ABOVE*/  
  /////////////////////////////////////////////////////
 
	/* YOUR CODE GOES BELOW*/
  ////////////////////////////////////////////////////
	
  if(counter == 0) {
  
    counter = 1;
	
	  //SCI_OutString("Esduino is ready for operation");
	  //SCI_OutChar(CR);
	} else {
	  
	  counter = 0;
	  //SCI_OutString("Esduino is NOT ready for operation");
	  //SCI_OutChar(CR);
	}
	
	Lab4Delay1ms(500);
	

 	/* YOUR CODE GOES ABOVE*/
  //////////////////////////////////////////////////// 
 
  /* RESETS INTERRUPT (Don't Edit)*/
  //////////////////////////////////////////////////// 
  temp = TC0;   	//Refer back to TFFCA, we enabled FastFlagClear, thus by reading the Timer Capture input we automatically clear the flag, allowing another TIC interrupt
  }
 
 /*
 * This is the Interrupt Service Routine for TIC channel 1 (Code Warrior has predefined the name for you as "Vtimch1"                                                   
 */       	
interrupt  VectorNumber_Vtimch1 void ISR_Vtimch1(void)
{
  /* DECLARE ALL YOUR LOCAL VARIABLES BELOW*/
  /////////////////////////////////////////////////////
  unsigned int temp; //DON'T EDIT THIS
 
 
  /* DECLARE ALL YOUR LOCAL VARIABLES ABOVE*/  
  /////////////////////////////////////////////////////
 
	/* YOUR CODE GOES BELOW*/
  ////////////////////////////////////////////////////
  if(mode == 0) {
    
    mode = 1;
  } 
  
  else {
    
    mode = 0;
  }
 
  Lab4Delay1ms(500);
 
 	/* YOUR CODE GOES ABOVE*/
  //////////////////////////////////////////////////// 
 
  /* RESETS INTERRUPT (Don't Edit)*/
  //////////////////////////////////////////////////// 
  temp = TC1;   	//Refer back to TFFCA, we enabled FastFlagClear, thus by reading the Timer Capture input we automatically clear the flag, allowing another TIC interrupt
  }
 
/* FUNCTIONS GO BELOW: Don't Edit */
 
// Lazy delay function to waste time for 1ms. Avoids the use of the timer, which is being used elsewhere
void Lab4Delay1ms(unsigned int numTimes){
  unsigned int i;
  unsigned int j;
 
  for(j = 0; j<numTimes; j++){
	for(i = 0; i<68; i++){
  	// Delay
  	PTJ = PTJ;
  	PTJ = PTJ;
  	PTJ = PTJ;
  	PTJ = PTJ;
  	PTJ = PTJ;
	}
  }  
}

void setClk(void) {

  CPMUPROT = 0x00; //disable clock write protections               
  CPMUCLKS = 0x80; //PLLSEL = 1, selecting bus clock
  CPMUOSC = 0x80; //OSCE = 1, and oscillator freq reference = 8 MHz, fref = 1 MHz
  CPMUREFDIV = 0x41; //REFFRQ = 1, REFDIV = 1, set ref divider & freq range
  
  //f_ref = f_osc/(REFDIV + 1) , 
  
  CPMUSYNR = 0x02; //VCOFRQ = 0, SYNDIV = 2, set VCLOCLK freq range
  
  //VCOCLK = f_vco = 2 * f_ref * (SYNDIV + 1) 
  
  CPMUPOSTDIV=0x03; //POSTDIV = 3, set post divide
  
  //PLLCLK = VCO_clk/(POSTDIV + 1)           

  CPMUPROT = 1; //enable clock write protections
  CPMUFLG = 0x08; //lock = 1, reflects current state of PLL lock condition   
}









