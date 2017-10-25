#include <at89c51ed2.h>
#include <mcs51reg.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define HEAP_SIZE 1600
unsigned char xdata heap[HEAP_SIZE];

int putstr (char *s);

 //   char buff_size[10];
 //   xdata char * buffer_0;
 //   xdata char * buffer_1;
 //   int buffs,character;

_sdcc_external_startup()
{
    AUXR |=0x0C;

    TMOD = 0x20;
    TH1 = -3;
    SCON = 0x50;
    TR1 = 1;
    return 0;
}

void main(void)
{
    char *buff_size;
    char character;
    char ch[4];
    xdata char * buffer_0;
    xdata char * buffer_1;
    int buffs, i=0;
 //   char *cc = &character;

    init_dynamic_memory((MEMHEADER xdata *)heap, HEAP_SIZE);

    while(1)
    {
    printf("Enter buffer size between 32 and 1600 bytes, divisible by 16\n\r");

    buff_size = gets(ch);

    buffs=atoi(buff_size);

//    if(((buffs % 16) != 0) && (buffs < 32) && (buffs > 1600))
//        break;

    buffer_0 = malloc(buffs);
    buffer_1 = malloc(buffs);

    if((buffer_0 == NULL) || (buffer_1 == NULL))
    {
        printf("malloc buffer failed\n\r");
        printf("Choose a smaller buffer size\n\r");
        continue;
    }
    else
    break;
    }

    printf("Enter a character\n\r");
    character = getchar();
    putchar(character);
    if (character >= 'A' && character <= 'Z' || character >= 'a' && character <= 'z')
    {
        *buffer_0= character;

        putchar(*buffer_0);
        buffer_0 ++;
    }

 }
void putchar(char c)
{
    SBUF=c;
    while (!TI);
    TI=0;
}
char getchar()
{
    while (!RI);
    RI=0;
    return SBUF;
}
