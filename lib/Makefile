OBJS := hashlib.o 
OBJS += logger.o
OBJS += ssllib.o
OBJS += timelib.o

OBJ_LIB += OBJS

all: $(OBJS)
	cp *.o $(OBJ_DIR)

$(OBJS): %.o:%.cpp
	$(CC) $(CC_FLAGS) -c $^ -o $@ -std=c++11

.PHONY: clean

clean:
	rm -f $(OBJS)
