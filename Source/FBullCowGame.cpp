//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Craig O'Donnell on 1/16/17.
//  Copyright © 2017 Craig O'Donnell. All rights reserved.
//

/*
    These are the methods of the FBullCowGame class
 */

#pragma once

#include "FBullCowGame.hpp"
#include <iostream>
#include <map>

#define TMap std::map // to make more Unreal friendly



// -- CONSTRUCTOR -- //
FBullCowGame::FBullCowGame() {
    reset();
}

// reset function
void FBullCowGame::reset()
{
    const int32  MAX_TRIES = getMaxTries();
    myCurrentTry = MAX_TRIES;
    
    const FString HIDDEN_WORD = "plane"; // this MUST be an isogram
    myHiddenWord = HIDDEN_WORD;
    
    return;
}


// -- GETTERS (ALSO METHODS) -- //

int32 FBullCowGame::getMaxTries() const
{   // TODO: Revise this based on difficulty and number of tries
    TMap<int32, int32> WordLengthToMaxTries {{3,5}, {4,7}, {5,10}, {6,15}, {7,23}}; // This initializes the map
    return WordLengthToMaxTries[myHiddenWord.length()];
}

int32 FBullCowGame::getCurrentTry() const
{
    return myCurrentTry;
}

FString FBullCowGame::getHiddenWord() const
{
    return myHiddenWord;
}

bool FBullCowGame::isGameWon(FString guess) const
{
    if (guess == myHiddenWord) {
        return true;
    }
    else {
        return false;
    }
}

bool FBullCowGame::isIsogram(FString guess) const {
    // Treat 0 and 1 letter words as isograms
    if (guess.length() <= 1) {
        return true;
    }
    
    // Set up map
    TMap<char, bool> LetterSeen;
    
    // Loop through letters in word
    for (auto Letter : guess) {
        Letter = tolower(Letter);
        // if letter is in dictionary/map
        if (LetterSeen[Letter]) {
            // we do not have an isogram
            return false;
        }
        else {
            // add letter to map
            LetterSeen[Letter] = true;
        }
    }

    
    return true;
}

bool FBullCowGame::isLowercase(FString guess) const {
    for (auto Letter : guess) {
        if (!islower(Letter)) {
            return false;
        }
    }
    return true;
}

EGuessStatus FBullCowGame::checkGuessValidity(FString guess) const
{
    int32 hiddenWordLength = myHiddenWord.length();
    int32 guessLength = guess.length();
    bool isGuessIsogram = isIsogram(guess);
    bool isGuessLowercase = isLowercase(guess);
    
    if (!isGuessIsogram) {
        return EGuessStatus::Not_Isogram;
    }
    else if (!isGuessLowercase) {
        return EGuessStatus::Not_Lowercase;
    }
    else if (guessLength != hiddenWordLength){
        return EGuessStatus::Wrong_Length;
    }
    else {
        return EGuessStatus::OK;
    }
}


// -- METHODS -- //

// Receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString guess)
{
    // increment turns left
    myCurrentTry--;
    
    // setup return variable
    FBullCowCount BullCowCount;
    
    // performs the bull cow check
    int32 hiddenWordLength = myHiddenWord.length();
    int32 guessLength = guess.length(); // Should be the same as above, but for now this is safer
    
    for (int32 MHWFactor = 0; MHWFactor < hiddenWordLength; MHWFactor++) {
        for (int32 GFactor = 0; GFactor < guessLength; GFactor++) {
            if (myHiddenWord[MHWFactor] == guess[GFactor]) {
                if (MHWFactor == GFactor) {
                    BullCowCount.Bulls++;
                }
                else {
                    BullCowCount.Cows++;
                }
            }
            else {
                // nothing happens
            }
        }
    }
    // loop through all letters in the guess
        // compare letters against the hidden word
    return BullCowCount;
}

// Prints a summary of the game
void FBullCowGame::printGameSummary(bool isGameWon)
{
    if(isGameWon) {
        std::cout << "Congratulations! You have won the game." << std::endl;
    }
    else {
        std::cout << "You are out of guesses!" << std::endl;
    }
    std::cout << std::endl;
    return;
}
