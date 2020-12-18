# LibreBridge-for-Bridge-Club-Play
This takes LibreBridge by juef17 as a base and changes it into an online game for up to 4 tables.

Motivated by the closing down of our Bridge club due to Coronavirus I have made this online alternative.

Starting from the excellent base of the single player LibreBridge I have adapted it to enable up to 4 tables at a time
to play duplicate bridge as they would in a bridge club.

The game runs in parallel in a browser on each players computer/tablet and sends messages using WebSockets to keep all
the players at a table in Sync.

The program has been compiled using QT 5.14.2 on Linux and using emscripten 1.38.30 to produce the Webassembly code.

I used nodejs servers to serve out the code and receive and broadcast the messages between the clients using Websockets.

The directory LibreBridge_club contains all the source code.
The directory multiserver contains all the nodejs javascript servers plus LibreBridge Webassembly compiled for a server at address 192.168.1.3

A file startdeal.txt on the server is read at startup to set the start deal number, get any new text to be displayed on the notice
board of the opening page and to load a list of player names.  If this file is not found defaults are used.

Scores for each session are saved on the server by table number in csv format for offline analysis 

CAVEAT  - I am not a programmer and have no software background so you might find some ugly code and bad practice herein.
When I started I knew nothing about Qt, Webassembly, WebSockets or Javascript and now know I have only scratched the surface.
However we have been using this succesfully to play club bridge over the internet.

file:///home/joe/Pictures/Startscreen.png
