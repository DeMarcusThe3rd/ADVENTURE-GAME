# How to Run the Program

## On Windows

1. **Install a C Compiler**:
   - If you don't have one, install a C compiler like MinGW or use an IDE like Code::Blocks or Visual Studio.

2. **Compile the Code**:
   - Open Command Prompt or the terminal in your IDE and navigate to the folder containing the source files.
   - Use the following command with MinGW:
     ```sh
     gcc -o adventuregame main.c adventuregame.c
     ```

3. **Run the Executable**:
   - After compiling, you can run the program by executing the generated file:
     ```sh
     adventuregame.exe
     ```

4. **Follow On-Screen Instructions**:
   - The program will provide instructions and prompts for user input. Follow these prompts to play the game.

## On Linux

1. **Compile the Code**:
   - Use a C compiler like `gcc`. Open the terminal and navigate to the folder containing the source files.
   - Use the following command:
     ```sh
     gcc -o adventuregame main.c adventuregame.c
     ```

2. **Run the Executable**:
   - After compiling, you can run the program by executing the generated file:
     ```sh
     ./adventuregame
     ```

3. **Follow On-Screen Instructions**:
   - The program will provide instructions and prompts for user input. Follow these prompts to play the game.

# General Working

## main.c
- **Initialization**: Sets up the game environment.
- **User Input Handling**: Reads user inputs and passes them to the game logic for processing.
- **Game Loop**: Runs the main game loop, updating the game state and displaying results to the user.

## adventuregame.c
- **Game Mechanics**: Contains the core logic for the game, including player actions, game events, and outcomes.
- **Interaction Handling**: Processes user commands and updates the game state accordingly.
- **Utility Functions**: Includes various helper functions to support the game mechanics.

## adventuregame.h
- **Function Prototypes**: Declares the functions implemented in adventuregame.c.
- **Macros**: Defines constants and macros used throughout the game.

For a more detailed and in-depth explanation on the workings of the code, a PDF titled "Report 2" can be found and accessed in this folder.
