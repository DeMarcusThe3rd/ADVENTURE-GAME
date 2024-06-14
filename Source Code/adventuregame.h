//adventure game struct
typedef struct adventureGame { //Declaration of members in the struct
    /*COMMAND MEMBERS*/
    const char* helpCommands[10];
    const char* subHelpCommands[10];
    char command[1000];// Command typed by the user
    char buffer[1000]; //Buffer to store previous command typed

    /*MOVE OR ROOM MEMEBRS*/
    int room; // The room the user is in
    const char* rooms[13];  //name of the rooms
    const char* roomDesc[13]; //description of room
    int moveToArray[13][4]; //validity of the direction they can move to
    const char* direction[4];  //direction the player went or will go
    const int totalRoom; //total room in the game

    /*MONSTER MEMBERS*/
    const char * monsterArray[13];  //name of monsters
    int monsterStatusArray[13];  //health or status of the monster
    const char* monsterDesc[13];  //description of the monsters
    const char* monsterDeath[13]; //death message for monster
    const char* monsterDead[13]; //message if its already dead

    /*ITEM MEMBERS*/
    int inventory;  //number of items in inventory
    int itemLoc[13];  //location of items
    const char *itemArray[13];  //name of items
    const char* itemDesc[13];  // description of items

    /*DAMAGE MEMBERS*/
    int healthPoints;  //health points
    int damage;  //damage of weapon

    /*SCORE MEMBERS*/
    int exPoints;   //experience points
    int exMonsterValue[13];  //experience points given by each monster
    int exItemValue[13];  //experience points given by each item

}adventureGame;

//function definitions

/*COMMANDS FUNCTION*/
void repeatCommand(adventureGame *ag);  //repeats last command if nothing is typed
void replaceNewLine(adventureGame *ag);  //replaces new line generated with end of string character
int processCommand(adventureGame *ag);  //scans command typed
void help(adventureGame *ag);  //displays series of available commands in the game

/*ROOM FUNCTIONS*/
void processLook(adventureGame *ag);  //describes area around you
int processMovement(adventureGame *ag); //movement commands
void unlockDoor(adventureGame *ag);  //unlocks door when conditions are met

/*DAMAGE FUNCTIONS*/
void processDamageMonster(adventureGame *ag);  //damage dealt to monster
void alternateDamageMonster(adventureGame *ag);  //alternate kill command
int processDamagePlayer(adventureGame *ag);  //damage dealt by monsters
void checkNegative(adventureGame *ag);  //checks if health is less than 0 for monster and player
void checkHealth(adventureGame *ag);  //checks if health is more than max
int attackDamage(adventureGame *ag);  //calculates damage dealt to monsters
int crit(int damage);  //rng crit damage calculation
int dodge(int damage);  //rng dodge chance calculation

/*INVENTORY FUNCTIONS*/
void processGet(adventureGame *ag);  //picking up items
void processDrop(adventureGame *ag); //dropping items
void printInventory(adventureGame *ag); //displays inventory

/*HEALING FUNCTIONS*/
void processEat(adventureGame *ag);  //eat food
void processUse(adventureGame *ag);  //use medpack
void processDrink(adventureGame *ag);  //drink elixir

/*SCORE AND EXIT*/
void stats(adventureGame *ag);  //displays health,score, monsters slain
void score(adventureGame *ag);  //calculates score
void winCondition(adventureGame *ag); //message printed when win conditions are met
void exitMessage(adventureGame *ag);  //normal exit message




