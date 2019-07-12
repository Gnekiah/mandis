#OBJS := connector.o 
OBJS += kadbucket.o
OBJS += p2pnet.o
#OBJS += p2pnet_session.o
OBJS += req_session.o
#OBJS += request.o
#OBJS += request_parser.o
#OBJS += request_handler.o
#OBJS += server.o
#OBJS += session.o
#OBJS += udpclient.o
#OBJS += udpserver.o

all: $(OBJS)
	cp *.o $(OBJ_DIR)

$(OBJS): %.o:%.cpp
	$(CC) $(CC_FLAGS) -c $^ -o $@

.PHONY: clean

clean:
	rm -f $(OBJS)
