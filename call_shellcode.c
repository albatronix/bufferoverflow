/* call_shellcode.c  */

/*A program that creates a file containing code for launching shell*/
#include <stdlib.h>
#include <stdio.h>

const char code[] =
  "\x31\xc0"             /* xorl    %eax,%eax              */ //making eax 0
  "\x50"                 /* pushl   %eax                   */ //pushing eax into esp (stack pointer)-- pushing 0 into esp
													//more accurate to say we're pushing eax onto the stack?
													//does esp now point to... eax?
  "\x68""//sh"           /* pushl   $0x68732f2f            */ //decimal 1752379183, pushing this into stack pointer
  "\x68""/bin"           /* pushl   $0x6e69622f            */ //decimal 1852400175, pushing this into stack pointer
															//: /bin/sh is an executable representing the system shell
  "\x89\xe3"             /* movl    %esp,%ebx              */ //moving the stack pointer contents into ebx register
  "\x50"                 /* pushl   %eax                   */ //pushing eax (0) into esp
  "\x53"                 /* pushl   %ebx                   */ //pushing contents of ebx into esp
  "\x89\xe1"             /* movl    %esp,%ecx              */ //moving contents of esp into ecx
  "\x99"                 /* cdq                            */ //convert double to quad-- convert what double?
  "\xb0\x0b"             /* movb    $0x0b,%al              */ //moving 11 into the lower byte of the %ax register
  "\xcd\x80"             /* int     $0x80                  */ //interrupt (and making a system call, maybe?)
;

int main(int argc, char **argv)
{
   char buf[sizeof(code)]; //declare an array of characters "buf" with length sizeof the code
   strcpy(buf, code); //put the code into the buffer array
   ((void(*)( ))buf)( ); //casts buf into a function pointer, type void(*)() and calls the resulting function 
						//last set of () would contain arguments if there were any
   } 

