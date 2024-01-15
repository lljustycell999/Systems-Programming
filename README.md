# CSC 322 - Systems Programming
This repository contains the projects completed as part of the CSC 322 - Systems Programming course at SUNY Oswego taught by Professor Aleksander Pantaleev.

# Lab 1 Specification:
This is your C lab. It consists of programming a small text-based game purely in C. The game was designed for OOP, which C does not support naturally. Thus this lab will simultaneously teach you the specifics of the C language, and the difference between structured programming and OOP.

You can find a complete description of the project in this pdf document (CSC 322 Lab 1 Notes.pdf).

The description above says you should use XML as input. To make the project a little easier, I am changing a few things. First, there will be no names and descriptions for anything in the game, only numbers (as in room number 0); change the game output accordingly. In addition, I am changing the input definition to the following:

When the game starts, it takes from stdin (so no files are opened/closed/used in the project code) input in the following format:
* n (integer, the number of rooms, 1 <= n < 100)
* The next n lines are the following: state north south east west (five integers, signifying the cleanliness of the room and the numbers of the respective neighbors. State can be 0 for clean, 1 for half-dirty, 2 for dirty. -1 signifies no neighbor. Numbering of the rooms starts at 0)
* The next line is: m (integer, the number of creatures, 1 <= m < 100)
* The next m lines are: creatureType location (two integers; creatureType is 0 for the PC, 1 for an animal, 2 for an NPC. Location is the number of the room the creature is in. Numbering starts at 0)
* The input will be well-formed according to the above description and the game specification (i.e., you should not worry about checking for errors in the input such as putting an animal in a dirty room from the start and the like).
* After the above is read from stdin, the game should continue reading game commands from stdin.

Make sure you use as few globals as possible. You must not use global arrays or global structs; you are allowed to use up to three global pointers and a global int for the respect value.

<img width="440" alt="Screen Shot 2024-01-15 at 2 43 50 PM" src="https://github.com/lljustycell999/CSC322/assets/123667513/1cad3368-27da-4faa-8fd3-9cf01a69771a">

Warning: There is an infinite loop bug in my project that occurs if the player decides to move in a direction that instantly takes you back to the same room you just left (For example, you are in room 0 and moving in a certain direction sends you back to room 0 immediately). 

# Lab 2 Specification:
The specifications for Lab 2 is available in the Lab 2 folder under the name bomblab.pdf. No code is required for this lab.

# Lab 3 Specification:
This is your cache lab. It consists of implementing a cache simulator given various parameters, and then watching it perform under different circumstances. To make things simple, you'll only be dealing with reads.

When your simulator starts, it should take from stdin (so no files are opened/closed/used in the project code) input in the following format:

* The first four lines contain the fundamental parameters of the cache, one per line. All four are integers: S, E, B, and m.
* The next line contains the replacement policy. The only ones you need are LFU and LRU. The replacement policy will be entered as either LFU or LRU, so read three chars here.
* The next two lines contains the fundamental parameters of the hardware: the hit time (h) and the miss penalty (p). Both are integers: h and p.
* That was the input. The runtime information follows immediately. All further lines contain integer addresses that your simulation attempts to read from main memory through the cache, one per line. The simulation stops when the "address" you read is -1.

You should output all information to stdout in the following format:

* For each address you read (except the final -1), output a line containing the address itself (in hex form), followed by a space, followed by a single character: H for cache hit or M for cache miss.

* Once you read -1, output on a single line the miss rate of the cache that you have calculated, followed by a space, followed by the total cycles spent during the simulation. Remember to complete this last output line with a newline character, then exit the simulation.

LFU Demo:
Input Example: <img width="56" alt="Screen Shot 2024-01-15 at 3 23 48 PM" src="https://github.com/lljustycell999/CSC322/assets/123667513/606dc5e4-d47f-4c36-8502-f620e7e132c9">
Output Example: <img width="54" alt="Screen Shot 2024-01-15 at 3 24 40 PM" src="https://github.com/lljustycell999/CSC322/assets/123667513/502fcf92-dc46-42b6-ba23-ff6586018f2d">

LRU Demo:
Input Example: <img width="42" alt="Screen Shot 2024-01-15 at 3 26 34 PM" src="https://github.com/lljustycell999/CSC322/assets/123667513/a1279e25-148c-42b4-9a48-db8ce8cea6ca">
Output Example: <img width="60" alt="Screen Shot 2024-01-15 at 3 26 44 PM" src="https://github.com/lljustycell999/CSC322/assets/123667513/6ec2dd5c-3255-4d93-a0b9-653389c64c3c">

# Lab 4 Specification:
The specifications for Lab 4 is available in the Lab 4 folder under the name shlab.pdf.
