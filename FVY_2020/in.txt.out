.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib "..\Debug\MyLib.lib"
ExitProcess PROTO:DWORD 
.stack 4096

 outnum PROTO : DWORD

 outstr PROTO : DWORD

 outstrline PROTO : DWORD

 outnumline PROTO : DWORD

 system_pause PROTO 

 lenght PROTO  : DWORD

 power PROTO : DWORD, : DWORD
.const
 null_division BYTE 'ERROR: DIVISION BY ZERO', 0
 overflow BYTE 'ERROR: VARIABLE OVERFLOW', 0 
	L1 SDWORD 2
	L2 SDWORD 10
	L3 SDWORD 3
	L4 BYTE 'My first program!', 0
	L5 SDWORD 5
	L6 BYTE 'a = ', 0
	L7 BYTE ' ', 0
	L8 SDWORD 1
	L9 SDWORD 0
.data
	_abstmp SDWORD 0
	mainstr DWORD ?
	maina SDWORD 0
	mainc SDWORD 0
	maini SDWORD 0

.code

_abs PROC _absa :  SDWORD 
	push _absa
	push L1
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop _absa

	push L2
	pop _abstmp

	mov edx, _absa
	cmp edx, L3
	jg right1
	jmp next1
right1:	mov eax, _abstmp
	ret

SOMETHINGWRONG:
push offset null_division
call outstrline
call system_pause
push -1
call ExitProcess

EXIT_OVERFLOW:
push offset overflow
call outstrline
call system_pause
push -2
call ExitProcess

next1:	mov eax, _absa
	ret
_abs ENDP
main PROC
	push offset L4
	pop mainstr


push mainstr
call outstrline
	push L5
	pop maina

	push L1
	pop mainc


push offset L6
call outstr

push maina
call outnum

push offset L7
call outstrline
	push maina
	push L8
	push _abs
	push mainc
	pop edx
	pop edx
	push mainc
		call _abs
	push eax
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push L3
	pop eax
	pop ebx
	imul ebx
	jo EXIT_OVERFLOW
	push eax
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop maini

	mov edx, maini
	cmp edx, L9
	jg cycle1
	jmp continue1
 cycle1:
push maini
call outnumline
	push maini
	push L8
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop maini

	mov edx, maini
	cmp edx, L9
	jg cycle1
continue1:call system_pause
push 0
call ExitProcess
SOMETHINGWRONG:
push offset null_division
call outstrline
call system_pause
push -1
call ExitProcess
EXIT_OVERFLOW:
push offset overflow
call outstrline
call system_pause
push -2
call ExitProcess
main ENDP
end main