/*
 * File:   main.c
 * Author: Sourav Gupta
 * By:- circuitdigest.com
 * Created on April 1, 2018, 2:26 PM
 */
// PIC16F877A Configuration Bit Settings
// 'C' source line config statements
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "supporing_cfile\lcd.h"
#include "supporing_cfile\eusart1.h"
/*
 Hardware related definition
 */
#define _XTAL_FREQ 200000000 //Crystal Frequency, used in delay
/*
 Other Specific definition
 */
void system_init(void);
unsigned char incomer_data = 0;
unsigned char longitude[13];
unsigned char latitude[13];
unsigned int array_count=0;
/* Sample line received from the GPS :- 
[$GPGGA,100156.000,2690.9416,N,07547.8441,E,1,08,1.0,442.8,M,-42.5,M,,0000*71]
1. string always starts with a ?$? sign
2. GPGGA : Global Positioning System Fix Data
3. ?,? Comma indicates the separation between two values
4. 100156.000 : GMT time as 10(hr):01(min):56(sec):000(ms)
5. 2650.9416,N: Latitude 26(degree) 50(minutes) 9416(sec) North
6. 07547.8441,E: Longitude 075(degree) 47(minutes) 8441(sec) East
7. 1 : Fix Quantity 0= invalid data, 1= valid data, 2=DGPS fix
8. 08 :  Number of satellites currently viewed.
9. 1.0: HDOP
10. 442.8,M : Altitude (Height above sea level in meter)
11. -42.5,M : Geoids height
12. __ , DGPS data
13. 0000 : DGPS data
14. *71 : checksum 
*/     
void main(void) {
    TRISB = 0x00; // Setting as output
    system_init(); // System getting ready and initialising the LCD and USART driver.
    //LCD_ScrollMessage("Circuitdigest.com");
    while(1){           
        incomer_data=EUSART1_Read(); // Check the string '$GPGGA,'
/*------------------------------ Step by step finding the GPGGA line----------------------------*/
        if(incomer_data=='$'){ // First statement of the GPS data start with a $ sign
            incomer_data=EUSART1_Read(); // If the first if become true then the next phase
            if(incomer_data=='G'){
                incomer_data=EUSART1_Read();
                if(incomer_data=='P');{
                    incomer_data=EUSART1_Read();
                    if(incomer_data=='G');{
                    incomer_data=EUSART1_Read();
                    if(incomer_data=='G'){
                        incomer_data=EUSART1_Read();
                        if(incomer_data=='A'){
                            incomer_data=EUSART1_Read();
                            if(incomer_data==','){ // first , received
                                incomer_data=EUSART1_Read(); // At this stage Final check in done, GPGGA is found.
                                while (incomer_data != ','){ // skipping GMT Time 
                                    incomer_data=EUSART1_Read();
                                }
                                incomer_data=EUSART1_Read();
                                latitude[0] = incomer_data;                                
                                while(incomer_data != ','){
                                for(array_count=1;incomer_data!='N';array_count++){
                                    incomer_data=EUSART1_Read();
                                    latitude[array_count]=incomer_data; // Store the Latitude data
                                    }
                                    incomer_data=EUSART1_Read();
                                    if(incomer_data==','){
                                        for(array_count=0;incomer_data!='E';array_count++){
                                        incomer_data=EUSART1_Read();
                                        longitude[array_count]=incomer_data; // Store the Longitude data
                                        }
                                    }
                                    array_count=0;                                    
                                    //lcd_com(0x80); // LCD line one selection
                                    while(array_count<12){ // Array of Latitude data is 11 digit
                                        lcd_data(latitude[array_count]); // Print the Latitude data
                                        array_count++;
                                        }
                                    array_count=0;
                                    lcd_com(0xC0); // Lcd line two selection
                                    while(array_count<13){ // Array of Longitude data is 12 digit
                                        lcd_data(longitude[array_count]); // Print the Longitude data
                                        array_count++;
                                    }                                  
                                        //lcd_com(0x01); //clear LCD
                                }
                            }
                        }                        
                    }
                   }
                }
            }                                           
        }                            
                                for(array_count=0;array_count<=13;array_count++){
                                    incomer_data=0;
                                    latitude[array_count]=0;
                                    longitude[array_count]=0;
                                }
         array_count = 0;
    }    
}
/*
 This Function is for system initialisations.
 */
void system_init(void){
    lcd_init(); // This will initialise the lcd
    EUSART1_Initialize(); // This will initialise the Eusart
}