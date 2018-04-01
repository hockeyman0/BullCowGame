/* This is the consol executable, that makes use of the BullCow class
This acts as the view in an MVC pattern, and is repsonsible for all user interaction.
For game logic see the FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//NOT using namespace std;
//Mapping to Unreal syntax
using FText = std::string;
using int32 = int;

FBullCowGame BCGame;


void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();


int main()
{
  
    bool bPlayAgain = false;
    do {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    } while (bPlayAgain);
    return 0;

}

void PlayGame() {
    const int32 NUMBER_OF_TURNS = 5;
    FText Guess = "";
    EGuessStatus Status;
    BCGame.Reset();

    // loop asking for guesses while the game
    // is NOT won and there are still tries remaining
    while (!BCGame.IsGameWon() && (BCGame.GetCurrentTry() <= BCGame.GetMaxTries()))
    {
        Guess = GetValidGuess();

        // submit valid guess to the game, and receive counts
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        // print number of bulls and cows
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n";
        std::cout << "Your word was \"" << Guess << "\"!\n\n";
    }

    PrintGameSummary();

}

void PrintGameSummary() {
    if (BCGame.IsGameWon()) {
        std::cout << "Well done! You win!\n";
    }
    else {
        std::cout << "Sorry, better luck next time.\n";
    }
}

// Ascii Intro to game
void PrintIntro() {
    std::cout << "Hello World!!\n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";

    return;
}

// loop until a valid guess
FText GetValidGuess() {
    FText Guess = "";
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    int32 CurrentTry = BCGame.GetCurrentTry();

    do
    {
        
        
        std::cout << "Take a stab at it (Try " << CurrentTry << "): ";
        std::getline(std::cin, Guess);

        Status = BCGame.CheckGuessValidity(Guess);
        if (Status != EGuessStatus::OK) {
            std::cout << "Not a valid guess! Try again.\n";
        }
        switch (Status)
        {
        case EGuessStatus::Wrong_Length:
            std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
            break;
        case EGuessStatus::Not_Lowercase:
            std::cout << "Please enter a guess in all lowercase characters.\n";
            break;
        case EGuessStatus::Not_Isogram:
            std::cout << "Isograms do not have repeating letters.\n";
            break;
        case EGuessStatus::Invalid_Character:
            std::cout << "Do not enter any special characters!\n";
            break;
        case EGuessStatus::Invalid_Status:
            std::cout << "Something went wrong...\n";
            break;
        case EGuessStatus::OK:
        default:
            return Guess;
        }

    } while (Status != EGuessStatus::OK);

    //This should never run...
    return Guess;
}

bool AskToPlayAgain() {
    FText Response = "";
    do
    {
        std::cout << "Would you like to play again with the same word..? (y/n): ";
        std::getline(std::cin, Response);
        std::cout << "\n";
        if (Response[0] == 'y' || Response[0] == 'Y') {
            return true;
        }
        else if (Response[0] == 'n' || Response[0] == 'N')
        {
            return false;
        }
        std::cout << "I'm sorry, what?...\n";

    } while (true);
}
