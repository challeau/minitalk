# minitalk
> grade: 125/100

A simple communication project based on UNIX signals.<br\>
The program `client` sends a character string to the program `server` using only SIGUSR1 and SIGUSR2. The server then prints the received string.

## Usage: 
- run `make` to create both executables.
- in one terminal, run `./server` to start the server. It will displayu its pid.
- in another terminal, run `./client <server pid> <string to be sent>` to start the client and send a string.

_Note: several clients can send strings to the same server. Supports Unicode._

<br/>

# minitalk - Français
> note: 125/100

Un projet de communication simple basé sur les signaux UNIX.<br\>
Le programme `client` envoie une chaîne de caractères au programme `server`, en utilisant uniquement les signaux SIGUSR1 et SIGUSR2. Le serveur imprime la chaîne qu'il reçoit.

## Utilisation: 
- lancer `make` pour créer les deux exécutables.
- dans un terminal, lancer `./server` pour démarer le serveur. Il affiche son pid.
- dans un autre terminal, lancer `./client <pid du serveur> <chaîne à envoyer>` pour démarer le client et envoyer une chaîne.

_À noter: plusieurs clients peuvent envoyer des chaînes au même serveur. Support Unicode._
