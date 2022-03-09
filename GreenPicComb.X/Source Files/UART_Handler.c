
#include "UART_Handler.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "xc.h"

uint8_t string[53];
//void parser(uint8_t * string){
    
//}
int myAtoi(uint8_t* str, int length)
{
    // Initialize result
    int res = 0;
 
    // Iterate through all characters
    // of input string and update result
    // take ASCII character of corresponding digit and
    // subtract the code from '0' to get numerical
    // value and multiply res by 10 to shuffle
    // digits left to update running total
    int i = 0;
    for (i = 0; i < length; ++i)
        
        res = res * 10 + ((int)str[i] - 48);
 
    // return result.
    return res;
}

double myAtof(uint8_t* str, int length)
{
    // Initialize result
    double res = 0;
 
    // Iterate through all characters
    // of input string and update result
    // take ASCII character of corresponding digit and
    // subtract the code from '0' to get numerical
    // value and multiply res by 10 to shuffle
    // digits left to update running total
    int i = 0;
    for (i = 0; i < length; ++i)
        if (str[i] == '.'){
            i++;
            res = res + (((double)((int)str[i] - 48))/10);
        }
        else {res = res * 10 + ((int)str[i] - 48);}
 
    // return result.
    return res;
}
INSTRUCTION splitter(){
    
    int i = 0;
    
    /*uint8_t string[53] = {0};
    for (i = 0; i < 53; i++){
        string[i] = string1[i];
    }
    i = 0;
    */
    INSTRUCTION tInst;
    
    while (i<53){
        int l = i;
        switch(string[i]){
            case '<':
                i++;
                break;
                /*
            case '>': 
                inst[j] = tInst;
                j++;
                i++;
                break;
                */
            case ',': 
                i++;
                break;
            case 'c':
                l++;
                tInst.isConfig = ((int)string[l]-48);
                i++;
                break;
            case 'm': {
                l++;
                tInst.micro = ((int)string[l]-48);
                i++;
                break;
            }
            case 't': {
                uint8_t temp[4];
                int k = 0;
                for (k = 1; k < 5; k++){
                    temp[k-1] = string[(l + k)];
                }
                tInst.temp = myAtof(temp,4);
                i++;
                break;
            }
            case 'h': {
                uint8_t temp[4];
                int k = 0;
                 for (k = 1; k < 5; k++){
                    temp[k-1] = string[(l+k)];
                }
                tInst.pH =  myAtof(temp,4);
                i++;
                break; 
            }
            case 'e': {
                uint8_t temp[4];
                int k = 0;
                for (k = 1; k < 5; k++){
                    temp[k-1] = string[(l+k)];
                }
                tInst.EC =  myAtoi(temp, 4);
                i++;
                break;   
            }
            case 'w':               
                l++;
                tInst.waterLevel = ((int)string[l]-48);
                i++;
                break; 
            case 'a':
                l++;
                tInst.pacid = ((int)string[l]-48);
                i++;
                break;
            case 'b':
                l++;
                tInst.pbase = ((int)string[l]-48);
                i++;
                break;
            case 'n':
                l++;
                tInst.pnutrition = ((int)string[l]-48);
                i++;
                break;
            case 'f':
                l++;
                tInst.fan = ((int)string[l]-48);
                i++;
                break;
            case 'l':
                l++;
                tInst.light = ((int)string[l]-48);
                i++;
                break;             
            case 'p':
                l++;
                tInst.ppump = ((int)string[l]-48);
                i++;
                break;    
            case 'x':
                l++;
                tInst.pwater = ((int)string[l]-48);
                i++;
                break;
            case 'r':
                l++;
                tInst.paer = ((int)string[l]-48);
                i++;
                break;
            default:
                    i++;
                    
                
        }
    }
    //free(string);
    return tInst;
}

void readUart1(){
    //uint8_t c;
    //c = UART1_Read();
    //*U1recInst[3][10][10] = NULL;
    int i;
    
    //U1STAbits.URXEN = 1;
    for (i = 0; i < 53; i++){        
        string[i] = UART1_Read();
    }
    
   // uint8_t * pstring ;
   // pstring = (uint8_t *)malloc(53);
   // strcpy(pstring, string);
    //writeUart1(*string);
    /*
        int i = 0, j = 0, k = 0;
        while(c != ';'){
         
            if(c == '<'){
                    if (i == 0){                   
                        c = UART1_Read();
                    }
                    if (i != 0){
                        i++;
                        *U1recInst[i][j][k] = c;
                        c = UART1_Read();
                    }              
                }
                else if(c == '>'){
                    c = UART1_Read();
                    j = 0, k = 0;               
                }
                else if(c == ','){
                        j++;
                        k = 0;
                        c = UART1_Read();                             
                    }                
                else if (c == '.'){
                        *U1recInst[i][j][k] = c;
                        k++;
                        c = UART1_Read();
                    }
                else {
                    *U1recInst[i][j][k] = c;
                    k++;
                    c = UART1_Read();
                }                    
        }
     */
      //  return string;
}

void writeUart1(uint8_t * string){
    int i;
     for(i = 0; i < strlen(string); i++){         
            UART1_Write(*(string + i));
        }   
}

void readUart2(){
    uint8_t c;
  
        c = UART2_Read();
 //       *U2recInst[3][10][10] = NULL;
        int i = 0, j = 0, k = 0;
        while(c != ';'){        
            
                if(c == '<'){
                    if (i == 0){                   
                        c = UART2_Read();
                    }
                    if (i != 0){
                        i++;
                        //*U2recInst[i][j][k] = c;
                        c = UART2_Read();
                    }              
                }
                else if(c == '>'){
                    c = UART2_Read();
                    j = 0, k = 0;               
                }
                else if(c == ','){
                        j++;
                        k = 0;
                        c = UART2_Read();                             
                    }                
                else if (c == '.'){
                        //*U2recInst[i][j][k] = c;
                        k++;
                        c = UART2_Read();
                    }
                else {
                    //*U2recInst[i][j][k] = c;
                    k++;
                    c = UART2_Read();
                }                    
        }
        return;
}

void writeUart2(uint8_t *string){
    int i;
     for(i = 0; i < sizeof(string); i++){         
            UART2_Write(string[i]);
        }
}
/*
uint8_t* compiler(bool toPic, SENSOR_READ sensors){
    char* string[150];
    if (toPic == true){
        
        if (U1recInst[1][0][0] == (uint8_t *)'m'){
            strncat(*string, (const char*) "<m2,", 4);
            int i = 1;
            while((U1recInst[1][i][0] != NULL) & (i < 10)){
                int j;
                for(j = 0; j < 4 ; j++){
                    strncat(*string, (const char*)U1recInst[1][i][j], 1);
                }
                strncat(*string, (const char*)',' , 1);
                i++;
            }
        }
               
        if (U1recInst[2][0][0] == (uint8_t *)'m'){
            strncat(*string, (const char*)"><m2" , 4);
            int i = 1;
            while((U1recInst[2][i][0] != NULL) & (i < 10)){
                int j;
                for(j = 0; j < 4 ; j++){
                    strncat(*string, (const char*)U1recInst[2][i][j], 1);
                }
                strncat(*string, (const char*)',' , 1);
                i++;
            }
            strncat(*string, (const char*)">;" , 2);
        }
        else{
            strncat(*string,(const char*)">" , 2);
        }
    }
    // unfinished
    if (toPic == false){
        // add in the sensor data
        
        
        strncat(*string, (const char*) "<m2,", 4);
        
        
        
        
        if (U2recInst[1][0][0] == (uint8_t *)'m'){
            strncat(*string, (const char*) "<m2,", 4);
            int i = 1;
            while((U2recInst[1][i][0] != NULL) & (i < 10)){
                int j;
                for(j = 0; j < 4 ; j++){
                    strncat(*string, (const char*)U2recInst[1][i][j], 1);
                }
                strncat(*string, (const char*)',' , 1);
                i++;
            }
        }
               
        if (U2recInst[2][0][0] == (uint8_t *)'m'){            
            strncat(*string, (const char*)"><m2" , 4);          
            int i = 1;
            while((U2recInst[2][i][0] != NULL) & (i < 10)){
                int j;
                for(j = 0; j < 4 ; j++){
                    strncat(*string, (const char*)U2recInst[2][i][j], 1);
                }
                strncat(*string, (const char*)',' , 1);
                i++;
            }
            strncat(*string, (const char*)">;" , 2);
        }
        else{
            strncat(*string,(const char*)">" , 2);
        }
    }
    return (uint8_t*)*string;
}
 */