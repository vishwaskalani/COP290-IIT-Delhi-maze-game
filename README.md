# COP Assignment - 2 - A 2 player maze game

## Authors

### Member1 - Ishaan Govil  Entry Number - 2020CS50497
### Member2 - Vishwas Kalani   Entry Number - 2020CS10411

---

## README Contents -

1. Assignment description
2. Directory description
3. Libraries and other tools used 
4. Brief description of game development
5. Brief description of socketing
6. Instructions to run the game
7. Acknowledgements

-----------------------------------------------------------
## Assignment description :

- Creating a maze that matches the IIT Delhi campus as closely as possible.
- Designing a two player game, over that maze with some sort of target or final goal. Thinking of a way to give points to the players as the game progresses and a win/loss criteria. 
- Both the players should be able to play the game over Wi-Fi. Appropriate rules shown at game start. Smooth controls. Appropriate messages when network is slow. 

-----------------------------------------------------------

## Directory description :

There are following files in the main directory(2020CS10411_2020CS50497.tar.gz) along with a .gitignore and license file. :

| Files | Description |
| :---        |    :----   |
| *main.cpp* | Contains a main function, which uses the libaudioAPI function from the library created and handles command line arguements |
| *Makefile* | Contains all the commands to be run on terminal to compile the files and run the executable
 |
| *README.md* | Description of the programs written and methods of running them |
| *audio.cpp* | Contains the functions created for the library |
| *audio.h* | Header file for creating library |

	

---

## Libraries and other tools used:


- We have used the SDL and its few other extension libraries like SDL_image and SDL_ttf. The installation commands for a linux based machine or WSL users are
`sudo apt-get install libsdl2-dev  `
`sudo apt-get install libsdl2-image-dev`
`sudo apt-get install libsdl2-ttf-dev`



---

## Brief description of maze and game development :


>>We have made the IIT Delhi map, taking the snippets of the campus from google earth maps. We have used those snippets to make roads and buildings more clearly distinguishable in "pixel art".
>>Since the campus is large we divided the campus maps in 5 maps named map1, map2 , map3, map4 and map5. 
>>The maps have been rendered on the surface as textures and so our the players and other features. 
>>The restricted motion of the player has been ensured by checking the collision of the player with certain sections of map where it can't go. The collisions have been checked through rectangular boxes. The players have been themselves imagined as rectangular boxes to check the collisions.
>>For entering certain buildings or changing the maps, the texture rendered in the background has been switched to the maps of the various building that have been drawn.
>>The attributes of the players vary with the places they enter or things they do for instance the health of the player continuously decreases. The attributes have been mentioned in the player class and have been modified by appropriate functions.
  

-----------------------------------------------------------

## Acknowledgements :

- *Lazy Foo' Productions* - We have built upon various source codes which have been provided by the *Beginning Game Programming v2.0*. We would like to thank the authors of the website for providing such wonderful tutorials.
- We have built upon the description of pure sockets from the website *Geek for Geeks*.
- We have referred to documentation of SDL and its extension libraries for knowing the functionality of various SDL functions.
- We have used *pixel art* for drawing maps, buildings, players etc.
- We have used a true type fonts file *Caviar-Dreams* for showing the score of players.