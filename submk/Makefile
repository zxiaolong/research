
include ./include/base.mk

.PHONY: all subdir

all: subdir
	@echo "main: TOP_DIR： $(TOP_DIR)"
	@touch $(TOP_DIR)/main.touch

subdir:
	make -C subdir

clean:
	-@rm $(TOP_DIR)/main.touch
	make clean -C subdir