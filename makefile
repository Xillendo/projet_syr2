CC 		= gcc
CFLAGS	= -Wall -g -std=c11

SRC		= src/lecteur.c include/audio.c

OBJ 	= obj/lecteur.o obj/audio.o
	
main: $(OBJ)
	$(CC) -o ./bin/$@ $(OBJ)
	
obj/lecteur.o: src/lecteur.c
	$(CC) $(CFLAGS) -c -o obj/lecteur.o src/lecteur.c	
	
obj/audio.o: include/audio.c
	$(CC) $(CFLAGS) -c -o obj/audio.o include/audio.c
	
depend:
	makedepend $(SRC)
	
clean:
	rm ./obj/*.o
	rm ./bin/*
	
# DO NOT DELETE

src/lecteur.o: /usr/include/stdio.h /usr/include/features.h
src/lecteur.o: /usr/include/stdc-predef.h /usr/include/libio.h
src/lecteur.o: /usr/include/_G_config.h /usr/include/wchar.h
src/lecteur.o: /usr/include/stdlib.h /usr/include/alloca.h
src/lecteur.o: /usr/include/unistd.h /usr/include/getopt.h
src/lecteur.o: /usr/include/strings.h /usr/include/xlocale.h include/audio.h
include/audio.o: /usr/include/stdlib.h /usr/include/features.h
include/audio.o: /usr/include/stdc-predef.h /usr/include/alloca.h
include/audio.o: /usr/include/stdio.h /usr/include/libio.h
include/audio.o: /usr/include/_G_config.h /usr/include/wchar.h
include/audio.o: /usr/include/string.h /usr/include/xlocale.h
include/audio.o: /usr/include/errno.h /usr/include/unistd.h
include/audio.o: /usr/include/getopt.h /usr/include/fcntl.h
include/audio.o: /usr/include/time.h /usr/include/stdint.h include/audio.h
