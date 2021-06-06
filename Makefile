all:
	gcc pyhello.c -o pyhello -I/usr/include/python2.7 -lpython2.7
	gcc pyfunc.c -o pyfunc -I/usr/include/python2.7 -lpython2.7

clean:
	rm pyhello pyfunc