file kernel.elf
target remote :1234
b kernel.c:kmain
c
