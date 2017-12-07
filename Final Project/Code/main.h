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

void LCDInit(void);
void ShowOnLCD(uint8_t value);
void StringOnLCD(char *str);
unsigned long pulseIn_1(void);
unsigned long pulseIn_2(void);
unsigned long pulseIn_3(void);

/* [] END OF FILE */
