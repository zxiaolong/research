
all: sem sem2 namedsem

sem:
	@gcc sem.c -o sem -lpthread

sem2:
	@gcc sem2.c -o sem2 -lpthread

namedsem:
	@gcc namedsem1.c -o namedsem1 -lpthread
	@gcc namedsem2.c -o namedsem2 -lpthread

clean:
	-@rm -f sem sem2
	-@rm -f namedsem1 namedsem2
