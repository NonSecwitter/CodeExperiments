/////////////////////////////////////////////////////////////////////
////////// While loop with pre-initialized count variable ///////////
/////////////////////////////////////////////////////////////////////

$LN5@main:

; 7    : 
; 8    : 	while (count < SIZE && arr[count] != search)

	cmp	DWORD PTR _count$[ebp], 5
	jge	SHORT $LN4@main
	mov	eax, DWORD PTR _count$[ebp]
	mov	ecx, DWORD PTR _arr$[ebp+eax*4]
	cmp	ecx, DWORD PTR _search$[ebp]
	je	SHORT $LN4@main

; 9    : 		count++;

	mov	eax, DWORD PTR _count$[ebp]
	add	eax, 1
	mov	DWORD PTR _count$[ebp], eax
	jmp	SHORT $LN5@main
$LN4@main:


/////////////////////////////////////////////////////////////////////////
////////////For loop with pre-initialized count variable'////////////////
/////////////////////////////////////////////////////////////////////////

jmp	SHORT $LN3@main
$LN2@main:

; 12   : 
; 13   : 	for (; count < SIZE && arr[count] != search; count++);

	mov	eax, DWORD PTR _count$[ebp]
	add	eax, 1
	mov	DWORD PTR _count$[ebp], eax
$LN3@main:
	cmp	DWORD PTR _count$[ebp], 5
	jge	SHORT $LN1@main
	mov	eax, DWORD PTR _count$[ebp]
	mov	ecx, DWORD PTR _arr$[ebp+eax*4]
	cmp	ecx, DWORD PTR _search$[ebp]
	je	SHORT $LN1@main
	jmp	SHORT $LN2@main
$LN1@main:
