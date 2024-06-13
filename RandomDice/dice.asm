$include(at89c51xd2.inc)  ; Include 8051 specific library

org 0H  ; Start at memory location 0
sjmp START  ; Jump to the START function

org 03H  ; Set memory location 3 for an interrupt
ajmp BUTTON  ; Absolute jump to BUTTON function, since short jump isn't sufficient
reti  ; Return from interrupt

org 0BH  ; Set memory location 0BH for another interrupt
acall OUTPUT  ; Call OUTPUT function
mov P1, A  ; Move the value in accumulator to P1
reti  ; Return from interrupt

org 40H  ; Start at memory location 40H

START:  ; START function
clr P3.2  ; Clear port 3.2 to indicate dice rolling
sjmp SETUP  ; Short jump to SETUP function

SETUP:  ; SETUP function
mov R1, #6  ; Load register R1 with decimal 6
mov TMOD, #00000001B  ; Set TMOD to enable 16-bit timer
mov A, R1  ; Move value of R1 to accumulator
mov DPTR, #0100H  ; Set MOVC base address
mov IEN0, #10000011B  ; Enable external 0 and global interrupts
acall TIMER  ; Call TIMER function

AGRAB:  ; AGRAB function
mov A, R1  ; Move accumulator value to R1

LOOP:
djnz R1, AGRAB  ; Decrement R1, jump to AGRAB if not zero
mov R1, #6  ; Reload R1 with 6 to restart timer
sjmp AGRAB  ; Jump to AGRAB

TIMER:  ; TIMER function
mov TL0, #00000010B  ; Load TL0 with timer low byte
mov TH0, #00000000B  ; Load TH0 with timer high byte
setb TR0  ; Start the timer
ret  ; Return from function

OUTPUT:  ; OUTPUT function
movc A, @A+DPTR  ; Read value from data table
acall DELAY  ; Call DELAY function
ret  ; Return from function

org 101H  ; Data table at memory location 101H
; Hex values representing dice faces
db 08H  ; Dice face 1
db 14H  ; Dice face 2
db 1CH  ; Dice face 3
db 55H  ; Dice face 4
db 5DH  ; Dice face 5
db 77H  ; Dice face 6

BUTTON:  ; BUTTON function
mov TMOD, #00000000B  ; Reset TMOD
acall OUTPUT  ; Call OUTPUT function
mov P1, A  ; Move accumulator value to P1
acall TIMER  ; Call TIMER function
reti  ; Return from interrupt

DELAY:  ; DELAY function
jb P3.2, DELAY  ; Wait until P3.2 is set
ret  ; Return from function

end  ; End of program
