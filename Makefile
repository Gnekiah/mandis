CC = g++
CC_FLAGS = 

MANDIS_SRV_TARGET = mandis
MANDIS_CLI_TARGET = mandis-cli

TOP_DIR = $(PWD)
OBJ_DIR = $(TOP_DIR)/build
BIN_DIR = $(TOP_DIR)/bin
INC_DIR = -I$(TOP_DIR)/include
SRC_DIR = $(TOP_DIR)/lib \
          $(TOP_DIR)/mandis-p2p \
          $(TOP_DIR)/mandis-fs \
          $(TOP_DIR)/mandis \
          $(TOP_DIR)/mandis-cli

OBJ_LIB := $(OBJ_DIR)/lib.o
OBJ_MANDIS := $(OBJ_DIR)/mandis.o
OBJ_MANDIS_FS := $(OBJ_DIR)/mandis_fs.o
OBJ_MANDIS_P2P := $(OBJ_DIR)/mandis_p2p.o
OBJ_MANDIS_CLI := $(OBJ_DIR)/mandis_cli.o

export CC CC_FLAGS 
export MANDIS_SRV_TARGET MANDIS_CLI_TARGET
export TOP_DIR OBJ_DIR BIN_DIR INC_DIR SRC_DIR
export OBJ_LIB OBJ_MANDIS OBJ_MANDIS_FS OBJ_MANDIS_P2P OBJ_MANDIS_CLI

all:
	@echo "Checking Directory..."
	$(CHECK_DIR)
	@echo "Making..."
	@echo $(SRC_DIR)
	$(MAKE) -C $(SRC_DIR)
	$(CC) -o $(BIN_DIR)/$(MANDIS_SRV_TARGET) $(OBJ_LIB) $(OBJ_MANDIS) $(OBJ_MANDIS_FS) $(OBJ_MANDIS_P2P)
	$(CC) -o $(BIN_DIR)/$(MANDIS_CLI_TARGET) $(OBJ_LIB) $(OBJ_MANDIS_CLI)

CHECK_DIR:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

.PHONY: clean

clean:
	$(MAKE) -C $(SRC_DIR) clean
	rm -rf $(OBJ_DIR)