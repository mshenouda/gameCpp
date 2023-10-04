#include "game.h"

Game::Game()
{
    mapIntToLetter[1] = 'A';
    mapIntToLetter[2] = 'B';
    mapIntToLetter[3] = 'C';
    
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
        char ch = mapIntToLetter[val];
        guessVec.push_back(ch);
    }
}

void Game::gameIntro(){
    cout<<left<<"The machine will guess 3 letters A, B, C in any order masked by *"<<endl;
    cout<<left<<"You guess the 3 lettes"<<endl;
    cout<<left<<"Press down A,B or C case Insensitive\nPress X case Insensitive to exit\n";
    cout<<left<<"Guess results will be shown R(failure), G(success), O(letter existed but misoriented)"<<endl;
    cout<<left<<"The game will reset upon 3 successful hits, till you exit"<<endl;
    cout<<left<<"Machine guess is shown as a hint in faded yellow with strikethrough, Don't look at it unless you have to !!"<<endl;
    cout<<left<<"Press any letter to continue"<<endl;
    cin.get();
}

/*
    Logic for playing the game
    Forever loop that exits only if user presses X or x
    Any invalid input outside(A,B,C) won't be stored as valid input
    Upon success guess, game will reset
*/

void Game::playGame() {

    bool playOnce = true;
    gameIntro();
    srand(unsigned(time(NULL)));
    
    while(true) {       
        if(playOnce) {
            playOnce = false;        
            makeGuess();
        }

        printGuesses();
        cout<<left<<"Input a char :"<<endl;
        char ch=cin.get();
        cin.ignore();
        if (toupper(ch) == 'X') {
            cout<<"Exitting now..."<<endl;
            printGameStats();
            break;
        } else if (toupper(ch) != 'A' && toupper(ch) != 'B' && toupper(ch) != 'C') {
            errorMessage();
            continue;
        }
        
        record(toupper(ch));
        playOnce = gameResult();
    };
}

void Game::successMessage(){
    system("clear");
    cout<<"Congratulations, you guess it right"<<endl;
    cout<<left<<"Press any letter to continue"<<endl;
    cin.get();
}

void Game::errorMessage() {
    system("clear");
    cout<<"Error, wrong presses only A, B or C"<<endl;
    cout<<left<<"Press any letter to continue"<<endl;
    cin.get();
}

void Game::record(char ch)
{
    trialsCounter++;
    if (pressVec.size() == vecLen)
    {   pressVec.erase(pressVec.begin());
    }  
    pressVec.push_back(ch);   
}

/*
    The algorithm is brute force, when user added a valid character, it compares the 
    whole pressVec (user input) against guessVec(machine input) on content and index basis
    and fills in the resultVec accordingly
    Space complexity O(n)
    Time complexity  O(n^2) 
*/
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
    
    if(counter == vecLen) {
        successMessage();
        successCounter++;
        return true;
    }
    return false;
}

void Game::printGameStats() {
    cout<<"---------------------------------"<<endl;
    cout<<"You did trails = "<<trialsCounter<<endl;
    cout<<"You guess it right = "<<successCounter<<endl;
    cout<<"---------------------------------"<<endl;
} 

void Game::printGuesses() {
    
    system("clear");
    cout<<left<<"guesses";
    for(const auto& p: guessVec) {
        cout<<"\033[2;3;9;37;43m"<<p;
    }
    cout<<"\033[0m"<<endl;
    cout<<left<<setw(30)<<"Letter positions"<<setw(3)<<"1"<<setw(3)<<"2"<<setw(3)<<"3"<<endl;
    cout<<left<<setw(30)<<"Machine code"<<setw(3)<<"*"<<setw(3)<<"*"<<setw(3)<<"*"<<endl;
    cout<<left<<setw(30)<<"Your Guess";    
    for(const auto& p: pressVec) {
        cout<<setw(3)<<p<<setw(3);
    }

    cout<<endl;
    cout<<left<<setw(30)<<"Results ";
    for(const auto& r: resultVec) {
        cout<<setw(3)<<r<<setw(3);
    }
    cout<<endl<<endl;
}
