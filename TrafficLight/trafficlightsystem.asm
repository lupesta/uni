/*
* filename: Final Traffic Light Finite State Machine
* Author: Luke Pestaille
* Date: 5/12/22
* Revision Number: 4
* Target Device: PIC18F452
* Compiler: XC8
* Summary: In this final implementation the ped crossing and the side road sensor have been implemented so that both buttons work and all the states work
*/

 
//Configuration statements

// PIC18F452 Configuration Bit Settings
// 'C' source line config statements

// CONFIG1H
#pragma config OSC = HS         // Oscillator Selection bits (HS oscillator)
#pragma config OSCS = OFF       // Oscillator System Clock Switch Enable bit (Oscillator system clock switch option is disabled (main oscillator is source))

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bit (Brown-out Reset disabled)
#pragma config BORV = 20        // Brown-out Reset Voltage bits (VBOR set to 2.0V)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 128      // Watchdog Timer Postscale Select bits (1:128)

// CONFIG3H
#pragma config CCP2MUX = ON     // CCP2 Mux bit (CCP2 input/output is multiplexed with RC1)

// CONFIG4L
#pragma config STVR = ON        // Stack Full/Underflow Reset Enable bit (Stack Full/Underflow will cause RESET)
#pragma config LVP = OFF         // Low Voltage ICSP Enable bit (Low Voltage ICSP enabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-001FFFh) not code protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-001FFFh) not write protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-001FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from Table Reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from Table Reads executed in other blocks)

// #pragma config statements should precede project file includes.

// Use project enums instead of #define for ON and OFF.

//Included Files

#include <xc.h>     // XC8 compiler specifics

//Definitions
#define MAINROADRED   PORTBbits.RB0
#define MAINROADAMBER PORTBbits.RB1
#define MAINROADGREEN PORTBbits.RB2
#define SIDEROADRED   PORTBbits.RB3
#define SIDEROADAMBER PORTBbits.RB4
#define SIDEROADGREEN PORTBbits.RB5
#define PEDCROSSINGRED   PORTBbits.RB6
#define PEDCROSSINGGREEN PORTBbits.RB7

#define OUTPIN PORTBbits.RA0 //Output pin
#define OUTCFG TRISD //Port A Direction
#define INPIN PORTAbits.RB0 //Input pin
#define IPCFG TRISA //Port B direction

//Global Variables

int pedCrossing =0; // this is the integer variable that will be used to check if the ped crossing button has been pressed
int SideRoadSensor =0; // this is the integer variable that will be used to check if the side road sensor has been pressed
  
//functions
void setup(void); // this will initialise the setup function which is used to set up the interrupt control registers
void shortdelay(void); // the shortest of delays and is used for the shorter traffic light transitions
void mediumdelay(void); // the second longest delay and is used for when the side road is green
void longdelay(void); // the longest delay and used when the main road is green, or the side road sensor is set and side road is green 

//Interrupt Functions that will be used for the two buttons 
void __interrupt() HighInt(void){ // the interupt function is of high priority
 if(INTCONbits.INT0F){ //test for external 0 flag which is the upper button on the PIC
 INTCONbits.INT0F=0; //Resets the interrupt flag
 pedCrossing = 1; // the ped crossing variable needs to be set to one to allow the ped crossing to go to green on the next red/red main/side combo
 }
 if(INTCON3bits.INT1IF){ //test for external 1 flag which is the lower button on the PIC
 INTCON3bits.INT1IF=0; //Resets the interrupt flag
 SideRoadSensor =1; // the side road sensor variable needs to be set to allow the longer phase of side road to go through
 }
 return; // this allows us to leave the interrupt and return to the code that we are running
}
 
//Main Function
void main(void){
setup(); //the setup function is called at the start of the main function to ensure that all of interrupt bits are set

state1:
if (SideRoadSensor == 1){
    PORTD = 0b01011110; // this outputs: a red for the main road, a green for the side road, and red on the ped crossing
    longdelay(); // the long delay is used to allow many cars to go through which is needed if the side road sensor is pressed
}
if (SideRoadSensor == 0){
     PORTD = 0b01011110; //this outputs: a red for the main road, a green for the side road, and red on the ped crossing
     mediumdelay(); //this delay needs to be longer than the short delay as the green phase always lasts longer than the 
}
SideRoadSensor = 0; // we need to set the side road sensor back to zero to reset it
goto state2; // we then move on to the next state


state2:
PORTD = 0b01101110; //this outputs: a red for the main road, an amber for the side road, and red on the ped crossing
shortdelay();
goto state3; // we then move on to the next state


state3:
if (pedCrossing ==1){
    PORTD = 0b01110110; //this outputs a red for the main road, a red for the side road, and red on the ped crossing
    mediumdelay(); // the delay here is used in case a car is going to go through a red light
    PORTD = 0b10110110; //this outputs a red for the main road and an red for the side road, and green on the ped crossing
    longdelay(); // the long delay allows for enough time for all of the pedestrians to get over the crossing
    PORTD = 0b01110110; // this outputs a red for the main road and an red for the side road, and red on the ped crossing
    mediumdelay(); // the delay here is needed as we do not want the pedestrian crossing turning green as soon as both lights are red
}
if (pedCrossing ==0){
PORTD = 0b01110110; //this outputs a red for the main road and an red for the side road
mediumdelay();
}
pedCrossing = 0; // we need to reset the flag back to zero to allow it to go default to the normal loop
goto state4; // we then move on to the next state


state4:
PORTD = 0b01110100; //this outputs a red/amber for the main road and a red for the side road
shortdelay();
goto state5; // we then move on to the next state


state5:
PORTD = 0b01110011; //this outputs a green for the main road and a red for the side road
longdelay(); // the long delay here is used as we are giving the main road a longer 
goto state6; // we then move on to the next state


state6:
PORTD = 0b01110101; //this outputs a amber for the main road and a red for the side road
shortdelay();
goto state7; // we then move on to the next state


state7:
if (pedCrossing ==1){
    PORTD = 0b01110110; // this outputs a red for the main road and an red for the side road with a red on the crossing
    mediumdelay(); // the delay here is needed as we do not want the pedestrian crossing turning green as soon as both lights are red
    PORTD = 0b10110110; //this outputs a red for the main road and an red for the side road with a green on the crossing
    longdelay(); // the long delay allows for enough time for all of the pedestrians to get over the crossing
    PORTD = 0b01110110; // this outputs a red for the main road and an red for the side road with a red on the crossing
    mediumdelay(); // the delay here is needed as we do not want the pedestrian crossing turning green as soon as both lights are red
}
if (pedCrossing ==0){
PORTD = 0b01110110; //this outputs a red for the main road and an red for the side road
mediumdelay();
}
pedCrossing = 0; // we need to reset the flag back to zero to allow it to go default to the normal loop
goto state8; // we then move on to the next state


state8:
PORTD = 0b01100110; //this outputs a red for the main road and a red/amber for the side road
shortdelay();
goto state1; // we then move back to the start again
}

//The setup function which allows us to look at all of the interrupt control bits that are set 

void setup(void) {
    OUTCFG = 0;
    PORTB = 1;
    INTCON2bits.RBPU=0; // Port B inputs all have weak pull-ups, thus turn them all on
    INTCON3bits.INT1P=1; // Port B inputs all have weak pull-ups, thus turn them all on
    INTCON3bits.INT1IE=1; // Port B inputs all have weak pull-ups, thus turn them all on
    ADCON1bits.PCFG=0b0111; //Configures all Port A bits as digital
    INTCON=0b10010000; //Sets Global & Ext int 0 enable
}

void shortdelay(void){
    unsigned int i;
    unsigned int j;
    for(j=0;j<80;j++){
        for(i=0;i<10000;i++){
        }
    }
}

void mediumdelay(void){
    unsigned int k;
    unsigned int l;
    for(l=0;l<150;l++){
       for(k=0;k<10000;k++){
        }
    }
}

void longdelay(void){
    unsigned int m;
    unsigned int n;
    for(n=0;n<400;n++){
        for(m=0;m<10000;m++){
    }
}
}