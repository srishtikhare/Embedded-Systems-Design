/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>
#include<stdlib.h>

char out_1[6];
char p_1[5];
unsigned long duration_1 = 0;

char out_2[6];
char p_2[5];
unsigned long duration_2 = 0;

char out_3[6];
char p_3[5];
unsigned long duration_3 = 0;

int flag1=0;
int flag2=0;
int flag3=0;

int count1=1;
int count2=1;
int count3=1;

char a,i,read[15];

void TOGGLE_EPIN(void)
{
    CyDelayUs(500);
    E_Write(1);
    CyDelayUs(500);
    E_Write(0);
    CyDelayUs(500);
}
                            
                        
#define InitPins                           \
                        do                 \
                        {                  \
                            DB7_Write(0);  \
                            DB6_Write(0);  \
                            DB5_Write(0);  \
                            DB4_Write(0);  \
                            DB3_Write(0);  \
                            DB2_Write(0);  \
                            DB1_Write(0);  \
                            DB0_Write(0);  \
                        }while(0)
                            
#define NewLine                            \
                        do                 \
                        {                  \
                            RS_Write(0);   \
                            RW_Write(0);   \
                            DB7_Write(1);  \
                            DB6_Write(1);  \
                            DB5_Write(0);  \
                            DB4_Write(0);  \
                            DB3_Write(0);  \
                            DB2_Write(0);  \
                            DB1_Write(0);  \
                            DB0_Write(0);  \
                            TOGGLE_EPIN(); \
                        }while(0)
                            
#define ClearDisplay                       \
                        do                 \
                        {                  \
                            RS_Write(0);   \
                            RW_Write(0);   \
                            DB7_Write(0);  \
                            DB6_Write(0);  \
                            DB5_Write(0);  \
                            DB4_Write(0);  \
                            DB3_Write(0);  \
                            DB2_Write(0);  \
                            DB1_Write(0);  \
                            DB0_Write(1);  \
                            TOGGLE_EPIN(); \
                        }while(0)

void LCDInit(void)  //function to initialize LCD
{
    E_Write(0);
    
    CyDelay(100);
    
    RS_Write(0);    //Startng byte 0x30
    RW_Write(0);
    DB7_Write(0);
    DB6_Write(0);
    DB5_Write(1);
    DB4_Write(1);
    DB3_Write(0);
    DB2_Write(0);
    DB1_Write(0);
    DB0_Write(0);
    TOGGLE_EPIN();
        
    CyDelay(5); //5 ms delay
    
    RS_Write(0);    //Startng byte 0x30
    RW_Write(0);
    DB7_Write(0);
    DB6_Write(0);
    DB5_Write(1);
    DB4_Write(1);
    DB3_Write(0);
    DB2_Write(0);
    DB1_Write(0);
    DB0_Write(0);
    TOGGLE_EPIN();

    CyDelayUs(100); //5 uss delay
    
    RS_Write(0);    //Startng byte 0x30
    RW_Write(0);
    DB7_Write(0);
    DB6_Write(0);
    DB5_Write(1);
    DB4_Write(1);
    DB3_Write(0);
    DB2_Write(0);
    DB1_Write(0);
    DB0_Write(0);
    TOGGLE_EPIN();   


    CyDelay(5); //5 ms delay
    
    RS_Write(0);    //0x31
    RW_Write(0);
    DB7_Write(0);
    DB6_Write(0);
    DB5_Write(1);
    DB4_Write(1);
    DB3_Write(1);
    DB2_Write(0);
    DB1_Write(0);
    DB0_Write(0);
    TOGGLE_EPIN();
    
    //Display off    
    CyDelay(5);    

    RS_Write(0);
    RW_Write(0);
    DB7_Write(0);
    DB6_Write(0);
    DB5_Write(0);
    DB4_Write(0);
    DB3_Write(1);
    DB2_Write(0);
    DB1_Write(0);
    DB0_Write(0);
    TOGGLE_EPIN();
    
    //Display clear
    CyDelay(5);    

    RS_Write(0);
    RW_Write(0);
    DB7_Write(0);
    DB6_Write(0);
    DB5_Write(0);
    DB4_Write(0);
    DB3_Write(0);
    DB2_Write(0);
    DB1_Write(0);
    DB0_Write(1);
    TOGGLE_EPIN();
    
    //Entry mode set    
    CyDelay(5);    
    
    RS_Write(0);
    RW_Write(0);
    DB7_Write(0);
    DB6_Write(0);
    DB5_Write(0);
    DB4_Write(0);
    DB3_Write(0);
    DB2_Write(1);
    DB1_Write(1);
    DB0_Write(0);
    TOGGLE_EPIN();
    
    //OPERATION
    
// Function Set   
    CyDelay(100);
    
    RS_Write(0);
    RW_Write(0);
    DB7_Write(0);
    DB6_Write(0);
    DB5_Write(1);
    DB4_Write(1);
    DB3_Write(1);
    DB2_Write(0);
    DB1_Write(0);
    DB0_Write(0);
    TOGGLE_EPIN();
    
 // Display on/off control   
    CyDelay(100);
    
    RS_Write(0);
    RW_Write(0);
    DB7_Write(0);
    DB6_Write(0);
    DB5_Write(0);
    DB4_Write(0);
    DB3_Write(1);
    DB2_Write(1);
    DB1_Write(0);
    DB0_Write(0);
    TOGGLE_EPIN();
    
 // Entry mode set
    CyDelay(100);
    
    RS_Write(0);
    RW_Write(0);
    DB7_Write(0);
    DB6_Write(0);
    DB5_Write(0);
    DB4_Write(0);
    DB3_Write(0);
    DB2_Write(1);
    DB1_Write(1);
    DB0_Write(0);
    TOGGLE_EPIN();    
}
    
void ShowOnLCD(uint8_t value);  //function declaration
    
void StringOnLCD(char *str) //function to print strings on LCD
{
    uint8_t i,j=0,val,value[33];

    for(i=0;str[i] != '\0';i++)
    {
        value[j] = str[i];
        j++;
    }
    
   for(i=0;i<j;i++) //print characters i loop to form a string
    {
        val = value[i];
        
        ShowOnLCD(val);
    }
}
    
void ShowOnLCD(uint8_t value)   //function to print character on LCD
{
 
    InitPins;   //initialize pins to zero
    
    CyDelay(5);
    
    RS_Write(1);
    RW_Write(0);
    
    if(value & 0x80)    //if 8th bit is set
    {
        DB7_Write(1);
    }
    
    if(value & 0x40)    //if 7th bit is set
    {
        DB6_Write(1);
    }

    if(value & 0x20)    //if 6th bit is set
    {
        DB5_Write(1);
    }
    
    if(value & 0x10)    //if 5th bit is set
    {
        DB4_Write(1);
    }
    
    if(value & 0x08)    //if 4th bit is set
    {
        DB3_Write(1);
    }
    
    if(value & 0x04)    //if 3rd bit is set
    {
        DB2_Write(1);
    }
    
    if(value & 0x02)    //if 2nd bit is set
    {
        DB1_Write(1);
    }
    
    if(value & 0x01)    //if 1st bit is set
    {
        DB0_Write(1);
    } 
    TOGGLE_EPIN();
}

unsigned long pulseIn_1(void) { //fuction to calculate the Echo pin HIGH duration

    unsigned long pulseWidth_1 = 0; //to count the duration for which Echo stays high
    unsigned long loopCount_1 = 0;  //loop counter
    unsigned long loopMax_1 = 5000000;  //loopcounter upper limit

    // While the Echo pin is not HIGH, make sure the timeout hasn't been reached
    while ((Echo_1_Read()) != 1) {
        LED_Write(0);
        if (loopCount_1++ == loopMax_1) {
            return 0;
        }
    }

    // When the Echo pin is HIGH, increment the counter while still keeping track of the timeout
    while ((Echo_1_Read()) == 1) {
        LED_Write(1); //make LED high on board when Echo goes high
        if (loopCount_1++ == loopMax_1) {
            return 0;
        }
        pulseWidth_1++;
    }

    // Return the pulse time in microseconds
    return pulseWidth_1 * 2.36; // Calculated the pulseWidth++ loop to be about 2.36uS in length
}

unsigned long pulseIn_2(void) { //fuction to calculate the Echo pin HIGH duration

    unsigned long pulseWidth_2 = 0; //to count the duration for which Echo stays high
    unsigned long loopCount_2 = 0;  //loop counter
    unsigned long loopMax_2 = 5000000;  //loopcounter upper limit

    // While the Echo pin is not HIGH, make sure the timeout hasn't been reached
    while ((Echo_2_Read()) != 1) {
        if (loopCount_2++ == loopMax_2) {
            return 0;
        }
    }

    // When the Echo pin is HIGH, increment the counter while still keeping track of the timeout
    while ((Echo_2_Read()) == 1) {
        if (loopCount_2++ == loopMax_2) {
            return 0;
        }
        pulseWidth_2++;
    }

    // Return the pulse time in microseconds
    return pulseWidth_2 * 2.36; // Calculated the pulseWidth++ loop to be about 2.36uS in length
}

unsigned long pulseIn_3(void) { //fuction to calculate the Echo pin HIGH duration

    unsigned long pulseWidth_3 = 0;
    unsigned long loopCount_3 = 0;  //loop counter
    unsigned long loopMax_3 = 5000000;  //loopcounter upper limit

    // While the Echo pin is not HIGH, make sure the timeout hasn't been reached
    while ((Echo_3_Read()) != 1) {
        if (loopCount_3++ == loopMax_3) {
            return 0;
        }
    }

    // When the Echo pin is HIGH, increment the counter while still keeping track of the timeout
    while ((Echo_3_Read()) == 1) {
        if (loopCount_3++ == loopMax_3) {
            return 0;
        }
        pulseWidth_3++;
    }

    // Return the pulse time in microseconds
    return pulseWidth_3 * 2.36; // Calculated the pulseWidth++ loop to be about 2.36uS in length
}

int main()
{
    VCC2_Write(1);
    GND2_Write(0);
    
    VCC3_Write(1);
    GND3_Write(0);
    
    LCDInit();  //Initialize LCD
    ClearDisplay;   //Clear LCD display
    LED_Write(0);
    
    UART_1_IntClock_Start();    //Start UART clock
    UART_1_Start(); //Start UART
    
    RS_Write(0);      // set LCD address
    RW_Write(0);
    DB7_Write(1);
    DB6_Write(0);
    DB5_Write(0);
    DB4_Write(0);
    DB3_Write(0);
    DB2_Write(0);
    DB1_Write(0);
    DB0_Write(0);
    TOGGLE_EPIN();
      
    CyDelay(10);
    StringOnLCD("GARBAGE MONITOR");
    
    RS_Write(0);      // set LCD address for Trash Bin 1
    RW_Write(0);
    DB7_Write(1);
    DB6_Write(1);
    DB5_Write(0);
    DB4_Write(0);
    DB3_Write(0);
    DB2_Write(0);
    DB1_Write(0);
    DB0_Write(0);
    TOGGLE_EPIN();
      
    CyDelay(10);
    StringOnLCD("BIN 1:   ");
    
    RS_Write(0);      // set LCD address for Trash Bin 1
    RW_Write(0);
    DB7_Write(1);
    DB6_Write(1);
    DB5_Write(0);
    DB4_Write(0);
    DB3_Write(1);
    DB2_Write(1);
    DB1_Write(0);
    DB0_Write(1);
    TOGGLE_EPIN();
      
    CyDelay(10);
    StringOnLCD("in.");
    
    RS_Write(0);      // set LCD address for Trash Bin 2
    RW_Write(0);
    DB7_Write(1);
    DB6_Write(0);
    DB5_Write(0);
    DB4_Write(1);
    DB3_Write(0);
    DB2_Write(0);
    DB1_Write(0);
    DB0_Write(0);
    TOGGLE_EPIN();
      
    CyDelay(10);
    StringOnLCD("BIN 2:   ");
    
    RS_Write(0);      // set LCD address for Trash Bin 2
    RW_Write(0);
    DB7_Write(1);
    DB6_Write(0);
    DB5_Write(0);
    DB4_Write(1);
    DB3_Write(1);
    DB2_Write(1);
    DB1_Write(0);
    DB0_Write(1);
    TOGGLE_EPIN();
      
    CyDelay(10);
    StringOnLCD("in.");
    
    RS_Write(0);      // set LCD address for Trash Bin 3
    RW_Write(0);
    DB7_Write(1);
    DB6_Write(1);
    DB5_Write(0);
    DB4_Write(1);
    DB3_Write(0);
    DB2_Write(0);
    DB1_Write(0);
    DB0_Write(0);
    TOGGLE_EPIN();
      
    CyDelay(10);
    StringOnLCD("BIN 3:   ");
    
    RS_Write(0);      // set LCD address for Trash Bin 3
    RW_Write(0);
    DB7_Write(1);
    DB6_Write(1);
    DB5_Write(0);
    DB4_Write(1);
    DB3_Write(1);
    DB2_Write(1);
    DB1_Write(0);
    DB0_Write(1);
    TOGGLE_EPIN();
      
    CyDelay(10);
    StringOnLCD("in.");
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    while(1)
    {
/*************************************** Trash Bin 1 ***************************************/
        Trigger_1_Write(0); //code to trigger the Echo pin (applied to Trigger pin)
        CyDelayUs(2);
        Trigger_1_Write(1);
        CyDelayUs(10);
        Trigger_1_Write(0);
        CyDelayUs(2);

        duration_1 = pulseIn_1();   //Reading microseconds value during which Echo pin stays HIGH

        duration_1 = duration_1*0.017;  //Conversion of microseconds to inches
        
        if(duration_1 >6 && duration_1<14)
        {
            flag1=1;
        }
                
        RS_Write(0);      // set address
        RW_Write(0);
        DB7_Write(1);
        DB6_Write(1);
        DB5_Write(0);
        DB4_Write(0);
        DB3_Write(0);
        DB2_Write(1);
        DB1_Write(1);
        DB0_Write(1);
        TOGGLE_EPIN();
        
        CyDelay(10);

        sprintf(out_1,"%03lu",duration_1);  //convert unsigned long to char
        p_1[0]=out_1[0];    //make the xx.xx format of the string to print on LCD
        p_1[1]=out_1[1];
        p_1[2]='.';
        p_1[3]=out_1[2];
        p_1[4]=out_1[3];
        StringOnLCD(p_1);   //print string on LCD
        
/*************************************** Trash Bin 2 ***************************************/
        
        Trigger_2_Write(0);
        CyDelayUs(2);
        Trigger_2_Write(1);
        CyDelayUs(10);
        Trigger_2_Write(0);
        CyDelayUs(2);

        duration_2 = pulseIn_2();

        duration_2 = duration_2*0.017;
        
        if(duration_2>6 && duration_2<17)
        {
            flag2=1;
        }
                
        RS_Write(0);      // set address
        RW_Write(0);
        DB7_Write(1);
        DB6_Write(0);
        DB5_Write(0);
        DB4_Write(1);
        DB3_Write(0);
        DB2_Write(1);
        DB1_Write(1);
        DB0_Write(1);
        TOGGLE_EPIN();
        
        CyDelay(10);

        sprintf(out_2,"%03ld",duration_2);  //convert unsigned long to char
        p_2[0]=out_2[0];    //make the xx.xx format of the string to print on LCD
        p_2[1]=out_2[1];
        p_2[2]='.';
        p_2[3]=out_2[2];
        p_2[4]=out_2[3];
        StringOnLCD(p_2);   //print string on LCD
        
/*************************************** Trash Bin 3 ***************************************/
        
        Trigger_3_Write(0);
        CyDelayUs(2);
        Trigger_3_Write(1);
        CyDelayUs(10);
        Trigger_3_Write(0);
        CyDelayUs(2);

        duration_3 = pulseIn_3();

        duration_3 = duration_3*0.017;
        
        if(duration_3>6 && duration_3<17)
        {
            flag3=1;
        }
                
        RS_Write(0);      // set address
        RW_Write(0);
        DB7_Write(1);
        DB6_Write(1);
        DB5_Write(0);
        DB4_Write(1);
        DB3_Write(0);
        DB2_Write(1);
        DB1_Write(1);
        DB0_Write(1);
        TOGGLE_EPIN();
        
        CyDelay(10);

        sprintf(out_3,"%03ld",duration_3);  //convert unsigned long to char
        p_3[0]=out_3[0];    //make the xx.xx format of the string to print on LCD
        p_3[1]=out_3[1];
        p_3[2]='.';
        p_3[3]=out_3[2];
        p_3[4]=out_3[3];
        StringOnLCD(p_3);   //print string on LCD
    
    if(flag1 == 1 && count1<3)
    {
        UART_1_PutString("AT");//sent to access/init GSM module
        CyDelay(500);   //500 ms delay
        UART_1_PutChar(0x0D);   //carriage return
        CyDelay(500);   //500 ms delay
        UART_1_PutString("AT+CMGF=1");  //sent to set GSM to TEXT mode not PDU (data) mode
        CyDelay(500);   //500 ms delay
        UART_1_PutChar(0x0D);   //carriage return
        CyDelay(500);   //500 ms delay
        UART_1_PutString("AT+CMGS=\"+17203279021\"");   //sent to send a text message! You will get a '>' prompt for typing
        CyDelay(500);   //500 ms delay
        UART_1_PutChar(0x0D);   //carriage return
        CyDelay(500);   //500 ms delay
        UART_1_PutString("Trash Can 1: Completely filled!");    //message sent to cellphone
        CyDelay(100);   //100 ms delay
        UART_1_PutChar(0x1A);   //ctrl Z
        CyDelay(500);   //500 ms delay
        
        count1++;   //increment counter
        flag1=0;    //reset flag
    }
    
    if(flag2 == 1 && count2<3)
    {
        UART_1_PutString("AT"); //sent to access/init GSM module
        CyDelay(500);   //500 ms delay
        UART_1_PutChar(0x0D);   //carriage return
        CyDelay(500);   //500 ms delay
        UART_1_PutString("AT+CMGF=1");  //sent to set GSM to TEXT mode not PDU (data) mode
        CyDelay(500);   //500 ms delay
        UART_1_PutChar(0x0D);   //carriage return
        CyDelay(500);   //500 ms delay
        UART_1_PutString("AT+CMGS=\"+17203279021\"");   //sent to send a text message! You will get a '>' prompt for typing
        CyDelay(500);   //500 ms delay
        UART_1_PutChar(0x0D);   //carriage return
        CyDelay(500);   //500 ms delay
        UART_1_PutString("Trash Can 2: Completely filled!");    //message sent to cellphone
        CyDelay(100);   //100 ms delay
        UART_1_PutChar(0x1A);   //ctrl Z
        CyDelay(500);   //500 ms delay
        
        flag2=0;    //reset flag
        count2++;   //increment counter
    }
    
    if(flag3 == 1 && count3<3)
    {
        UART_1_PutString("AT"); //sent to access/init GSM module
        CyDelay(500);   //500 ms delay
        UART_1_PutChar(0x0D);   //carriage return
        CyDelay(500);   //500 ms delay
        UART_1_PutString("AT+CMGF=1");  //sent to set GSM to TEXT mode not PDU (data) mode 
        CyDelay(500);   //500 ms delay
        UART_1_PutChar(0x0D);   //carriage return
        CyDelay(500);   //500 ms delay
        UART_1_PutString("AT+CMGS=\"+17203279021\"");   //sent to send a text message! You will get a '>' prompt for typing
        CyDelay(500);   //500 ms delay
        UART_1_PutChar(0x0D);   //carriage return           
        CyDelay(500);   //500 ms delay
        UART_1_PutString("Trash Can 3: Completely filled!");    //message sent to cellphone
        CyDelay(100);   //100 ms delay
        UART_1_PutChar(0x1A);   //ctrl Z
        CyDelay(500);   //500 ms delay
        
        flag3=0;    //reset flag 
        count3++;   //increment counter
    }
    }
    return 0;
}

