.global _start
_start:
   /* Initialize stack pointers.
   This is done for all processor modes for now. Note that we only use one stack pointer.
   During initialization any switch to abort or undefined should be considered fatal, so
   that we do not need to preserve the sys stack. All modes, which need their own stacks
   should receive them during initialization. */

   mov   r2,               #0xD1   /*FIQ mode*/
   msr   cpsr_c,   r2
   ldr   sp,           =_estack

   mov   r2,           #0xD2   /*IRQ mode*/
   msr   cpsr_c,   r2
   ldr   sp,           =_estack

   mov   r2,           #0xD7   /*Abort mode*/
   msr   cpsr_c,   r2
   ldr   sp,           =_estack

   mov   r2,           #0xDB   /*Undefined mode*/
   msr   cpsr_c,   r2
   ldr   sp,           =_estack

   mov   r2,           #0xDF   /*System mode*/
   msr   cpsr_c,   r2
   ldr   sp,           =_estack

   mov   r2,           #0xD3   /*Supervisor mode*/
   msr   cpsr_c,   r2
   ldr   sp,           =_estack
   
   /* set PU0 function to GPIO */
   mov   r0,   #0x1
   ldr   r1,   =0x6000D500
   str   r0,   [r1]
   
   /* set PU0 direction to output */
   ldr   r1,   =0x6000D510
   str   r0,   [r1]
   
   /* set PU0 value to high */
   ldr   r1,   =0x6000D520
   str   r0,   [r1]
   
   /* activate PU0 output stage */
   mov   r0,   #0x20
   ldr   r1,   =0x70003184
   str   r0,   [r1]
   
   bl main
   b .


