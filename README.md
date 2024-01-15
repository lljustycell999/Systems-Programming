# CSC 322 - Systems Programming
This repository contains the projects completed as part of the CSC 322 - Systems Programming course at SUNY Oswego taught by Professor Aleksander Pantaleev.

# CSC 322 Lab 1 Specification:
This is your C lab. It consists of programming a small text-based game purely in C. The game was designed for OOP, which C does not support naturally. Thus this lab will simultaneously teach you the specifics of the C language, and the difference between structured programming and OOP.

You can find a complete description of the project in this pdf document (CSC 322 Lab 1 Notes.pdf).

The description above says you should use XML as input. To make the project a little easier, I am changing a few things. First, there will be no names and descriptions for anything in the game, only numbers (as in room number 0); change the game output accordingly. In addition, I am changing the input definition to the following:

When the game starts, it takes from stdin (so no files are opened/closed/used in the project code) input in the following format:

* n (integer, the number of rooms, 1 <= n < 100)
  
The next n lines are the following:
* state north south east west (five integers, signifying the cleanliness of the room and the numbers of the respective neighbors. State can be 0 for clean, 1 for half-dirty, 2 for dirty. -1 signifies no neighbor. Numbering of the rooms starts at 0)

The next line is:
* m (integer, the number of creatures, 1 <= m < 100)

The next m lines are:
* creatureType location (two integers; creatureType is 0 for the PC, 1 for an animal, 2 for an NPC. Location is the number of the room the creature is in. Numbering starts at 0)
* The input will be well-formed according to the above description and the game specification (i.e., you should not worry about checking for errors in the input such as putting an animal in a dirty room from the start and the like).

* After the above is read from stdin, the game should continue reading game commands from stdin.

Make sure you use as few globals as possible. You must not use global arrays or global structs; you are allowed to use up to three global pointers and a global int for the respect value.

<img width="440" alt="Screen Shot 2024-01-15 at 2 43 50 PM" src="https://github.com/lljustycell999/CSC322/assets/123667513/1cad3368-27da-4faa-8fd3-9cf01a69771a">

# CSC 322 Lab 2 Specification:

# CSC 322 Lab 3 Specification:

# CSC 322 Lab 4 Specification:
