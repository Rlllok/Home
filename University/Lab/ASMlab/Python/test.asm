Data	Segment
HexV1	dd	0ff93H
DecV1	dd	(3 + 2) * (4 + 6)
BinV1	db	10000b
Data ends

code Segment
ww1 dd (10+15)*3 - 8
ww2 dw 14
begin:
m1:	
	jbe m2
	stc
	inc ebx
	dec HexV1[ebx+esi]
	dec ww1[eax+ebp]
	dec ww2[eax+eax]
	sub eax, ecx
	and eax, DecV1[eax+edx]
	or es:BinV1[eax+esi], 0101b
	mov ecx, 0ah
	cmp DecV1[edx+esi], ecx
	jbe m1	
	mov eax, 5
	push 5
	push 732h
m2:
code	ends
end
