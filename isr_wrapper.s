.global   _isr_wrapper
.align   4
 
_isr_wrapper:
    cli
    pushal
    call    _interrupt_handler
    popal
    sti
    iret
