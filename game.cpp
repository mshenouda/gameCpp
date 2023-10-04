#include "game.h"

Game::Game()
{
    mapLetterToInt['A'] = 1;
    mapLetterToInt['B'] = 2;
    mapLetterToInt['C'] = 3;
    trialsCounter = 0;
    successCounter = 0;
}

void Game::initalizeGame() {
    if(guessVec.size()>0) {
        guessVec.clear();
        pressVec.clear();
        resultVec.clear();
    }
    for(int i=0; i<vecLen; i++)
        resultVec.push_back('F');
}

void Game::makeGuess() {
    initalizeGame();  
    for(int i=0; i<vecLen; i++) {
        int val = (rand()%vecLen + 1);
        guessVec.push_back(val);
    }
}

void Game::playGame() {

    srand(unsigned(time(NULL)));
    bool flagOnce = true;
    while(true) {       
        if(flagOnce) {
            flagOnce = false;
            makeGuess();
            std::cout<<"\nPress down A,B or C\nPress x or X to exit\n";
        }

        std::cout<<std::setw(30)<<"Input a char ";
        char ch=getchar();
        if (ch == '\n')
            continue;
        else if (toupper(ch) == 'X') {
            std::cout<<"Exitting now..."<<std::endl;
            printGameStats();
            break;
        } else if (toupper(ch) != 'A' && toupper(ch) != 'B' && toupper(ch) != 'C') {
            std::cout<<"Error, wrong presses only A, B or C"<<std::endl;
            continue;
        }
        
        record(toupper(ch));
        flagOnce = gameResult();
    };
}

void Game::record(char ch)
{
    trialsCounter++;
    int val = mapLetterToInt[ch];
    if (pressVec.size() == vecLen)
    {   pressVec.erase(pressVec.begin());
    }  
    pressVec.push_back(val);   
}

bool Game::gameResult() { 

    int counter = 0;
    for(int i=0; i<pressVec.size() ;i++) 
    {
        bool seen = false;
        for(int j=0; j<guessVec.size();j++)
        {
            if(i == j && pressVec[i] == guessVec[j]) { 
                counter++;
                resultVec[i] = 'G';
                break;
            } else if (!seen && (pressVec[i] == guessVec[j])) {
                seen = true;
                resultVec[i] = 'O';
            } else if (!seen) {
                resultVec[i] = 'R';
            }
        }
    }
    
    printGuesses();
    if(counter == vecLen) {
        std::cout<<"Congratulations, you guess it right"<<std::endl;
        successCounter++;
        return true;
    }
    return false;
}

void Game::printGameStats() {
    std::cout<<"---------------------------------"<<std::endl;
    std::cout<<"You did trails = "<<trialsCounter<<std::endl;
    std::cout<<"You guess it right = "<<successCounter<<std::endl;
    std::cout<<"---------------------------------"<<std::endl;
} 

void Game::printGuesses() {
    
    system("clear");
    std::cout<<std::left<<std::setw(30)<<"Letter positions "<<std::setw(2)<<"1 "<<std::setw(2)<<"2 "<<std::setw(2)<<"3 "<<std::endl;
    std::cout<<std::left<<std::setw(30)<<"Machine code "<<std::setw(2)<<"* "<<std::setw(2)<<"* "<<std::setw(2)<<"* "<<std::endl;
    std::cout<<std::left<<std::setw(30)<<"Your Guess ";
    for(const auto& p: pressVec) {
        std::cout<<std::setw(2)<<p<<" ";
    }

    std::cout<<std::endl;
    std::cout<<std::left<<std::setw(30)<<"Results ";
    for(const auto& r: resultVec) {
        std::cout<<std::setw(2)<<r<<" ";
    }
    std::cout<<std::endl;
}
