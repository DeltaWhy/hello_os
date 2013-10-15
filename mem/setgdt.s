.global setGdt

gdtr:
    .int 0 # For limit storage
    .long 0 # For base storage
 
setGdt:
    MOV   4(%esp), %EAX
    MOV   %EAX, (gdtr + 2)
    MOV   8(%esp), %AX
    MOV   %AX, (gdtr)
    LGDT  (gdtr)
    RET
