OBJS := config.o 
OBJS += entry.o
OBJS += entry_session.o
OBJS += main.o
OBJS += p2pentry.o
OBJS += p2pentry_session.o

all: $(OBJS)
	cp *.o $(OBJ_DIR)

$(OBJS): %.o:%.cpp
	$(CC) $(CC_FLAGS) -c $^ -o $@

.PHONY: clean

clean:
	rm -f $(OBJS)
