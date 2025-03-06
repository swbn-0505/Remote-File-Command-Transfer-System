# Remote-File-Command-Transfer-System
## (This program works on LINUX Commands)

This project is a simple client-server application built using C and socket programming. It allows a client to remotely execute commands on a server, retrieve command outputs, search for files, and download files (except executable files and folders). The project utilizes TCP sockets to establish a reliable connection between the client and the server.

### Features
1. Establishes a TCP connection between the client and the server.
2. Allows the client to execute shell commands remotely on the server.
3. Retrieves and displays command output from the server.
4. Enables searching for files on the server.
5. Provides the ability to download non-executable files from the server.
6. Prevents downloading executable files and directories for security.

### Technologies Used
1. C programming
2. TCP Sockets
3. Linux system commands

### How It Works
1. The client connects to the server using a predefined IP and port.
2. The client sends a command to be executed on the server.
3. The server executes the command and sends back the output.
4. The client can then request file searches and downloads based on the command response.
5. The server checks if the requested file is downloadable (i.e., not a folder or executable).
6. If allowed, the file is transferred to the client.

### How to Run
#### 1. SERVER SIDE : 
#### Run the terminal in Server Computer
a. Compile the server code:
```gcc tcp_file_server.c -o server```

b. Run the server:
```./server```

#### 2. CLIENT SIDE : 
#### Run the terminal in Client computer or if Server computer and Client is same computer(for testing purpose) run a fresh terminal 
a. Compile the client code:
```gcc tcp_file_client.c -o client```

b. Run the client:
```./client```
 #### *** If used in same computer (localhost) it is prefered to use two different files one for Server and another for Client for better understanding of working process

 ### Future Improvements
1. Implement authentication and authorization for security.
2. Improve file transfer efficiency using chunked file transmission.
3. Enhance the user interface with better error handling.
4. Add multi-client support for handling multiple connections simultaneously.

#### This project demonstrates the basics of network programming, file handling, and remote command execution using C. 🚀
