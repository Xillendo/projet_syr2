CC 		= gcc
CFLAGS	= -Wall -g -std=c11

SRC		= src/audioserver.c src/audioclient.c src/lecteur.c include/audio.c 

OBJSERV	= obj/audioserver.o obj/audio.o
OBJCLI	= obj/audioclient.o obj/audio.o
OBJLEC	= obj/lecteur.o obj/audio.o
	
audioserver: $(OBJSERV)
	$(CC) -o ./bin/$@ $(OBJSERV)
	
audioclient: $(OBJCLI)
	$(CC) -o ./bin/$@ $(OBJCLI)
	
lecteur: $(OBJLEC)
	$(CC) -o ./bin/$@ $(OBJLEC)
	
obj/audioserver.o: src/audioserver.c
	$(CC) $(CFLAGS) -c -o obj/audioserver.o src/audioserver.c

obj/audioclient.o: src/audioclient.c
	$(CC) $(CFLAGS) -c -o obj/audioclient.o src/audioclient.c		
	
obj/audio.o: include/audio.c
	$(CC) $(CFLAGS) -c -o obj/audio.o include/audio.c
	
obj/lecteur.o: src/lecteur.c
	$(CC) $(CFLAGS) -c -o obj/lecteur.o src/lecteur.c
	
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
src/audioclient.o: /usr/include/stdio.h /usr/include/features.h
src/audioclient.o: /usr/include/stdc-predef.h /usr/include/libio.h
src/audioclient.o: /usr/include/_G_config.h /usr/include/wchar.h
src/audioclient.o: /usr/include/stdlib.h /usr/include/alloca.h
src/audioclient.o: /usr/include/string.h /usr/include/xlocale.h
src/audioclient.o: /usr/include/netinet/in.h /usr/include/stdint.h
src/audioclient.o: /usr/include/endian.h /usr/include/arpa/inet.h
src/audioclient.o: /usr/include/netdb.h /usr/include/rpc/netdb.h
src/audioclient.o: /usr/include/unistd.h /usr/include/getopt.h
src/audioclient.o: include/audio.h
include/audio.o: /usr/include/stdlib.h /usr/include/features.h
include/audio.o: /usr/include/stdc-predef.h /usr/include/alloca.h
include/audio.o: /usr/include/stdio.h /usr/include/libio.h
include/audio.o: /usr/include/_G_config.h /usr/include/wchar.h
include/audio.o: /usr/include/string.h /usr/include/xlocale.h
include/audio.o: /usr/include/errno.h /usr/include/unistd.h
include/audio.o: /usr/include/getopt.h /usr/include/fcntl.h
include/audio.o: /usr/include/time.h /usr/include/stdint.h include/audio.h
