TARGET:=fastboot.bin
TARGET_ELF:=$(patsubst %bin,%elf,${TARGET})

CC:=${CROSS_COMPILE}gcc
LD:=${CROSS_COMPILE}ld
AS:=${CROSS_COMPILE}as
OBJCOPY:=${CROSS_COMPILE}objcopy


objs:=init.o main.o

all: ${TARGET}


${TARGET}: ${TARGET_ELF}
	${OBJCOPY} -I elf32-littlearm -O binary $< $@

${TARGET_ELF}: ${objs} fastboot.lds
	${LD} ${objs} --script fastboot.lds -o $@
	
%.o: %.s
	${AS} $< -o $@

$.o: %.c
	${CC} -g $< -o $@