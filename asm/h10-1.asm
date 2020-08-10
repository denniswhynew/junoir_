INCLUDE Irvine32.inc
INCLUDE Macros.inc
.data
	inputs byte 501 dup(0)
	filelen dword 0
	inputname db "請輸入檔案名稱: ", 0
	filename byte 100 dup(0)
	hfile HANDLE ?
	strlen DWORD ?
	nBytes dword ?

	s1 db "cannot create file", 0
	s2 db "written file", 0
	s3 db "enter at most 500 characters and"
	   db "[Enter]: ", 0
.CODE
main PROC
	mov edx, OFFSET inputname
	call writestring
	call rstring
;creating file
	mov edx, OFFSET filename
	call CreateOutputFile
	mov hfile, eax
;Cheak file error
	cmp eax, INVALID_HANDLE_VALUE
	jne file_ok
	mov edx, offset s1
	call writestring
	jmp quit
file_ok:
;inputstring
	mov edx, offset s3
	call writestring
	call rinput
;write the file
	mov eax, hfile
	mov edx, offset inputs
	mov ecx, filelen
	call WriteToFile
	mov nBytes, eax
	call CloseFile
;display return value
	mov edx, offset s2
	call writestring
	mov eax, nBytes
	call writedec
quit:
	call crlf
call  WaitMsg
exit
;------------
rstring PROC near
	mov edx, OFFSET filename
	mov ecx, 99
	call ReadString
	call crlf
	mov strlen, eax
	ret
rstring endp
;------------
rinput PROC near
	mov edx, OFFSET inputs
	mov ecx, 500
	call ReadString
	call crlf
	mov filelen, eax
	ret
rinput endp

;------------
main ENDP
END main
