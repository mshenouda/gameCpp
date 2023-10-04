#pragma once
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include <time.h>
#include <cstdio>
#include <map>
#include <string>
#include <stdlib.h>
#include <iomanip>

using namespace std;

class Game{
    private:
        
        map<int, char> mapIntToLetter;
        const int vecLen = 3;
        int trialsCounter;
        int successCounter;
        vector<char> guessVec;
        vector<char> pressVec; 
        vector<char> resultVec;

    public:
        Game();
        void gameIntro();
        void initalizeGame();
        void makeGuess();
        void playGame();
        void record(char);
        bool gameResult();
        void printGameStats();
        void printGuesses();
        void errorMessage();
        void successMessage();

};
#endif