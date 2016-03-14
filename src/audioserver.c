#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "../include/audio.h"

#define BUFFER_SIZE 256
#define COMMAND_SIZE 64
#define PORT 54322

void exec_server(int sfd);
int get_next_buffer(int fd, uint8_t* buffer);
void exit_server(uint8_t* buf, int sfd, int ffd);

void sig_exit(int signum);
 
int send_buf(int sfd, uint8_t* buf, struct sockaddr_in dest);
int send_metadata(int sfd, struct sockaddr_in dest, int sample_rate, int sample_size, int channels);


int get_file(char* name);

int main(){
	
	struct sockaddr_in maddr;
	int socket_fd;
	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(socket_fd < 0){
		perror("Error socket");
		exit(1);
	}
	
	maddr.sin_family = AF_INET;
	maddr.sin_port = htons(PORT);
	maddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	int ret_bind;
	ret_bind = bind(socket_fd, (struct sockaddr *) &maddr, sizeof(struct sockaddr_in));
	if(ret_bind < 0){
		perror("Error bind");
		exit(1);
	}
	
	exec_server(socket_fd);
	
	return 0;
}

void exec_server(int fd){
	//protocol commands
	char* get = "GET";
	char* next = "NEXT";
	char* last = "LAST";
	
	char* end = "END";
	
	int file_fd;
	
	//int stop = 0;
	
	uint8_t* buffer = (uint8_t*) malloc(BUFFER_SIZE * sizeof(uint8_t));
	
	char buf[COMMAND_SIZE];
	int buf_len = sizeof(buf);
	unsigned int from_len = sizeof(struct sockaddr_in);
	struct sockaddr_in from;
	
	while(1){
		int ret = recvfrom(fd, buf, buf_len, 0, (struct sockaddr*) &from, &from_len);
		if(ret < 0){
			perror("Error recvfrom");
			exit(1); // ?????
		}
		
		char *cmd;
		char *arg;
		//split of the received buffer
		cmd = strtok(buf, " "); //1st split is the command
		arg = strtok(NULL, " "); //2nd  split is the file (if GET)
		
		
		//exec command
		if(cmd != NULL) {
			// Commande NEXT
			if(strncmp(cmd, next, strlen(next)) == 0){ 
				int ret_get_nxt = get_next_buffer(file_fd, buffer);
				int r = send_buf(fd, buffer, from);
				if(r < 0){
					exit(1);
				}
				if(ret_get_nxt == 1){
					int send_return;
					send_return = sendto(fd, end, sizeof(end), 0, (struct sockaddr*) &from, sizeof(struct sockaddr_in));
					if(send_return < 0){
						perror("Error send END message");
						exit(1);
					}
				}
			// Commande LAST	
			} else if(strncmp(cmd, last, strlen(last)) == 0){
				int r = send_buf(fd, buffer, from);
				if(r < 0){
					exit(1);
				}
			// Commande GET	
			} else if(strncmp(cmd, get, strlen(get)) == 0){
				if(arg != NULL){
					int sample_rate;
					int sample_size;
					int channels;
					file_fd = aud_readinit(arg, &sample_rate, &sample_size, &channels);	
					if(file_fd < 0){
						perror("Error open file");
						sample_rate = NULL;
						sample_size = NULL;
						channels = NULL;
					}
					int ret_send_meta;
					ret_send_meta = send_metadata(fd, from, sample_rate, sample_size, channels);
					if(ret_send_meta < 0){
						exit(1);
					}					
				}
			} else {
				printf("Error : unknown protocol command\n");
				exit(1);
			}
		} else {
			printf("Error : NULL command\n");
			exit(1);
		}
	}
	//free(buffer);
}

int send_buf(int sfd, uint8_t *buf, struct sockaddr_in dest){
	int send_return;
	send_return = sendto(sfd, buf, sizeof(buf), 0, (struct sockaddr*) &dest, sizeof(struct sockaddr_in));
	if(send_return < 0){
		printf("Send_buf : Failed to send packet\n");
		return -1;
	} else {
		printf("packet send\n");
		return 0;
	}
}

int get_next_buffer(int fd, uint8_t* buf){
	int read_size = read(fd, buf, BUFFER_SIZE);
	if(read_size == -1){
		perror("Error read file");
		return -1;
	} else if(read_size != BUFFER_SIZE){
		return 1;
	} else {
		return 0;
	}
}

int send_metadata(int sfd, struct sockaddr_in dest, int sample_rate, int sample_size, int channels){
	int buf[3];
	if(sample_rate != NULL){
		buf[0] = sample_rate;
		buf[1] = sample_size;
		buf[2] = channels;
		int send_return;
		send_return = sendto(sfd, buf, sizeof(buf), 0, (struct sockaddr*) &dest, sizeof(struct sockaddr_in));
		if(send_return < 0){
			printf("send_metadata : Failed to send packet\n");
			return -1;
		} else {
			printf("send_metadata : Packet send\n");
			return 0;
		}
	} else {
		buf[0] = 0;
		buf[1] = 0;
		buf[2] = 0;
		int send_return;
		send_return = sendto(sfd, buf, sizeof(buf), 0, (struct sockaddr*) &dest, sizeof(struct sockaddr_in));
		if(send_return < 0){
			printf("send_metadata : Failed to send packet\n");
			return -1;
		}else{
			return 0;
		}
	}
}
	
/*
void exit_server(char* buf, int sfd, int ffd){
	printf("Closing active file...");
	int r1 = close(ffd);
	if(r1 < 0){
		perror("Can't close file file descriptor !");
	}
	printf("Closing socket...\n");
	int r2 = close(sfd);
	if(r2 < 0){
		perror("Can't close socket file descriptor !");
	}
	free(buf);
	exit(0);
}*/

		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	
