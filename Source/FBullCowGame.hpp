//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Craig O'Donnell on 1/16/17.
//  Copyright © 2017 Craig O'Donnell. All rights reserved.
//

/*
    This is the definition of the FBullCowGame class
 */

#pragma once

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <string>

#endif /* FBullCowGame_hpp */

// to make more Unreal friendly
using FString = std::string;
using int32 = int;

// Initializes these two counters to zero
struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

// creates enumeration of possible guess statuses
enum class EGuessStatus
{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase,
};

class FBullCowGame {
public:
    
    FBullCowGame(); // Constructor
    
    int32 getMaxTries() const;
    int32 getCurrentTry() const;
    FString getHiddenWord() const;
    bool isGameWon(FString) const;
    EGuessStatus checkGuessValidity(FString) const;
    
    void printGameSummary(bool isGameWon);
    void reset();
    FBullCowCount SubmitGuess(FString);
    
private:
    // See constructor for initialization
    int32 myCurrentTry; // redundant...
    FString myHiddenWord;
    bool isIsogram(FString) const;
    bool isLowercase(FString) const;
};
