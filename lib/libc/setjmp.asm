; vim: ft=nasm ai
[BITS 32]

	global setjmp

[SECTION .text]
setjmp:
	mov [ecx+0], esi
	mov [ecx+4], edi
	mov [ecx+8], ebx
	mov [ecx+12], ebp
	mov [ecx+16], esp
	ret

longjmp:
	mov esi, [ecx+0]
	mov edi, [ecx+4]
	mov ebx, [ecx+8]
	mov ebp, [ecx+12]
	mov esp, [ecx+16]
	mov eax, edx
	ret
