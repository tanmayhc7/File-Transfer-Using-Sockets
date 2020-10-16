#include "command_handler.h"

/*
It takes pointer to the payload and the length for checksum as input arguments.5
This Function calculates checksum and returns an "int" checksum. It uses mod 100 checksum algorithm
*/
int checksum(char * buffer, int length)
{
	int i;
	int checksum = 0;
	for(i=0;i<length;i++)
	{
		checksum = (checksum + *buffer)%100;
	}
	return checksum;
}

/*
This function encrypts and decrypts entire files.
This function uses XOR for encryption. It performs character by character encryption and uses a character key.
*/
void encrypt_data(char* filename)
{
	char c;
	char key = 'j';
	FILE * fp;
	fp = fopen(filename,"rw");

	c = getc(fp);
	while(c!=EOF)
	{
		fputc(c^key,fp);
		c = fgetc(fp);
	}
	
	fclose(fp);
}

void decode_command(char* cmd){
}

void send_file(char * filename){
}

void receive_file(char * filename){
}

void list_file(void){
}

void delete_file(char * filename){
}


