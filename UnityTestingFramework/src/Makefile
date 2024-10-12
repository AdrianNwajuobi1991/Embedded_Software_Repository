CC=gcc
AR=ar
PROJECT_DIR=/home/adrian/STM32CubeIDE/workspace_1.14.0/UnityTestingFramework
LIBRARY_ROOT=$(PROJECT_DIR)
OBJECTS_DIR=$(PROJECT_DIR)/objects
INCLUDE_DIR=-I$(PROJECT_DIR)/src
CFLAGS=-g -c -std=gnu11 -Wall $(INCLUDE_DIR) -O0
ARFLAGS=r
ARCHIVE_NAME=libunity.a
OBJECTS= $(OBJECTS_DIR)/unity.o \

all: $(OBJECTS) create_static_library
	
$(OBJECTS_DIR)/unity.o: $(PROJECT_DIR)/src/unity.c
	$(CC) $(CFLAGS) $^ -o $@
	
create_static_library: $(OBJECTS)
	$(AR) $(ARFLAGS) $(ARCHIVE_NAME) $^
	mv $(ARCHIVE_NAME) $(LIBRARY_ROOT)
	
clean:
	rm $(OBJECTS_DIR)/*.o $(LIBRARY_ROOT)/$(ARCHIVE_NAME)