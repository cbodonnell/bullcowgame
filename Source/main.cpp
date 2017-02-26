//
//  main.cpp
//  BullCowGame
//
//  Created by Craig O'Donnell on 1/15/17.
//  Copyright © 2017 Craig O'Donnell. All rights reserved.
//

/*
 BullCowGame
 This is a word game where the user tries to guess a hidden word. This will be used in the Escape the Room game.
 
 This acts as the view in the MVC pattern and is responsible for all user interaction. For game logic, see the FBullCowGame class.
 */



#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

using namespace std; // don't get in the habit of doing this...

// to make syntax Unreal friendly
using FText = string;
using int32 = int;

// -- PROTOTYPES -- // these can generally be added via header file

void printIntro();
FText getValidGuess();
void repeatGuess(FText Guess);
void remainingGuesses(int32 guessNum);
void playGame();
bool askPlayAgain();

// Create an instance of the game that is REUSED throughout game
FBullCowGame GAME;

// -- MAIN FUNCTION -- //

int main() {
    // Main function (entry point) of program
    do {
        printIntro();
        playGame();
    }
    while (askPlayAgain()); // continues to loop so long as the (condition) is TRUE
    return 0; // Exit the application
}

// -- FUNCTIONS -- //

void printIntro() {
    // Introduce the game
    FText hiddenWord = GAME.getHiddenWord();
    const int32 WORD_LENGTH = hiddenWord.length();
    cout << "\nWelcome to Bulls and Cows\n";
    cout << "Can you guess the " << WORD_LENGTH;
    cout << " letter isogram I'm thinking of?\n";
    cout << endl;
    return;
}

// loop until user gives a valid guess
FText getValidGuess() {
    
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText guess;
    
    do {
        // Get a guess from the player
        cout << "Type your guess here: ";
        guess = "";
        getline (cin,guess); // using getline takes entire line of input and writes to a variable
        
        Status = GAME.checkGuessValidity(guess);
        switch (Status) {
            case EGuessStatus::Wrong_Length:
                cout << "\nPlease enter a " << GAME.getHiddenWord().length() << " letter word.\n" << endl;
                break;
            case EGuessStatus::Not_Lowercase:
                cout << "\nPlease use lowercase letters.\n" << endl;
                break;
            case EGuessStatus::Not_Isogram:
                cout << "\nPlease enter an isogram (no repeating letters).\n" << endl;
                break;
            default:
                break;
        }
    } while (Status != EGuessStatus::OK); // loop until we would get no errors
    
    return guess;
}

void repeatGuess(FText Guess) {
    // Repeat guess back to the player
    cout << endl;
    cout << "Your guess was " << Guess << ".";
    cout << endl;
    return;
}

void remainingGuesses(int32 guessNum) {
    // States number of guesses remaining to the player
    cout << "Guesses remaining: " << guessNum << ".\n\n";
    return;
}

// plays a single game to completion
void playGame() {
    // Sets game to its default state
    GAME.reset();
    
    // this is the code for the game itself
    bool isGameWon;
    
    do {
        // States number of guesses remaining
        int32 guessesRemaining = GAME.getCurrentTry();
        remainingGuesses(guessesRemaining);
        
        // Gets the guess from the user
        FText guess = getValidGuess();
        
        // Submit valid guess to the game
        FBullCowCount BullCowCount = GAME.SubmitGuess(guess);
        
        // Read guess back to user
        repeatGuess(guess);
        
        // Print number of bulls and cows
        cout << "Bulls: " << BullCowCount.Bulls << endl;
        cout << "Cows: " << BullCowCount.Cows << endl;
        cout << endl;
        
        isGameWon = GAME.isGameWon(guess);
        
    } while (!isGameWon && GAME.getCurrentTry() > 0);
    
    // Print game summary
    GAME.printGameSummary(isGameWon);
    
    return;
}

bool askPlayAgain() {
    // asks player if they want to play again
    cout << "Do you want to play again (y/n)? ";
    FText response = "";
    getline(cin, response);
    return (response[0] == 'y') || (response[0] == 'Y'); // performs OR conditional to return a boolean
}
