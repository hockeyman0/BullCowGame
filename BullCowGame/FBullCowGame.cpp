#include "FBullCowGame.h"
#include <map>
#define TMap std::map

void FBullCowGame::Reset()
{
    constexpr int32 MAX_TRIES = 8;

    const FString HIDDEN_WORD = "plane";
    MyHiddenWord = HIDDEN_WORD;

    const FString INVALID_CHARACTERS = "!@#$%^&*()_+1234567890-={}[] ";
    MyInvalidCharacters = INVALID_CHARACTERS;
    
    MyCurrentTry = 1;
    //MyCurrentGuess = "";
    bGameWon = false;
    return;
}

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetMaxTries() const {
    TMap<int32, int32> WordLengthToMaxTries{
        {3,4},
        {4,7},
        {5,10},
        {6,15},
        {7,20}
    };

    return WordLengthToMaxTries[MyHiddenWord.length()];
}


bool FBullCowGame::IsGameWon() const { return bGameWon; }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!IsIsogram(Guess)) // checks if guess is isogram
    {
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowercase(Guess)) // checks that guess is all lowercase
    {
        return EGuessStatus::Not_Lowercase;
    } 
    else if (Guess.length() != GetHiddenWordLength()) // checks that guess is proper length
    {
        return EGuessStatus::Wrong_Length;
    }
    else if (CheckInvalidCharacters(Guess)) // checks no invalid characters were used
    {
        return EGuessStatus::Invalid_Character;
    }

    return EGuessStatus::OK;
}

bool FBullCowGame::CheckInvalidCharacters(FString Word) const
{
    for (char Letter : MyInvalidCharacters) {
        if (Word.find(Letter) != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
    // treat 0 and 1 letter words as isograms
    if (Word.length() <= 1 ){ return true; }

    TMap<char, bool> LetterSeen;
    for (auto Letter : Word)
    {
        Letter = tolower(Letter);
        if (LetterSeen[Letter]) 
        {
            return false; 
        } else {
            LetterSeen[Letter] = true;
        }
    }
        //if value already false then make it true
        //if value already true then break look and return false
    return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
    if (Word.length() == 0) { return true; }

    for (auto Letter : Word) {
        if (!islower(Letter)) {
            return false;
        }
    }
    return true;
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

FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
