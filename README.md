# Higher-Or-Lower Game in C (for SEEM3460 course project)

This is a project for the SEEM3460 Computer Processing Systems Concepts course at The Chinese University of Hong Kong. 
The objective of this assignment is to complete the game “Higher-Or-Lower” in C by implementing several methods. 

## Getting Started

### Prerequisites

- GTK library
- Linux platform

### Installing

1. Clone the repository
```
git clone https://github.com/diatomicc/seem3460.git
```
2. Change directory to the project folder
```
cd <repository-name>
```
3. Compile the program
```
make main
```
4. Run the program
```
./main
```

## Usage

- At the beginning of a new game, one card is dealt to each player.
- The game has 9 rounds. In each round, an extra card will be dealt to each player.
- Before the card is dealt, the player guesses whether the coming card is higher or lower than his opponent’s last card dealt by clicking the “Higher” or “Lower” button.
- A correct guess wins 10 points while a wrong guess loses 5 points. All players start from zero points. After the rounds, the player who scores most points wins.
- The “New Game” button, whenever it is clicked, should reset everything and start a new game. The “Quit Game” button should close the game window.

## Program Structure

The program consists of three main files:

1. `main.c`: This file contains the main function of the program and should not be modified unless necessary. It calls the functions in `gui.c` and `highlow.c` to run the game logic and create the GUI.

2. `gui.c`: This file contains functions related to creating and modifying the GUI elements of the program. It includes functions such as `clear_child` to clear all images in a container, `set_prompt` to display the game prompt, and `activate` to register all GUI components. 

3. `highlow.c`: This file contains functions related to the game logic of the Higher-Or-Lower game. It includes functions such as `add_new_card` to add a specific card image into a container, `card_shuffle` to shuffle the card deck, `higher_lower` to handle user input for the Higher or Lower button, and `new_game` to start a new game.

In addition to these three main files, the program also includes a `gui.h` header file that defines the functions in `gui.c`. This file should be modified if necessary to add new functions or modify existing ones. 

The program also includes a `makefile` that is used to compile the program. To compile the program, run the command `make main`. To run the program, use the command `./main`.

The program uses the GTK library to create the GUI, and it is important to note that it can only be compiled and run on a Linux platform.


### Usage

The game is played by 2 human players. At the beginning of a new game, one card is dealt to each player. The game has 9 rounds. In each round, an extra card will be dealt to each player. Before the card is dealt, the player guesses whether the coming card is higher or lower than his opponent’s last card dealt by clicking the “Higher” or “Lower” button. A correct guess wins 10 points while a wrong guess loses 5 points. All players start from zero points. After the rounds, the player who scores most points wins.

The “New Game” button, whenever it is clicked, should reset everything and start a new game. The “Quit Game” button should close the game window.


### Authors

- Juhee Hur

### Acknowledgments

- [SEEM3460 Course Website](http://www.se.cuhk.edu.hk/~seem3460)
- [Graham Glass and King Ables. Unix for Programmers and Users. Prentice Hall.](https://www.pearson.com/us/higher-education/program/Glass-Unix-for-Programmers-and-Users-3rd-Edition/PGM314641.html)
- [William Stallings. Operating Systems Internals and Design Principles. Prentice Hall.](https://www.pearson.com/us/higher-education/program/Stallings-Operating-Systems-Internals-and-Design-Principles-9th-Edition/PGM2088727.html)
- [Mark Sobell. A Practical Guide to Linux Commands: Editors, and Shell Programming. Prentice Hall.](https://www.pearson.com/us/higher-education/program/Sobell-Practical-Guide-to-Linux-Commands-Editors-and-Shell-Programming-4th-Edition/PGM334550.html)
