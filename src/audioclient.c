#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include "../include/audio.h"

#define BUFFER_SIZE 8192
#define COMMAND_SIZE 64
#define PORT 54322

//void load_buffer(int socket_fd, uint8_t* buffer);
void read_buffer(int audio_fd, uint8_t* buffer);

void play(int socket_fd, struct sockaddr_in dest, int sample_rate, int sample_size, int channels);

int main(int argc, char **argv){
	
	//uint8_t* buffer1 = (uint8_t*) malloc(BUFFER_SIZE * sizeof(uint8_t));
	//uint8_t* buffer2 = (uint8_t*) malloc(BUFFER_SIZE * sizeof(uint8_t));
	
	unsigned int sockaddr_in_length = sizeof(struct sockaddr_in);
	
	if(argc != 3){
		printf("Error, 2 argument needed : server_host_name, file_name\n");
		exit(1);
	}
	
	int socket_fd;
	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(socket_fd < 0){
		perror("Error socket");
		exit(1);
	} 
	
	printf("Socket created succesfully\n");
	
	struct hostent *resolv;
	struct in_addr *addr;
	
	resolv = gethostbyname(argv[1]);
	if(resolv==NULL){
		printf("Address not found for %s\n", argv[1]);
		exit(1);
	} 
	
	addr = (struct in_addr*) resolv->h_addr_list[0];
	
	printf("IP address for %s is %s\n", argv[1], inet_ntoa(*addr));
	
	struct sockaddr_in destaddr;
	destaddr.sin_family = AF_INET;
	destaddr.sin_port = htons(PORT);
	destaddr.sin_addr = *addr;
	
	//Ask for the file
	char* file_name = argv[2];
	printf("File name = %s\n", file_name);
	char buf[COMMAND_SIZE];
	snprintf(buf, COMMAND_SIZE, "GET %s", file_name);
	printf("Sending command : %s\n", buf);
	int send_return;
	send_return = sendto(socket_fd, buf, COMMAND_SIZE, 0, (struct sockaddr*) &destaddr, sockaddr_in_length);
	if(send_return < 0){
		perror("Error sendto");
		exit(1);
	}
	
	//get the server response
	//audio metadata
	struct sockaddr_in from;
	int metadata[3];
	printf("Waiting for server response...\n");
	int ret = recvfrom(socket_fd, metadata, sizeof(metadata), 0, (struct sockaddr*) &from, &sockaddr_in_length);
	if(ret < 0){
		perror("Error recvfrom");
		exit(1);
	}
	
	int sample_rate = metadata[0];
	int sample_size = metadata[1];
	int channels = metadata[2];
	printf("Serveur response is :\nSample_rate = %d\nSample_size = %d\nChannels = %d\n", sample_rate, sample_size, channels);
	if(sample_rate == 0){
		printf("Error, the requested file do not exist\n");
		exit(1);
	}
	play(socket_fd, destaddr, sample_rate, sample_size, channels);
	return 0; 
}


/**
 * 
 * */	
void play(int socket_fd, struct sockaddr_in dest, int sample_rate, int sample_size, int channels){
	unsigned int sockaddr_in_length = sizeof(struct sockaddr_in);
	int audio_fd = aud_writeinit(sample_rate, sample_size, channels);
	if(audio_fd < 0){
		perror("Error aud_writeinit");
		exit(1);
	}
	uint8_t* buffer = (uint8_t*) malloc(BUFFER_SIZE * sizeof(uint8_t));
	//Ask for the next buffer
	char* cmd = "NEXT";
	char* end = "END";
	int send_return;
	send_return = sendto(socket_fd, cmd, sizeof(cmd), 0, (struct sockaddr*) &dest, sockaddr_in_length);
	if(send_return < 0){
		perror("Error sendto in play()");
		exit(1);
	}
	
	struct sockaddr_in from;
	int ret = recvfrom(socket_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*) &from, &sockaddr_in_length);
	printf("Bytes received = %d\n", ret);
	if(ret < 0){
		perror("Error recvfrom in play()");
		exit(1);
	}
	while(strncmp("END", (char*) buffer, strlen(end)) != 0){
		read_buffer(audio_fd, buffer);
		int send_return;
		send_return = sendto(socket_fd, cmd, sizeof(cmd), 0, (struct sockaddr*) &dest, sockaddr_in_length);
		if(send_return < 0){
			perror("Error sendto in play()");
			exit(1);
		}
		int ret = recvfrom(socket_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*) &from, &sockaddr_in_length);
		printf("Bytes received = %d\n", ret);
		if(ret < 0){
			perror("Error recvfrom in play()");
			exit(1);
		}
	}
	close(socket_fd);
	free(buffer);
}

void read_buffer(int audio_fd, uint8_t* buffer){
	int write_size;
	write_size = write(audio_fd, buffer, BUFFER_SIZE);
	if(write_size < 0){
		perror("Error writing in the audio file");
	}
}
	
	
