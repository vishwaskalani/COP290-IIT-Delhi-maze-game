# COP290 Task - 2 - A 2-player maze game

## Authors

### Member1 - Ishaan Govil - Entry Number - 2020CS50497
### Member2 - Vishwas Kalani -  Entry Number - 2020CS10411

---

## README Contents -

1. Assignment description
2. Directory description
3. Libraries and other tools used 
4. Brief description of maze and game development
5. Brief description of socketing
6. Instructions to run the game
7. Acknowledgements

---
## Assignment description :

- Creating a maze that matches the IIT Delhi campus as closely as possible.
- Designing a two player game, over that maze with some sort of target or final goal. Thinking of a way to give points to the players as the game progresses and a win/loss criteria. 
- Both the players should be able to play the game over Wi-Fi. Appropriate rules shown at game start. Smooth controls. 

---

## Directory description:

The github repository is divided into various directories and files namely - 

1. **classfiles** - Contains the `player2` and `ltexture` classes.	
2. **client-files** - Contains the files that the client should run on his computer in order to run the game.
3. **server-files** - Contains the files that the server should run on his computer in order to run the game.
4. **Resources** - Contains all the `.png` files needed to be displayed in the game.
5. **audioResources** - Contains all the `.wav` files needed for the sound effects of the game.
6. **caviar.ttf** - The file containing the font that is used to display the player attributes on the screen.
7. **README.md** - The current file containing all project description.
8. **RULES.pdf** - The file containing the rules of our game which a player is advised to read in order to play the game.
9. **status.txt** - Contains the status of our game.

---

## Libraries and other tools used:


- We have used the SDL and its few other extension libraries like SDL_image and SDL_ttf. The installation commands for a linux based machine or WSL users are

`sudo apt-get install libsdl2-dev  `

`sudo apt-get install libsdl2-image-dev`

`sudo apt-get install libsdl2-ttf-dev`



---

## Brief description of maze and game development:


- We have made the IIT Delhi map, taking the snippets of the campus from google earth maps. We have used those snippets to make roads and buildings more clearly distinguishable in "pixel art".
- Since the campus is large we divided the campus maps in 5 maps named map1, map2 , map3, map4 and map5. 
- The maps have been rendered on the surface as textures and so our the players and other features. 
- The restricted motion of the player has been ensured by checking the collision of the player with certain sections of map where it can't go. The collisions have been checked through rectangular boxes. The players have been themselves imagined as rectangular boxes to check the collisions.
- For entering certain buildings or changing the maps, the texture rendered in the background has been switched to the maps of the various building that have been drawn.
- The attributes of the players vary with the places they enter or things they do for instance the health of the player continuously decreases. The attributes have been mentioned in the player class and have been modified by appropriate functions.
- The appropriate sound effects have also been added at various events like entering a location, exiting the location and taking a 
Yulu.

---

## Brief description of Socketing:

To ensure that two players are able to play the game at the same time and can view each other's attribute as well as each other's character, we have made use of socketing to send and read the buffer betweeen the server and the client (both ways) containing the player's attributes and its co-ordinates in a properly space seperated format. We then extract these attributes and co-ordinates from the buffer and assign them to the 2nd player on both the sides.

---
## Instructions to run the game:

1. The server and the client pc should connect to the same Wi-fi network or local hotspot.
2. The server should run the ifconfig command incase they are on a WSL or VM machine to get the IP address of the same.
3. Now the server should run `netsh interface portproxy add v4tov4 listenport=8080 listenaddress=0.0.0.0 connectport=8080 connectaddress=*ipaddress of WSL or Virtual Box*` command in the windows powershell opened in administrator mode to set up the proxy and reroute the data coming to the pc through the WSL or Virtual Box machine.
4. Now the server should run the `ipconfig` command in the  powershell opened as administrator.
5. Copy the `IPv4 address` written under the `Wi-fi` subheading.
6. The server and the client should now bring out all the files from the `server-files` and `client-files` respectively into the main directory.
7. The client should now replace the IP address already written in the `Client.cpp` file with the IP address sent by the server.
8. The server and client should now both run the `make` command on their machines.
9. Now the server should run the `./testfile.out` command followed by the client running the same command.
10. Both the players are now ready to play the game and can start plaiying by pressing the `Enter` Key.

`P.S.` - The instruction no.s `2` and `3` can be skipped in case the server machine is an Ubuntu or Linux machine.

---
## Acknowledgements :

- *Lazy Foo' Productions* - We have built upon various source codes which have been provided by the *Beginning Game Programming v2.0*. We would like to thank the authors of the website for providing such wonderful tutorials.
- We have built upon the description of pure sockets from the website *Geeks for Geeks*.
- We have referred to documentation of SDL and its extension libraries for knowing the functionality of various SDL functions.
- We have used *pixel art* for drawing maps, buildings, players etc.
- We have used a true type fonts file *Caviar-Dreams* for showing the score of players.