LIB = ../libstm32f4xx_stdperiph_driver.a

CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar
RANLIB = arm-none-eabi-ranlib

CFLAGS = -Wall -g -Os -mlittle-endian -mthumb
CFLAGS += -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffreestanding -nostdlib -nostartfiles
CFLAGS += -DUSE_STDPERIPH_DRIVER
CFLAGS += -I./inc -I./template

CMSIS_PATH = ../CMSIS
CFLAGS += -I$(CMSIS_PATH)/STM32F4xx -I$(CMSIS_PATH)/Include

SRCS_PATH = ./src
SRCS = \
$(SRCS_PATH)/misc.c \
$(SRCS_PATH)/stm32f4xx_adc.c \
$(SRCS_PATH)/stm32f4xx_can.c \
$(SRCS_PATH)/stm32f4xx_crc.c \
$(SRCS_PATH)/stm32f4xx_cryp_aes.c \
$(SRCS_PATH)/stm32f4xx_cryp_des.c \
$(SRCS_PATH)/stm32f4xx_cryp_tdes.c \
$(SRCS_PATH)/stm32f4xx_cryp_des.c \
$(SRCS_PATH)/stm32f4xx_dac.c \
$(SRCS_PATH)/stm32f4xx_dbgmcu.c \
$(SRCS_PATH)/stm32f4xx_dcmi.c \
$(SRCS_PATH)/stm32f4xx_dma.c \
$(SRCS_PATH)/stm32f4xx_exti.c \
$(SRCS_PATH)/stm32f4xx_flash.c \
$(SRCS_PATH)/stm32f4xx_fsmc.c \
$(SRCS_PATH)/stm32f4xx_gpio.c \
$(SRCS_PATH)/stm32f4xx_hash_md5.c \
$(SRCS_PATH)/stm32f4xx_hash_sha1.c \
$(SRCS_PATH)/stm32f4xx_hash.c \
$(SRCS_PATH)/stm32f4xx_i2c.c \
$(SRCS_PATH)/stm32f4xx_iwdg.c \
$(SRCS_PATH)/stm32f4xx_pwr.c \
$(SRCS_PATH)/stm32f4xx_rcc.c \
$(SRCS_PATH)/stm32f4xx_rng.c \
$(SRCS_PATH)/stm32f4xx_rtc.c \
$(SRCS_PATH)/stm32f4xx_sdio.c \
$(SRCS_PATH)/stm32f4xx_spi.c \
$(SRCS_PATH)/stm32f4xx_syscfg.c \
$(SRCS_PATH)/stm32f4xx_tim.c \
$(SRCS_PATH)/stm32f4xx_usart.c \
$(SRCS_PATH)/stm32f4xx_wwdg.c \
#../inc/core_support/core_cm4.c

OBJS = $(SRCS:.c=.o)

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) -r $(LIB) $(OBJS)
	$(RANLIB) $(LIB)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	-rm -f $(OBJS)
	-rm -f $(LIB)

oclean:
	-rm -f $(OBJS)


.PHONY: all clean
