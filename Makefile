CC = g++
CC_FLAGS := -std=c++11 -g
CC_FLAGS += -pthread
CC_FLAGS += -lboost_thread
CC_FLAGS += -lboost_system
CC_FLAGS += -lboost_filesystem
CC_FLAGS += -lssl
CC_FLAGS += -lcrypto
CC_FLAGS += -lboost_date_time

MANDIS_SRV_TARGET = mandis
MANDIS_CLI_TARGET = mandis-cli

TOP_DIR = $(PWD)
OBJ_DIR = $(TOP_DIR)/build
BIN_DIR = $(TOP_DIR)/bin
INC_DIR = -I$(TOP_DIR)/include

SRC_LIB = $(TOP_DIR)/lib
SRC_MANDIS = $(TOP_DIR)/mandis
SRC_MANDIS_FS = $(TOP_DIR)/mandis-fs 
SRC_MANDIS_P2P = $(TOP_DIR)/mandis-p2p 
SRC_MANDIS_CLI = $(TOP_DIR)/mandis-cli

OBJ_LIB := $(OBJ_DIR)/hashlib.o
OBJ_LIB += $(OBJ_DIR)/logger.o
OBJ_LIB += $(OBJ_DIR)/ssllib.o
OBJ_LIB += $(OBJ_DIR)/timelib.o
OBJ_MANDIS := $(OBJ_DIR)/config.o 
OBJ_MANDIS += $(OBJ_DIR)/entry.o
OBJ_MANDIS += $(OBJ_DIR)/entry_session.o
OBJ_MANDIS += $(OBJ_DIR)/main.o
OBJ_MANDIS += $(OBJ_DIR)/p2pentry.o
OBJ_MANDIS += $(OBJ_DIR)/p2pentry_session.o
OBJ_MANDIS_FS := $(OBJ_DIR)/block.o 
OBJ_MANDIS_FS += $(OBJ_DIR)/file.o
OBJ_MANDIS_FS += $(OBJ_DIR)/foofs.o
OBJ_MANDIS_P2P := $(OBJ_DIR)/kadbucket.o
OBJ_MANDIS_P2P += $(OBJ_DIR)/p2pnet.o
OBJ_MANDIS_P2P += $(OBJ_DIR)/req_session.o

export CC CC_FLAGS 
export MANDIS_SRV_TARGET MANDIS_CLI_TARGET
export TOP_DIR OBJ_DIR BIN_DIR INC_DIR
export SRC_LIB SRC_MANDIS SRC_MANDIS_FS SRC_MANDIS_P2P SRC_MANDIS_CLI
export OBJ_LIB OBJ_MANDIS OBJ_MANDIS_FS OBJ_MANDIS_P2P OBJ_MANDIS_CLI

all: CHECK_DIR $(OBJ_LIB) $(OBJ_MANDIS) $(OBJ_MANDIS_FS) $(OBJ_MANDIS_CLI) $(OBJ_MANDIS_P2P)
	$(CC) $(CC_FLAGS) -o $(BIN_DIR)/$(MANDIS_SRV_TARGET) $(OBJ_LIB) $(OBJ_MANDIS) $(OBJ_MANDIS_FS) $(OBJ_MANDIS_P2P)

CHECK_DIR:
	@echo "Checking Directory..."
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

$(OBJ_LIB):
	$(MAKE) -w -C $(SRC_LIB)
$(OBJ_MANDIS):
	$(MAKE) -w -C $(SRC_MANDIS)
$(OBJ_MANDIS_FS):
	$(MAKE) -w -C $(SRC_MANDIS_FS)
$(OBJ_MANDIS_P2P):
	$(MAKE) -w -C $(SRC_MANDIS_P2P)
$(OBJ_MANDIS_CLI):
	$(MAKE) -w -C $(SRC_MANDIS_CLI)
	
.PHONY: clean

clean:
	$(MAKE) -C $(SRC_LIB) clean
	$(MAKE) -C $(SRC_MANDIS) clean
	$(MAKE) -C $(SRC_MANDIS_FS) clean
	$(MAKE) -C $(SRC_MANDIS_P2P) clean
	$(MAKE) -C $(SRC_MANDIS_CLI) clean
	rm -rf $(OBJ_DIR)
