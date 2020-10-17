//Handler files
#include "command_handler.h"

//Global variables
static const int buffer_size=1000;

int main(int argc,char* argv[]){
	
	if(argc<3){
		printf("Usage:  <server_ip> <server_port>\n");
		exit(EXIT_FAILURE);
	}

	//Intiailize server socket struct	

	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(argv[1]);
	server.sin_port=htons(atoi(argv[2]));	
	
	//Create server socket
	if((server_socket = socket(AF_INET,SOCK_DGRAM,0) ) < 0){
		printf("Error Creating Socket...\n");
		exit(EXIT_FAILURE);
	}

	char handshake__get_server_msg[buffer_size];	
	char handshake__send_client_msg[]="Handshaking Successful";
	
	//Send handshaking message to server
	printf("Establishing handshaking with the server...\n");
	server_bytes=sendto(server_socket, handshake__send_client_msg, strlen(handshake__send_client_msg), 0 , (struct sockaddr*)&server, sizeof(struct sockaddr));
	if(server_bytes < 0){
		printf("Error sending data to Server\n");
		exit(EXIT_FAILURE);
	}
	
	//Receive handshaking message from server
	bzero(handshake__get_server_msg,sizeof(handshake__get_server_msg));
		
	addr_length=sizeof(struct sockaddr);
	printf("Receiving handshaking data from the server...\n");
		
	server_bytes = recvfrom(server_socket, handshake__get_server_msg, sizeof(handshake__get_server_msg), 0 , (struct sockaddr*)&server, (socklen_t *)&addr_length);
	if(server_bytes < 0){
		printf("Error receiving data from Server\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Acknowledgement received from server...\n");
	//Check is handshaking is successful or not
	if(strcmp(handshake__send_client_msg,handshake__get_server_msg) == 0){
		printf("Server sent : %s\n",handshake__get_server_msg);
	} else{
		printf("Handshaking unsuccessful\n");
		exit(EXIT_FAILURE);
	}
	
	char command_buf[30];
	
	while(1){
	
		//print out file transfer options
		printf("\n\n\t\t*****UDP Based FTP*****\n");
		printf("\n\t\t1. get <filename>");
		printf("\n\t\t2. put <filename>");
		printf("\n\t\t3. delete <filename>");
		printf("\n\t\t4. list");
		printf("\n\t\t5. exit");
		
		//get user command
		printf("\n\n\t\tEnter Command: ");
		
		bzero(command_buf,sizeof(command_buf));
		//get user command into buffer using API: char *fgets(char *s, int size, FILE *stream)
		fgets(command_buf,sizeof(command_buf),stdin);
		
		//send user command to server
		server_bytes=sendto(server_socket, command_buf, strlen(command_buf), 0 , (struct sockaddr*)&server, sizeof(struct sockaddr));
		
		decode_command(command_buf);	
	}
	
	//Close the server socket
	close(server_socket);
	
	exit(EXIT_SUCCESS);	
}
