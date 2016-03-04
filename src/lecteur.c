#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

#include "../include/audio.h"

#define BUFFER_SIZE 128

int main(int argc, char **argv) {
	
	char BUFFER[BUFFER_SIZE];
	
	if(argc != 2){
		printf("1 argument needed\n");
		exit(1);
	}
	
	int fdaudio;
	int fdoutput;
	
	char* filename;
	int sample_rate;
	int sample_size;
	int channels;
	
	filename = argv[1];
	
	fdaudio = aud_readinit(filename, &sample_rate, &sample_size, &channels);
	if(fdaudio < 0){
		perror("Error aud_readinit");
		exit(1);
	}
	
	fdoutput = aud_writeinit(sample_rate, sample_size, channels);
	if(fdoutput < 0){
		perror("Error aud_writeinit");
		exit(1);
	}
	
	int read_size;
	read_size = read(fdaudio, BUFFER, BUFFER_SIZE);	
	if(read_size < 0){
		perror("Error read");
		exit(1);
	}
	
	int write_size;
	
	while(read_size == BUFFER_SIZE) {
		write_size = write(fdoutput, BUFFER, BUFFER_SIZE);
		bzero(BUFFER, BUFFER_SIZE);
		if(write_size < 0){
			perror("Error write");
			exit(1);
		}
		read_size = read(fdaudio, BUFFER, BUFFER_SIZE);
		if(read_size < 0){
			perror("Error read");
			exit(1);
		}
	}
	write_size = write(fdoutput, BUFFER, BUFFER_SIZE);
	if(write_size < 0){
		perror("Error write");
		exit(1);
	}
	
	close(fdaudio);
	close(fdoutput);
	
	return 0;
	
}

	
