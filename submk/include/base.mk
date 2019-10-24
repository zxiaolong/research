
# top dir of base.mk
TOP_DIR=$(dir $(lastword $(MAKEFILE_LIST)))

# toolchain dir
TOOLCHAIN_DIR=/opt/toolchain/gcc

# checking toolchain
ifeq ("$(wildcard $(TOOLCHAIN_DIR))","")
$(error "ERROR: $(TOOLCHAIN_DIR) not exist!")
endif