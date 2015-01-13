OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

MEMORY
{
ram(RW): 		ORIGIN = 0x80000000, LENGTH = 10M
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
 		*(.data .data.*);
 	} > ram
}
