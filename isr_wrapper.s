.global   _isr_wrapper
.align   4
 
_isr_wrapper:
    pushal
    call    _interrupt_handler
    popal
    iret
