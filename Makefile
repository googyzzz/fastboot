TARGET:=fastboot.bin
TARGET_ELF:=$(patsubst %bin,%elf,${TARGET})

CC:=${CROSS_COMPILE}gcc
LD:=${CROSS_COMPILE}ld
AS:=${CROSS_COMPILE}as
OBJCOPY:=${CROSS_COMPILE}objcopy


CCFLAGS:= -marm -nostdinc -march=armv4 -mtune=arm7tdmi -ffunction-sections -fdata-sections -fno-common -msoft-float
INCLUDES:=-Iinclude
objs:=init.o string_mod.o main.o

all: ${TARGET}


${TARGET}: ${TARGET_ELF}
	${OBJCOPY} -I elf32-littlearm -O binary $< $@

${TARGET_ELF}: ${objs} fastboot.lds
	${LD} ${objs} --script fastboot.lds -o $@
	
%.o: %.s
	${AS} $< -o $@

%.o: %.c
	${CC} ${CCFLAGS} ${INCLUDES} -g -c $< -o $@

.PHONY: clean        
clean:
	rm -f ${objs} ${TARGET} ${TARGET_ELF}
