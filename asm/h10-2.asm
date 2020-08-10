INCLUDE Irvine32.inc
INCLUDE Macros.inc
BUFFER_SIZE = 50000
.data
	buffer byte BUFFER_SIZE DUP(?)
	filename byte 80 DUP(0)
	str1 byte 80 DUP(0)
	hfile handle ?
	flag dword 1
.CODE
main PROC
	mWrite "請輸入檔案名稱: "
	mov edx, offset filename
	mov ecx, sizeof filename
	call readstring

;open file
	mov edx, OFFSET filename
	call openinputfile
	mov hfile, eax

;Cheak file error
	cmp eax, INVALID_HANDLE_VALUE
	jne file_ok
	mWrite <"無法開啟檔案",0dh,0ah>
	jmp quit
file_ok:
;read file
	mov edx, offset buffer
	mov ecx, BUFFER_SIZE
	call ReadFromFile
	jnc checkbuffer
	mWrite "讀取檔案錯誤"
	call WriteWindowsMsg
	jmp close_file
checkbuffer:
	cmp eax, BUFFER_SIZE
	jb bsize_ok
	mWrite <"Error: buffer too small for file",0dh,0ah>
	jmp quit
bsize_ok:
	mov buffer[eax], 0
	mWrite "File size: "
	call writedec
;display buffer
	mWrite <"Buffer: ",0dh,0ah,0dh,0ah>
	mov edx, offset buffer
	call writestring
	call crlf
close_file:
	mov eax, hfile
	call closefile
quit:
;------------------
	mWrite "請輸入欲比較字串: "
	mov edx, offset str1
	mov ecx, sizeof str1
	call readstring
	call substring_check
	.IF flag == 0
		mWrite "字串存在檔案中"
	.else
		mWrite "字串不存在檔案中"
	.endif
;------------------
	call crlf
call  WaitMsg
exit
;----
substring_check PROC near	;0 or 1
	xor esi, esi
	.while [buffer+esi] != 0
		mov al, [buffer+esi]
		.if al == [str1]
			xor ecx, ecx
			.while [str1+ecx] != 0
				mov ah, [buffer+esi+ecx]
				.if ah == [str1+ecx]
					mov flag, 0
				.else
					mov flag, 1
					.break
				.endif
				inc ecx
			.endw
		.endif
		inc esi
	.endw
	ret
substring_check endp
;----
main ENDP
END main
