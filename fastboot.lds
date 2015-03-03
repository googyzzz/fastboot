OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

MEMORY
{
ram(RW): 		ORIGIN = 0x80108000, LENGTH = 10M
}

SECTIONS
{
	.text :
	{
		*(.text .text.*);
	} > ram

	.rodata : 
	{
  		*(.rodata .rodata.* .gnu.linkonce.r.*);
 	} > ram

 	.data : 
 	{
 		*(EXCLUDE_FILE(hypervisor.elf.o) .data .data.*);
 	} > ram
        
        .stack (NOLOAD) : ALIGN(8)
        {
          _sstack = .;
          . = . + 8000;
          . = ALIGN(8);
          _estack = .;
        } > ram
        
        .piggy.data : ALIGN(8)
        {
          _elf_start = .;
          hypervisor.elf.o (.data);
          _elf_end   = .;
        } > ram
      
}
