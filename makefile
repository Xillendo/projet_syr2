CC 		= gcc
CFLAGS	= -Wall -g -std=c11

SRC		= src/audioserver.c include/audio.c

OBJ 	= obj/audioserver.o obj/audio.o
	
audioserver: $(OBJ)
	$(CC) -o ./bin/$@ $(OBJ)
	
obj/audioserver.o: src/audioserver.c
	$(CC) $(CFLAGS) -c -o obj/audioserver.o src/audioserver.c	
	
obj/audio.o: include/audio.c
	$(CC) $(CFLAGS) -c -o obj/audio.o include/audio.c
	
depend:
	makedepend $(SRC)
	
clean:
	rm ./obj/*.o
	rm ./bin/*

# DO NOT DELETE

src/audioserver.o: /usr/include/stdio.h /usr/include/features.h
src/audioserver.o: /usr/include/stdc-predef.h /usr/include/libio.h
src/audioserver.o: /usr/include/_G_config.h /usr/include/wchar.h
src/audioserver.o: /usr/include/stdlib.h /usr/include/alloca.h
src/audioserver.o: /usr/include/unistd.h /usr/include/getopt.h
src/audioserver.o: /usr/include/netinet/in.h /usr/include/stdint.h
src/audioserver.o: /usr/include/endian.h /usr/include/arpa/inet.h
src/audioserver.o: /usr/include/string.h /usr/include/xlocale.h
src/audioserver.o: /usr/include/fcntl.h /usr/include/time.h
src/audioserver.o: /usr/include/signal.h include/audio.h
include/audio.o: /usr/include/stdlib.h /usr/include/features.h
include/audio.o: /usr/include/stdc-predef.h /usr/include/alloca.h
include/audio.o: /usr/include/stdio.h /usr/include/libio.h
include/audio.o: /usr/include/_G_config.h /usr/include/wchar.h
include/audio.o: /usr/include/string.h /usr/include/xlocale.h
include/audio.o: /usr/include/errno.h /usr/include/unistd.h
include/audio.o: /usr/include/getopt.h /usr/include/fcntl.h
include/audio.o: /usr/include/time.h /usr/include/stdint.h include/audio.h
