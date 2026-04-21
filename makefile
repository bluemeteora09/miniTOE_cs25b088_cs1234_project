a.out: main.o graphic.o filesys.o users.o
	gcc -o miniTOE main.o graphic.o filesys.o users.o

main.o: main.c
	gcc -c main.c

graphic.o: graphic.c
	gcc -c graphic.c

filesys.o: filesys.c
	gcc -c filesys.c

users.o: users.c
	gcc -c users.c

clean:
	rm *.o miniTOE