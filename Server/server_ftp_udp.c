#include "command_handler.h"

//Global variables
static const int buffer_size=1000;

int main (int argc, char * argv[]){

	if(argc!=2){
		printf("Usage: <port_num>\n");
		exit(EXIT_FAILURE);
	}

	bzero((void*)&client,sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(atoi(argv[1]));
	client.sin_addr.s_addr=INADDR_ANY;

	if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0))< 0)
		printf("unable to create socket");

	/***************
	  Once we've created a socket, we must bind that socket to the local address and port we've supplied in the sockaddr_in struct
	 ******************/
	if (bind(client_socket, (struct sockaddr *)&client, sizeof(client)) < 0)
		printf("unable to bind socket\n");

	addr_length=sizeof(struct sockaddr);

	printf("Receiving handshaking message from client...\n");

	char handshake__send_server_msg[]="Handshaking Successful";

	//wait for incoming message
	char handshake__get_client_msg[buffer_size];
	bzero(handshake__get_client_msg,sizeof(handshake__get_client_msg));
	client_bytes = recvfrom(client_socket, handshake__get_client_msg, sizeof(handshake__get_client_msg), 0 , (struct sockaddr*)&client, (socklen_t *)&addr_length);

	if(client_bytes>0 && strcmp(handshake__send_server_msg,handshake__get_client_msg)==0){
		printf("%s\n",handshake__send_server_msg);
	} else{
		printf("Handshake unsuccessful... \n");
		exit(EXIT_FAILURE);
	}

	client_bytes= sendto(client_socket, handshake__send_server_msg, strlen(handshake__send_server_msg), 0 , (struct sockaddr*)&client, addr_length);


	// Run the code continuously until exit command is typed
	char buffer[buffer_size];
	while(1)
	{
		printf("\n\n\t\t\tWaiting for command\n\n");

		bzero(buffer,sizeof(buffer));

		client_bytes = recvfrom(client_socket, buffer, sizeof(buffer), 0 , (struct sockaddr*)&client, (socklen_t *)&addr_length);

		decode_command(buffer);
	}	
	close(client_socket);




	return 0;
}
