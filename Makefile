CC = g++
CC_FLAGS = 

MANDIS_SRV_TARGET = mandis
MANDIS_CLI_TARGET = mandis-cli

TOP_DIR = $(PWD)
OBJ_DIR = $(TOP_DIR)/build
BIN_DIR = $(TOP_DIR)/bin
INC_DIR = -I$(TOP_DIR)/include

export CC CC_FLAGS 
export MANDIS_SRV_TARGET MANDIS_CLI_TARGET
export TOP_DIR OBJ_DIR BIN_DIR INC_DIR

all:
	CHECK_DIR

CHECK_DIR:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

OBJ_LIB := lib.o
OBJ_MANDIS := mandis.o
OBJ_MANDIS_FS := mandis_fs.o
OBJ_MANDIS_P2P := mandis_p2p.o
OBJ_MANDIS_CLI := mandis_cli.o

OBJECT = cims.o addInfo.o commodity.o deleteInfo.o help.o loadInfo.o logOff.o menu.o printInfo.o searchInfo.o 
HEAD = addInfo.h commodity.h deleteInfo.h help.h loadInfo.h logOff.h menu.h printInfo.h searchInfo.h
cims: $(OBJECT)
	g++ -o cims $(OBJECT)
cims.o: cims.cpp $(HEAD)
	g++ -c cims.cpp
addInfo.o: addInfo.cpp addInfo.h commodity.h
	g++ -c addInfo.cpp
commodity.o: commodity.cpp commodity.h
	g++ -c commodity.cpp
deleteInfo.o: deleteInfo.cpp deleteInfo.h
	g++ -c deleteInfo.cpp
help.o: help.cpp help.h
	g++ -c help.cpp
loadInfo.o: loadInfo.cpp loadInfo.h commodity.h
	g++ -c loadInfo.cpp
logOff.o: logOff.cpp logOff.h commodity.h
	g++ -c logOff.cpp
menu.o: menu.cpp menu.h
	g++ -c menu.cpp
printInfo.o: printInfo.cpp printInfo.h commodity.h
	g++ -c printInfo.cpp
searchInfo.o: searchInfo.cpp searchInfo.h commodity.h
	g++ -c searchInfo.cpp
.PHONY: clean
clean:
	rm $(OBJECT)



# SPDX-License-Identifier: GPL-2.0
# UFSHCD makefile
obj-$(CONFIG_SCSI_UFS_DWC_TC_PCI) += tc-dwc-g210-pci.o ufshcd-dwc.o tc-dwc-g210.o
obj-$(CONFIG_SCSI_UFS_DWC_TC_PLATFORM) += tc-dwc-g210-pltfrm.o ufshcd-dwc.o tc-dwc-g210.o
obj-$(CONFIG_SCSI_UFS_QCOM) += ufs-qcom.o
obj-$(CONFIG_SCSI_UFSHCD) += ufshcd.o
obj-$(CONFIG_SCSI_UFSHCD_PCI) += ufshcd-pci.o
obj-$(CONFIG_SCSI_UFSHCD_PLATFORM) += ufshcd-pltfrm.o

obj-$(CONFIG_SCSI_UFSHCD_RAMUFS) += rufs.o
rufs-objs += rufslib.o ramufs.o