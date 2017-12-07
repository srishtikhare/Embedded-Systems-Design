org 0000h ;start address of Main
LJMP Main

org 000Bh ;start address of ISR for timer0
LJMP ISR

org 0100h
Main:;mov r0,#80h
mov DPTR,#80h
mov r3,#80h ;for suppl
mov r2,#00h ;for suppl
mov r5,#0Ah ;move counter value to r5
clr p1.1 ;clear pin attached to led
mov tmod,#0000001b ;configure TMOD register for mode0, timer0
mov ie,#10000010b ;configure IE register for mode0, timer0
mov th0,#5Bh ;put count value to tho
mov tl0,#0F9h ;put cout value in tl0
setb tr0 ;start timer0

loop:mov a,r2
movx @DPTR,a
inc r2
cjne r2,#7Fh,val2
mov r2,#00h
val2:sjmp loop ;infinite loop

ISR:mov a,r3
movx @DPTR,a
inc r3
cjne r3,#0FFh,val1
mov r3,#80h
val1:setb p1.2 ;set P1.2 bit
djnz r5,label1 ;decrement r0 and compare to zero
cpl p1.1 ;complement P1.1 bit
mov r5,#0Ah ;reinitialize r0
setb tr0 ;start timer0
label1:mov th0,#5Bh ;reinitialize th0
mov tl0,#0F9h ;reinitialize tl0
setb tr0 ;start timer0
clr p1.2 ;clear P1.2 bit
reti ;return from interrupt
end
