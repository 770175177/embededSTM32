TARGET	:= demo
OUT_DIR	:= out

REMOTE_USER	:=
REMOTE_IP	:=
REMOTE_PASSWD	:=
REMOTE_DIR	:=
REMOTE_DNSCRIPT	:= download_script.jlink 

CROSS_COMPILE	:= arm-none-eabi-
CC 	:= $(CROSS_COMPILE)gcc
OBJDUMP	:= $(CROSS_COMPILE)objdump
OBJCOPY	:= $(CROSS_COMPILE)objcopy
OBJSIZE	:= $(CROSS_COMPILE)size

DEFINE	:= -DUSE_STDPERIPH_DRIVER \
	   -DSTM32F10X_MD

CFLAGS	:= -g \
	   -mcpu=cortex-m3 \
	   -mthumb \
	   -nostartfiles
#	   --specs=nosys.specs

LIBS	:= 

CFLAGS	+= $(DEFINE)
LDFILE	:= ./libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32_flash.ld

INC	:= -I./libraries/CMSIS/CM3/CoreSupport \
	   -I./libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x \
	   -I./libraries/STM32F10x_StdPeriph_Driver/inc \
	   -I./drivers \
	   -I./app

SRCS	:= libraries/CMSIS/CM3/CoreSupport/core_cm3.c \
	   libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c \
	   libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_md.s \
	   libraries/STM32F10x_StdPeriph_Driver/src/misc.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_adc.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_can.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_crc.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dac.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dbgmcu.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_i2c.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_iwdg.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_sdio.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c \
	   libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_wwdg.c \
	   drivers/stm32f10x_it.c \
	   drivers/usart1.c \
	   drivers/led.c \
	   app/main.c

OBJS	:= $(patsubst %.c,%.o,$(patsubst %.s,%.o,$(SRCS)))
OBJO	:= $(patsubst %.o,$(OUT_DIR)/%.o,$(OBJS))
DIRS	:= $(dir $(OBJO))

$(shell for dir in $(DIRS); do if [ ! -d $$dir ]; then mkdir -p $$dir; fi done)

all: $(TARGET).elf
	@echo "Create bin file $(OUT_DIR)/$@"
	@$(OBJCOPY) -O binary -S $(OUT_DIR)/$< $(OUT_DIR)/$(TARGET).bin
	@$(OBJCOPY) -O ihex $(OUT_DIR)/$< $(OUT_DIR)/$(TARGET).hex

$(TARGET).elf: $(OBJS)
	@echo "Link all, Create elf file $(OUT_DIR)/$@"
	@$(CC) $(INC) $(CFLAGS) $(LIBS) -Wl,-Map=$(OUT_DIR)/$(TARGET).map $(OBJO) \
		-T$(LDFILE) -o $(OUT_DIR)/$@
	@$(OBJSIZE) $(OUT_DIR)/$@

%.o: %.c
	@echo "Create Object $(OUT_DIR)/$@"
	@$(CC) $(INC) $(CFLAGS) -c $< -o $(OUT_DIR)/$@

%.o: %.s
	@echo "Create Object $(OUT_DIR)/$@"
	@$(CC) $(INC) $(CFLAGS) -c $< -o $(OUT_DIR)/$@

burn:
	@echo "Copy the $(TARGET).bin to remote server $(REMOTE_IP):$(REMOTE_DIR)"
	@echo "erase\nloadfile $(REMOTE_DIR)$(TARGET).bin\nreset\nexit\n" > $(OUT_DIR)/$(REMOTE_DNSCRIPT)
	@expect -c "set timeout -1; spawn scp $(OUT_DIR)/$(TARGET).bin $(OUT_DIR)/$(REMOTE_DNSCRIPT) $(REMOTE_USER)@$(REMOTE_IP):$(REMOTE_DIR); expect \"password:\"; send \"$(REMOTE_PASSWD)\r\"; interact"
	@echo "Download the remote $(OUT_DIR)/$(TARGET).bin to device flash"
	@expect -c "set timeout -1; spawn ssh $(REMOTE_USER)@$(REMOTE_IP) \"JLinkExe -device STM32F103C8 -if swd -speed 4000 -CommanderScript $(REMOTE_DIR)/$(REMOTE_DNSCRIPT)\"; expect \"password:\"; send \"$(REMOTE_PASSWD)\r\"; interact"

.PHONY:
clean:
	rm -rf $(OUT_DIR)/*

