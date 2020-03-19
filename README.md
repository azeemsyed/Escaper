Escape Room Overview
===
The premise of Escape Room is to help Arbitrary the “yellow box” up to the flag without getting caught. Though the course, Arbitrary can possible get eaten by red monsters and sent to jail in the top left course or Arbitrary has the possibility of taking down blocks and head for the flag. 

Escape room is built in ENVIRO simulation environment with the following features: 
- Behaviors are defined with C++ plugins containing ELMA processes
-  Arbitrary, is controlled by keyboard events, handles collision events, and uses sensors
- Inanimate objects(Guard, Bumpers, Blocks) and static objects (like walls) are added to the environment
- JSON configuration files are used to define the environment

Additional information about ENVIRO can be found here: 
- [Enviro](https://github.com/klavinslab/enviro)



How to Install and Run the Code 
===

Installation
---
Clone the following code from github: 
```bash
git clone https://github.com/azeemsyed/Escaper/
```
From Dockerhub
---
Note: This is under the assumption the user has docker installed

To start a Docker container with ENVIRO pre-loaded into it, do:

```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:alpha bash
esm start
```

The above commands do the following:

- The `-p80:80 option maps *port* 80 from the Docker container to ports on your host computer. This should allow you to go to 
    > http://localhost
    with your web browser and see the ENVIRO client. It should say "Error: Failed to fetch. Is the server running?" at this point. 

- The `-p8765:8765` option allows the ENVIRO client to communicate with the `enviro` server (not yet running) via a *WebSocket*.

- The command `esm start` uses the <u>e</u>nviro <u>s</u>etup <u>m</u>anager to start a web server from which your browser can access the ENVRIO client. 

Running Escaper
---
Go into the project, make the project and start the enviro sever as follows.
```bash
cd Escape 
make
enviro
```
Then navigate to `http://localhost` you should see a rectangular walled area. 

You can press `Ctrl-C` to stop the enviro server. 


How to Play Escape Room
===
Since the premise of the game is to get Arbitrary to the flag, we can use the following keyboard commands to help Arbitrary achieve his goals. 

- “a” to move Arbitrary left
- “d” to move Arbitrary right
- “s” to shot bullets at blocks and robots
- “spacebar” to jump up

If Arbitrary is caught by a guard, hit the restart button on the top right and you'll start all over again

System Architecture
===
Escaper consists of 5 different agents and static objects. Static objects are used to design the level. The position of the static objects are defined in 'config.json'.

Agent 'Guy' aka Arbitrary
---
- The file 'src/guy.h' contains information about the speed of arbitrary, bullets capability, and behavior when it hits a ghost. 
- The file 'defs/guy.json' contains information about "Yellow" Arbitrary in the game. This information dictates shape and physical properties.

 Agent 'Ghost' aka Guard
----
- The file 'src/ghost.h' contains information about the speed of the ghost and how the ghost will behave when it hits a bumper. 
- The file 'defs/ghost.json' contains information about the red ghost in the game. This information dictates shape and physical properties.

Agent 'Bumper'  
---
- The file 'src/bumper.h' contains information about how the ghost will behave when it hits a bumper. 
- The file 'defs/bumper.json' contains information about the orange bumper in the game. This information dictates shape and physical properties.

Agent 'Bullet':  
---
- The file 'src/bullet.h' contains information about the speed of the bullet and how the bullet will behave when it hits a block. 
- The file 'defs/bullet.json' contains information about the black bullet in the game. This information dictates shape and physical properties.

Agent 'Block'
---
- The file 'src/block.h' contains information about the block and how it will behave when a bullet hits it.
- The file 'defs/block.json' contains information about the orange block in the game. This information dictates shape and physical properties.


Features Underdevelopment
===
I am currently still in development of expanding Escape Room, features that are currently being implemented:

- Glitching if mouse is hovering over the restart button
- Multiple levels
- Counting blocks destroyed

Key Challenges and Overcomings
===
There were a several major challenges and obstacles I faced while building Escape Room. 

One of the challenges I faced was implementing multiple guards to go back and forth across the screen. When I implemented multiple guards, either multiple or all the guards would get stuck and not move across the screen. I solved this issue by placing the guards at difference places during the “x” axis and verified that only one guard at a time will hit a bumper. Additionally, the placement of the guards in my JSON file had an affect when I would run the code. 

Another key challenge I had was being able to destroy blocks with bullets. When Arbitrary would shoot , the bullets would bounce off the blocks. I solved this issue by incorporating a pop function in my block.h 


Acknowledgements
===
Thanks to Professor Eric Klavins, Rajendra Hathwar and Victor Cannestro for your continuous support, guidance, and mentoring. 

The Escape Room uses code from the following: 
- [Elma](https://github.com/klavinslab/elma)
- [Enviro](https://github.com/klavinslab/enviro)

