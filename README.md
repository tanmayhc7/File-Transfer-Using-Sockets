# Xfer - Multimedia Transfer using Sockets 
This project implements **FTP** using Sockets to transfer files between a client and a server hosted via a localhost.</br>
Packets are sent using **UDP** i.e. Datagrams. </br>
This implementation also includes **file encryption** and **checksum validation** to ensure error-free transfer of data between the client and the server.</br>

Steps to run the implementation:
```
1) Server Side:
$ cd Server
$ make
$./server 18000 #where 18000 is the port number for the server

2) Client Side:
$ cd Client
$ make
$ ./client 127.0.0.1 18000 #arg1= server IP arg2= server port no.
```
Now a menu will pop up on the terminal which can be used to insert,retrieve or delete files from the server and get a list of all the files present on the server.
