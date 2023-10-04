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

class Game{
    private:
        
        std::map<char, int> mapLetterToInt;
        const int vecLen = 3;
        int trialsCounter;
        int successCounter;
        std::vector<int> guessVec;
        std::vector<int> pressVec; 
        std::vector<char> resultVec;

    public:
        Game();
        void initalizeGame();
        void makeGuess();
        void playGame();
        void record(char);
        bool gameResult();
        void printGameStats();
        void printGuesses();
};
#endif