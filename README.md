# tcp_project-QT-Framework-
Programming task

The task is to create a simple echo server/client with QT framework(C/C++), you may consider to write a TCP client/server to support following functions:

Define a communication protocol between client/server.
You could define the communication protocol on your own to support.
Client can send an arbitrary string within 100 characters to the server.
Client can receive an arbitrary string from the server.
A unique client ID is used to identify a session between the client and a server.
Please provide the communication protocol definition and frame example.
A simple TCP server
It listens to 127.0.0.1, port 1502. It could handle communications from multiple clients simultaneously.
It sends back the message received from a client with a “ [ACK:<client_id>]” string append.
A simple TCP client
There will be three Text Edit areas on the GUI.
Server address: to identify the address for a client to connect.
Client ID: to identify the ID of current client.
Text to send: to input the text that will be sent to the server.
There will be three Push Buttons on the GUI.
Connect Button: to setup the TCP connection between the client and server.
Disconnect Button: to disconnect with the server.
Send Button: to send the message to the server.
There will be two Text Browsers on GUI.
System Logs: to show connection status changes and history messages sent to the server.
Received Messages: to show the history messages received from the server.
