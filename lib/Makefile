OBJS := hashlib.o 
OBJS += logger.o
OBJS += ssllib.o
OBJS += timelib.o

SRCS := $(OBJS:.o=.cpp)

$(OBJ_LIB): $(OBJS)
	@echo "make mandis lib..."
	@echo $^
	@echo $@
	$(CC) $(CC_FLAGS) -c $(OBJS) -o $(OBJ_LIB)

$(OBJS): %.o:%.cpp
	@echo $($@:.o=.cpp)
	@echo $@
	$(CC) $(CC_FLAGS) -c $^ -o $@ -std=c++11

.PHONY: clean

clean:
	@echo $@
