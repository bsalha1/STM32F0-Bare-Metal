TARGETS=blink.c lib/gpio.c
LINKER_SCRIPT=stm32.ld
PROGRAM_NAME=prog1
TTL_NODE=/dev/ttyUSB0
BUILD_DIRECTOR=build/

GCC = arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -c -I'lib/includes/'
BASE_SRCS = $(wildcard *.c)
LIB_SRCS = $(wildcard lib/src/*.c)

all:
	@make clean
	@make compile
	@make link
	@make copy

clean:
	rm -rf build/
	rm -f *.o

compile:
	@echo "=-=-=-=-COMPILING-=-=-=-="
	$(GCC) $(BASE_SRCS)
	$(GCC) $(LIB_SRCS)

link:
	@echo "\n=-=-=-=-=LINKING=-=-=-=-="
	@mkdir -p build
	arm-none-eabi-ld -T ${LINKER_SCRIPT} -o build/${PROGRAM_NAME}.elf $(wildcard *.o)

copy:
	@echo "\n=-=-=-COPYING BINARY-=-=-="
	arm-none-eabi-objcopy -O binary build/${PROGRAM_NAME}.elf build/${PROGRAM_NAME}.bin

flash:
	sudo stm32flash -w build/${PROGRAM_NAME}.bin -v ${TTL_NODE}