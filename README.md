# ComputerProgramming-Lab1-DiceGames-HT2021
The program utilizes the C Standard General Utilities Library (stdlib.h) and Time Library (time.h) for random number generation and basic utilities. The Windows-specific header (windows.h) is used for system-specific functions like Sleep, and conio.h for console input/output.

Key features include:

Dice Rolling Functions: roll2Dice rolls two dice and returns their sum, while roll1Dice rolls a single dice.
Game Implementations:
craps: A classic dice game where players bet on roll outcomes.
abyss: A game involving specific rules and conditions based on dice rolls.
pigs: A simpler dice game focused on accumulating points up to a target score.
Game Mechanics: Each game has specific rules and mechanics, implemented in separate functions.
Main Menu: The displayMainMenu function provides a user interface for selecting different games.
Game Loop: The main function includes a loop that keeps the program running, allowing users to choose different games or exit.
