
BUILD:=./build
SRC:=log4c.c
OBJS:=log4c.o

all: static dynamic 

static: $(OBJS) 
	@ar -crv $(BUILD)/liblog4c.a $(OBJS) 
	@$(CC) test.c -o $(BUILD)/test-s -L$(BUILD) -Bstatic -llog4c

dynamic:
	@$(CC) -shared -fPIC -o $(BUILD)/liblog4c.so $(SRC)
	@$(CC) test.c -o $(BUILD)/test-d -L$(BUILD) -llog4c

clean:
	-@cd $(BUILD); rm -f *.o *.a *.so
	-@cd $(BUILD); rm -f test-s test-d

.PHONY: all clean static dynamic

