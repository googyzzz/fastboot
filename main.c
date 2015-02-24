#include <elf.h>
#include "string_mod.h"

static unsigned long load_elf_image_phdr(unsigned long addr);

/* method may be simplified for and command directly used in main */
static void do_bootelf_exec(unsigned long (*entry)(int, char * const[]), int argc, char * argv[])
{
	entry(argc, argv);
}

int main(void)
{
	/* address of the elf file */
	unsigned long addr = 1234;	
	/* not known if needed, argc and argv for entry with commands */
	int argc = 0;
	char * argv[1];
	argv[0] = "";

	/* use method load_elf_image_phdr to copy the elf file */
	addr = load_elf_image_phdr(addr);

	/* start the elf file at copy adress */
	do_bootelf_exec((void *)addr, argc, argv);

	return 0;
}

/* method load_elf_image_phdr copied from u-boot command_elf.c file */
static unsigned long load_elf_image_phdr(unsigned long addr)
{
	Elf32_Ehdr *ehdr;		/* Elf header structure pointer     */
	Elf32_Phdr *phdr;		/* Program header structure pointer */
	int i;

	ehdr = (Elf32_Ehdr *) addr;
	phdr = (Elf32_Phdr *) (addr + ehdr->e_phoff);

	/* Load each program header */
	for (i = 0; i < ehdr->e_phnum; ++i) {
		void *dst = (void *)(uintptr_t) phdr->p_paddr;
		void *src = (void *) addr + phdr->p_offset;
		if (phdr->p_filesz)
			memcpy(dst, src, phdr->p_filesz);
		if (phdr->p_filesz != phdr->p_memsz)
			memset(dst + phdr->p_filesz, 0x00,
				phdr->p_memsz - phdr->p_filesz);
		/* edit: at the moment, the method is not used, because no enabled cache
		flush_cache((unsigned long)dst, phdr->p_filesz);
		*/
		++phdr;
	}

	return ehdr->e_entry;
}
