#include "FBullCowGame.h"

void FBullCowGame::Reset()
{
    constexpr int32 MAX_TRIES = 8;
    MyMaxTries = MAX_TRIES;

    const FString HIDDEN_WORD = "planet";
    MyHiddenWord = HIDDEN_WORD;

    const FString INVALID_CHARACTERS = "!@#$%^&*()_+1234567890-={}[] ";
    MyInvalidCharacters = INVALID_CHARACTERS;
    
    MyCurrentTry = 1;
    //MyCurrentGuess = "";
    bGameWon = false;
    return;
}

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }


bool FBullCowGame::IsGameWon() const
{
    return bGameWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (false)// if the guess isn't an isogram, return error Not_Isogram
    {
        return EGuessStatus::Not_Isogram;
    }
    // if the guess isn't all lowercase
    else if (false) 
    {
        return EGuessStatus::Not_Lowercase;
    } 
    // if the guess length is wrong
    else if (Guess.length() != GetHiddenWordLength()) 
    {
        return EGuessStatus::Wrong_Length;
    }
    // if the guess contains invalid characters
    else if (CheckInvalidCharacters(Guess))
    {
        return EGuessStatus::Invalid_Character;
    }

    return EGuessStatus::OK; // TODO make actual error
}

bool FBullCowGame::CheckInvalidCharacters(FString Guess) const
{
    for (int32 i = 0; i < MyInvalidCharacters.length(); i++) {
        if (Guess.find(MyInvalidCharacters[i]) != std::string::npos) {
            return true;
        }
    }
    return false;
}



// recieves a VALID guess, incremenets turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{

    MyCurrentTry++;
    FBullCowCount BullCowCount;
    
    // loop through all letters in the hidden word
    for (int32 i = 0; i < MyHiddenWord.length(); i++) {
        // compare letters against the guess
        for (int32 j = 0; j < Guess.length(); j++) {
            // if they match then
            if (MyHiddenWord[i] == Guess[j]) {
                if (i == j) {
                    BullCowCount.Bulls++;
                } else {
                    BullCowCount.Cows++;
                }
            }
        }
            
    }
    if (BullCowCount.Bulls == GetHiddenWordLength()) {
        bGameWon = true;
    }
    return BullCowCount;
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

FString FBullCowGame::GetHiddenWord() const
{
    return MyHiddenWord;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
    return MyHiddenWord.length();
}
