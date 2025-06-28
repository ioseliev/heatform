CC := arm-none-eabi-gcc
LD := arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy

CFLAGS := -g -O2 -Iinc/

TARGET := bin/heatform.bin
TARGET_ELF = $(basename ${TARGET})

SRCS := $(notdir $(wildcard src/*.c))
OBJS := $(addprefix obj/, ${SRCS:.c=.o})


${TARGET}: ${TARGET_ELF}
	${OBJCOPY} -O binary ${TARGET_ELF} ${TARGET}

${TARGET_ELF}: ${OBJS}
	@mkdir -p ${@D}
	${LD} -o $@ $^

obj/%.o: src/%.c
	@mkdir -p ${@D}
	${CC} -c ${CFLAGS} -o $@ $<

.PHONY: clean
clean:
	rm -f ${TARGET} ${TARGET_ELF} ${OBJS}
