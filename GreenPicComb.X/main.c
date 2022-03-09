/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.0
        Device            :  PIC24FJ256GA705
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.70
        MPLAB 	          :  MPLAB X v5.50
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

// Setting OSC values
#define FOSC (8000000UL)
#define FCY (FOSC/2)
#define _XTAL_FREQ 8000000

// Defining the inputs
#define Swater1 PORTAbits.RA2
#define Swater2 PORTAbits.RA3
#define Swater3 PORTAbits.RA13
#define Swater4 PORTBbits.RB3
#define STemp PORTCbits.RC0
#define pic1 PORTCbits.RC1
#define pic2 PORTCbits.RC2

// defining the outputs
#define Plight (PORTBbits.RB1)
#define Pmain (PORTAbits.RA8)
#define Pbase (PORTAbits.RA9)
#define Pacid (PORTAbits.RA14)
#define Pnutrient (PORTBbits.RB0)
#define Pwater (PORTCbits.RC3)
#define Pfan (PORTCbits.RC4)
#define Paer (PORTAbits.RA2)

// temp
#define DS18B20_PIN      PORTCbits.RC0
#define DS18B20_PIN_Dir  TRISCbits.TRISC0

// adding the includes
#include "mcc_generated_files/system.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <xc.h>



#define address 99
// renaming pins & setting initial state

// adding a default sensor state struct
typedef struct{
    float pH; // pH
    float EC;   // EC
    float temp; // Temp
    int water;  // Water Level
}SENSOR_READ;

 uint8_t str[53] = {'0'};
 uint16_t raw_temp;
 char temp[] = "000.0000 C";
/*
                         Main application
*/
// grabs the pH from the ADC
uint16_t grabpH(){   
    
    // enabling the ADC
    ADC1_Enable();
    // setting the channel
    ADC1_ChannelSelect(channel_AN4);  
    // enabling the trigger
    ADC1_SoftwareTriggerEnable();
    // letting the ADC Capture data
    __delay_ms(100);
    // ending the capture period
    ADC1_SoftwareTriggerDisable();
    // allowing the ADC to compile
    while(!ADC1_IsConversionComplete(channel_AN4));
    // saving the returned value
    uint16_t conversion = ADC1_ConversionResultGet(channel_AN4);
    // disabling ADC channel for power saving
    ADC1_Disable(); 
    
    return conversion;
}

// grabs the EC Data
// TODO: change to UART from I2C / Cleanup
float grabEC(){
    /*
    LATBbits.LATB6 = 0;   //where LATBx = the SDAx pin
    LATBbits.LATB6 = 1;
    uint8_t data[32] = {0};
    uint8_t * pdata = &data[0];
    I2C1_MESSAGE_STATUS * pstatus;
    uint8_t send = 'R';
    uint8_t *psend = &send;                                                                //reset i, we will need it later 
    I2C1_MasterWrite(
                                psend,
                                1,
                                address,
                                pstatus);
    __delay_ms(600);     
    //wait the correct amount of time for the circuit to complete its instruction.
     I2C1_MasterRead(
                                pdata,
                                32,
                                address,
                                pstatus);                     //receive a byte.
                            //load this byte into our array.
                                        //call the circuit and request 32 bytes (this could be too small, but it is the max i2c buffer size for an Arduino)
     /*
     code = *pdata;                                                      //the first byte is the response code, we read this separately.
     
      while (bool I2C1_MasterQueueIsEmpty(){         //are there bytes to receive.
        in_char = Wire.read();                   //receive a byte.
        ec_data[i] = in_char;                    //load this byte into our array.
        i += 1;                                  //incur the counter for the array element.
        if (in_char == 0) {                      //if we see that we have been sent a null command.
          i = 0;                                 //reset the counter i to 0.
          break;                                 //exit the while loop.
        }
      }
*/
      
    
    
    /*
    // arduino test
    char *ec;                        //char pointer used in string parsing.
    char *tds;                       //char pointer used in string parsing.
    char *sal;                       //char pointer used in string parsing.
    char *sg;                        //char pointer used in string parsing.

    float ec_float;                  //float var used to hold the float value of the conductivity.
    float tds_float;                 //float var used to hold the float value of the TDS.
    float sal_float;                 //float var used to hold the float value of the salinity.
    float sg_float;                  //float var used to hold the float value of the specific gravity.

        

    ec = strtok((char*)pdata, ",");          //let's pars the string at each comma.
    tds = strtok(NULL, ",");            //let's pars the string at each comma.
    sal = strtok(NULL, ",");            //let's pars the string at each comma.
    sg = strtok(NULL, ",");             //let's pars the string at each comma.
    
    ec_float=atof(ec);
    tds_float=atof(tds);
    sal_float=atof(sal);
    sg_float=atof(sg);
    */
    return 0 ;
    //ec_float;
   
    } 
    
// grabs the water level from the input pins
int grabWater(){
    // 4 is the highest level
    if (Swater4 == 1) {
       // const char* str[4] = "w100";
        return 4;
    }
    // 3 is the second highest level
    else if (Swater3 == 1){
        //static char* str[3] = "w75";
        return 3;
    }
    // 2 is the third highest level
    else if (Swater2 == 1){
        //static char* str[3] = "w50";
        return 2;
    }
    // 1 is the lowest level
    else if (Swater1 == 1){
        //static char* str[3] = "w25";
        return 1;
    }
    // defaulting to 0
    else {
        //static char* str[2] = "w0";
        return 0;
    }
}
int ds18b20_start()
{
  DS18B20_PIN = 0;      // send reset pulse to the DS18B20 sensor
  DS18B20_PIN_Dir = 0;  // configure DS18B20_PIN pin as output
  __delay_us(500);      // wait 500 us
 
  DS18B20_PIN_Dir = 1;  // configure DS18B20_PIN pin as input
  __delay_us(100);      // wait 100 us to read the DS18B20 sensor response
 
  if (!DS18B20_PIN)
  {
    __delay_us(400);    // wait 400 us
    return 1;           // DS18B20 sensor is present
  }
 
  return 0;   // connection error
}
 
void ds18b20_write_bit(uint8_t value)
{
  DS18B20_PIN = 0;
  DS18B20_PIN_Dir = 0;  // configure DS18B20_PIN pin as output
  __delay_us(2);        // wait 2 us
 
  DS18B20_PIN = (int)value;
  __delay_us(80);       // wait 80 us
 
  DS18B20_PIN_Dir = 1;  // configure DS18B20_PIN pin as input
  __delay_us(2);        // wait 2 us
}
 
void ds18b20_write_byte(uint8_t value)
{
    uint8_t i;
  for(i = 0; i < 8; i++)
    ds18b20_write_bit(value >> i);
}
 
int ds18b20_read_bit(void)
{
  static int value;
 
  DS18B20_PIN = 0;
  DS18B20_PIN_Dir = 0;  // configure DS18B20_PIN pin as output
  __delay_us(2);
 
  DS18B20_PIN_Dir = 1;  // configure DS18B20_PIN pin as input
  __delay_us(5);        // wait 5 us
 
  value = DS18B20_PIN;  // read and store DS18B20 state
  __delay_us(100);      // wait 100 us
 
  return value;
}
 
uint8_t ds18b20_read_byte(void)
{
  uint8_t value = 0;
 uint8_t i; 
  for(i = 0; i < 8; i++)
    value |= ds18b20_read_bit() << i;
 
  return value;
}
 
int ds18b20_read(uint16_t *raw_temp_value)
{
  if (!ds18b20_start())   // send start pulse
    return 0;             // return 0 if error
 
  ds18b20_write_byte(0xCC);   // send skip ROM command
  ds18b20_write_byte(0x44);   // send start conversion command
 
  while(ds18b20_read_byte() == 0);  // wait for conversion complete
 
  if (!ds18b20_start())  // send start pulse
    return 0;            // return 0 if error
 
  ds18b20_write_byte(0xCC);  // send skip ROM command
  ds18b20_write_byte(0xBE);  // send read command
 
  // read temperature LSB byte and store it on raw_temp_value LSB byte
  *raw_temp_value  = ds18b20_read_byte();
  // read temperature MSB byte and store it on raw_temp_value MSB byte
  *raw_temp_value |= (uint16_t)(ds18b20_read_byte() << 8);
 
  return 1;   // OK --> return 1
}
 
float grabTemp()
{
    float temp;
    // reads from the sensor, stores the value as raw
    if(ds18b20_read(&raw_temp)){
        // use negative calculation
        if (raw_temp > 2000){
            temp = (((((float)raw_temp - 65536)/16) * 9/5) + 32);
        }
        // use positive calculation
        else {
            temp = ((((float)raw_temp/16) * 9/5) + 32);
        }
    }
}
// updates the sensors
// TODO: add in EC  / Water Sensors
SENSOR_READ updateSensor(){
    SENSOR_READ sensors;
    
    // grabs pH & converts to value
    int pHRaw = grabpH();
    sensors.pH = (((float)pHRaw - 851.06)/(-54.911));
    //sensors.EC =  grabEC();
    
    // grabs the temp;
    sensors.temp = grabTemp();
    
    //sensors.water = grabWater();
    sensors.EC = 1740;
    sensors.water = 4;
    
    return sensors;
}

// grabs the input pin states and sensors and compiles into an instruction enum
INSTRUCTION updatePICState(SENSOR_READ sensors){   
    INSTRUCTION inst;
    // saving sensor state
    inst.pH = sensors.pH;
    inst.EC = sensors.EC;
    inst.temp = sensors.temp;
    inst.waterLevel = sensors.water;
    // saving pump state
    inst.light = Plight;
    inst.pnutrition = Pnutrient;
    inst.pacid = Pacid;
    inst.pbase = Pbase;
    inst.pwater = Pwater;
    inst.ppump = Pmain;
    inst.fan = Pfan;
    inst.paer = Paer;
    // setting config bit    
    inst.isConfig = 0;
    inst.micro = 0;    
    
    return inst;
}

// the controller for the demo
void controller(INSTRUCTION inst){
    //trigger pump
    if (inst.ppump == 1){
        Pmain = 0;    
    }
    else { Pmain = 1; }
    //trigger pwater
     if (inst.pwater == 1){
        Pwater = 0;    
    }
     else { Pwater = 1; }
    //trigger pnutrition
     if (inst.pnutrition == 1){
        Pnutrient = 0;    
    }
     else { Pnutrient = 1; }
    //trigger pbase
     if (inst.pbase == 1){
        Pbase = 0;    
    }
     else { Pbase = 1; }
    //trigger pacid
     if (inst.pacid == 1){
        Pacid = 0;    
    }
    else { Pacid = 1; }
    //trigger fan
     if (inst.fan == 1){
        Pfan = 0;    
    }
    else { Pfan = 1; }
    //trigger light
    if (inst.light == 1){
        Plight = 0;    
    }
    else { Plight = 1; }
    if (inst.paer == 1){
        Paer = 0;
    }
    else {Paer = 1;}
    
    //__delay_ms(500);
    
}

void instCompiler(INSTRUCTION inst){
    // create empty string and iterator
    
    // add starting identifiers
    uint8_t startStr[] = {"<m0,c0,"};    
    sprintf(str,"%st%04.1f,h%04.1f,e%i,w%i,a%i,b%i,n%i,f%i,l%i,p%i,x%i,r%i>;",startStr,inst.temp,inst.pH,inst.EC,inst.waterLevel,inst.pacid,inst.pbase,inst.pnutrition,inst.fan,inst.light,inst.ppump,inst.pwater,inst.paer);
    
}

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();    
    while(1){
       
        // Read updated data
        
        //readUart2();
        //SENSOR_READ sensorData = updateSensor();        
        //writeUart1(compiler(false, sensorData));
        
       
        //__delay_ms(1000);
        
        //writeUart1(compiler(true,sensorData));
        //updatePIC();
        //INSTRUCTION inst;
        //writeUart2(compiler(true, sensorData));
        /*
        uint8_t string[] = "<m0,cy,t14.5,h10.4,e1740,w6,p1,n0,a1,b1,x0,l1,f1>;";
        uint8_t string1[] = "<m0,cy,t14.5,h10.4,e1740,w6,p0,n1,a0,b0,x1,l0,f0>;";
        uint8_t string2[] = "<m0,cy,t14.5,h10.4,e1740,w6,p0,n0,a1,b1,x0,l0,f1>;";
        uint8_t string3[] = "<m0,cy,t14.5,h10.4,e1740,w6,p0,n1,a0,b1,x0,l1,f0>;";
        uint8_t * pstring = &string[0];
        uint8_t * pstring1 = &string1[0];
        uint8_t * pstring2 = &string2[0];
        uint8_t * pstring3 = &string3[0];
        
        int i = 0;
        for (i =0; i<4; i++){
            switch(i){
                case 0:
                    inst = splitter(pstring);
                    controller(inst);
                    break;
                case 1:
                    inst = splitter(pstring1);
                    controller(inst);
                    break;
                case 2:
                    inst = splitter(pstring2);
                    controller(inst);
                    break;
                case 3:
                    inst = splitter(pstring3);
                    controller(inst);
                    break;
            }
            __delay_ms(250);
        }
        */
        
        
        // resets the string
        uint8_t string[53] = {0};
        uint8_t pstring = &string[0];
        
        
        // takes a new command 
        readUart1();
        
        // controlls based on that command
        controller(splitter());
        __delay_ms(10);
        // compiles current states
        instCompiler(updatePICState(updateSensor()));
        
        // sends those current states to the PI
        int i;
        for(i = 0; i < strlen(str); i++){         
            UART1_Write(str[i]);
        }   
        
        // waits
        __delay_ms(10);
        
    }
    return 1;
}
/**
 End of File
*/

