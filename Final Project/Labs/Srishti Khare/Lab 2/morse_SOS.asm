;Dot duration=300ms
;Dash duration=900ms
;Inter letter duration=300ms
;Inter word duration=2100ms

org 0000h

MAIN:
mov r0,#0Ah;set couter value to get 300ms delay
mov r1,#1Eh;set couter value to get 900ms delay
mov r2,#046h;set couter value to get 2100ms delay
mov tmod,#0000001b;setup timer 0

;implementing S
cpl p1.1;dot1 on
ACALL Delay_300ms

cpl p1.1;dot1 off
ACALL Delay_300ms

cpl p1.1;dot2 on
ACALL Delay_300ms

cpl p1.1;dot2 off
ACALL Delay_300ms

cpl p1.1;dot3 on
ACALL Delay_300ms

cpl p1.1;dot3 off
ACALL Delay_2100ms

;implementing O
cpl p1.1;dash1 on
ACALL Delay_900ms

cpl p1.1;dash1 off
ACALL Delay_300ms

cpl p1.1;dash2 on
ACALL Delay_900ms

cpl p1.1;dash 2 off
ACALL Delay_300ms

cpl p1.1;dash3 on
ACALL Delay_900ms

cpl p1.1;dash3 off
ACALL Delay_2100ms

;implementing S
cpl p1.1;dot1 on
ACALL Delay_300ms

cpl p1.1;dot1 off
ACALL Delay_300ms

cpl p1.1;dot2 on
ACALL Delay_300ms

cpl p1.1;dot2 off
ACALL Delay_300ms

cpl p1.1;dot3 on
ACALL Delay_300ms

cpl p1.1;dot3 off
ACALL Delay_2100ms

SJMP MAIN;jump to main again

Delay_300ms:;generating delay for 300ms
mov r0,#0Ah;move counter value to R0
A1:mov th0,#093h;set timer values
mov tl0,#0FFh
setb tr0;start timer 0
L1:jnb tf0,L1;clear flag bit,if set
clr tf0
dec r0
cjne r0,#00h,A1;perform operation 10 times to get desired result
ret;return to main

Delay_900ms:;generating delay for 300ms
mov r1,#01Eh;move counter value to R1
A2:mov th0,#093h;set timer values
mov tl0,#0FFh
setb tr0;start timer 0
L2:jnb tf0,L2;clear flag bit,if set
clr tf0
dec r1
cjne r1,#00h,A2;perform operation 30 times to get desired result
ret;return to main

Delay_2100ms:;generating delay for 300ms
mov r2,#046h;move counter value to R2
A3:mov th0,#093h;set timer values
mov tl0,#0FFh
setb tr0;start timer 0
L3:jnb tf0,L3;clear flag bit,if set
clr tf0
dec r3
cjne r3,#00h,A3;perform operation 70 times to get desired result
ret;retun to main
end

