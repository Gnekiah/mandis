OBJS := hashlib.o 
OBJS += logger.o
OBJS += ssllib.o
OBJS += timelib.o

SRCS := $(OBJS:.o=.c)

all:
	$(CC) $(CC_FLAGS) -c $^ -o $(OBJ_LIB)

clean:
	@echo $@