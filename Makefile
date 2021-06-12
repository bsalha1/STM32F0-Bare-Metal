TARGETS=blink.c
LINKER_SCRIPT=stm32.ld
NAME=blink
TTL_NODE=/dev/ttyUSB0

all:
	@echo "\n========COMPILING========"
	arm-none-eabi-gcc -v -mcpu=cortex-m0 -mthumb -c -o ${NAME}.o ${TARGETS}
	@echo "\n=========LINKING========="
	arm-none-eabi-ld --verbose -T ${LINKER_SCRIPT} -o ${NAME}.elf ${NAME}.o
	@echo "\n======COPYING BINARY======"
	arm-none-eabi-objcopy -v -O binary ${NAME}.elf ${NAME}.bin

flash:
	sudo stm32flash -w ${NAME}.bin -v ${TTL_NODE}