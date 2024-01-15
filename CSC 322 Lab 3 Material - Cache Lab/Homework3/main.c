#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct Cache Cache;

struct Cache{

    bool validBit;
    int tag;
    int numHits;
    int lastHitAttempt;

};

int main() {

    //Input
    int numSets = 0; //S
    int numSetLines = 0; //E
    int blockSize = 0; //B
    int numAddressBits = 0; //m (rarely used)
    char replacementPolicy[3]; //LFU or LRU
    int hitTime = 0; //h
    int missPenalty = 0; //p
    unsigned int hexAddress = 0;

    //Counters
    double numAddresses = 0;
    double numMisses = 0;
    int addressArrayIndex = 0;
    int numCyclesUsed = 0;

    //Holding onto Data
    unsigned int addressArray[100];
    unsigned int *currentAddress;

    //Variables Requiring Calculations
    int missRate;
    int numBlockOffsetBits;
    int numSetIndexBits;
    int setIndex;
    int tag;

    //Manage Cache Simulator
    printf("Enter the number of sets: "); //to user
    scanf("%d", &numSets); //from user
    printf("Enter the number of lines per set: "); //to user
    scanf("%d", &numSetLines); //from user

    Cache block[numSets][numSetLines];
    for(int cnt1 = 0; cnt1 < numSets; cnt1++){

        for(int cnt2 = 0; cnt2 < numSetLines; cnt2++){

            block[cnt1][cnt2].validBit = false;
            block[cnt1][cnt2].tag = 0;
            block[cnt1][cnt2].numHits = 0;
            block[cnt1][cnt2].lastHitAttempt = 0;

        }

    }
    printf("Enter the block size: "); //to user
    scanf("%d", &blockSize); //from user
    printf("Enter the number of address bits: "); //to user
    scanf("%d", &numAddressBits); //from user
    printf("Enter the replacement policy: "); //to user
    scanf("%s", replacementPolicy); //from user
    printf("Enter the hit time (in cycles): "); //to user
    scanf("%d", &hitTime); //from user
    printf("Enter the miss penalty (in cycles): "); //to user
    scanf("%d", &missPenalty); //from user
    while(hexAddress != -1) {

        printf("Enter a hex address (typing -1 will display the stats): "); //to user
        scanf("%x", &hexAddress); //from user
        addressArray[addressArrayIndex] = hexAddress;
        addressArrayIndex++;

    }
    numBlockOffsetBits = log2(blockSize);
    numSetIndexBits = log2(numSets);
    for(int cnt = 0; cnt < addressArrayIndex; cnt++){

        currentAddress = &addressArray[cnt];
        if(*currentAddress == -1){

            missRate = (int) round((numMisses / numAddresses) * 100);
            printf("%d %d", missRate, numCyclesUsed);

            break;

        }
        tag = (int) (*currentAddress >> (numBlockOffsetBits + numSetIndexBits));
        setIndex = (int) ((*currentAddress >> numBlockOffsetBits) & ((1 << numSetIndexBits) - 1));
        numCyclesUsed = numCyclesUsed + hitTime;
        numAddresses++;
        for(int currentLine = 0; currentLine < numSetLines; currentLine++){

            if(block[setIndex][currentLine].validBit == true){

                if(block[setIndex][currentLine].tag == tag){

                    block[setIndex][currentLine].numHits++;
                    block[setIndex][currentLine].lastHitAttempt = numAddresses;

                    printf("%x H\n", *currentAddress);

                    break;

                }
                else{

                    if(numSetLines != 1){

                        if(currentLine == numSetLines - 1){

                            if(strcmp(replacementPolicy, "LRU") == 0){

                                int leastRecentReference = 0;
                                int lruSetIndex = 0;
                                int lruLineIndex = 0;
                                for(int potentialEvictLine = 0; potentialEvictLine < numSetLines; potentialEvictLine++){

                                    if(potentialEvictLine == 0){

                                        leastRecentReference = block[setIndex][potentialEvictLine].lastHitAttempt;
                                        lruSetIndex = setIndex;
                                        lruLineIndex = potentialEvictLine;

                                    }
                                    else if(block[setIndex][potentialEvictLine].lastHitAttempt <= leastRecentReference){

                                        leastRecentReference =  block[setIndex][potentialEvictLine].lastHitAttempt;
                                        lruSetIndex = setIndex;
                                        lruLineIndex = potentialEvictLine;

                                    }

                                }
                                block[lruSetIndex][lruLineIndex].tag = tag;
                                block[lruSetIndex][lruLineIndex].lastHitAttempt = numAddresses;
                                block[lruSetIndex][lruLineIndex].numHits = 0;

                            }
                            else if(strcmp(replacementPolicy, "LFU") == 0){

                                int leastFrequentReference = 0;
                                int lfuSetIndex = 0;
                                int lfuLineIndex = 0;
                                for(int potentialEvictLine2 = 0; potentialEvictLine2 < numSetLines;
                                    potentialEvictLine2++){

                                    if(potentialEvictLine2 == 0){

                                        leastFrequentReference = block[setIndex][potentialEvictLine2].numHits;
                                        lfuSetIndex = setIndex;
                                        lfuLineIndex = potentialEvictLine2;

                                    }
                                    else if(block[setIndex][potentialEvictLine2].numHits <= leastFrequentReference){

                                        leastFrequentReference = block[setIndex][potentialEvictLine2].numHits;
                                        lfuSetIndex = setIndex;
                                        lfuLineIndex = potentialEvictLine2;

                                    }

                                }
                                block[lfuSetIndex][lfuLineIndex].tag = tag;
                                block[lfuSetIndex][lfuLineIndex].lastHitAttempt = numAddresses;
                                block[lfuSetIndex][lfuLineIndex].numHits = 0;

                            }
                            printf("%x M\n", *currentAddress);
                            numMisses++;
                            numCyclesUsed = numCyclesUsed + missPenalty;

                            break;

                        }

                    }
                    else{

                        block[setIndex][currentLine].tag = tag;
                        block[setIndex][currentLine].numHits = 0;
                        block[setIndex][currentLine].lastHitAttempt = numAddresses;

                        printf("%x M\n", *currentAddress);
                        numMisses++;
                        numCyclesUsed = numCyclesUsed + missPenalty;

                        break;

                    }

                }

            }
            else{

                block[setIndex][currentLine].validBit = true;
                block[setIndex][currentLine].tag = tag;
                block[setIndex][currentLine].lastHitAttempt = numAddresses;

                printf("%x M\n", *currentAddress);
                numMisses++;
                numCyclesUsed = numCyclesUsed + missPenalty;

                break;

            }

        }

    }
    return 0;

}
