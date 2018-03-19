#pragma once
#include <string>
#include <iostream>
using FString = std::string;
using int32 = int;

// all values initialized to zero
struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase,
    Invalid_Character
};

class FBullCowGame {
public:
    FBullCowGame();

    int32 GetMaxTries() const;
    bool IsGameWon() const;
    int32 GetCurrentTry() const;
    FString GetHiddenWord() const;
    int32 GetHiddenWordLength() const;
    EGuessStatus CheckGuessValidity(FString) const;
    bool CheckInvalidCharacters(FString) const;
    void Reset();  // TODO make a more rich return value.
    
    // provide a method for counting bulls & cows, and increasing turn #

    // counts bulls & cows, and increases try # assuming valid guess
    FBullCowCount SubmitValidGuess(FString);
private:
    int32 MyCurrentTry;
    int32 MyMaxTries;
    FString MyHiddenWord;
    FString MyInvalidCharacters;
    //FString MyCurrentGuess;
    bool bGameWon;
};