OBJS := main.o 

all: $(OBJS)
	$(CC) $(CC_FLAGS) -o $(BIN_DIR)/$(MANDIS_CLI_TARGET) $(OBJS)

$(OBJS): %.o:%.cpp
	$(CC) $(CC_FLAGS) -c $^ -o $@

.PHONY: clean

clean:
	rm -f $(OBJS)
