OBJS := hashlib.o 
OBJS += logger.o
OBJS += ssllib.o
OBJS += timelib.o

SRCS := $(OBJS:.o=.c)

$(OBJ_LIB): $(SRCS)
	@echo "make mandis lib..."
	@echo $^
	@echo $@
	$(CC) $(CC_FLAGS) -c $^ -o $(OBJ_LIB)

clean:
	@echo $@