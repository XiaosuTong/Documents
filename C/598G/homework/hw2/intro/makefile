mean:	mean1.o mean2.o
	gcc -o mean mean1.o mean2.o

mean1.o:	mean1.c mean.h
		gcc -c mean1.c

mean2.o: 	mean2.c mean.h
		gcc -c mean2.c

clean:
	rm mean mean1.o mean2.o
