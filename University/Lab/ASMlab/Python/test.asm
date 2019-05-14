Data segment
hexv1 dd 0ff93h
decv1 dw 3 + 2 * 4
binv1 db 10000b
date ends

code segment
ww1 dd (10+15)*3 - 8
begin:
m1: jbe m2
    stc
    inc ebx
    dec hexv1[ebx+esi]
    dec ww1[eax+ebp]
    sub eax, ecx
    and eax, decv1[eax+edx]
    or es:binv1[eax+esi], 0101b
    mov ecx, 0ah
    cmp decv1[edx+esi], ecx
    jbe m1
m2:
code ends
end