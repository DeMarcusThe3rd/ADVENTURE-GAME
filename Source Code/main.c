#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CW2.h"


int main()
{
    adventureGame ag={ //Initialization of members in struct
    /*MOVE ARRAYS*/
    .totalRoom=13,
    .rooms={
            {"The Grand Hall"},           //ROOM 1
            {"The Pantry"},               //ROOM 2
            {"The Graveyard"},            //ROOM 3
            {"The Medical Bay"},          //ROOM 4
            {"The Forbidden Prison"},     //ROOM 5
            {"The Armoury"},              //ROOM 6
            {"Dracula's Lair"},           //ROOM 7
            {"The Living Room"},          //ROOM 8
            {"The Lab"},                  //ROOM 9
            {"The Church"},               //ROOM 10
            {"The Altar Room"},           //ROOM 11
            {"Secret Armoury"},           //ROOM 12
            {"The Dragon's Den"},         //ROOM 13


    },
    .moveToArray={
        //NORTH --> SOUTH --> EAST --> WEST
                {-1,5,1,-1},   //ROOM 1
                {-1,-1,2,0},   //ROOM 2
                {-1,7,3,1},    //ROOM 3
                {-1,8,4,2},    //ROOM 4
                {-1,-2,-1,3},  //ROOM 5
                {0,-1,-1,-1},  //ROOM 6
                {-1,10,7,-1},  //ROOM 7
                {2,11,8,6},    //ROOM 8
                {3,-1,-1,7},   //ROOM 9
                {4,-1,-1,-1},  //ROOM 10
                {6,-1,11,-1},  //ROOM 11
                {7,-1,-2,10},  //ROOM 12
                {-1,-1,-1,11}, //ROOM 13

    },

    /*LOOK ARRAY*/
    .direction={
                {"North"},
                {"South"},
                {"East"},
                {"West"},
    },

    .roomDesc= {
                {"You breathe in the air, as a sense of grandeur washes over you.\n"},                                                                 //ROOM 1
                {"The air is infused with the aroma of wholesome ingredients, appeasing your appetite.\n"},                                            //ROOM 2
                {"A haunting silence lingers, the air heavy with the weight of history.\n"},                                                           //ROOM 3
                {"You feel a sense of serenity washing over you, promising relief and recovery.\n"},                                                   //ROOM 4
                {"Stone walls echo with distant whispers, and the air is heavy with an ominous stillness.\n"},                                         //ROOM 5
                {"The scent of leather and steel fills the room as you prepare for the challenges that lie ahead.\n"},                                 //ROOM 6
                {"The air is thick with an eerie silence, as the sound of your heartbeat echoes throughout the room.\n"},                              //ROOM 7
                {"You see dusty furnitures draped in tattered sheets, the once vibrant living space which has surrendered to the passage of time.\n"}, //ROOM 8
                {"The air crackles with intellectual curiosity and the potential for groundbreaking discoveries.\n"},                                  //ROOM 9
                {"You feel a sense of tranquility, a subtle scent of aged wood and candle wax fills the air, evoking a sense of sacred history.\n"},  //ROOM 10
                {"You see an altar as the centerpiece of the room, urging you to connect with the spiritual essence that permeates the room.\n"},      //ROOM 11
                {"A secret room that hosts many dangerous weapons, you feel a force of nature locked behind the doors in front.\n"},                   //ROOM 12
                {"The air crackles with the distant rumble of slumbering beasts, and the scent of smoldering embers hangs in the atmosphere.\n"},      //ROOM 13
    },

    /*FIGHT ARRAYS*/
    .monsterArray={
                    {""},                   //ROOM 1
                    {""},                   //ROOM 2
                    {"zombie"},             //ROOM 3
                    {""},                   //ROOM 4
                    {"Werewolf"},           //ROOM 5
                    {"monster"},            //ROOM 6
                    {"Dracula"},            //ROOM 7
                    {""},                   //ROOM 8
                    {""},                   //ROOM 9
                    {"Lizard-Man"},         //ROOM 10
                    {"Dracula's Bride"},    //ROOM 11
                    {""},                   //ROOM 12
                    {"Dragon"},             //ROOM 13
    },

    .monsterDesc={  //ROOM 1 --> ROOM 13
                    {""},
                    {""},
                    {"It looks like it is hungry for your brains...\n"},
                    {""},
                    {"The bloodlust of the werewolf awakens under the silver glow of the full moon!\n"},
                    {"It seems like it is asleep...\n"},
                    {"You feel the sins crawling up your back.\n"},
                    {""},
                    {""},
                    {"A scaley creature appears!\n"},
                    {"You feel the sins crawling up your back...again...\n"},
                    {""},
                    {"The fiery breathe of the dragon makes you sweat buckets, whereas it's ferocious nature makes you tremble in fear.\n"},

    },

    .monsterDeath={   //ROOM 1 --> ROOM 13
                    {""},
                    {""},
                    {"The undead is dead once again...or is it?\n"},
                    {""},
                    {"I guess the predator does becomes the prey.\n"},
                    {"It was so innocent...\n"},
                    {"*poof* He vanishes into the night...\n"},
                    {""},
                    {""},
                    {"Couldn't he regenerate from that?\n"},
                    {"*poof* She vanishes into th- oh never mind shes still here.\n"},
                    {""},
                    {"The mighty dragon breathes its last, wings sagging as its fiery spirit is extinguished.\n"},
    },

    .monsterDead={   //ROOM 1 --> ROOM 13
                    {""},
                    {""},
                    {"I did say it might not be dead but it most likely is.\n"},
                    {""},
                    {"You attack the corpse...it's definitely dead.\n"},
                    {"Stop,stop! He's already dead!\n"},
                    {"He literally vanished in front of you.\n"},
                    {""},
                    {""},
                    {"Just to be sure I suppose...\n"},
                    {"You are just sadistic.\n"},
                    {""},
                    {"You break into his den and stole his riches I think it suffered enough...\n"},
    },

    .monsterStatusArray={-1,-1,5,-1,12,4,12,-1,-1,5,7,-1,12}, //ROOM 1 --> ROOM 13

    /*ITEM ARRAYS*/
    .inventory=0,
    .itemLoc={-1,1,-1,3,-1,5,6,7,8,9,-1,11,12},
    .itemArray={
                {""},                   //ROOM 1
                {"Food"},               //ROOM 2
                {""},                   //ROOM 3
                {"Medpack"},            //ROOM 4
                {""},                   //ROOM 5
                {"Sword"},              //ROOM 6
                {"Copper Key"},         //ROOM 7
                {"Bronze Key"},         //ROOM 8
                {"Elixir"},             //ROOM 9
                {"Diamond Cross"},      //ROOM 10
                {""},                   //ROOM 11
                {"Silver Spear"},       //ROOM 12
                {"Golden Chalice"},     //ROOM 13
    },

    .itemDesc={   //ROOM 1 --> ROOM 13
                {""},
                {"It looks delicious!\n"},
                {""},
                {"Good ol' reliable for closing up wounds.\n"},
                {""},
                {"It gleams in the dark, awaiting it's next worthy wielder.\n"},
                {"Maybe it unlocks a door somewhere?\n"},
                {"Maybe it unlocks a door somewhere?\n"},
                {"Who knows how long its been there...Is it even safe to drink?\n"},
                {"It is imbued with a sacred power that vanquishes evil..."},
                {""},
                {"Wait are Dracula's weak to silver or Werewolves?\n"},
                {"I could get rich selling that on e-Bay.\n"},
    },
    /*DAMAGE ARRAYS*/
    .healthPoints = 12,
    .damage=1,

    /*EXPERIENCE POINTS ARRAYS*/
    .exPoints = 0,
    .exMonsterValue={0,0,100,0,500,120,500,0,0,125,330,0,1000},
    .exItemValue={0,5,0,10,0,400,20,20,10,240,0,400,1000},
    /*HELP ARRAYS*/
    .helpCommands = {
                    {"MOVEMENT COMMANDS"},
                    {"LOOK COMMANDS"},
                    {"FIGHT COMMANDS"},
                    {"GET COMMANDS"},
                    {"DROP COMMANDS"},
                    {"INVENTORY COMMANDS"},
                    {"HEAL COMMANDS"},
                    {"UNLOCKING DOORS"},
                    {"STATISTICS"},
                    {"EXIT GAME"},
    },
    .subHelpCommands = {
                    {"north, n, south, s, east, e, west, w"},
                    {"look,l"},
                    {"killMonster,killmonster,km, kill (monster name)"},
                    {"get (item name)"},
                    {"drop (item name)"},
                    {"inventory, i"},
                    {"eat food, drink elixir, use medpack"},
                    {"unlock door"},
                    {"stats"},
                    {"exit"},
    },
    };
    printf("Welcome to the adventure game\n");
    printf("Type \"help\" to view a list of commands!\n");
    printf("Start your adventure!\n");
    srand(time(NULL));
        while (fgets(ag.command,1000,stdin)){
            printf("+----------------------------------------------------------------------------------------------------------------------+\n");
            repeatCommand(&ag);
            if (processCommand(&ag)==0) break;
            printf("+----------------------------------------------------------------------------------------------------------------------+\n");
        }
}

