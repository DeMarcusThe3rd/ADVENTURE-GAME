#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adventuregame.h"
#include <time.h>

/*REPEATS COMMAND*/
void repeatCommand(adventureGame *ag){
    if(strcmp(ag->command,"\n")!=0){  //while command typed is not newline character
        strcpy(ag->buffer,ag->command);  //copies the command into a buffer
    }
    else strcpy(ag->command,ag->buffer);  //if it is a newline character, the command is replaced with the buffer command
}

/*SCANS POSSIBLE COMMAND ENTERED*/
int processCommand(adventureGame *ag) {
    replaceNewLine(ag);

    if (strcmp(ag->command,"exit")==0) {  //checks if 'exit' was typed
        score(ag);
        winCondition(ag);
        exitMessage(ag);
        return(0);
    }
    if (strcmp(ag->command,"look")==0||strcmp(ag->command,"l")==0) {  //checks if 'look' or 'l' was typed
        processLook(ag);
        return(1);
    }
    if(strcasecmp(ag->command,"killMonster")==0 || strcasecmp(ag->command,"km")==0){ //checks if 'killMonster' or 'km' was typed
        processDamageMonster(ag);
        processDamagePlayer(ag);
        return(1);
    }
    if (strncmp(ag->command,"kill ",5)==0){  //checks if 'kill' was typed
        alternateDamageMonster(ag);
        return(1);
    }

    if (strcmp(ag->command,"unlock door")==0){  //checks if 'unlock door' was typed
        unlockDoor(ag);
        return(1);
    }
    if (strncmp(ag->command,"get ",4)==0){  //checks if 'get ' was typed
        processGet(ag);
        return(1);
    }

    if (strcmp(ag->command,"inventory")==0 || strcmp(ag->command,"i")==0){  //checks if 'inventory' or 'i' was typed
        printInventory(ag);
        return(1);
    }

    if (strncmp(ag->command,"drop ",5)==0){  //checks if 'drop ' was typed
        processDrop(ag);
        return(1);
    }

    if (strcmp(ag->command,"help")==0){  //checks if 'help' was typed
        help(ag);
        return(1);
    }
    if (strcmp(ag->command,"stats")==0){  //checks if 'stats' was typed
        stats(ag);
        return(1);
    }
    if(strncmp(ag->command,"drink ",6)==0){  //checks if 'drink ' was typed
        processDrink(ag);
        return(1);
    }
    if(strncmp(ag->command,"eat ",4)==0){  //checks if 'eat ' was typed
        processEat(ag);
        return(1);
    }
    if(strncmp(ag->command,"use ",4)==0){  //checks if 'use ' was typed
        processUse(ag);
        return(1);
    }
    if(processMovement(ag)){  //movement
    return (1);
}
}

/*REPLACE NEW LINE*/
void replaceNewLine(adventureGame *ag) {
    for (int i=0;ag->command[i]!='\0'; i++) {  //iterate through all characters of the command
    if (ag->command[i]=='\n') {  //encounters new line
        ag->command[i]='\0';  //replace with end of string
        return;
        }
    }
}

/*HELP FUNCTION*/
void help(adventureGame *ag){
    char header[17]={"LIST OF COMMANDS"};
    printf("+---------------------------------------------------------------------------+\n");
    printf("|                 %-53s     |\n",header);
    printf("+---------------------------------------------------------------------------+\n");
    for (int i=0;i<10;i++) {  //prints contents of the table
        printf("|    %-18s| %-50s |\n", ag->helpCommands[i], ag->subHelpCommands[i]);
        printf("+---------------------------------------------------------------------------+\n");
    }
}

/*LOOK FUNCTION*/
void processLook(adventureGame *ag) {
    for(int i=0;i<4;i++){  //loop through all possible directions
        if(ag->moveToArray[ag->room][i]>-1){  //if room is accessible
            printf("%s is to the %s. ",ag->rooms[ag->moveToArray[ag->room][i]],ag->direction[i]);
        }
/*FOR LOCKED ROOMS*/
        if(ag->moveToArray[ag->room][i]==-2 && ag->room == 4){  //-2 means room is locked
            printf("%s is to the %s. ",ag->rooms[9],ag->direction[i]);
        }
        if(ag->moveToArray[ag->room][i]==-2 && ag->room == 11){
            printf("%s is to the %s. ",ag->rooms[12],ag->direction[i]);
        }
    }

    printf("\n");
/*FOR MONSTER*/
    if (ag->monsterStatusArray[ag->room]>0){  //if monster is alive
        printf("There is a %s here.\n",ag->monsterArray[ag->room]);
        printf("%s",ag->monsterDesc[ag->room]);
    }
    else if (ag->monsterStatusArray[ag->room]==0) {  //if monster is dead
        printf("There is a dead %s here.\n",ag->monsterArray[ag->room]);
    }
/*FOR ITEMS*/
    for (int i=0;i<ag->totalRoom;i++) {  //loops through all indexes of item location
        if (ag->itemLoc[i] == ag->room){  //checks if the item is in the room
            printf("You see %s here.\n",ag->itemArray[i]);
            printf("%s",ag->itemDesc[i]);
        }
    }
}

/*MOVE FUNCTION*/
int processMovement(adventureGame *ag){

    if(strcmp(ag->command,"north")==0||strcmp(ag->command,"n")==0){ //accepts north or n as input
        if (ag->moveToArray[ag->room][0]!=-1) { //checks if room exists
            ag->room=ag->moveToArray[ag->room][0]; //updates room
            printf("You are now in %s\n",ag->rooms[ag->room]);
            printf("%s",ag->roomDesc[ag->room]);

        }
        else printf("You can't go north from here!\n"); //error message
        return(1);
    }
    if(strcmp(ag->command,"south")==0||strcmp(ag->command,"s")==0){  //accepts south or s as input
        if (ag->moveToArray[ag->room][1]>-1) {
            ag->room=ag->moveToArray[ag->room][1];
            printf("You are now in %s\n",ag->rooms[ag->room]);
            printf("%s",ag->roomDesc[ag->room]);
        }
        else if (ag->moveToArray[ag->room][1]==-2){ //checks if room is locked
            printf("This room is locked...\n");
            printf("It seems like you need a Bronze Key to open it.\n");
        }
        else printf("You can't go south from here!\n");
        return(1);
        }

    //similar logic as above
     if(strcmp(ag->command,"east")==0||strcmp(ag->command,"e")==0){     //accepts east or e as input
        if (ag->moveToArray[ag->room][2]>-1) {
            ag->room=ag->moveToArray[ag->room][2];
            printf("You are now in %s\n",ag->rooms[ag->room]);
            printf("%s",ag->roomDesc[ag->room]);
        }
        else if (ag->moveToArray[ag->room][2]==-2){
            printf("This room is locked...\n");
            printf("It seems like you need a Copper Key to open it.\n");
        }
        else printf("You can't go east from here!\n");
        return(1);
        }
     if(strcmp(ag->command,"west")==0||strcmp(ag->command,"w")==0){     //accepts west or w as input
         if (ag->moveToArray[ag->room][3]!=-1) {
            ag->room=ag->moveToArray[ag->room][3];
            printf("You are now in %s\n",ag->rooms[ag->room]);
            printf("%s",ag->roomDesc[ag->room]);
        }
        else printf("You can't go west from here!\n");
        return(1);
        }
printf("Unknown command \"%s\" type \"help\" for list of commands. \n",ag->command);

}

/*UNLOCK DOOR*/
void unlockDoor(adventureGame *ag){
    if (((ag->room)==4) && (ag->itemLoc[7]==-2)) {  //checks if player is in the correct room and has the key
        if(ag->monsterStatusArray[4]>0){   //checks if monster is alive
            printf("The Werewolf blocks the door!\n");
            return;
        }
        ag->moveToArray[ag->room][1]=9;  //updates the movement function
        printf("You used the Bronze Key.\n");
        printf("Ka-chink!\n");
        --ag->inventory;    //updates inventory
        ag->itemLoc[7]=-1;  //removes key from game
        return;

    }
    //similar logic as above but without monster blocking path
    if (((ag->room)==11) && (ag->itemLoc[6]==-2)) {
        ag->moveToArray[ag->room][2]=12;
        printf("You insert the Copper Key.\n");
        printf("*click*\n");
        --ag->inventory;
        ag->itemLoc[6]=-1;
    }
    else printf("There are no doors to unlock here...\n");  //error message
}

/*KILL FUNCTION*/
void processDamageMonster(adventureGame *ag) {
    if (ag->monsterStatusArray[ag->room] == -1){  //checks if monster exists
        printf("There is nothing here to kill...\n");

    } else if (ag->monsterStatusArray[ag->room] == 0) {  //checks if monster is dead
        printf("%s", ag->monsterDead[ag->room]);

    } else if (ag->monsterStatusArray[ag->room] > 0){  //checks if monster is alive
        attackDamage(ag);   //damage calculation
        ag->monsterStatusArray[ag->room]-=crit(ag->damage);   //reduce monster health
        checkNegative(ag);

        if (ag->monsterStatusArray[ag->room]!=0){   //if monster isnt dead
            printf("The %s takes damage!\n", ag->monsterArray[ag->room]);
        }
        if (ag->monsterStatusArray[ag->room]==0){   //if monster is dead in combat
            printf("The %s falls to the ground...\n",ag->monsterArray[ag->room]);
            printf("%s",ag->monsterDeath[ag->room]);
        }
    }
    return;
}

/*ALTERNATE KILL FUNCTION*/
void alternateDamageMonster(adventureGame *ag) {  //same logic
    char *monsterName = &ag->command[5];  //scans monster name typed
    if (monsterName[0] == '\0') {
        printf("You can't kill something that doesn't exist...\n");
        return;
    }
        if (strcasecmp(monsterName, ag->monsterArray[ag->room]) == 0) {
            if (ag->monsterStatusArray[ag->room] == -1) {
                printf("There is nothing here to kill...\n");
                return;

            } else if (ag->monsterStatusArray[ag->room] == 0) {
                printf("%s", ag->monsterDead[ag->room]);
                return;

            } else if (ag->monsterStatusArray[ag->room] > 0) {
                attackDamage(ag);
                ag->monsterStatusArray[ag->room] -= crit(ag->damage);
                checkNegative(ag);
                processDamagePlayer(ag);
                checkNegative(ag);

                if (ag->monsterStatusArray[ag->room] != 0) {
                    printf("The %s takes damage!\n", ag->monsterArray[ag->room]);
                }

                if (ag->monsterStatusArray[ag->room] == 0) {
                    printf("The %s falls to the ground...\n", ag->monsterArray[ag->room]);
                    printf("%s",ag->monsterDeath[ag->room]);
                }
            }
        }

        else printf("Maybe you should try looking around...\n");


    return;
}

/*RNG + DAMAGE CALCULATION*/
int crit(int damage){ //critical hit for 2x damage
    double P =(double)rand()/RAND_MAX;
    if(P<=0.10){  //10% chance
        printf("You land a critical hit!\n");
        return 2*damage;  //returns twice the damage
    }
    return damage;  //if fail, return regular damage
}

/*RNG + DAMAGE MITIGATION*/
int dodge(int damage){  //DODGE FOR 0 DAMAGE
    double P =(double)rand()/RAND_MAX;
    if(P<=0.2){
        printf("You dodged the attack!\n");
        return 0*damage;
    }
    printf("You take damage!\n");
    return damage;
}
/*DAMAGE CALCULATION*/
int attackDamage(adventureGame *ag){
    ag->damage=1;
    for(int i=0;i<ag->totalRoom;i++){
        //DAMAGE FOR NEUTRAL CIRCUMSTANCES
        if(ag->itemLoc[i]==-2){  //checks if item is picked up
            if (strcasecmp(ag->itemArray[i], "Sword") == 0 && ag->damage<4){
                ag->damage=4;  //updates damage value
                }
            if (strcasecmp(ag->itemArray[i], "Silver Spear") == 0 && ag->damage<3){
                ag->damage=3;   //updates damage value
                }
            if (strcasecmp(ag->itemArray[i], "Diamond Cross") == 0 && ag->damage<2){
                ag->damage=2;   //updates damage value
                }
        }
    }
        //DAMAGE FOR SPECIAL CIRCUMSTANCES
        if(ag->itemLoc[11]==-2 && ag->room==4){  //for werewolf
            ag->damage=6;
        }
        if(ag->itemLoc[9]==-2 && (ag->room==6 || ag->room ==10)&& ag->damage<6){  //for dracula and bride with diamond cross
            ag->damage=6;
            return;
        }

        if(ag->itemLoc[5]==-2 && (ag->room==6 || ag->room ==10)){    //for dracula and bride without diamond cross
            ag->damage=2;
        }
}

/*KILL FUNCTION*/
int processDamagePlayer(adventureGame *ag){
    if (ag->monsterStatusArray[ag->room]>0){  //Zombie and Monster
        if ((ag->room == 2) ||(ag->room == 5)){
            ag->healthPoints-=dodge(1);
            checkNegative(ag);
        }
        if (ag->room == 9){ //Lizard-Man
            ag->healthPoints-=dodge(2);
            checkNegative(ag);
        }
        if(ag->room == 4){  //Werewolf
            ag->healthPoints-=dodge(4);
            checkNegative(ag);
        }
        if((ag->room == 6) || (ag->room == 10 )){ //Dracula and Dracula's Bride
            ag->healthPoints-=dodge(5);
            checkNegative(ag);
        }
        if(ag->room == 12){  //Dragon
            ag->healthPoints-=dodge(6);
            checkNegative(ag);
        }
    }
    else return;
    if (ag->healthPoints==0){
        printf("You died.\n");
        score(ag);
        printf("Score: %d",ag->exPoints);
        exit(0);
    }
    printf("Health: %d\n",ag->healthPoints);
}

/*NEGATIVE VALUE CHECKER*/
void checkNegative(adventureGame *ag){  //resets negative values to 0
    ag->monsterStatusArray[ag->room]= ag->monsterStatusArray[ag->room]>0 ? ag->monsterStatusArray[ag->room] : 0;  //is health greater than zero? if no set to 0
    ag->healthPoints= ag->healthPoints>0 ? ag->healthPoints: 0;  //same logic but for player health
}

/*ITEM FUNCTION*/
void processGet(adventureGame *ag) {
    char *itemName = &ag->command[4];  //scans item name typed by user
    for (int i = 0; i < ag->totalRoom; i++) {
        if (ag->inventory<3){   //checks if player carries more than 3 items
        if (strcasecmp(itemName, ag->itemArray[i]) == 0) {

            if((ag->room==6 || ag->room == 9 || ag->room == 12)&& ag->monsterStatusArray[ag->room]>0){  //checks if monster is alive in these rooms
                printf("It look's like it won't give the item up without a fight!\n");
                return;
            }
            if (ag->itemLoc[i]== ag->room) {  //checks if player is at the item location
                printf("You picked up the %s!\n", ag->itemArray[i]);
                ag->itemLoc[i] = -2;  //updates item location
                ag->inventory++;
                return;
            }

            else {
            printf("Maybe you should continue to look around...\n");
            return;
            }
        }
        }
        else{
            printf("Your inventory is full!\n");
            return;
        }
    }
    printf("You can't find that item...\n");
    return;
}

/*ITEM FUNCTION*/
void printInventory(adventureGame *ag){
    int i=0,j=0;
    printf("You are carrying: \n");
    for (i=0,j=0;i<ag->totalRoom;i++){   //iterate all rooms
        if (ag->itemLoc[i]==-2){        //checks which item has been picked up
            printf("%2d. %s\n",++j,ag->itemArray[i]);
        }
    }
    if (j==0){
        printf("Nothing\n");
        return;
    }
}

/*ITEM FUNCTION*/
void processDrop(adventureGame *ag) {
    char *itemName = &ag->command[5];  //scans item name typed by user

    if (ag->inventory == 0) {
        printf("You have nothing in your inventory...\n");
        return;
    }

    for (int i = 0; i < ag->totalRoom; i++) {
        if (ag->itemLoc[i] == -2) {  //checks if item is in players inventory
            if (strcasecmp(itemName, ag->itemArray[i]) == 0) {  //compare item name typed and actual item name
                printf("You dropped the %s!\n", ag->itemArray[i]);
                ag->itemLoc[i] = ag->room;  //updates item location
                --ag->inventory;
                return;
            }
        }
    }
    printf("You don't have %s in your inventory!\n",itemName);
    return;
}

/*HEALING FUNCTION*/
void processEat(adventureGame *ag){
    char *itemName = &ag->command[4];   //scans item name typed
    if (itemName[0] == '\0') {
        printf("You are literally eating air.\n");
        return;
    }
    if(ag->healthPoints==12 && ag->itemLoc[1]==-2 && strcasecmp(itemName,"Food")==0){  //checks to see if player is full health
        printf("That wouldn't have any effect.\n");
        return;
    }
    if(ag->itemLoc[1]==-2){
        if(strcasecmp(itemName,"Food")==0){  //checks if item name typed matches actual item name
            ag->healthPoints+=5;   //adds health
                checkHealth(ag);
                printf("You ate the food and regained some stamina!\n");
                --ag->inventory;  //remove from inventory
                ag->itemLoc[1]=-1;  //remove from game
        }
        else printf("You can't eat that...\n");
    }
    else if(ag->itemLoc[1]==-1){
        printf("You don't have any food left!\n");
    }
    else if(ag->itemLoc[1]>0){
        printf("You don't have any eatable items!\n");
    }
}

/*HEALING FUNCTION*/
void processUse(adventureGame *ag){  //same logic
    char *itemName = &ag->command[4];
    if (itemName[0] == '\0') {
        printf("You used....nothing.\n");
        return;
    }
    if(ag->healthPoints==12 && ag->itemLoc[3]==-2 && strcasecmp(itemName,"Medpack")==0){
        printf("That wouldn't have any effect.\n");
        return;
    }
    if(ag->itemLoc[3]==-2){
        if(strcasecmp(itemName,"Medpack")==0){
            ag->healthPoints+=10;
                checkHealth(ag);
                printf("You used the medpack and closed up your wounds!\n");
                --ag->inventory;
                ag->itemLoc[3]=-1;
        }
        else printf("You can't use that...\n");
    }
    else if(ag->itemLoc[3]==-1){
        printf("You don't have any medpacks left!\n");
    }
    else if(ag->itemLoc[3]>0){
        printf("You don't have any usable items!\n");
    }
}

/*HEALING FUNCTION*/
void processDrink(adventureGame *ag){  //same logic
    char *itemName = &ag->command[6];
    if (itemName[0] == '\0') {
        printf("Tastes like nothing. Did you forget to pour a potion into the cup?\n");
        return;
    }
    if(ag->healthPoints==12 && ag->itemLoc[8]==-2 && strcasecmp(itemName,"Elixir")==0){
        printf("That wouldn't have any effect.\n");
        return;
    }
    if(ag->itemLoc[8]==-2){
        if(strcasecmp(itemName,"Elixir")==0){
            ag->healthPoints+=10;
                checkHealth(ag);
                printf("You drank the elixir and feel rejuvenated!\n");
                --ag->inventory;
                ag->itemLoc[8]=-1;
        }
        else printf("You can't drink that...\n");
    }
    else if(ag->itemLoc[8]==-1){
        printf("You don't have any elixir left!\n");
    }
    else if(ag->itemLoc[8]>0){
        printf("You don't have any drinkable items!\n");
    }
}

/*HEALTH CHECKER*/
void checkHealth(adventureGame *ag){  //reset values beyond max hp to 12
    ag->healthPoints = ag->healthPoints>12 ? 12 : ag->healthPoints;  //is player health beyond max? if yes set to 12
}

/*STATISTICS FUNCTION*/
void stats(adventureGame *ag){
    score(ag);
    printf("Health: %d\n",ag->healthPoints);  //displays health
    monsterSlain(ag);
}

void monsterSlain(adventureGame *ag){
    int kills=0;
    for(int i=0;i<ag->totalRoom;i++){
        if(ag->monsterStatusArray[i]==0){  //checks for dead monsters
            kills++;
        }
    }
    printf("Monsters Slain: %d\n",kills);
}

/*SCORE CALCULATION*/
void score(adventureGame *ag){
    for(int i=0;i<ag->totalRoom;i++){  //loops through every room
        if(ag->monsterStatusArray[i]==0){  //checks for dead monsters
            ag->exPoints+=ag->exMonsterValue[i];  //adds experience points for monster
        }
    if(ag->itemLoc[i]==-2){  //checks for items in inventory
        ag->exPoints+=ag->exItemValue[i];  //adds experience points for item in inventory
    }
    }
}


/*WIN AND EXIT FUNCTION*/
void winCondition(adventureGame *ag){
    if(ag->room==0 && ag->itemLoc[12]==-2){  //checks if player is in the correct room and has golden chalice
        printf("You win!\n");
        score(ag);  //calculates score
        printf("Score: %d\n",ag->exPoints);
        monsterSlain(ag);  //calculates monster slain
        exit(0);
    }
}

/*EXIT FUNCTION*/
void exitMessage(adventureGame *ag){  //Function to print exit message
    printf("You exit the game.\n");
    printf("Score: %d\n",ag->exPoints);
    monsterSlain(ag);
}




