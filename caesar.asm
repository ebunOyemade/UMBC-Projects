;; Ebun Oyemade
	;; RJ01532
	;; This code takes in a of 8 or more characters and shifts at
	;; 25 letters right/left to perform a cipher
        section .data
msg:    db      "Enter a shift value beytween -25 and 25(included)",10
len:    equ      $-msg

msg2:	db	"Enter a string greater than 8 characters",10
len2:	equ	$-msg2

msg3:	db	"Current message:"
len3:	equ	$-msg3

msg4:	db	"Edited message:"
len4:	equ	$-msg4
	
	
char:	db	0,0
	
newline db      10

        section .bss
num    	resb	4
string	resb	255

	
        section .text
        global  main
mai:
	xor	r9,r9
        mov     rax,1
        mov     rdi,1
        mov     rsi,msg
        mov     rdx,len
        syscall

        mov     rax,0
        mov     rdi,0
        mov     rsi,num
        mov     rdx,255
	syscall
	call convert
	

        mov     rax,1
        mov     rdi,1
        mov     rsi,msg2
        mov     rdx,len2
        syscall

	mov     rax,0
        mov     rdi,0
        mov     rsi,string
        mov     rdx,255
        syscall
	call	count_char

	mov	rax,1
	mov	rdi,1
	mov	rsi,msg3
	mov	rdx,len3
	syscall
	

	mov	rax,1
	mov	rdi,1
	mov	rsi,string
	mov	rdx,255
	syscall

	mov     rax,1
        mov     rdi,1
        mov     rsi,msg4
        mov     rdx,len4
        syscall
	
	mov	rsi,num
	call	convert		;calls convert again to al can contain num
	mov	rsi,string
	call	check

	mov     rax,1
        mov     rdi,1
	mov	rsi,string
        mov     rdx,255
        syscall


        mov     rax,60
        xor     rdi,rdi
        syscall

convert:
	xor	r9,r9
	mov	al,[rsi]
	inc 	rsi
	cmp	al,45		;checks for negative number
	je 	convert
	sub	al,48
	cmp	byte[rsi],48	;checks if it a double digit number
	jl	shift
	mov	al,byte[rsi]
	sub	al,48
	dec	rsi
	jmp	multiply
		
multiply:			;adds 20 when 2 is first 
	cmp	r9,10
	je	shift
	add	al,[rsi]
	sub	al,48
	inc	r9
	jmp 	multiply
	ret
		
check:	
	ret
redo:				;prompts user to reenter number if the previous was invalid
	mov     rax,1
        mov     rdi,1
        mov     rsi,msg
        mov     rdx,len
        syscall

        mov     rax,0
        mov     rdi,0
        mov     rsi,num
        mov     rdx,64
        syscall

	jmp	convert
	
count_char:			;counts number of characters in string
	cmp	[rsi],byte 0
	jle	char_check
	add	r12,1
	inc	rsi
	jmp	count_char
	
char_check:			;checks if there are 8 characters in a string
	cmp	r12,8
	jl	redo_string
	ret
	
redo_string:			;prompts user for new string if previous was invalid
	xor	r12,r12
	mov     rax,1
        mov     rdi,1
        mov     rsi,msg2
        mov     rdx,len2
        syscall

        mov     rax,0
        mov     rdi,0
        mov     rsi,string
        mov     rdx,255
        syscall

	jmp	count_char
	
Rshift: 			;right shift for uppercase
	cmp	[num],byte 45
	je	Lshift
	cmp	[rsi],byte 97
	jge	lowerRshift
        add	[rsi],al
	cmp	[rsi],byte 90
	jg	RshiftCont
	ret
RshiftCont:			;case when letter is out of range
	sub	[rsi],byte 91
	add	[rsi],byte 65
	ret
lowerRshift:
	sub	[rsi],byte 32		;case for right shift lower case
        add     [rsi],al
        cmp     [rsi],byte 90
        jg	lowerRshiftCont
	add	[rsi],byte 32
        ret
lowerRshiftCont:
	sub     [rsi],byte 91
        add     [rsi],byte 65
	add	[rsi],byte 32
        ret
Lshift:			;case for left shift uppercase
	cmp     [rsi],byte 97
        jge      lowerLshift
        sub     [rsi],al
        cmp     [rsi],byte 65
        jl	LshiftCont
	ret
LshiftCont:			
	sub     [rsi],byte 65
        add	[rsi],byte 91 
        ret
lowerLshift:			;case for left shift lowercase
	sub     [rsi],al
        cmp     [rsi],byte 97
        jl	lowerLshiftCont
        ret
lowerLshiftCont:
	sub	[rsi],byte 97
	add	[rsi],byte 123
	ret

shift:
	cmp	al,25
	jg	reset
	cmp     [rsi],byte 0
        je      end
	call	upperCheck
	call	Rshift
        inc     rsi
        jmp     shift
reset:
	sub	al,26
	cmp	al,25
	jg	reset
	ret
	
upperCheck:			;checks a character is an upper case letter
	cmp	[rsi],byte 65
	jl	invalid
	cmp	[rsi],byte 90
	jg	lowerCheck
	ret
lowerCheck:			;checks a character is an lower case letter
	cmp	[rsi],byte 97	
	jl	invalid
	cmp	[rsi],byte 122
	jg	invalid
	ret
invalid:			;skips non-letter characters
	inc	rsi
	jmp	shift
end:
	ret
