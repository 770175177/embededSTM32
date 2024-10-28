TARGET	:= demo
OUT_DIR	:= out

REMOTE_USER	:= heng
REMOTE_IP	:= 192.168.0.109
REMOTE_PASSWD	:= 770175177
REMOTE_DIR	:= /home/heng/workspace/stm32/
REMOTE_DNSCRIPT	:= download_script.jlink 
GDBCMD_SCRIPT	:= gdb.script

CROSS_COMPILE	:= arm-none-eabi-
CC 	:= $(CROSS_COMPILE)gcc
OBJDUMP	:= $(CROSS_COMPILE)objdump
OBJCOPY	:= $(CROSS_COMPILE)objcopy
OBJSIZE	:= $(CROSS_COMPILE)size

DEFINE	:= -DUSE_STDPERIPH_DRIVER \
	   -DSTM32F10X_MD

CFLAGS	:= -g \
	   -Os \
	   -ffunction-sections \
	   -fdata-sections \
	   -mcpu=cortex-m3 \
	   -mthumb \
	   -nostartfiles

LDFLAGS	:= -Wl,--gc-sections \

LIBS	:= 

CFLAGS	+= $(DEFINE)
LDFLASHFFILE	:= ./libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32_flash.ld
LDSRAMFILE	:= ./libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32_sram.ld

INC	:= -I./libraries/CMSIS/CM3/CoreSupport \
	   -I./libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x \
	   -I./libraries/STM32F10x_StdPeriph_Driver/inc \
	   -I./freeRTOS/config \
	   -I./freeRTOS/inc \
	   -I./freeRTOS/portable/GCC/ARM_CM3 \
	   -I./include \
	   -I./drivers/config \
	   -I./drivers/delay \
	   -I./drivers/led \
	   -I./drivers/sys \
	   -I./drivers/usart \
	   -I./include/mini_printf \
	   -I./include/ring_buffer \
	   -I./include/cmd_line/lib/include \
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
	   freeRTOS/portable/GCC/ARM_CM3/port.c \
	   freeRTOS/portable/MemMang/heap_4.c \
	   freeRTOS/src/croutine.c \
	   freeRTOS/src/event_groups.c \
	   freeRTOS/src/list.c \
	   freeRTOS/src/queue.c \
	   freeRTOS/src/stream_buffer.c \
	   freeRTOS/src/tasks.c \
	   freeRTOS/src/timers.c \
	   drivers/config/stm32f10x_it.c \
	   drivers/delay/delay.c \
	   drivers/led/led.c \
	   drivers/sys/sys.c \
	   drivers/usart/usart.c \
	   include/mini_printf/mini_printf.c \
	   include/ring_buffer/ring_buffer.c \
	   include/cmd_line/lib/src/embedded_cli.c \
	   app/app_tasks.c \
	   app/app_init.c \
	   app/app_cmd.c \
	   app/main.c

OBJS	:= $(patsubst %.c,%.o,$(patsubst %.s,%.o,$(SRCS)))
OBJO	:= $(patsubst %.o,$(OUT_DIR)/%.o,$(OBJS))
DIRS	:= $(dir $(OBJO))
PWD	:= $(shell pwd)

$(shell for dir in $(DIRS); do if [ ! -d $$dir ]; then mkdir -p $$dir; fi done)

all: $(TARGET).elf
	@echo "Create bin file $(OUT_DIR)/$@"
	@$(OBJDUMP) -d $(OUT_DIR)/$(TARGET).elf > $(OUT_DIR)/$(TARGET).asm
	@$(OBJCOPY) -O binary -S $(OUT_DIR)/$< $(OUT_DIR)/$(TARGET).bin
	@$(OBJCOPY) -O ihex $(OUT_DIR)/$< $(OUT_DIR)/$(TARGET).hex

sram: $(TARGET)_sram.elf
	@echo "Create sbin file $(OUT_DIR)/$(TARGET)_sram.bin"
	@$(OBJDUMP) -d $(OUT_DIR)/$< > $(OUT_DIR)/$(TARGET)_sram.asm
	@$(OBJCOPY) -O binary -S $(OUT_DIR)/$< $(OUT_DIR)/$(TARGET)_sram.bin
	@$(OBJCOPY) -O ihex $(OUT_DIR)/$< $(OUT_DIR)/$(TARGET)_sram.hex
	@ln -sf $(PWD)/$(OUT_DIR)/$(TARGET)_sram.bin $(PWD)/$(OUT_DIR)/$(TARGET).bin

$(TARGET).elf: $(OBJS)
	@echo "Link all, Create elf file $(OUT_DIR)/$@"
	@$(CC) $(INC) $(CFLAGS) $(LIBS) $(LDFLAGS) $(OBJO) -o $(OUT_DIR)/$@ \
		-T$(LDFLASHFFILE) -Wl,-Map=$(OUT_DIR)/$(TARGET).map 
	@$(OBJSIZE) $(OUT_DIR)/$@

$(TARGET)_sram.elf: $(OBJS)
	@echo "Link all, Create self file $(OUT_DIR)/$@"
	@$(CC) $(INC) $(CFLAGS) $(LIBS) $(LDFLAGS) $(OBJO) -o $(OUT_DIR)/$@ \
		 -T$(LDSRAMFILE) -Wl,-Map=$(OUT_DIR)/$(TARGET)_sram.map
	@$(OBJSIZE) $(OUT_DIR)/$@

%.o: %.c
	@echo "Create Object $(OUT_DIR)/$@"
	@$(CC) $(INC) $(CFLAGS) -c $< -o $(OUT_DIR)/$@

%.o: %.s
	@echo "Create Object $(OUT_DIR)/$@"
	@$(CC) $(INC) $(CFLAGS) -c $< -o $(OUT_DIR)/$@

dnload:
	@echo "Copy the $(TARGET).bin to remote server $(REMOTE_IP):$(REMOTE_DIR)"
	@echo "erase\nloadfile $(REMOTE_DIR)$(TARGET).bin 0x08000000\nreset\nexit\n" > \
		$(OUT_DIR)/$(REMOTE_DNSCRIPT)
	@expect -c "set timeout -1; spawn \
		scp $(OUT_DIR)/$(TARGET).bin $(OUT_DIR)/$(REMOTE_DNSCRIPT) \
			$(REMOTE_USER)@$(REMOTE_IP):$(REMOTE_DIR); \
		expect \"password:\"; \
		send \"$(REMOTE_PASSWD)\r\"; \
		interact"

flash: dnload
	@echo "Burn the remote $(REMOTE_DIR)/$(TARGET).bin to device flash"
	@expect -c "set timeout -1; spawn \
		ssh $(REMOTE_USER)@$(REMOTE_IP) \
		\"JLinkExe -device STM32F103C8 -if swd -speed 4000 -CommanderScript \
			$(REMOTE_DIR)$(REMOTE_DNSCRIPT)\"; \
		expect \"password:\"; \
		send \"$(REMOTE_PASSWD)\r\"; \
		interact"

debug:
	@echo "set architecture arm\ntar remote $(REMOTE_IP):2331\n \
		load\nlayout src\nb main\nc\n" > \
		$(OUT_DIR)/$(GDBCMD_SCRIPT)
	@gdb-multiarch $(OUT_DIR)/$(TARGET).elf -x $(OUT_DIR)/$(GDBCMD_SCRIPT)

.PHONY:
clean:
	rm -rf $(OUT_DIR)/*

