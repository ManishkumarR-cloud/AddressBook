lion.pani : main.o contact.o validation.o file.o 
	gcc -o lion.pani main.o contact.o validation.o file.o
main.0:main.c
	gcc -c main.c
contact.0:contact.c
	gcc -c contact.c
validation.o:validation.c
	gcc -c validation.c
file.o:file.c
	gcc -c file.c
clean:
	rm *.pani *.o