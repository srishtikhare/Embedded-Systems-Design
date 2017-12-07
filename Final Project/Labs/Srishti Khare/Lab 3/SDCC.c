#include <at89c51ed2.h>
#include <mcs51reg.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

//Virtual debug port

#ifdef DEBUG
#define DEBUGPORT(a)    dataout(0x7FFF,a);
#else
#define DEBUGPORT(a)
#endif // DEBUG

#define HEAP_SIZE 1600  //declared healp size

unsigned char xdata heap[HEAP_SIZE];

void putchar(char c)    //putchar implemented
{
    SBUF=c;
    while (!TI);
    TI=0;
}
char getchar()  //getchar implemented
{
    while (!RI);
    RI=0;
    return SBUF;
}

int putstr (char *s);

_sdcc_external_startup()
{
    AUXR |=0x0C;    //Enable XRAM
    TMOD = 0x20;    //Timer 8-bit auto reload mode
    TH1 = -3;   //Set baudrate as 9600
    SCON = 0x50;    //Enabling reception
    TR1 = 1;    //Start timer
    return 0;
}

int getinput(void)      //Definition of getval function to fetch input for multiple characters from the user
{

    char input_size[4];
    input_size[0]=getchar();
    putchar(input_size[0]);
    input_size[1]=getchar();
    putchar(input_size[1]);
    input_size[2]=getchar();
    putchar(input_size[2]);
    input_size[3]=getchar();
    putchar(input_size[3]);

    if(input_size[0]>=48&&input_size[0]<=57&&input_size[1]>=48&&input_size[1]<=57&&input_size[2]>=48&&input_size[2]<=57&&input_size[3]>=48&&input_size[3]<=57)
    {
        return(atoi(input_size));
    }
    else
    {
        return (-1);
    }
}

void main(void)
{
    //variable definitions
    xdata char * buffer_0;
    xdata char * buffer_1;
    xdata char * buffer_[50];
    int val,total=0;
    int k=0;
    int buff_one_zero_size,storage_chars=0,storage_chars_1=0;
    int buff_zero_addr=0;
    int buff_one_addr=0;
    int free_space_0=0;
    int free_space_1=0;
    int j=2;
    int i=2;
    int num=0;
    int q=2;
    int flag=0;
    int temp1=0;
    char ch[4];
    char character;
    char swap_buff;
    int bytes_n[50];
    int buffs=0;
    int temp=0;
    int b=0;
    int b1=0;
    int chars=0, chars_old=0;

    //initialize memory
    init_dynamic_memory((MEMHEADER xdata *)heap, HEAP_SIZE);

    //uset help sheet
    printf_tiny("********************* USER HELP SHEET *********************************\n\n\r");

    printf_tiny("Character  :   'storage'   :   Stored in buffer_0\n\n\r");
    printf_tiny("Character  :   '+'   :   Creates new buffers\n\n\r");
    printf_tiny("Character  :   '-'   :   Deletes existing buffers\n\n\r");
    printf_tiny("Character  :   '?'   :   Prints heap report. Clears buffer 0\n\n\r");
    printf_tiny("Character  :   '='   :   Prints contents of buffer 0\n\n\r");
    printf_tiny("Character  :   '%'   :   Swaps buffers 0 and 1\n\r");
    printf_tiny("Character  :   '@'   :   Deletes all current buffers\n\r");

    printf_tiny("********************* END *********************************\n\n\r");

    while(1)
    {
    //Enter buffer size for buffer_0 and buffer_1 allotment
    a1: printf_tiny("Enter buffer size between 32 and 1600 bytes, divisible by 16\n\r");
    printf_tiny("Enter values as 4 digits\n\r");

    buffs = getinput(); //get input from user

    //check if entered values are in range
    if((buffs >= 32) && (buffs <= 1600) && (buffs % 16 == 0))
    {
        //alloctae memory to buffer
        buffer_0 = malloc(buffs);
        buffer_1 = malloc(buffs);

        //if buffer assignemnt failed, free it
        if((buffer_0 == NULL) || (buffer_1 == NULL))
        {
            printf_tiny("*************** malloc buffer failed ***************\n\r");
            printf_tiny("*************** Choose a smaller buffer size ***************\n\r");
            free(buffer_0);
            free(buffer_1);

        }
        else
        {   //update buffer counters
            total += buffs;
            total += buffs;
            buff_zero_addr = buffs;
            buff_one_addr = buffs;
            buff_one_zero_size = buffs;

            printf_tiny("\n\r*************** buffer_0 and buffer_1 allocated successfully ***************\n\r"); //print success message
        }
    }
    else
    {
        printf_tiny("\n\r*************** Try again ***************\n\r"); //print error message and again take inputs
        goto a1;
    }

    while(1)
    {
    /////////////////////////////////////////////////////////////////////////storage character///////////////////////////////////////////////////////////////////////
        if(flag == 1)
        {
            flag = 0;
            break;
        }
        printf_tiny("\n\rEnter a character\n\r");   //enter a character
        character = getchar();
        putchar(character);

        if (character >= 'A' && character <= 'Z' || character >= 'a' && character <= 'z')   //if character is storage
        {
            storage_chars++;
            chars++;    //increment "characters" variable

             if((buffer_0+b)==buffs)
            {   printf("\n\r***************Buffer is full. Start echo. ***************\n\r");
                printf_tiny("/n/r");
                putchar(character);
                printf_tiny("\n\r***************** This is an echo! ***************\n\r"); //if buffer_0 is full, echo it
            }
            else //or
            {
            *(buffer_0+b)= character;   //store it in buffer_0
           // buff_zero_counter++;

            printf_tiny("\n\rThe character you entered is: "); //print input character again

            putchar(*(buffer_0+b));
            b++;
            b1=b;
            printf_tiny("\n\r");
            }
            continue; //loop back
        }

    ///////////////////////////////////////////////////////////////command character ('+')////////////////////////////////////////////////////////////////////////////
        switch(character) //switch case
        {
        case '+':   //if character is +
        label1: printf_tiny("\n\rEnter buffer size between 20 and 400 bytes\n\r");
        printf_tiny("Enter input as 4 digits\n\r");

//                gets(ch);
//                buffs=atoi(ch);
                buffs = getinput();
                chars++;

                if((buffs >= 20) && (buffs <= 400))
                {
                    if((total<=1600))
                    {
                        buffer_[q] = malloc(buffs); //create buffers for given memory until heap is full

                        if(buffer_[q] == NULL)
                        {
                            printf_tiny("\n\rmalloc buffer failed\n\r");
                            break;
                        }
                        else
                        {
                            printf_tiny("Buffer space successfully allocated\n\r");
                            total += buffs;
                            bytes_n[q-2] = buffs;
                            printf_tiny("buffer_%d allocated\n\r",q);
                            q++;
                        }
                      //  goto label1;
                    }
                    else
                    printf_tiny("Heap full\n\r");   //buffers created till heap was empty and available
                }
                else
                {
                    printf_tiny("Try again\n\r");    //if memory values are wrong, try again
                    goto label1;
                }
            break;

    //////////////////////////////////////////////////////////////command character ('-')////////////////////////////////////////////////////////////////////////////
        case '-':
                printf_tiny("\n\rEnter the buffer number to be freed\n\r");
                printf_tiny("\n\rEnter input as 4 digits\n\r");
                label2: num = getinput();
                chars++;    //increment "characters" variable

              //  num=atoi(ch);

                val=0;

                if(num == 0)
                {
                    printf_tiny("\n\rYou cannot delete buffer_0\n\r");
                }

                if((num == 1) && (buffer_1 != NULL))
                {
                    free(buffer_1);
                    buffer_1 = NULL;
                    printf_tiny("\n\rbuffer_1 freed successfully.\n\r");
                }
                else if(buffer_1 == NULL)
                {
                    printf_tiny("\n\rBuffer does not exist. Try again.\n\r");
                }
                if(val==1)
                {
                    printf_tiny("\n\rBuffer does not exist. Try again.\n\r");
                }

                if(num > 1)
                {
                    if(buffer_[num] != NULL)
                    {
                        free(buffer_[num]);
                        buffer_[num] = NULL;
                        printf_tiny("\n\rbuffer_%d freed successfully.\n\r",num);
                    }
                    else
                    {
                        printf_tiny("\n\rBuffer does not exist. Try again.\n\r");
                        val=1;
                    }
                }
                if(val==1)
                    printf_tiny("\n\rBuffer does not exist. Try again.\n\r");

            break;

  //////////////////////////////////////////////////////////////character ('?')////////////////////////////////////////////////////////////////////////////
        case '?':
                storage_chars = b;

                printf_tiny("\n\rNumber of total characters received: %d\n\r",chars);
                printf_tiny("Number of storage characters received: %d\n\n\r",storage_chars);

                printf_tiny("\n\r********************************** HEAP REPORT *******************************\n\n\r");

                printf_tiny("*************** buffer_0 info ***************\n\n\r");
                //print contents of buffer 0
                printf_tiny("buffer_0\n\r");
                printf("buffer_0 start address: %p\n\r",buffer_0);
                printf("buffer_0 end address: %p\n\r",buffer_0+buff_zero_addr);
                printf_tiny("Total allocated size of buffer_0: %d\n\r",buff_one_zero_size);
                printf_tiny("Number of storage characters currently in buffer_0: %d\n\r",storage_chars);
                free_space_0 = buff_one_zero_size - storage_chars;
                printf_tiny("Number of free spaces in buffer_0: %d\n\n\r",free_space_0);
                printf_tiny("\n\r");

                if(buffer_1 == NULL)    //check if buffer 1 still exists, else print eror message
                {
                  printf_tiny("buffer_1 has been deleted\n\r");
                  printf_tiny("\n\n\r");
                }
                else
                {   //print contents of buffer 1
                printf_tiny("*************** buffer_1 info ***************\n\n\r");
                printf_tiny("buffer_1\n\r");
                printf("buffer_1 start address: %p\n\r",buffer_1);
                printf("buffer_1 end address: %p\n\r",buffer_1+buff_one_addr);
                printf_tiny("Total allocated size of buffer_1: %d\n\r",buff_one_zero_size);
                printf_tiny("Number of storage characters currently in buffer_1: %d\n\r",storage_chars_1);
                free_space_1 = buff_one_zero_size - storage_chars_1;
                printf_tiny("Number of free spaces in buffer_1: %d\n\n\r",free_space_1);
                printf_tiny("\n\r");
                }

            for(temp1=0;temp1<15;temp1++)   //print contents of remaining existing buffer
        {
            if((bytes_n[temp1]>19)&&((bytes_n[temp1])<401)&&(buffer_[temp1+2]!=NULL))
            {
            printf_tiny("*************** buffer_%d info ***************\n\n\r",temp1+2);
            printf_tiny("Buffer number %d\n\r",temp1+2);
            printf("Buffer Start Address %p\n\r",(buffer_[temp1+2]));
            printf("Buffer End Address%p\n\r",(buffer_[temp1+2]+bytes_n[temp1]));
            printf_tiny("Total allocated size of buffer : %d \n\r",bytes_n[temp1+2]);
            }
        else
            continue;
        }
                //calculate and print total number of character information
                printf_tiny("Total number of characters received since the last '?': %d\n\n\r",(chars - chars_old));
                printf_tiny("\n\r");

                chars_old = chars;
                //print contents of buffer 0
                printf_tiny("*************** Contents of buffer_0 ***************\n\r");

                for(k=0;k<b;k++)
                {
                   if(k%48==0)
                   {
                       printf_tiny("\n\r");
                   }
                   printf("%c ",*(buffer_0+k));
                }
                printf_tiny("\n\r");
                b1=0;

                break;

    //////////////////////////////////////////////////////////////command character ('=')////////////////////////////////////////////////////////////////////////////
        case '=':
                DEBUGPORT(0xFF)
                //print contents of buffer 0
                printf_tiny("*************** Contents of buffer_0 ***************\n\r");

                for(k=0;k<b1;k++)
                {
                   if(k%16==0)
                   {
                       printf_tiny("\n\r");
                       printf("%p: ",(buffer_0+k));
                   }
                   printf("%x ",*(buffer_0+k));
                }
                printf_tiny("\n\r");
                break;

    //////////////////////////////////////////////////////////////command character ('%')////////////////////////////////////////////////////////////////////////////
        case '%':   //swap contents of buffer 0 and buffer 1, if buffer 1 exists
                if(buffer_1 == NULL)
                {
                    printf_tiny("\n\rbuffer_1 deleted\n\r");
                    printf("\n\r");
                    printf("Swap not possible\n\r");
                    printf("\n\r");
                    break;

                }   //print contents of buffer 0 and buffer 1 before swapping
                printf_tiny("\n\n\r-------- Before swap --------\n\n\r");
                printf("\n\r");
                printf_tiny("*************** Contents of buffer_0 ***************\n\r");

                for(k=0;k<b;k++)
                {
                   if(k%16==0)
                   {
                       printf_tiny("\n\r");
                       printf("%p: ",(buffer_0+k));
                   }
                   printf("%x ",*(buffer_0+k));
                }

                printf_tiny("\n\r");
                printf_tiny("*************** Contents of buffer_1 ***************\n\r");

                for(k=0;k<b;k++)
                {
                   if(k%16==0)
                   {
                       printf_tiny("\n\r");
                       printf("%p: ",(buffer_1+k));
                   }
                   printf("%x ",*(buffer_1+k));
                }
                printf_tiny("\n\r");

                for(i=0;i<buffs;i++)
                {
                    swap_buff = *(buffer_0+i);
                    *(buffer_0+i) = *(buffer_1+i);
                    *(buffer_1+i) = swap_buff;
                }   //print contents of buffer 0 and buffer 1 after swapping
                printf_tiny("\n\n\r-------- After swap --------\n\n\r");
                printf_tiny("*************** Contents of buffer_0 ***************\n\r");

                for(k=0;k<b;k++)
                {
                   if(k%16==0)
                   {
                       printf_tiny("\n\r");
                       printf("%p: ",(buffer_0+k));
                   }
                   printf("%x ",*(buffer_0+k));
                }

                printf_tiny("\n\r");
                printf_tiny("*************** Contents of buffer_1 ***************\n\r");

                for(k=0;k<b;k++)
                {
                   if(k%16==0)
                   {
                       printf_tiny("\n\r");
                       printf("%p: ",(buffer_1+k));
                   }
                   printf("%x ",*(buffer_1+k));
                }
                printf_tiny("\n\r");
                printf_tiny("*************** Parameters swapped ***************\n\r");

                //swap parameters

                //swap buffer counters
                temp = buff_zero_addr;
                buff_zero_addr = buff_one_addr;
                buff_one_addr = temp;

                //swap number of characters stored
                temp = storage_chars;
                storage_chars = storage_chars_1;
                storage_chars_1 = temp;

                  //swap amount of free space
                temp = free_space_0;
                free_space_0 = free_space_1;
                free_space_1 = temp;

                break;

    //////////////////////////////////////////////////////////////command character ('@')////////////////////////////////////////////////////////////////////////////
        case '@':
                flag=1; //ste flag to go back to the start of program
                free(buffer_0); //free buffer 0
                buffer_0 = NULL;
                printf_tiny("\n\rbuffer_0 deleted\n\r");    //print message

                free(buffer_1); //free buffer 1, if it exists
                buffer_1 = NULL;
                printf_tiny("\n\rbuffer_1 deleted\n\r");    //print message

                for(i=2;buffer_[i]!=NULL;i++)
                {
                    free(buffer_[i]);   //free the respective buffer, if it exists
                    buffer_[i] = NULL;
                    printf_tiny("\n\rbuffer_%d deleted\n\r",i); //print message
                }
                printf_tiny("\n\r");
    //reinitialize all values to default
     val,total=0;
     k=0;
     buff_one_zero_size,storage_chars=0,storage_chars_1=0;
     buff_zero_addr=0;
     buff_one_addr=0;
     free_space_0=0;
     free_space_1=0;
     j=2;
     i=2;
     num=0;
     q=2;
     flag=1;
     temp1=0;
     character;
     swap_buff;
     buffs=0;
     temp=0;
     b=0;
     chars=0, chars_old=0;
      break;

        default: chars++;   //increment "characters" variable
        break;
        }
    }
    }
 }
