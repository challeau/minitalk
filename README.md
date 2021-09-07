# minitalk - FINISHED

> grade: 125/100

A simple communication program based on UNIX signals.
A message is sent by client to server (which then prints it), using only SIGUSR1 and SIGUSR2.
Usage: 
- run ```make``` to create both executables.
- in one terminal, run ```./server``` to start the server. it will displayu its pid.
- in another terminal, run ```./client <server pid> <string to be sent>``` to launch the client.
