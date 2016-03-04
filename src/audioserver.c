#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 256

void exec_server(int sfd);
char* get_next_buffer(int sfd, int n);

int send(char* buf, int seqnum);


int get_file(char* name);

int main(){
	
	struct sockaddr_in maddr;
	int socket_fd;
	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(socket_fd < 0){
		perror("Error socket");
		exit(
	}
	
	maddr.sin_family = AF_INET;
	maddr.sin_port = htons(54322);
	maddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	int ret_bind;
	ret_bind = bind(socket_fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in));
	if(ret_bind < 0){
		perror("Error bind");
		exit(1);
	}
	
	exec_server(socket_fd);
	
	return 0;
}

void exec_server(int fd){
	//protocol commands
	char get = "GET";
	char next = "NEXT";
	char last = "LAST";
	
	int last_seq;
	int current_seq;
	
	int fd;
	
	int stop = 1;
	
	char* buffer = (char*) malloc(BUFFER_SIZE * sizeof(char));
	
	char buf[32];
	int buf_len = sizeof(pckt);
	int from_len = sizeof(struct sockaddr_in);
	struct sockaddr_in from;
	
	while(stop){
		int ret = recvfrom(fd, buf, buf_len, 0, (struct sockaddr*) &from, &from_len);
		if(ret < 0){
			perror("Error recvfrom");
			exit(1); // ?????
		}
		
		char *cmd;
		char *arg;
		//split of the received buffer
		cmd = strtok(buf, ' '); //1st split is the command
		arg = strtok(NULL, ' '); //2nd  split is the file (if GET)
		
		//exec command
		if(cmd != NULL) {
			if(strncmp(cmd, next, strlen(next)) == 0){
				last_seq = current_seq;
				current_seq++;
				buffer = get_next_buffer(fd, current_seq);
				stop = send(buff, current_seq);
			} else if(strncmp(cmd, last, strlen(last)) == 0){
				stop = send(buff, current_seq);
			} else if(strncmp(cmd, get, strlen(get)) == 0){
				if(arg != NULL){
					fd = open(arg, O_RDONLY);	
					if(fd < 0){
						perror("Error open file");
						exit(1);
					}
					current_seq = 0;
					last_seq = 0;
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
	free(buffer);
}
			
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	
