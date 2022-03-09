/*
 * File:   main.c
 * Author: Sourav Gupta
 *
 * Created on 11 April 2018, 17:57
 */

/*
 * Configuration Related settings. Specific for microcontroller unit.
 */

/*
 * System Header files inclusions
 */

#include <xc.h>
#include <string.h>
#include <ds18b20.h>
#define FOSC (8000000UL)
#define FCY (FOSC/2)
#include <libpic30.h>
/*
 * Ds18b20 related definition
 */

#define skip_rom 0xCC
#define	convert_temp 0x44 
#define	write_scratchpad 0x4E
#define	resolution_12bit 0x7F
#define read_scratchpad 0xBE

/*
 * User interface related definitions
 */

#define temp_gap  20

float pre_val=0, aft_val=0;

/*
 * Program flow related functions
 */

//void sw_delayms(unsigned int d);


/* Main function / single Thread*/
float getTemp(){
             
    //TRISDbits_t.TRISD6 = 1;
    unsigned short TempL, TempH;
	//unsigned int t, t2;
	//float difference1=0, difference2=0;          
    while(1){
        float i=0;
/* This is for presence detection of temp-sensing probe*/		
		   
		
        //lcd_puts ("                ");
		ow_reset();		
		write_byte(write_scratchpad);
	    write_byte(0);
		write_byte(0);
		write_byte(resolution_12bit); // 12bit resolution
		ow_reset();
		write_byte(skip_rom); 
		write_byte(convert_temp); 
		
		while (read_byte()==0xff);
			__delay_ms(500); 
			
			ow_reset();
			
			write_byte(skip_rom);
			write_byte(read_scratchpad);
		
			TempL = read_byte();
			TempH = read_byte();
            
	
	/*This is for positive Temperature*/
	
			i=((unsigned int)TempH << 8 ) + (unsigned int)TempL; //put both value in one variable
			i = i * 6.25;   //calculations used from the table provided in the data sheet of ds18b20		
            return i;
        } 
    return 0;
    }         
    