CC := arm-none-eabi-gcc
AS := arm-none-eabi-as
LD := arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy

CFLAGS := -ffreestanding -fno-builtin -mcpu=cortex-a8 -mfpu=neon -mhard-float -g -O2 -std=c11 -Iinc/
AFLAGS := -mfpu=neon

TARGET := bin/heatform.bin
TARGET_ELF = $(basename ${TARGET})

SRCS := $(notdir $(wildcard src/*.c))
OBJS := $(addprefix obj/, ${SRCS:.c=.o})


${TARGET}: ${TARGET_ELF}
	${OBJCOPY} -O binary ${TARGET_ELF} ${TARGET}

${TARGET_ELF}: obj/start.o ${OBJS}
	@mkdir -p ${@D}
	${LD} -T src/memmap.ld -o $@ $^

obj/start.o: src/start.s
	${AS} ${AFLAGS} -o $@ $<

obj/%.o: src/%.c
	@mkdir -p ${@D}
	${CC} -c ${CFLAGS} -o $@ $<

.PHONY: clean
clean:
	rm -f ${TARGET} ${TARGET_ELF} ${OBJS} obj/start.o
