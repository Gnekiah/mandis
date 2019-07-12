OBJS := block.o 
OBJS += file.o
OBJS += foofs.o

all: $(OBJS)
	cp *.o $(OBJ_DIR)

$(OBJS): %.o:%.cpp
	$(CC) $(CC_FLAGS) -c $^ -o $@

.PHONY: clean

clean:
	rm -f $(OBJS)
