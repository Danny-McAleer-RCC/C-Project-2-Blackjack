/*
    Author: Danny McAleer
    Date: Febuary 13, 2026 3:03 PM
    Purpose: Project 2: Blackjack
    Version 2
    Version Notes: added function for face cards and suits
    
*/

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
using namespace std;

//User libraries

//Global Constants

//Function Prototypes

void rule();//shows player rules
void ybetgam(string pName, float &bal, int &winP, int &lossP, int &gameNum);//betting enabled
void nbetgam(string pName, int &winP, int &lossP, int &gameNum);//betting disabled
int drawC(string &cardNam);//face cards and suits

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

    float bal = 1000.00,//player balance
          betAmt,//bet amount
          winloss = 0.00,//winnings or losses
          netChan;//net changes to balance
    
    cout<<"Welcome to Blackjack!"<<endl;
    cout<<"What is your name?"<<endl;//ask for name
    cin>>pName;

    ifstream inFile("Blackjack_Data.txt");

    if(inFile){
        while(inFile>>skip>>fName){//look for name in txt file
            if(fName == pName){
                match = true;
            }else{
                getline(inFile, dummy);//dont read if names dont match
            }
        }
    }
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
            ybetgam(pName, bal, winP, lossP, gameNum);
        }else if(betting == false){
            nbetgam(pName, winP, lossP, gameNum);
        }
        

        
        
        cout<<endl<<"Play another game? Y/N"<<endl;
        cin>>play;//asks user if they want to play another game

        if (play == 'y' || play == 'Y') {
            cout<<endl;
        }
        
    };

    netChan = bal - 1000.00f;//set net change

    if(netChan > 0){//payer gained money
        cout<<"The total change to your balance was: $"<<fabs(netChan)<<endl;
    }else if(netChan < 0){//player lost money
        cout << "The total change to your balance was: -$"<<fabs(netChan)<<endl;
    }else{//balance did not change
        cout<<"There was no change to your balance."<<endl;
    }

    fstream data("Blackjack_Data.txt");//output data and stats to text file
    data<<"User "<<pName<<" played "<<gameNum<<" games of Blackjack and won "<<winP<<" times and lost "<<lossP<<" times, and had a final balance of $"<<fixed<<setprecision(2)<<bal;

    //Exit The Program
    cout<<"Goodbye "<<pName<<"!"<<endl;//say goodbye to the user
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

            case 'n':cout<<endl; 
                     break;
            case 'N':cout<<endl; 
                     break;
        }
}

void ybetgam(string pName, float &bal, int &winP, int &lossP, int &gameNum){//games with bets
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
            cVal;

        char stdOrhi,//stand or hit
             bet;//player bet

        bool betting,//betting on/off
             rulesho,//show player the rules of blackjack
             stopgam,//stops the game
             match,//if name from file is same to inputted name
             pStand = false;//player stands

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
        cVal = drawC(cName);//player card 1
        totalP += cVal;
        cout<<pName<<" Card 1: "<<cName<<endl;
        cVal = drawC(cName);//player card 2
        totalP += cVal;
        cout<<pName<<" Card 2: "<<cName<<endl<<endl;

        //dealer cards
        cVal = drawC(cName);//dealer card 1
        totalD += cVal;
        cout<<"Dealer Card 1: "<<cName<<endl;
        cVal = drawC(cName);//dealer card 2
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
            winP = winP + 1;
            stopgam = true;

            cout<<endl<<pName<<" has a Blackjack!"<<endl;
            cout<<pName<<" Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<" won: $"<<fixed<<setprecision(2)<<winloss<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;
            
        }else if(totalD == 21){//dealer starts with 21
            winloss = betAmt;
            bal -= winloss;
            lossP = lossP + 1;
            stopgam = true;

            cout<<endl<<"Dealer has a Blackjack!"<<endl;
            cout<<"Dealer Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<" lost: $"<<fixed<<setprecision(2)<<winloss<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;
        }

        while(totalP < 21 && !pStand){//if no instant blackjacks
            if(stopgam==false){
                cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;
                cout<<endl<<"Bet? Y/N"<<endl;//ask user if they want to bet
                cin>>bet;

                    if(bet == 'y' || bet == 'Y'){
                        cout<<"Enter bet amount: "<<endl;//ask user how much to bet
                        cin>>betAmt;

                        while(betAmt > bal || betAmt <= 0){//stop invalid bet amounts
                                cout<<"Invalid bet amount! Please try again"<<endl;
                                cout<<"Bet? Y/N"<<endl;
                                cin>>betAmt;
                            
                        }
                    }
                

                cout<<endl<<"Press 'h' to hit or 's' to stand"<<endl;
                cin>>stdOrhi;//ask user if they want to hit or stand

                if(stdOrhi=='h' || stdOrhi=='H'){//if player hits
                    cVal = drawC(cName);//player card 3+
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
                cVal = drawC(cName);//dealer card 3+
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
            lossP = lossP + 1;
            stopgam = true;

            cout<<endl<<pName<<" Busts!"<<endl;
            cout<<"Dealer Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<" lost: $"<<fixed<<setprecision(2)<<winloss<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;
            
        }else if(totalD > 21){//dealer busts
            winloss = (betAmt * 2);
            bal = bal + winloss;
            winP = winP + 1;
            stopgam = true;

            cout<<endl<<"Dealer Busts!"<<endl;
            cout<<pName<<" Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<" won: $"<<fixed<<setprecision(2)<<winloss<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;

        }else if(totalP < 21 && totalP > totalD){//player is closer to 21
            winloss = (betAmt * 2);
            bal = bal + winloss;
            winP = winP + 1;

            cout<<endl<<pName<<" is closer to 21!"<<endl;
            cout<<pName<<" Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<" won: $"<<fixed<<setprecision(2)<<winloss<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;

        }else if(totalD < 21 && totalD > totalP){//dealer is closer to 21
            winloss = betAmt;
            bal -= winloss;
            lossP = lossP + 1;

            cout<<endl<<"Dealer is closer to 21!"<<endl;
            cout<<"Dealer Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<" lost: $"<<fixed<<setprecision(2)<<winloss<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;

        }else if(totalD == totalP){//tie
            winloss = 0.00;
            bal = bal;

            cout<<endl<<"Push (Tie)!"<<endl;
            cout<<"Nobody Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;
            
        }else if(totalP == 21){//player has 21
            winloss = (betAmt * 3);
            bal = bal + winloss;
            winP = winP + 1;
            stopgam = true;

            cout<<endl<<pName<<" has a Blackjack!"<<endl;
            cout<<pName<<" Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<" won: $"<<fixed<<setprecision(2)<<winloss<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;
            
        }else if(totalD == 21){//dealer has 21
            winloss = betAmt;
            bal -= winloss;
            lossP = lossP + 1;
            stopgam = true;

            cout<<endl<<"Dealer has a Blackjack!"<<endl;
            cout<<"Dealer Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<pName<<" lost: $"<<fixed<<setprecision(2)<<winloss<<endl;
            cout<<pName<<"'s Balance: $"<<fixed<<setprecision(2)<<bal<<endl;
            
        }
}

void nbetgam(string pName, int &winP, int &lossP, int &gameNum){//games without bets
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
            cVal;

        char stdOrhi,//stand or hit
             bet;//player bet

        bool betting,//betting on/off
             rulesho,//show player the rules of blackjack
             stopgam,//stops the game
             match,//if name from file is same to inputted name
             pStand = false;//player stands

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
        cVal = drawC(cName);//player card 1
        totalP += cVal;
        cout<<pName<<" Card 1: "<<cName<<endl;
        cVal = drawC(cName);//player card 2
        totalP += cVal;
        cout<<pName<<" Card 2: "<<cName<<endl<<endl;

        //dealer cards
        cVal = drawC(cName);//dealer card 1
        totalD += cVal;
        cout<<"Dealer Card 1: "<<cName<<endl;
        cVal = drawC(cName);//dealer card 2
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

            cout<<endl<<pName<<" has a Blackjack!"<<endl;
            cout<<pName<<" Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;
            
        }else if(totalD == 21){//dealer starts with 21
            stopgam = true;

            cout<<endl<<"Dealer has a Blackjack!"<<endl;
            cout<<"Dealer Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;
            
        }

        while(totalP < 21 && !pStand){//if no instant blackjacks
            if(stopgam==false){
                    cout<<endl;

                cout<<endl<<"Press 'h' to hit or 's' to stand"<<endl;
                cin>>stdOrhi;//ask user if they want to hit or stand

                if(stdOrhi=='h' || stdOrhi=='H'){//if player hits
                    cVal = drawC(cName);//player card 3+
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
                cVal = drawC(cName);//dealer card 3+
                totalD += cVal;
                dCarNum++;
                cout<<endl<<"Dealer Card "<<dCarNum<<": "<<cName<<endl;
                cout<<"Dealer has: "<<totalD<<endl<<endl;//show dealer total
            }
        }

        //Display Inputs/Outputs

        if(totalP > 21){//player busts
            stopgam = true;

            cout<<endl<<pName<<" Busts!"<<endl;
            cout<<"Dealer Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;
            
            
        }else if(totalD > 21){//dealer busts
            stopgam = true;

            cout<<endl<<"Dealer Busts!"<<endl;
            cout<<pName<<" Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;
            

        }else if(totalP < 21 && totalP > totalD){//player is closer to 21

            cout<<endl<<pName<<" is closer to 21!"<<endl;
            cout<<pName<<" Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;
            

        }else if(totalD < 21 && totalD > totalP){//dealer is closer to 21

            cout<<endl<<"Dealer is closer to 21!"<<endl;
            cout<<"Dealer Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;

        }else if(totalD == totalP){//tie

            cout<<endl<<"Push (Tie)!"<<endl;
            cout<<"Nobody Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;
            
        }else if(totalP == 21){//player has 21
            stopgam = true;

            cout<<endl<<pName<<" has a Blackjack!"<<endl;
            cout<<pName<<" Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;
            
        }else if(totalD == 21){//dealer has 21
            stopgam = true;

            cout<<endl<<"Dealer has a Blackjack!"<<endl;
            cout<<"Dealer Wins!"<<endl;
            cout<<pName<<"'s Score: "<<winP<<" wins and "<<lossP<<" losses."<<endl;
            cout<<endl;
            
        }
}

int drawC(string &cardNam){
    int rank = rand() % 13 + 1; // 1 to 13
    int suitNum = rand() % 4;   // 0 to 3
    string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    string rankNam;
    int value;

    if(rank == 1){
        rankNam = "Ace";
        value = 11;
    }else if(rank == 11){
        rankNam = "Jack";
        value = 10;
    }else if (rank == 12){
        rankNam = "Queen";
        value = 10;
    }else if(rank == 13){
        rankNam = "King";
        value = 10;
    }else{
        rankNam = to_string(rank);
        value = rank;
    }

    cardNam = rankNam + " of " + suits[suitNum];
    return value;
}