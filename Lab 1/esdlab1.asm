org 0000h ;start at 0x0000
clr c ;clear carry bit
mov 0x30,#0x00 ;set error to 0xFF
mov a,#0x1C ;x
add a,#02h ;x+2
jnc continue1 ;cont to execute code if no error
mov 0x30,#01h;add error
jmp ENDLOOP ;enter infinite loop
continue1:mov r6,a ;copy of x+2
mov 20h,a ;x+2 at 0x02
mov b,#07h ;put denominator in reg b
mov r4,b ;y
cjne r4,#00h,continue2 ;cont to execute code in no error occurs
mov 0x30,#02h;error handling
jmp ENDLOOP ;enter infinite loop
;division
continue2:mov r0,#00h ;set result as 0
label1: subb a,b ;sub num 
inc r0 ;quotient of divide
jnc label1 ;for calculation in a loop
dec r0 ;result of (x+2)/y
mov 0x21,r0 ;result at 0x21
;remainder
mov a,r0
mov r7,b
dec r7
mov b,a
label2:add a,b
dec r7
cjne r7,#00h,label2
mov r5,a
mov a,r6
subb a,r5
mov 0x22,a ;remainder of (x+2)/y
;multiplication
mov a,r0 
clr c ;clear carry bit
rlc a ;right rotate a with carry
clr c ;cler carry
rlc a ;right rotate a with carry
jnc label3
mov 0x30,#03h ;error code
label3:mov 0x23,a ;put z
ENDLOOP:mov r5,#01h ;infinite loop
cjne r5,#00h,ENDLOOP
end
