BUILDDIR = build/bin
ODIR = build/obj

CORE = STM32F4/core
PERIPH = STM32F4/general
NUCLEO = STM32F4/nucleo
LIBS = ub_lib

SOURCES += $(NUCLEO)/src/startup_stm32f4xx.c \
		   $(NUCLEO)/src/system_stm32f4xx.c

SOURCES += $(PERIPH)/src/misc.c \
		   $(PERIPH)/src/stm32f4xx_exti.c \
		   $(PERIPH)/src/stm32f4xx_gpio.c \
		   $(PERIPH)/src/stm32f4xx_rcc.c \
		   $(PERIPH)/src/stm32f4xx_syscfg.c \
		   $(PERIPH)/src/stm32f4xx_adc.c \
		   $(PERIPH)/src/stm32f4xx_dma.c \
		   $(PERIPH)/src/stm32f4xx_spi.c \
		   $(PERIPH)/src/stm32f4xx_tim.c


SOURCES += src/main.c \
		   src/adc.c \
		   src/interrupt.c \
		   src/osci.c \
		   src/tm_stm32f4_adc.c \
		   src/tm_stm32f4_dma.c \
		   src/tm_stm32f4_fonts.c \
		   src/tm_stm32f4_gpio.c \
		   src/tm_stm32f4_ili9341.c \
		   src/tm_stm32f4_spi.c \
		   src/tm_stm32f4_spi_dma.c \
		   src/Touch.c



OBJECTS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))

INCLUDES += -I$(NUCLEO)/api \
			-I$(CORE) \
			-I$(PERIPH)/api \
			-I./api \
			-I

ELF = $(BUILDDIR)/program.elf
HEX = $(BUILDDIR)/program.hex
BIN = $(BUILDDIR)/program.bin

CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
AR = arm-none-eabi-ar
OBJCOPY = arm-none-eabi-objcopy

CFLAGS  = -O0 -g -Wall -I.\
   -mcpu=cortex-m4 -mthumb \
   -mfpu=fpv4-sp-d16 -mfloat-abi=hard \
   -lc -specs=nosys.specs \
   $(INCLUDES) -DUSE_STDPERIPH_DRIVER

LDSCRIPT = flash.ld
LDFLAGS += -T$(LDSCRIPT) -mthumb -mcpu=cortex-m4 -nostdlib

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

$(ELF): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

$(BUILDDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

#$(BUILDDIR)/%.o: %.s
	#mkdir -p $(dir $@)
	#$(CC) -c $(CFLAGS) $< -o $@

flash: $(BIN)
	st-flash write $(BIN) 0x8000000

clean:
	rm -rf build
