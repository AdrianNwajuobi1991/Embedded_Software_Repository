CC=arm-none-eabi-gcc
AR=arm-none-eabi-ar
MACH=cortex-m7
LIBRARY_ROOT=/home/adrian/STM32CubeIDE/workspace_1.14.0/NUCLEOF767ZIDriversUnitTestProject/export_mcu_peripheral_libraries
PROJECT_DIR=/home/adrian/STM32CubeIDE/workspace_1.14.0/NUCLEOF767ZIDriversUnitTestProject
OBJECTS_DIR=$(LIBRARY_ROOT)/objects
INCLUDE_DIR=-I$(PROJECT_DIR)/device_driver_interfaces -I$(PROJECT_DIR)/device_layout_definitions \
	-I$(PROJECT_DIR)/register_bitwise_operations_utils -I$(PROJECT_DIR)/dependency_injection_interfaces
DRIVER_SRCS_DIR=$(PROJECT_DIR)/core_drivers
CFLAGS=-g -c -DPRODUCTION_MODE -mcpu=$(MACH) -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -std=gnu11 -Wall $(INCLUDE_DIR) -O0
ARFLAGS=r
ARCHIVE_NAME=libSTM32F767ZIPeripheralDrivers.a
OBJECTS= $(OBJECTS_DIR)/STM32F767ZI_GPIO_Driver.o $(OBJECTS_DIR)/STM32F767ZI_SPI_Driver.o $(OBJECTS_DIR)/register_bit_utils.o \
	$(OBJECTS_DIR)/STM32F767ZI_I2C_Driver.o $(OBJECTS_DIR)/STM32F767ZI_USART_Driver.o $(OBJECTS_DIR)/STM32F767ZI_TIMER_Driver.o \
	$(OBJECTS_DIR)/STM32F767ZI_DMA_Driver.o

all: $(OBJECTS) create_static_library

$(OBJECTS_DIR)/register_bit_utils.o : $(PROJECT_DIR)/register_bitwise_operations_utils/register_bit_utils.c
	$(CC) $(CFLAGS) $^ -o $@

$(OBJECTS_DIR)/STM32F767ZI_GPIO_Driver.o : $(DRIVER_SRCS_DIR)/STM32F767ZI_GPIO_Driver.c
	$(CC) $(CFLAGS) $^ -o $@
	
$(OBJECTS_DIR)/STM32F767ZI_SPI_Driver.o : $(DRIVER_SRCS_DIR)/STM32F767ZI_SPI_Driver.c
	$(CC) $(CFLAGS) $^ -o $@
	
$(OBJECTS_DIR)/STM32F767ZI_I2C_Driver.o : $(DRIVER_SRCS_DIR)/STM32F767ZI_I2C_Driver.c
	$(CC) $(CFLAGS) $^ -o $@
	
$(OBJECTS_DIR)/STM32F767ZI_USART_Driver.o : $(DRIVER_SRCS_DIR)/STM32F767ZI_USART_Driver.c
	$(CC) $(CFLAGS) $^ -o $@
	
$(OBJECTS_DIR)/STM32F767ZI_TIMER_Driver.o : $(DRIVER_SRCS_DIR)/STM32F767ZI_TIMER_Driver.c
	$(CC) $(CFLAGS) $^ -o $@
	
$(OBJECTS_DIR)/STM32F767ZI_DMA_Driver.o : $(DRIVER_SRCS_DIR)/STM32F767ZI_DMA_Driver.c
	$(CC) $(CFLAGS) $^ -o $@
	
create_static_library: $(OBJECTS)
	$(AR) $(ARFLAGS) $(ARCHIVE_NAME) $^
	
clean:
	rm $(OBJECTS_DIR)/*.o $(LIBRARY_ROOT)/$(ARCHIVE_NAME)