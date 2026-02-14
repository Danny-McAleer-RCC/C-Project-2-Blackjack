/*
    Author: Danny McAleer
    Date: Febuary 14, 2026 3:00 AM
    Purpose: Project 2: Blackjack
    Version 7
    Version Notes: added bubble and selection sorting
    
*/

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//User libraries

//Global Constants

//Function Prototypes

void rule();//shows player rules
void ybetgam(string pName, float &bal, int &winP, int &lossP, int &gameNum, int &totlDra, char results[]);//betting enabled
void nbetgam(string pName, int &winP, int &lossP, int &gameNum, int &totlDra, char results[]);//betting disabled
int drawC(string &cardNam, int &totlDra, bool deck[][13]);//face cards and suits
bool findP(const vector<string> &v, string name);//find player name in txt file
void bublSrt(vector<string> &);//bubble sort
void selcSrt(char [], int);//selection sort

//Execution Begins Here
int main(int argv,char **argc){
    //set the random seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Varibles
        /*
        C++ Varible Guidelines:
        7 characters or less
        No doubles or auto
        */

    const int maxGame = 100;//maximum number of games
    char results[maxGame];//1D array to store wins losses and pushes

    char play,//start game
         betAlow;//allow betting
         

    string pName,//player name
           fName,//name from txt file
           skip,//skip words in txt file
           dummy;//dont read if names dont match

    bool betting,//betting on/off
         rulesho,//show player the rules of blackjack
         stopgam,//stops the game
         match = false,//if name from file is same to inputted name
         pStand = false;//player stands

    int winP = 0,//number of player wins
        lossP = 0,//number of player losses
        gameNum = 0;//number of games played

    static int totlDra = 0;//total draws

    float bal = 1000.00,//player balance
          betAmt,//bet amount
          winloss = 0.00,//winnings or losses
          netChan;//net changes to balance
    
    cout<<"Welcome to Blackjack!"<<endl;
    cout<<"What is your name?"<<endl;//ask for name
    cin>>pName;

    ifstream inFile("Blackjack_Data.txt");

    vector<string> players;
    while(inFile>>fName){
        players.push_back(fName);
    }

    match = findP(players, pName);
    bublSrt(players);//bubble sort the player list

    inFile.close();

    if(match){//welcome back message if user inputted name matches name in txt file
        cout<<"Welcome back, "<<pName<<"!"<<endl;
    }

    rule();
    

    cout<<"Start game of blackjack? Y/N"<<endl;//ask user to start
    cin>>play;

    while(play=='Y' || play == 'y'){

        cout<<endl<<"Do you want to allow betting for this game? Y/N"<<endl;//ask for betting
        cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;
        cin>>betAlow;

        betting = (betAlow == 'y' || betAlow == 'Y') ? true : false;//set betting as on or off

        if(betting == true){
            ybetgam(pName, bal, winP, lossP, gameNum, totlDra, results);
        }else if(betting == false){
            nbetgam(pName, winP, lossP, gameNum, totlDra, results);
        }
        

        
        
        cout<<endl<<"Play another game? Y/N"<<endl;
        cin>>play;//asks user if they want to play another game

        if(play == 'y' || play == 'Y'){
            cout<<endl;
        }
        
    };

    cout<<endl<<"There were "<<totlDra<<" draws this session"<<endl;

    netChan = bal - 1000.00f;//set net change

    if(netChan > 0){//payer gained money
        cout<<"The total change to your balance was: $"<<fabs(netChan)<<endl;
    }else if(netChan < 0){//player lost money
        cout << "The total change to your balance was: -$"<<fabs(netChan)<<endl;
    }else{//balance did not change
        cout<<"There was no change to your balance."<<endl;
    }

    if(gameNum > 0){
    selcSrt(results, gameNum);//selection sort to group W L and P
    }

    cout<<endl<<"Sorted Session History:"<<endl;
    for(int i = 0; i < gameNum; i++){
        cout<<"Game "<<(i + 1)<<": "<<results[i]<<endl;
    }

    cout<<endl<<"Session History"<<endl;
    for(int i = 0; i < gameNum; i++){
        cout<<"Game "<<(i + 1)<<": "<<results[i]<<endl;
    }

    fstream data("Blackjack_Data.txt");//output data and stats to text file
    data<<"User "<<pName<<" played "<<gameNum<<" games of Blackjack and won "<<winP<<" times and lost "<<lossP<<" times, and had a final balance of $"<<fixed<<setprecision(2)<<bal<<".";

    //Exit The Program
    cout<<endl<<"Goodbye "<<pName<<"!"<<endl;//say goodbye to the user
    return 0;
};

//Functions

void rule(){
    char rules;//show rules 

    cout<<endl<<"Do you want to read the rules of Blackjack? Y/N"<<endl;//ask user if they want to read rules of blackjack
    cin>>rules;

        switch(rules){//rules of blackjack by Wikipedia
            case 'y':cout<<endl<<"Rules of Blackjack:"<<endl;
                     cout<<"\"The object of the game is to win money by creating card totals higher than those of the dealer's hand but not exceeding 21, or by stopping at a total in the hope that the dealer will bust."<<endl;
                     cout<<"Number cards count as their number, the jack, queen, and king (\"face cards\" or \"pictures\") count as 10, and aces count as either 1 or 11 depending on whether or not counting it as 11 would cause a bust."<<endl;
                     cout<<"If a player exceeds 21 points, they bust and automatically lose. A total of 21 on the starting two cards is called a \"blackjack\" or \"natural,\"[11][12] and is the strongest hand.[13][14]\""<<endl;
                     cout<<"\t-Wikipedia"<<endl<<endl; 
                     break;
            case 'Y':cout<<endl<<"Rules of Blackjack:"<<endl;
                     cout<<"\"The object of the game is to win money by creating card totals higher than those of the dealer's hand but not exceeding 21, or by stopping at a total in the hope that the dealer will bust."<<endl;
                     cout<<"Number cards count as their number, the jack, queen, and king (\"face cards\" or \"pictures\") count as 10, and aces count as either 1 or 11 depending on whether or not counting it as 11 would cause a bust."<<endl;
                     cout<<"If a player exceeds 21 points, they bust and automatically lose. A total of 21 on the starting two cards is called a \"blackjack\" or \"natural,\"[11][12] and is the strongest hand.[13][14]\""<<endl;
                     cout<<"\t-Wikipedia"<<endl<<endl; 
                     break;

            case 'n':cout<<endl;//dont show rules 
                     break;
            case 'N':cout<<endl; 
                     break;
        }
}

void ybetgam(string pName, float &bal, int &winP, int &lossP, int &gameNum, int &totlDra, char results[]){//games with bets
    //Declare Varibles
        /*
        C++ Varible Guidelines:
        7 characters or less
        No doubles or auto
        */

        string cName;
        
        int totalP,//player total
            totalD,//dealer total
            cardP,//card number for player
            cardD,//card number for dealer
            minCard,//minimum card value
            maxCard,//maximum card value
            pCarNum,//number of cards for player
            dCarNum,//number of cards for dealer
            cVal;//card value

        char stdOrhi,//stand or hit
             bet;//player bet

        bool betting,//betting on/off
             rulesho,//show player the rules of blackjack
             stopgam,//stops the game
             match,//if name from file is same to inputted name
             pStand = false,//player stands
             deck[4][13] = {false};//card deck

        float betAmt,//bet amount
              winloss = 0.00,//winnings or losses
              netChan;//net changes to balance

        //Initalize Varibles
        totalP = 0;//no cards yet card total is 0
        totalD = 0;//no cards yet card total is 0
        betAmt = 0.00;//no bets yet bet amount is 0
        stopgam = false;//allow the game to start before stopping the game

    gameNum++;//increase game counter
        cout<<endl<<"Game "<<gameNum<<":"<<endl;
    
        //player cards
        cVal = drawC(cName, totlDra, deck);//player card 1
        totalP += cVal;
        cout<<pName<<" Card 1: "<<cName<<endl;
        cVal = drawC(cName, totlDra, deck);//player card 2
        totalP += cVal;
        cout<<pName<<" Card 2: "<<cName<<endl<<endl;

        //dealer cards
        cVal = drawC(cName, totlDra, deck);//dealer card 1
        totalD += cVal;
        cout<<"Dealer Card 1: "<<cName<<endl;
        cVal = drawC(cName, totlDra, deck);//dealer card 2
        totalD += cVal;
        cout<<"Dealer Card 2: "<<cName<<endl<<endl;

        cout<<pName<<" has: "<<totalP<<endl;//show player total
        cout<<"Dealer has: "<<totalD<<endl;//show dealer total

        //Mapping Process -> Input to Outputs
        //both now have 2 cards
        pCarNum = 2;
        dCarNum = 2;

        if(totalP == 21){//player starts with 21
            winloss = (betAmt * 3);
            bal = bal + winloss;
            winP++;
            stopgam = true;

            cout<<endl<<pName<<" has a Blackjack!"<<endl;
            cout<<pName<<" Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<" won: $"<<fixed<<setprecision(2)<<winloss<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;
            
        }else if(totalD == 21){//dealer starts with 21
            winloss = betAmt;
            bal -= winloss;
            lossP++;
            stopgam = true;
            results[gameNum - 1] = 'L';

            cout<<endl<<"Dealer has a Blackjack!"<<endl;
            cout<<"Dealer Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<" lost: $"<<fixed<<setprecision(2)<<winloss<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;

        }else if(totalP > 21){//player busts at start
            winloss = betAmt;
            bal -= winloss;
            lossP++;
            stopgam = true;
            results[gameNum - 1] = 'L';

            cout<<endl<<pName<<" Busts!"<<endl;
            cout<<"Dealer Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<" lost: $"<<fixed<<setprecision(2)<<winloss<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;
            
        }else if(totalD > 21){//dealer busts at start
            winloss = (betAmt * 2);
            bal = bal + winloss;
            winP++;
            stopgam = true;
            results[gameNum - 1] = 'W';

            cout<<endl<<"Dealer Busts!"<<endl;
            cout<<pName<<" Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<" won: $"<<fixed<<setprecision(2)<<winloss<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;
        }

        while(totalP < 21 && !pStand){//if no instant blackjacks or busts
            if(stopgam==false){
                cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;
                cout<<endl<<"Bet? Y/N"<<endl;//ask user if they want to bet
                cin>>bet;

                    if(bet == 'y' || bet == 'Y'){
                        cout<<"Enter bet amount: "<<endl;//ask user how much to bet
                        cin>>betAmt;

                        while(betAmt > bal || betAmt <= 0){//stop invalid bet amounts
                                cout<<"Invalid bet amount! Please try again"<<endl;
                                cin>>betAmt;
                            
                        }
                    }
                

                cout<<endl<<"Press 'h' to hit or 's' to stand"<<endl;
                cin>>stdOrhi;//ask user if they want to hit or stand

                if(stdOrhi=='h' || stdOrhi=='H'){//if player hits
                    cVal = drawC(cName, totlDra, deck);//player card 3+
                    totalP += cVal;
                    pCarNum++;
                    cout<<endl<<pName<<"'s Card "<<pCarNum<<": "<<cName<<endl;
                    cout<<pName<<" has: "<<totalP<<endl;//show player total
                }else{//if player stands
                    pStand = true;
                }
            }
            
        }

        while(totalD < 17){//dealer stands on 17
            if(stopgam == false){
                cVal = drawC(cName, totlDra, deck);//dealer card 3+
                totalD += cVal;
                dCarNum++;
                cout<<endl<<"Dealer Card "<<dCarNum<<": "<<cName<<endl;
                cout<<"Dealer has: "<<totalD<<endl<<endl;//show dealer total
            }
        }

        //Display Inputs/Outputs

        if(totalP > 21){//player busts
            winloss = betAmt;
            bal -= winloss;
            lossP++;
            stopgam = true;
            results[gameNum - 1] = 'L';

            cout<<endl<<pName<<" Busts!"<<endl;
            cout<<"Dealer Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<" lost: $"<<fixed<<setprecision(2)<<winloss<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;
            
        }else if(totalD > 21){//dealer busts
            winloss = (betAmt * 2);
            bal = bal + winloss;
            winP++;
            stopgam = true;
            results[gameNum - 1] = 'W';

            cout<<endl<<"Dealer Busts!"<<endl;
            cout<<pName<<" Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<" won: $"<<fixed<<setprecision(2)<<winloss<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;

        }else if(totalP < 21 && totalP > totalD){//player is closer to 21
            winloss = (betAmt * 2);
            bal = bal + winloss;
            winP++;
            results[gameNum - 1] = 'W';

            cout<<endl<<pName<<" is closer to 21!"<<endl;
            cout<<pName<<" Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<" won: $"<<fixed<<setprecision(2)<<winloss<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;

        }else if(totalD < 21 && totalD > totalP){//dealer is closer to 21
            winloss = betAmt;
            bal -= winloss;
            lossP++;
            results[gameNum - 1] = 'L';

            cout<<endl<<"Dealer is closer to 21!"<<endl;
            cout<<"Dealer Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<" lost: $"<<fixed<<setprecision(2)<<winloss<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;

        }else if(totalD == totalP){//tie
            winloss = 0.00;
            bal = bal;
            results[gameNum - 1] = 'P';

            cout<<endl<<"Push (Tie)!"<<endl;
            cout<<"Nobody Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;
            
        }else if(totalP == 21){//player has 21
            winloss = (betAmt * 3);
            bal = bal + winloss;
            winP++;
            stopgam = true;
            results[gameNum - 1] = 'W';

            cout<<endl<<pName<<" has a Blackjack!"<<endl;
            cout<<pName<<" Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<" won: $"<<fixed<<setprecision(2)<<winloss<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;
            
        }else if(totalD == 21){//dealer has 21
            winloss = betAmt;
            bal -= winloss;
            lossP++;
            stopgam = true;
            results[gameNum - 1] = 'L';

            cout<<endl<<"Dealer has a Blackjack!"<<endl;
            cout<<"Dealer Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<" lost: $"<<fixed<<setprecision(2)<<winloss<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;
            
        }
}

void nbetgam(string pName, int &winP, int &lossP, int &gameNum, int &totlDra, char results[]){//games without bets
    //Declare Varibles
        /*
        C++ Varible Guidelines:
        7 characters or less
        No doubles or auto
        */

        string cName;
        
        int totalP,//player total
            totalD,//dealer total
            cardP,//card number for player
            cardD,//card number for dealer
            minCard,//minimum card value
            maxCard,//maximum card value
            pCarNum,//number of cards for player
            dCarNum,//number of cards for dealer
            cVal;//card value

        char stdOrhi,//stand or hit
             bet;//player bet

        bool betting,//betting on/off
             rulesho,//show player the rules of blackjack
             stopgam,//stops the game
             match,//if name from file is same to inputted name
             pStand = false,//player stands
             deck[4][13] = {false};//card deck

        float betAmt,//bet amount
              winloss = 0.00,//winnings or losses
              netChan;//net changes to balance

        //Initalize Varibles
        totalP = 0;//no cards yet card total is 0
        totalD = 0;//no cards yet card total is 0
        betAmt = 0.00;//no bets yet bet amount is 0
        stopgam = false;//allow the game to start before stopping the game

        gameNum++;//increase game counter
        cout<<endl<<"Game "<<gameNum<<":"<<endl;
    
        //player cards
        cVal = drawC(cName, totlDra, deck);//player card 1
        totalP += cVal;
        cout<<pName<<" Card 1: "<<cName<<endl;
        cVal = drawC(cName, totlDra, deck);//player card 2
        totalP += cVal;
        cout<<pName<<" Card 2: "<<cName<<endl<<endl;

        //dealer cards
        cVal = drawC(cName, totlDra, deck);//dealer card 1
        totalD += cVal;
        cout<<"Dealer Card 1: "<<cName<<endl;
        cVal = drawC(cName, totlDra, deck);//dealer card 2
        totalD += cVal;
        cout<<"Dealer Card 2: "<<cName<<endl<<endl;

        cout<<pName<<" has: "<<totalP<<endl;//show player total
        cout<<"Dealer has: "<<totalD<<endl;//show dealer total

        //Mapping Process -> Input to Outputs
        //both now have 2 cards
        pCarNum = 2;
        dCarNum = 2;

        if(totalP == 21){//player starts with 21
            stopgam = true;
            results[gameNum - 1] = 'W';
            winP++;

            cout<<endl<<pName<<" has a Blackjack!"<<endl;
            cout<<pName<<" Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;
            
        }else if(totalD == 21){//dealer starts with 21
            stopgam = true;
            results[gameNum - 1] = 'L';
            lossP++;

            cout<<endl<<"Dealer has a Blackjack!"<<endl;
            cout<<"Dealer Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;
            
        }else if(totalP > 21){//player busts at start
            stopgam = true;
            results[gameNum - 1] = 'L';
            lossP++;

            cout<<endl<<pName<<" Busts!"<<endl;
            cout<<"Dealer Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;
            
            
        }else if(totalD > 21){//dealer busts at start
            stopgam = true;
            results[gameNum - 1] = 'W';
            winP++;

            cout<<endl<<"Dealer Busts!"<<endl;
            cout<<pName<<" Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;
        }

        while(totalP < 21 && !pStand){//if no instant blackjacks or busts
            if(stopgam==false){
                    cout<<endl;

                cout<<endl<<"Press 'h' to hit or 's' to stand"<<endl;
                cin>>stdOrhi;//ask user if they want to hit or stand

                if(stdOrhi=='h' || stdOrhi=='H'){//if player hits
                    cVal = drawC(cName, totlDra, deck);//player card 3+
                    totalP += cVal;
                    pCarNum++;
                    cout<<endl<<pName<<"'s Card "<<pCarNum<<": "<<cName<<endl;
                    cout<<pName<<" has: "<<totalP<<endl;//show player total
                }else{//if player stands
                    pStand = true;
                }
            }
            
        }

        while(totalD < 17){//dealer stands on 17
            if(stopgam == false){
                cVal = drawC(cName, totlDra, deck);//dealer card 3+
                totalD += cVal;
                dCarNum++;
                cout<<endl<<"Dealer Card "<<dCarNum<<": "<<cName<<endl;
                cout<<"Dealer has: "<<totalD<<endl<<endl;//show dealer total
            }
        }

        //Display Inputs/Outputs

        if(totalP > 21){//player busts
            stopgam = true;
            results[gameNum - 1] = 'L';
            lossP++;

            cout<<endl<<pName<<" Busts!"<<endl;
            cout<<"Dealer Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;
            
            
        }else if(totalD > 21){//dealer busts
            stopgam = true;
            results[gameNum - 1] = 'W';
            winP++;

            cout<<endl<<"Dealer Busts!"<<endl;
            cout<<pName<<" Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;
            

        }else if(totalP < 21 && totalP > totalD){//player is closer to 21
            results[gameNum - 1] = 'W';
            winP++;

            cout<<endl<<pName<<" is closer to 21!"<<endl;
            cout<<pName<<" Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;
            

        }else if(totalD < 21 && totalD > totalP){//dealer is closer to 21
            results[gameNum - 1] = 'L';
            lossP++;

            cout<<endl<<"Dealer is closer to 21!"<<endl;
            cout<<"Dealer Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;

        }else if(totalD == totalP){//tie
            results[gameNum - 1] = 'P';

            cout<<endl<<"Push (Tie)!"<<endl;
            cout<<"Nobody Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;
            
        }else if(totalP == 21){//player has 21
            stopgam = true;
            results[gameNum - 1] = 'W';
            winP++;

            cout<<endl<<pName<<" has a Blackjack!"<<endl;
            cout<<pName<<" Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;
            
        }else if(totalD == 21){//dealer has 21
            stopgam = true;
            results[gameNum - 1] = 'L';
            lossP++;

            cout<<endl<<"Dealer has a Blackjack!"<<endl;
            cout<<"Dealer Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;
            
        }
}

int drawC(string &cardNam, int &totlDra, bool deck[][13]){
    int rank, suitNum;
    
    do {
        rank = rand() % 13;//0 to 12
        suitNum = rand() % 4;//0 to 3
    } while (deck[suitNum][rank] == true);

    deck[suitNum][rank] = true;//mark card as drawn

    string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    string ranks[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    int values[] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};

    cardNam = ranks[rank] + " of " + suits[suitNum];
    totlDra++;
    
    return values[rank];
}

bool findP(const vector<string> &v, string name){
    bool found = false;
    for (int i = 0; i < v.size() && !found; i++){
        if (v[i] == name) {
            found = true;
        }
    }
    return found;
}
void bublSrt(vector<string> &a){
    int n = a.size();
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(a[j] > a[j + 1]){
                string temp = a[j];//swap
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void selcSrt(char a[], int n){
    for(int i = 0; i < n - 1; i++){
        int minIdx = i;
        for(int j = i + 1; j < n; j++){
            if(a[j] < a[minIdx]){
                minIdx = j;
            }
        }
        char temp = a[minIdx];//swap found minimum element withfirst element
        a[minIdx] = a[i];
        a[i] = temp;
    }
}
