#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MovePC(int numCreatures, char userCommand[9], int roomOfPC);
void LetPCLook(int numCreatures, int roomOfPC);
void LetPCCleanRoom(int numCreatures, int numRooms, int roomOfPC);
void LetPCDirtyRoom(int numCreatures, int numRooms, int roomOfPC);
void MoveCreature(int creatureID, int roomOfPC, char * tokenString);
void LetCreatureLook(int numCreatures, int creatureID);
void MakeCreatureCleanRoom(int numCreatures, int numRooms, int creatureID, int roomOfPC);
void MakeCreatureDirtyRoom(int numCreatures, int numRooms, int creatureID, int roomOfPC);
void DisplayHelpStatement();
void DisplayGameOverStatement();

struct Creature {

    int creatureType;
    int creatureLocation;
    int deletionStatus;
    int creatureNumID;

};

struct Room {

    int roomState;
    int northRoom;
    int southRoom;
    int eastRoom;
    int westRoom;
    struct Creature *creatures;
    int creatureCount;

};

struct Room *aRoom;
struct Creature *aCreature;
int respect = 40;

int GetNumberOfRooms( ){

    int numRooms = -1;

    //Get Number of Rooms
    while(numRooms >= 100 || numRooms <= 1) {

        printf("Please enter the number of rooms greater than 1 and less than 100: "); //to user
        scanf("%d", &numRooms); //from user

    }
    return numRooms;

}

void GetRoomInformation(int numRooms){

    //Get Room Information
    for(int roomNumber = 0; roomNumber < numRooms; roomNumber++){

        scanf("%d %d %d %d %d", &aRoom[roomNumber].roomState, &aRoom[roomNumber].northRoom,
            &aRoom[roomNumber].southRoom, &aRoom[roomNumber].eastRoom, &aRoom[roomNumber].westRoom); //from user
        aRoom[roomNumber].creatureCount = 0;
        aRoom[roomNumber].creatures = malloc(sizeof(struct Creature)*10);

    }

}

int GetNumberOfCreatures( ){

    int numCreatures = -1;

    //Get Number of Creatures
    while(numCreatures >= 100 || numCreatures <= 1){

        printf("Please enter the number of creatures greater than 1 and less than 100: "); //to user
        scanf("%d", &numCreatures); //from user

    }
    return numCreatures;

}

int GetCreatureInformation(int numCreatures){

    int roomOfPC;
    int creatureType = -1;
    int creatureLocation = -2;

    //Get Creature Information
    for(int creatureID = 0; creatureID < numCreatures; creatureID++){

        scanf("%d %d", &creatureType, &creatureLocation); //from user
        aCreature[creatureID].creatureType = creatureType;
        aCreature[creatureID].creatureLocation = creatureLocation;
        aCreature[creatureID].deletionStatus = 0;
        aCreature[creatureID].creatureNumID = creatureID;
        aRoom[creatureLocation].creatures[aRoom[creatureLocation].creatureCount] = aCreature[creatureID];
        aRoom[creatureLocation].creatureCount++;
        if(aCreature[creatureID].creatureType == 0)
            roomOfPC = aCreature[creatureID].creatureLocation;
        printf("%d", roomOfPC);
    }
    return roomOfPC;

}

void GetGameCommand(char * userCommand){

    //Get Game Command
    printf("Enter a command: "); //to user
    scanf("%s", userCommand); //from user
    printf("\n");

}

int PerformGameCommand(int numCreatures, int numRooms, int roomOfPC, char * userCommand){

    //Perform Game Command
    if(strcmp(userCommand, "north") == 0)
        roomOfPC = MovePC(numCreatures, userCommand, roomOfPC);
    else if(strcmp(userCommand, "south") == 0)
        roomOfPC = MovePC(numCreatures, userCommand, roomOfPC);
    else if(strcmp(userCommand, "east") == 0)
        roomOfPC = MovePC(numCreatures, userCommand, roomOfPC);
    else if(strcmp(userCommand, "west") == 0)
        roomOfPC = MovePC(numCreatures, userCommand, roomOfPC);
    else if(strcmp(userCommand, "look") == 0)
        LetPCLook(numCreatures, roomOfPC);
    else if(strcmp(userCommand, "clean") == 0)
        LetPCCleanRoom(numCreatures, numRooms, roomOfPC);
    else if(strcmp(userCommand, "dirty") == 0)
        LetPCDirtyRoom(numCreatures, numRooms, roomOfPC);
    else if(strcmp(userCommand, "help") == 0)
        DisplayHelpStatement( );
    else {

        char *tokenString;
        char *delim = ":";

        tokenString = strtok(userCommand, delim);
        int creatureID = atoi(tokenString);
        tokenString = strtok(NULL, delim);
        printf(tokenString);

        for(int cnt = 0; cnt < numCreatures; cnt++) {

            if(aCreature[cnt].creatureNumID == creatureID && aCreature[cnt].deletionStatus == 0 &&
                aCreature[cnt].creatureType != 0){

                if(strcmp(tokenString, "north") == 0)
                    MoveCreature(creatureID, roomOfPC, tokenString);
                else if(strcmp(tokenString, "south") == 0)
                    MoveCreature(creatureID, roomOfPC, tokenString);
                else if(strcmp(tokenString, "east") == 0)
                    MoveCreature(creatureID, roomOfPC, tokenString);
                else if(strcmp(tokenString, "west") == 0)
                    MoveCreature(creatureID, roomOfPC, tokenString);
                else if(strcmp(tokenString, "look") == 0)
                    LetCreatureLook(numCreatures, creatureID);
                else if(strcmp(tokenString, "clean") == 0)
                    MakeCreatureCleanRoom(numCreatures, numRooms, creatureID, roomOfPC);
                else if(strcmp(tokenString, "dirty") == 0)
                    MakeCreatureDirtyRoom(numCreatures, numRooms, creatureID, roomOfPC);

            }

        }

    }
    return roomOfPC;

}

int MovePC(int numCreatures, char userCommand[9], int roomOfPC){

    int newRoomLocation = -1;

    //Move PC
    if(strcmp(userCommand, "north") == 0)
        newRoomLocation = aRoom[roomOfPC].northRoom;
    else if(strcmp(userCommand, "south") == 0)
        newRoomLocation = aRoom[roomOfPC].southRoom;
    else if(strcmp(userCommand, "east") == 0)
        newRoomLocation = aRoom[roomOfPC].eastRoom;
    else if(strcmp(userCommand, "west") == 0)
        newRoomLocation = aRoom[roomOfPC].westRoom;

    if(aRoom[newRoomLocation].creatureCount >= 10)
        printf("Room full\n"); //to user
    else if(newRoomLocation == -1)
        printf("Cannot move in that direction\n"); //to user
    else {

        roomOfPC = newRoomLocation;
        for(int cnt = 0; cnt < numCreatures; cnt++){

            if(aCreature[cnt].creatureType == 0)
                aCreature[cnt].creatureLocation = roomOfPC;

        }
        if(strcmp(userCommand, "north") == 0)
            printf("You leave towards the north\n"); //to user
        if(strcmp(userCommand, "south") == 0)
            printf("You leave towards the south\n"); //to user
        if(strcmp(userCommand, "east") == 0)
            printf("You leave towards the east\n"); //to user
        if(strcmp(userCommand, "west") == 0)
            printf("You leave towards the west\n"); //to user

    }
    printf("\n");
    return roomOfPC;

}

void LetPCLook(int numCreatures, int roomOfPC){

    //Let PC Look
    printf("PC is currently in room %d\n", roomOfPC); //to user

    if(aRoom[roomOfPC].roomState == 0)
        printf("The room is currently clean\n"); //to user
    else if(aRoom[roomOfPC].roomState == 1)
        printf("The room is currently half-dirty\n"); //to user
    else if(aRoom[roomOfPC].roomState == 2)
        printf("The room is currently dirty\n"); //to user

    printf("Here are the neighboring rooms:\n"); //to user
    if(aRoom[roomOfPC].northRoom != -1)
        printf("%d to the north\n", aRoom[roomOfPC].northRoom); //to user
    if(aRoom[roomOfPC].southRoom != -1)
        printf("%d to the south\n", aRoom[roomOfPC].southRoom); //to user
    if(aRoom[roomOfPC].eastRoom != -1)
        printf("%d to the east\n", aRoom[roomOfPC].eastRoom); //to user
    if(aRoom[roomOfPC].westRoom != -1)
        printf("%d to the west\n", aRoom[roomOfPC].westRoom); //to user
    printf("Here are the creatures in the room with the PC:\n"); //to user
    for(int cnt = 0; cnt < numCreatures; cnt++){

        if(aCreature[cnt].creatureLocation == roomOfPC && aCreature[cnt].deletionStatus == 0){

            if(aCreature[cnt].creatureType == 0)
                printf("PC\n"); //to user
            else if(aCreature[cnt].creatureType == 1){

                printf("%d, ", aCreature[cnt].creatureNumID); //to user
                printf("an animal\n"); //to user

            }
            else if(aCreature[cnt].creatureType == 2){

                printf("%d, ", aCreature[cnt].creatureNumID); //to user
                printf("an NPC\n"); //to user

            }

        }

    }
    printf("\n");

}

void LetPCCleanRoom(int numCreatures, int numRooms, int roomOfPC){

    int potentialNorthRoom = -1;
    int potentialSouthRoom = -1;
    int potentialEastRoom = -1;
    int potentialWestRoom = -1;
    int newRoom = -2;

    //Let PC Clean Room
    if(aRoom[roomOfPC].roomState == 0)
        printf("Room is already clean\n"); //to user
    else if(aRoom[roomOfPC].roomState == 1 || aRoom[roomOfPC].roomState == 2){

        aRoom[roomOfPC].roomState = aRoom[roomOfPC].roomState - 1;
        for(int cnt1 = 0; cnt1 < numCreatures; cnt1++){

            if(aCreature[cnt1].creatureLocation == roomOfPC && aCreature[cnt1].deletionStatus == 0){

                if(aCreature[cnt1].creatureType == 1){

                    printf("%d licks your face\n", aCreature[cnt1].creatureNumID); //to user
                    respect = respect + 1;
                    printf("Your respect is now: %d\n", respect); //to user

                }
                else if(aCreature[cnt1].creatureType == 2){

                    printf("%d grumbles at you\n", aCreature[cnt1].creatureNumID); //to user
                    respect = respect - 1;
                    printf("Your respect is now: %d\n", respect); //to user
                    if(aRoom[roomOfPC].roomState == 0){

                        if(aRoom[roomOfPC].northRoom != -1){

                            potentialNorthRoom = aRoom[roomOfPC].northRoom;
                            if(aRoom[potentialNorthRoom].creatureCount >= 10)
                                potentialNorthRoom = -1;

                        }
                        if(aRoom[roomOfPC].southRoom != -1){

                            potentialSouthRoom = aRoom[roomOfPC].southRoom;
                            if(aRoom[potentialSouthRoom].creatureCount >= 10)
                                potentialSouthRoom = -1;

                        }
                        if(aRoom[roomOfPC].eastRoom != -1){

                            potentialEastRoom = aRoom[roomOfPC].eastRoom;
                            if(aRoom[potentialEastRoom].creatureCount >= 10)
                                potentialEastRoom = -1;

                        }
                        if(aRoom[roomOfPC].westRoom != -1){

                            potentialWestRoom = aRoom[roomOfPC].westRoom;
                            if(aRoom[potentialWestRoom].creatureCount >= 10)
                                    potentialWestRoom = -1;

                        }
                        if(potentialNorthRoom == -1 && potentialSouthRoom == -1 && potentialEastRoom == -1 &&
                            potentialWestRoom == -1){

                            aCreature[cnt1].deletionStatus = 1;
                            printf("%d drilled a hole and left the game forever\n", aCreature[cnt1].creatureNumID);
                                //to user
                            for(int hatePC = 0; hatePC < numCreatures; hatePC++){

                                if(aCreature[hatePC].creatureLocation == roomOfPC && aCreature[hatePC].deletionStatus
                                    == 0){

                                    if(aCreature[hatePC].creatureType == 1){

                                        printf("%d growls at you\n", aCreature[hatePC].creatureNumID); //to user
                                        respect = respect - 1;
                                        printf("Your respect is now: %d\n", respect); //to user

                                    }
                                    else if(aCreature[hatePC].creatureType == 2){

                                        printf("%d grumbles at you\n", aCreature[hatePC].creatureNumID); //to user
                                        respect = respect - 1;
                                        printf("Your respect is now: %d\n", respect); //to user

                                    }

                                }

                            }

                        }
                        else{

                            while(newRoom != potentialNorthRoom && newRoom != potentialSouthRoom && newRoom !=
                                potentialEastRoom && newRoom != potentialWestRoom)
                                newRoom = rand() % numRooms;
                            aCreature[cnt1].creatureLocation = newRoom;
                            if(aRoom[roomOfPC].northRoom == newRoom)
                                printf("%d leaves towards the north\n", aCreature[cnt1].creatureNumID); //to user
                            else if(aRoom[roomOfPC].southRoom == newRoom)
                                printf("%d leaves towards the south\n", aCreature[cnt1].creatureNumID); //to user
                            else if(aRoom[roomOfPC].eastRoom == newRoom)
                                printf("%d leaves towards the east\n", aCreature[cnt1].creatureNumID); //to user
                            else if(aRoom[roomOfPC].westRoom == newRoom)
                                printf("%d leaves towards the west\n", aCreature[cnt1].creatureNumID); //to user
                            if(aRoom[newRoom].roomState == 0){

                                aRoom[newRoom].roomState = 1;
                                printf("Adjacent room was clean, so NPC dirtied it up to half-dirty\n"); //to user

                            }

                        }

                    }

                }

            }

        }

    }
    printf("\n");

}

void LetPCDirtyRoom(int numCreatures, int numRooms, int roomOfPC){

    int potentialNorthRoom = -1;
    int potentialSouthRoom = -1;
    int potentialEastRoom = -1;
    int potentialWestRoom = -1;
    int newRoom = -2;

    //Let PC Dirty Room
    if(aRoom[roomOfPC].roomState == 2)
        printf("Room is already dirty\n"); //to user
    else if(aRoom[roomOfPC].roomState == 0 || aRoom[roomOfPC].roomState == 1){

        aRoom[roomOfPC].roomState = aRoom[roomOfPC].roomState + 1;
        for(int cnt1 = 0; cnt1 < numCreatures; cnt1++){

            if(aCreature[cnt1].creatureLocation == roomOfPC && aCreature[cnt1].deletionStatus == 0){

                if(aCreature[cnt1].creatureType == 1){

                    printf("%d growls at you\n", aCreature[cnt1].creatureNumID); //to user
                    respect = respect - 1;
                    printf("Your respect is now: %d\n", respect); //to user
                    if(aRoom[roomOfPC].roomState == 2){

                        if(aRoom[roomOfPC].northRoom != -1){

                            potentialNorthRoom = aRoom[roomOfPC].northRoom;
                            if(aRoom[potentialNorthRoom].creatureCount >= 10)
                                potentialNorthRoom = -1;

                        }
                        if(aRoom[roomOfPC].southRoom != -1){

                            potentialSouthRoom = aRoom[roomOfPC].southRoom;
                            if(aRoom[potentialSouthRoom].creatureCount >= 10)
                                potentialSouthRoom = -1;

                        }
                        if(aRoom[roomOfPC].eastRoom != -1){

                            potentialEastRoom = aRoom[roomOfPC].eastRoom;
                            if(aRoom[potentialEastRoom].creatureCount >= 10)
                                potentialEastRoom = -1;

                        }
                        if(aRoom[roomOfPC].westRoom != -1){

                            potentialWestRoom = aRoom[roomOfPC].westRoom;
                            if(aRoom[potentialWestRoom].creatureCount >= 10)
                                potentialWestRoom = -1;

                        }
                        if(potentialNorthRoom == -1 && potentialSouthRoom == -1 && potentialEastRoom == -1 &&
                            potentialWestRoom == -1){

                            aCreature[cnt1].deletionStatus = 1;
                            printf("%d drilled a hole and left the game forever\n", aCreature[cnt1].creatureNumID);
                                //to user
                            for(int hatePC = 0; hatePC < numCreatures; hatePC++){

                                if(aCreature[hatePC].creatureLocation == roomOfPC && aCreature[hatePC].deletionStatus
                                    == 0) {

                                    if(aCreature[hatePC].creatureType == 1){

                                        printf("%d growls at you\n", aCreature[hatePC].creatureNumID); //to user
                                        respect = respect - 1;
                                        printf("Your respect is now: %d\n", respect); //to user

                                    }
                                    else if(aCreature[hatePC].creatureType == 2){

                                        printf("%d grumbles at you\n", aCreature[hatePC].creatureNumID); //to user
                                        respect = respect - 1;
                                        printf("Your respect is now: %d\n", respect); //to user

                                    }

                                }

                            }

                        }
                        else{

                            while(newRoom != potentialNorthRoom && newRoom != potentialSouthRoom && newRoom !=
                                potentialEastRoom && newRoom != potentialWestRoom)
                                newRoom = rand() % numRooms;
                            aCreature[cnt1].creatureLocation = newRoom;
                            if(aRoom[roomOfPC].northRoom == newRoom)
                                printf("%d leaves towards the north\n", aCreature[cnt1].creatureNumID); //to user
                            else if(aRoom[roomOfPC].southRoom == newRoom)
                                printf("%d leaves towards the south\n", aCreature[cnt1].creatureNumID); //to user
                            else if(aRoom[roomOfPC].eastRoom == newRoom)
                                printf("%d leaves towards the east\n", aCreature[cnt1].creatureNumID); //to user
                            else if(aRoom[roomOfPC].westRoom == newRoom)
                                printf("%d leaves towards the west\n", aCreature[cnt1].creatureNumID); //to user
                            if(aRoom[newRoom].roomState == 2){

                                aRoom[newRoom].roomState = 1;
                                printf("Adjacent room was dirty, so animal cleaned it up to half-dirty\n"); //to user

                            }

                        }

                    }

                }
                else if(aCreature[cnt1].creatureType == 2){

                    printf("%d smiles at you\n", aCreature[cnt1].creatureNumID); //to user
                    respect = respect + 1;
                    printf("Your respect is now: %d\n", respect); //to user

                }

            }

        }

    }
    printf("\n");

}

void MoveCreature(int creatureID, int roomOfPC, char * tokenString){

    int oldRoomLocation;
    int newRoomLocation = -1;

    //Move Creature
    oldRoomLocation = aCreature[creatureID].creatureLocation;
    if(roomOfPC == oldRoomLocation){

        if(strcmp(tokenString, "north") == 0)
            newRoomLocation = aRoom[roomOfPC].northRoom;
        else if(strcmp(tokenString, "south") == 0)
            newRoomLocation = aRoom[roomOfPC].southRoom;
        else if(strcmp(tokenString, "east") == 0)
            newRoomLocation = aRoom[roomOfPC].eastRoom;
        else if(strcmp(tokenString, "west") == 0)
            newRoomLocation = aRoom[roomOfPC].westRoom;

        if(aRoom[newRoomLocation].creatureCount >= 10){

            printf("Room full\n"); //to user
            if(aCreature[creatureID].creatureType == 1)
                printf("%d growls at you\n", creatureID); //to user
            else if(aCreature[creatureID].creatureType == 2)
                printf("%d grumbles at you\n", creatureID); //to user
            respect = respect - 1;
            printf("Respect is now: %d\n", respect); //to user

        }
        else if(newRoomLocation == -1)
            printf("Cannot move in that direction"); //to user
        else{

            aCreature[creatureID].creatureLocation = newRoomLocation;

            if(strcmp(tokenString, "north") == 0)
                printf("%d leaves towards the north\n", creatureID); //to user
            else if(strcmp(tokenString, "south") == 0)
                printf("%d leaves towards the south\n", creatureID); //to user
            else if(strcmp(tokenString, "east") == 0)
                printf("%d leaves towards the east\n", creatureID); //to user
            else if(strcmp(tokenString, "west") == 0)
                printf("%d leave towards the west\n", creatureID); //to user

            if(aRoom[newRoomLocation].roomState == 2 && aCreature[creatureID].creatureType == 1){

                aRoom[newRoomLocation].roomState = 1;
                printf("Adjacent room was dirty, so animal cleaned it up to half-dirty\n"); //to user

            }
            else if(aRoom[newRoomLocation].roomState == 0 && aCreature[creatureID].creatureType == 2){

                aRoom[newRoomLocation].roomState = 1;
                printf("Adjacent room was clean, so NPC dirtied it up to half-dirty\n"); //to user

            }

        }

    }
    else
        printf("Error: Creature is not in the same room as the PC\n"); //to user
    printf("\n");

}

void LetCreatureLook(int numCreatures, int creatureID){

    //Let Creature Look
    printf("%d is currently in room %d\n", creatureID, aCreature[creatureID].creatureLocation); //to user
    if(aRoom[aCreature[creatureID].creatureLocation].roomState == 0)
        printf("The room is currently clean\n"); //to user
    else if(aRoom[aCreature[creatureID].creatureLocation].roomState == 1)
        printf("The room is currently half-dirty\n"); //to user
    else if(aRoom[aCreature[creatureID].creatureLocation].roomState == 2)
        printf("The room is currently dirty\n"); //to user

    printf("Here are the neighboring rooms:\n"); //to user
    if(aRoom[aCreature[creatureID].creatureLocation].northRoom != -1)
        printf("%d to the north\n", aRoom[aCreature[creatureID].creatureLocation].northRoom); //to user
    if(aRoom[aCreature[creatureID].creatureLocation].southRoom != -1)
        printf("%d to the south\n", aRoom[aCreature[creatureID].creatureLocation].southRoom); //to user
    if(aRoom[aCreature[creatureID].creatureLocation].eastRoom != -1)
        printf("%d to the east\n", aRoom[aCreature[creatureID].creatureLocation].eastRoom); //to user
    if(aRoom[aCreature[creatureID].creatureLocation].westRoom != -1)
        printf("%d to the west\n", aRoom[aCreature[creatureID].creatureLocation].westRoom); //to user
    printf("Here are the creatures in the room with %d: \n", creatureID); //to user
    for(int cnt = 0; cnt < numCreatures; cnt++){

        if(aCreature[cnt].creatureLocation == aCreature[creatureID].creatureLocation && aCreature[cnt].deletionStatus
            == 0){

            if(aCreature[cnt].creatureType == 0)
                printf("PC\n"); //to user
            else if(aCreature[cnt].creatureType == 1){

                printf("%d, ", aCreature[cnt].creatureNumID); //to user
                printf("an animal\n"); //to user

            }
            else if(aCreature[cnt].creatureType == 2){

                printf("%d, ", aCreature[cnt].creatureNumID); //to user
                printf("an NPC\n"); //to user

            }

        }

    }
    printf("\n");

}

void MakeCreatureCleanRoom(int numCreatures, int numRooms, int creatureID, int roomOfPC){

    int potentialNorthRoom = -1;
    int potentialSouthRoom = -1;
    int potentialEastRoom = -1;
    int potentialWestRoom = -1;
    int newRoom = -2;

    //Make Creature Clean Room
    if(roomOfPC == aCreature[creatureID].creatureLocation){

        if(aRoom[roomOfPC].roomState == 0)
            printf("Room is already clean\n"); //to user
        else if(aRoom[roomOfPC].roomState == 1 || aRoom[roomOfPC].roomState == 2){

            aRoom[roomOfPC].roomState = aRoom[roomOfPC].roomState - 1;
            for(int cnt1 = 0; cnt1 < numCreatures; cnt1++){

                if(aCreature[cnt1].creatureLocation == roomOfPC && aCreature[cnt1].deletionStatus == 0){

                    if(aCreature[cnt1].creatureType == 1){

                        if(aCreature[cnt1].creatureNumID == creatureID){

                            printf("%d licks your face a lot\n", creatureID); //to user
                            respect = respect + 3;
                            printf("Your respect is now: %d\n", respect); //to user

                        }
                        else{

                            printf("%d licks your face\n", aCreature[cnt1].creatureNumID); //to user
                            respect = respect + 1;
                            printf("Your respect is now: %d\n", respect); //to user

                        }

                    }
                    else if(aCreature[cnt1].creatureType == 2){

                        if(aCreature[cnt1].creatureNumID == creatureID){

                            printf("%d grumbles at you a lot\n", creatureID); //to user
                            respect = respect - 3;
                            printf("Your respect is now: %d\n", respect); //to user

                        }
                        else{

                            printf("%d grumbles at you\n", aCreature[cnt1].creatureNumID); //to user
                            respect = respect - 1;
                            printf("Your respect is now: %d\n", respect); //to user

                        }
                        if(aRoom[roomOfPC].roomState == 0){

                            if(aRoom[roomOfPC].northRoom != -1){

                                potentialNorthRoom = aRoom[roomOfPC].northRoom;
                                if(aRoom[potentialNorthRoom].creatureCount >= 10)
                                    potentialNorthRoom = -1;

                            }
                            if(aRoom[roomOfPC].southRoom != -1){

                                potentialSouthRoom = aRoom[roomOfPC].southRoom;
                                if(aRoom[potentialSouthRoom].creatureCount >= 10)
                                    potentialSouthRoom = -1;

                            }
                            if(aRoom[roomOfPC].eastRoom != -1){

                                potentialEastRoom = aRoom[roomOfPC].eastRoom;
                                if(aRoom[potentialEastRoom].creatureCount >= 10)
                                    potentialEastRoom = -1;

                            }
                            if(aRoom[roomOfPC].westRoom != -1){

                                potentialWestRoom = aRoom[roomOfPC].westRoom;
                                if(aRoom[potentialWestRoom].creatureCount >= 10)
                                    potentialWestRoom = -1;

                            }
                            if(potentialNorthRoom == -1 && potentialSouthRoom == -1 && potentialEastRoom == -1 &&
                                potentialWestRoom == -1){

                                aCreature[cnt1].deletionStatus = 1;
                                printf("%d drilled a hole and left the game forever\n", aCreature[cnt1].creatureNumID);
                                    //to user
                                for(int hatePC = 0; hatePC < numCreatures; hatePC++){

                                    if(aCreature[hatePC].creatureLocation == roomOfPC &&
                                        aCreature[hatePC].deletionStatus == 0){

                                        if(aCreature[hatePC].creatureType == 1){

                                            printf("%d growls at you\n", aCreature[hatePC].creatureNumID); //to user
                                            respect = respect - 1;
                                            printf("Your respect is now: %d\n", respect); //to user

                                        }
                                        else if(aCreature[hatePC].creatureType == 2){

                                            printf("%d grumbles at you\n", aCreature[hatePC].creatureNumID); //to user
                                            respect = respect - 1;
                                            printf("Your respect is now: %d\n", respect); //to user

                                        }

                                    }

                                }

                            }
                            else {

                                while(newRoom != potentialNorthRoom && newRoom != potentialSouthRoom && newRoom !=
                                    potentialEastRoom && newRoom != potentialWestRoom)
                                    newRoom = rand() % numRooms;
                                aCreature[cnt1].creatureLocation = newRoom;
                                if(aRoom[roomOfPC].northRoom == newRoom)
                                    printf("%d leaves towards the north\n", aCreature[cnt1].creatureNumID); //to user
                                else if(aRoom[roomOfPC].southRoom == newRoom)
                                    printf("%d leaves towards the south\n", aCreature[cnt1].creatureNumID); //to user
                                else if(aRoom[roomOfPC].eastRoom == newRoom)
                                    printf("%d leaves towards the east\n", aCreature[cnt1].creatureNumID); //to user
                                else if(aRoom[roomOfPC].westRoom == newRoom)
                                    printf("%d leaves towards the west\n", aCreature[cnt1].creatureNumID); //to user
                                if(aRoom[newRoom].roomState == 0){

                                    aRoom[newRoom].roomState = 1;
                                    printf("Adjacent room was clean, so NPC dirtied it up to half-dirty\n"); //to user

                                }

                            }

                        }

                    }

                }

            }

        }

    }
    else
        printf("Error: Creature of interest is not in the room with the PC\n"); //to user
    printf("\n");

}

void MakeCreatureDirtyRoom(int numCreatures, int numRooms, int creatureID, int roomOfPC){

    int potentialNorthRoom = -1;
    int potentialSouthRoom = -1;
    int potentialEastRoom = -1;
    int potentialWestRoom = -1;
    int newRoom = -2;

    //Make Creature Dirty Room
    if(roomOfPC == aCreature[creatureID].creatureLocation){

        if(aRoom[roomOfPC].roomState == 2)
            printf("Room is already dirty\n"); //to user
        else if(aRoom[roomOfPC].roomState == 0 || aRoom[roomOfPC].roomState == 1){

            aRoom[roomOfPC].roomState = aRoom[roomOfPC].roomState + 1;
            for(int cnt1 = 0; cnt1 < numCreatures; cnt1++){

                if(aCreature[cnt1].creatureLocation == roomOfPC && aCreature[cnt1].deletionStatus == 0){

                    if(aCreature[cnt1].creatureType == 1){

                        if(aCreature[cnt1].creatureNumID == creatureID){

                            printf("%d growls at you a lot\n", creatureID); //to user
                            respect = respect - 3;
                            printf("Your respect is now: %d\n", respect); //to user

                        }
                        else{

                            printf("%d growls at you\n", aCreature[cnt1].creatureNumID); //to user
                            respect = respect - 1;
                            printf("Your respect is now: %d\n", respect); //to user

                        }
                        if(aRoom[roomOfPC].roomState == 2){

                            if(aRoom[roomOfPC].northRoom != -1){

                                potentialNorthRoom = aRoom[roomOfPC].northRoom;
                                if(aRoom[potentialNorthRoom].creatureCount >= 10)
                                    potentialNorthRoom = -1;

                            }
                            if(aRoom[roomOfPC].southRoom != -1){

                                potentialSouthRoom = aRoom[roomOfPC].southRoom;
                                if(aRoom[potentialSouthRoom].creatureCount >= 10)
                                    potentialSouthRoom = -1;

                            }
                            if(aRoom[roomOfPC].eastRoom != -1){

                                potentialEastRoom = aRoom[roomOfPC].eastRoom;
                                if(aRoom[potentialEastRoom].creatureCount >= 10)
                                    potentialEastRoom = -1;

                            }
                            if(aRoom[roomOfPC].westRoom != -1){

                                potentialWestRoom = aRoom[roomOfPC].westRoom;
                                if(aRoom[potentialWestRoom].creatureCount >= 10)
                                    potentialWestRoom = -1;

                            }
                            if(potentialNorthRoom == -1 && potentialSouthRoom == -1 && potentialEastRoom == -1 &&
                                potentialWestRoom == -1){

                                aCreature[cnt1].deletionStatus = 1;
                                printf("%d drilled a hole and left the game forever\n", aCreature[cnt1].creatureNumID);
                                    //to user
                                for(int hatePC = 0; hatePC < numCreatures; hatePC++){

                                    if(aCreature[hatePC].creatureLocation == roomOfPC &&
                                        aCreature[hatePC].deletionStatus == 0){

                                        if(aCreature[hatePC].creatureType == 1){

                                            printf("%d growls at you\n", aCreature[hatePC].creatureNumID); //to user
                                            respect = respect - 1;
                                            printf("Your respect is now: %d\n", respect); //to user

                                        }
                                        else if(aCreature[hatePC].creatureType == 2){

                                            printf("%d grumbles at you\n", aCreature[hatePC].creatureNumID); //to user
                                            respect = respect - 1;
                                            printf("Your respect is now: %d\n", respect); //to user

                                        }

                                    }

                                }

                            }
                            else {

                                while(newRoom != potentialNorthRoom && newRoom != potentialSouthRoom && newRoom !=
                                    potentialEastRoom && newRoom != potentialWestRoom)
                                    newRoom = rand() % numRooms;
                                aCreature[cnt1].creatureLocation = newRoom;
                                if(aRoom[roomOfPC].northRoom == newRoom)
                                    printf("%d leaves towards the north\n", aCreature[cnt1].creatureNumID); //to user
                                else if(aRoom[roomOfPC].southRoom == newRoom)
                                    printf("%d leaves towards the south\n", aCreature[cnt1].creatureNumID); //to user
                                else if(aRoom[roomOfPC].eastRoom == newRoom)
                                    printf("%d leaves towards the east\n", aCreature[cnt1].creatureNumID); //to user
                                else if(aRoom[roomOfPC].westRoom == newRoom)
                                    printf("%d leaves towards the west\n", aCreature[cnt1].creatureNumID); //to user
                                if(aRoom[newRoom].roomState == 2){

                                    aRoom[newRoom].roomState = 1;
                                    printf("Adjacent room was dirty, so animal cleaned it up to half-dirty\n");
                                        //to user

                                }

                            }

                        }

                    }
                    else if(aCreature[cnt1].creatureType == 2){

                        if(aCreature[cnt1].creatureNumID == creatureID){

                            printf("%d smiles at you a lot\n", creatureID); //to user
                            respect = respect + 3;
                            printf("Your respect is now: %d\n", respect); //to user

                        }
                        else{

                            printf("%d smiles at you\n", aCreature[cnt1].creatureNumID); //to user
                            respect = respect + 1;
                            printf("Your respect is now: %d\n", respect); //to user

                        }

                    }

                }

            }

        }

    }
    else
        printf("Error: Creature of interest is not in the room with the PC\n"); //to user
    printf("\n");

}

void DisplayHelpStatement( ){

    //Display Help Statement
    printf("Here is a list of the allowed commands:\n"); //to user
    printf("\n"); //to user
    printf("Type north/south/east/west to move PC in desired direction (Assuming adjacent room exists and is not "
        "full)\n"); //to user
    printf("Type look to get detailed information about the room the PC is currently in\n"); //to user
    printf("Type clean/dirty to either clean or dirty the room the PC is in respectively (Animals and NPCs in the "
        "same room as the PC will react accordingly)\n"); //to user
    printf("Type n:north/n:south/n:east/n:west to move creature with creature ID number n in desired direction (Note: "
        "The desired creature must be in the same room as the PC)\n"); //to user
    printf("Type n:look to get detailed information about the room the creature with creature ID number n is in\n");
        //to user
    printf("Type n:clean/n:dirty to make the creature with creature ID number n clean or dirty their current room "
        "location (Note: The desired creature must be in the same room\nas the PC. Animals and NPCs in that same "
        "room will react accordingly)\n"); //to user
    printf("Type help to display this list of all of the available commands for the game\n"); //to user
    printf("Type exit to quit the game\n"); //to user
    printf("\n"); //to user

}

void DisplayGameOverStatement( ){

    //Display Game Over Statement
    if(respect > 80)
        printf("Congratulations!!! You are loved by all!\n"); //to user
    else if(respect <= 0)
        printf("What a shame! You are hated by all!\n"); //to user
    printf("Game Over\n"); //to user

}

int main( ){

    int numRooms;
    int numCreatures;
    int roomOfPC;
    char *userCommand = malloc(9);

    //Manage Game
    numRooms = GetNumberOfRooms();
    aRoom = malloc(sizeof(struct Room)*numRooms);
    GetRoomInformation(numRooms);
    numCreatures = GetNumberOfCreatures();
    aCreature = malloc(sizeof(struct Creature)*numCreatures);
    roomOfPC = GetCreatureInformation(numCreatures);
    while(strcmp(userCommand, "exit") != 0 && respect > 0 && respect <= 80){

        GetGameCommand(userCommand);
        if(strcmp(userCommand, "exit") != 0)
            roomOfPC = PerformGameCommand(numCreatures, numRooms, roomOfPC, userCommand);

    }
    for(int freeRoom = 0; freeRoom < numRooms; freeRoom++)
        free(aRoom[freeRoom].creatures);
    free(userCommand);
    free(aRoom);
    free(aCreature);
    DisplayGameOverStatement();

    return 0;

}
