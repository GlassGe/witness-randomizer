# Witness Random Puzzle Generator (WitnessRPG)
The WitnessRPG takes many of the puzzles in Jonathan Blow's "The Witness" and makes them into new, randomly generated puzzles. The mod requires the game in order to function. No game files will be altered, as the randomizer works enterly in RAM. This mod uses WinAPI, so it is only compatible with Microsoft Windows.

This project is a fork of jbzdarkid's puzzle randomizer at https://github.com/jbzdarkid/witness-randomizer. His discoveries about how puzzle data is encoded in The Witness were invaluable to this project, so a huge thank you to jbzdarkid for his contributions.

**How to use the Witness Random Puzzle Generator:**

1. Launch The Witness
2. Start a New Game
3. Launch WitnessRPG.exe (from any location)
4. Choose difficulty and seed (leave seed blank for random)
5. Click "Randomize" and wait for the process to complete
6. Enjoy your randomly created puzzles! Puzzles will revert to normal after closing the game.

**To resume where you left off after closing and relaunching the game:**

1. Load the save you were previously playing on, if it is not already loaded
2. Launch WitnessRPG.exe (from any location)
3. Click "Randomize" and wait for the process to complete. You don't have to enter the seed or difficulty again. This is because the seed and difficulty were stored in your save file when you randomized initially, so they will be automatically restored and used.


**If you get stuck on a puzzle,** the solver provided in the "Solver" folder (WitnessPuzzle.exe) might be able to help you. However I can't guarantee it will always work correctly, and there are some mechanics it doesn't handle at the moment. Another option if you get stuck is to exit and reopen the game, solve the puzzle the normal way, then run the randomizer again.

Please report any issues (such as unsolvable/broken puzzles) on the issues page. **However, please read the "Issues" section in the wiki first, as your issue may be addressed there.**

Thanks for playing this mod, and good luck!
