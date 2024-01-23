#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <cstring>

using namespace std;

struct CaseData{
	int caseNum; //case number
	int contents; //values read from file
	int caseValue; // shuffled
	bool opened; //was case opened?
	bool contentUsed; //was contents used?
};

int readFiles(CaseData cases[], int caseAmount, int rounds[]){
	
	ifstream input;
	
	if(caseAmount == 16)
		input.open("Data16.txt");
	else
		if(caseAmount == 18)
			input.open("Data18.txt");
		else	
			if(caseAmount == 20)
				input.open("Data20.txt");
			else	
				if(caseAmount == 22)
					input.open("Data22.txt");
				else	
					if(caseAmount == 24)
						input.open("Data24.txt");
					else
						if(caseAmount == 26)
							input.open("Data26.txt");
				
						
//	if (!input.is_open()) {
//		cout << "\nFile "<<caseAmount<< " cannot be found\n";
//	}
//	else 
//		cout<<"\nFile "<<caseAmount<< " was Read Successfully... "<<endl<<endl; 
		
	int i=1;
	int numRounds;
	
	while(i <= caseAmount){
		
		cases[i].caseNum = i;
		input>>cases[i].caseValue;
		cases[i].contents= cases[i].caseValue;
		i++;
	}
	
	input>>numRounds;

	int c=1;
	
	while(c <= numRounds){
		input>> rounds[c];
		c++;
	}

	return numRounds;
}


void printStruct(CaseData cases[], int caseAmount){
	
	// to test data 
	
	cout<<"printing contents and cases"<<endl<<endl;
	
	for(int i=1;i<=caseAmount;i++){
		cout<<"Case:"<<cases[i].caseNum<<"\t Value: "<<cases[i].caseValue<< "\t Case used: "<<cases[i].opened<< "\t Content used: "<<cases[i].contentUsed<<endl;
	}
}


void initialize (CaseData cases[], int caseAmount){
	
	//initializes bool in struct
	
	int i=1;
	
	for( i=1; i<= caseAmount ;i++){
		cases[i].opened = false;
		cases[i].contentUsed = false;
	}
}


bool containsValue( CaseData cases[], int caseAmount, int random){
	
	//is value already stored in shuffled list

	int i;
	for (i=1;i<=caseAmount;i++){
		
		if (cases[i].caseValue == cases[random].caseValue){
			return true;
		}
	}
	return false;
}


void shuffleValues (CaseData cases[],int caseAmount) {
	
	//shuffles the values read from the file
	//random values in random cases
	
	int shuffleNum;
	int i;
	int tempSwap;
	
	for (i=1;i<=caseAmount;i++){
	
		shuffleNum = rand () % caseAmount +1;
				
		tempSwap = cases[shuffleNum].caseValue;
		cases[shuffleNum].caseValue = cases[i].caseValue;
		cases[i].caseValue = tempSwap;
					
			if (containsValue(cases,i,shuffleNum) == false ){
				
				cases[i].caseValue = tempSwap;
			}
		
	}
}


bool isValidAmount(int caseAmount){
	
	//is valid case amount option
	
	if( caseAmount == 16 ||  caseAmount == 18 ||  caseAmount == 20 ||  caseAmount == 22 ||  caseAmount == 24 ||  caseAmount == 26 )
		return true;
	else
		return false;
}


bool isValidCase(CaseData cases[] , int caseChosen, int caseAmount){
	
	//is valid case to choose?
	
	if(( caseChosen >= 1 && caseChosen <= caseAmount) && (cases[caseChosen].opened == false))
		return true;
	else
		return false;
}


bool isValidContent (CaseData cases[] , int caseChosen){
	
	//has this content been used before
	
	if(cases[caseChosen].contentUsed == false)
		return true;
	else
		return false;
}


bool isValidChoice (int choice){
	
	//is a valid choice for deal or no deal
	
	if( choice == 1 || choice == 0 )
		return true;
	else
		return false;
}


void printCases (CaseData cases[], int caseAmount , int caseChosen){
	
	//prints cases unopened 
	
	int i;
	
	cout<<"\n\t\t===============B R I E F C A S E S================\n";
	cout<<"\t\t==================================================\n";
	
	for (i=1; i<= caseAmount ; i++){
		
		if(isValidCase(cases, i, caseAmount)){
			cout<<"\t\t"<<cases[i].caseNum;
			if(i % 4 == 0)
				cout<<endl;
		}
		else
			if(!isValidCase(cases, i, caseAmount)){ 
				cout<<"\t\t"; //fills in opened cases with a space
				if(i % 4 == 0)
					cout<<endl;
			}		
	}
	
	cout<<"\n\t\t==================================================\n\n";
}


void printContents (CaseData cases[], int caseAmount , int caseChosen){
	
	//prints contents unused 
	
	int i;
	int x,y;
	
	cout<<"\n\t\t=============M O N E Y - B O A R D================\n";
	cout<<"\t\t==================================================\n";
	
	for (i=1; i<= caseAmount/2 ; i++){
		
		x= i;
		y= x + caseAmount/2;
		
		//code for layout
		
		if (isValidContent(cases,x)==true && isValidContent(cases,y)==true){
				
				cout<<"\t\t\t"<<cases[x].contents << "\t\t\t"<< cases[y].contents;
				cout<<endl;
		}
		else
			if (isValidContent(cases,x)==true && isValidContent(cases,y)==false){
				cout<<"\t\t\t"<<cases[x].contents << "\t\t\t";
				cout<<endl;
			}
			else 
				if (isValidContent(cases,x)==false && isValidContent(cases,y)==true){
					cout<<"\t\t\t\t\t\t"<<cases[y].contents;
					cout<<endl;
				}
			else 
				if((isValidContent(cases,x)==false) && (isValidContent (cases,y)==false)){
					cout<<"\t\t\t\t\t\t"; //fills in used contents with a space
					cout<<endl;
				}		
	}

	cout<<"\n\t\t==================================================\n\n";

}


double bankerDeal (CaseData cases[], int caseAmount , int currRound, int numRounds ){
	
	//banker makes the deal for each rounds
	
	int sumUnopened=0;
	int unopenedCount=0;
	double avg =0.0;
	double deal=0.0;
	double rounds=0.0;
	
	int i=1;
	
	while ( i <= caseAmount){
		
		if(cases[i].opened == false){
			
			//sum the values of the unopened cases
			
			unopenedCount++;
			sumUnopened = sumUnopened + cases[i].caseValue;

		}
		i++;
	}

	avg= (sumUnopened/unopenedCount) * 1.0;
	
	// tried casting as a double
	double curr= currRound * 1.0;
	double num= numRounds * 1.0;
	
	rounds= (curr / num) ;
	
	deal= avg * rounds;
	
	return deal;
}


void gameOfodds(CaseData cases[], int luckyCase ){
	
	//this is my twist
	
	int best;
	int oddsChoice;
	cout<<"________________________________________________________________________________________________________________________\n";
	cout<<"\n\t\tSince you actually made it this far...the banker find yuh brave"<<endl;
	cout<<"\n\n But he feeling a lil sorry for you. We know trinis like plenty money..but they know just how to lose it.."<<endl;
	cout<<"\n\tSo, he would like to play a game of odds with you...odds of what? Continue to find out haha"<<endl;
	cout<<"\n\t\t\tYou choose: best less than 10 or best less than 20"<<endl;
	cin>>best;
	
	cout<<"\n\n\t\t\tArite, Best less than "<<best<<" it is ... goodluck"<<endl;
	
	int question = rand () % best + 1; //1-10 or 1-20 
	
	if(question <= (best/2) + 1){  //best 10 = 10/2 = 5+1=6  //best 20 = 20/2 = 10 +1 = 11 
		cout<<"\n\t\tWhat are the odds between 1 - "<<best<<" you lose 1/2 your money? "<<endl;
		cin>>oddsChoice;
		
		// if random num is 4 and you select 3,4,5 you would either win or lose money
		
		if(oddsChoice == question || oddsChoice == question + 1 || oddsChoice == question - 1){ 
			cout<<"\n\t\tWayyyyys, you rel unlucky todayyyy! "<<endl;
			cout<<"\n\tYou would've received $" << cases[luckyCase].caseValue<<endl;
			
			cases[luckyCase].caseValue = cases[luckyCase].caseValue/2;
		}
		else
			cout<<"\n\t\t\tIssa good thing you didn't win these odds...aha"<<endl;
	}
	else {
		cout<<"\n\t\tWhat are the odds between 1 - "<< best << " you DOUBLE your money right now? "<<endl;
		cin>>oddsChoice;
			
			if(oddsChoice == question  || oddsChoice == question + 1 || oddsChoice == question - 1){
				cout<<"\n\t\tYou rel lucky todayyyy! "<<endl;
				cout<<"\n\tYou would've received $" << cases[luckyCase].caseValue<<endl<<endl;
				
				cases[luckyCase].caseValue = cases[luckyCase].caseValue * 2;
			}
			else{
				cout<<"\n\tWayyyys, you rel unlucky todayyy! But don't worry, atleast you still have your lucky case" <<endl;
				cout<<"\t\tI hear somebody now lose half the money in their case in the next room "<<endl;
			}
	}
}


void outcomes(CaseData cases[], int luckyCase, string name){
	
	string spend;
	
	cout<<"\n\t\t\t* The value of your lucky case # "<<luckyCase<< " is $" <<cases[luckyCase].caseValue<<" * "<<endl<<endl;
	
	if(cases[luckyCase].caseValue >= 1000000)
		cout<<"\t\tYou walking out of here a M I L L O N A I R E"<<endl<<endl;
	else 
		if(cases[luckyCase].caseValue >=500000)
			cout<<"\t\tYou leaving here $"<<cases[luckyCase].caseValue<<" R I C H E R " <<endl<<endl;
		else
			if(cases[luckyCase].caseValue >=50000)
				cout<<"\t\tNot bad, not bad, i see you made some bad choices along the way"<<endl<<endl;
			else
				if(cases[luckyCase].caseValue < 50000)
					cout<<"\t\t\tYou sure that was your lucky case? "<<endl<<endl;
			
		cout<<"\t\t\tSo how you gonna spend all this money? "<<endl;
		cin>>spend;
		
		cout<<"\n\t\t\tNice Nice, well is your money."<<endl;
		cout<<"\n\tJust remember be safe and it was good having you! lata "<<name<<endl;
			
			
}


void playGame(CaseData cases[], int caseAmount, int numRounds, int rounds[]){
	
	//game play
	
	int i=1;
	int caseChoice=1;
	int luckyCase;
	float offer;
	int playerOption;
	
	string name;
	
	cout<<"\t\t\t      Choose your lucky case \n";
	printCases(cases, caseAmount, caseChoice);
	
	cin>> caseChoice;
	
	luckyCase= caseChoice;
	
	cout<<"\t\t\tYou have selected case number "<<caseChoice<<endl;
	cout<<"\t     I hope you feeling that in yuh belly because it's final "<<endl;
	cout<<"\n\t * if yuh have it in you, wait til the end for a risk or reward * "<<endl;
	
	cout<<"\n\tBefore we begin, tell me your first name / nick name / anything you go by: ";
	cin>>name;
	
	cout<<"\n\n\tNice, Welcome "<<name<<"!"<<endl;
	
	cases[caseChoice].opened = true; //treating like it is opened
	
	for (int equalVal =1;equalVal<= caseAmount ; equalVal++){
		
		if(cases[caseChoice].caseValue == cases[equalVal].contents){
			cases[equalVal].contentUsed = false; //treating the contents as unopened so it would remain on the money board
			equalVal = caseAmount;
		}
	}
	
	while(i < numRounds ){
		
		//does not go up to (<=) numRounds because the last rounds is my twist.
		
		cout<<"\n\n\t\t\t\t******ROUND "<<i<<"*******\n\n";
		cout<<"\t\t\t You can open "<<rounds[i]<< " cases this round \n\n";
		
		int caseNum = rounds[i];
		int c=1;
		
		while ( c <= caseNum ){
			
			printCases(cases, caseAmount, caseChoice);
		
			cout<<"\t\tCase # "<< c <<" of this rounds:";
			cin>>caseChoice;
			
			while(!isValidCase(cases,caseChoice,caseAmount)){
			
				if(caseChoice < 1 || caseChoice > caseAmount){
					cout<<"\t\tWhere you seeing that number? Choose one you seeing please & thanks: ";
					cin>>caseChoice;
				}
				else
					if(cases[caseChoice].opened == true){
						cout<<"\t\tAy, you choose that case already. Choose ah next one please & thanks: ";
						cin>>caseChoice;
					}
			}
				
			cases[caseChoice].opened = true; //case was opened
			
			for (int equalVal =1;equalVal<= caseAmount ; equalVal++){
		
				if(cases[caseChoice].caseValue == cases[equalVal].contents){
					cases[equalVal].contentUsed = true; //contents was used
					equalVal = caseAmount;
				}
			}
			
			
			cout<<"\n\t\tCase "<<caseChoice<<" has a value of $"<<cases[caseChoice].caseValue<<endl;
			
			printContents(cases, caseAmount, caseChoice);
	     	
	     	c++;
		}
		
		if ( i < numRounds){
		
			offer = bankerDeal (cases,caseAmount ,i, numRounds );
			
			cout<<"\n\t\tThe banker is calling...."<<endl<<endl;
			cout<<"\t\tHe plans to offer you a deal of $"<<fixed<< setprecision(2) <<offer<<endl;	
			cout<<"\n\t\t.....DEAL (1) OR NO DEAL (0)......"	;
			
			cin>>playerOption;
			
			//checks valid choice
			
			while(!isValidChoice(playerOption)){
				cout<<"Enter a valid choice :) ";
				cin>>playerOption;
			}
			
			if(playerOption == 1){
				cout<<"\n\n\t\tYou have taken the deal!!! good choice or bad choice? ahaha "<<endl;
				cout<<"\t\t You now have $"<<offer<<endl;
				
				if(cases[luckyCase].caseValue > offer)
					cout<<"\n\t\tOh no, that's rel unlucky ahah...hardluck "<<endl;
				
				else
					cout<<"\n\t\tGood thing you took the deal, your lucky case wasn't so lucky.."<<endl;
					
				outcomes(cases, luckyCase, name);
					
				exit(0);
			}	
		}
		
		
	i++;
	}
	
	//last round of game
	gameOfodds(cases,luckyCase);
	
	outcomes(cases, luckyCase, name);
	
}


int main(){
	
	srand(time(NULL));
		
	CaseData cases[30]; 
	
	int caseAmount;
	int rounds[20];
	
	cout<<"\t\t==============================================\n";
	cout<<"\t\t\t  D E A L - O R - N O - D E A L\n";
	cout<<"\t\t\t\t ~trini edition~ \n";
	cout<<"\t\t==============================================\n\n";
	cout<<"\t\t    Select number of cases to play the game: \n\n";
	cout<<"\t\t\t * 16\t\t\t* 22\n";
	cout<<"\t\t\t * 18\t\t\t* 24\n";
	cout<<"\t\t\t * 20\t\t\t* 26\n";
	
	cin>>caseAmount;
	
	while(!isValidAmount(caseAmount)){
		cout<<"Invalid amount...Select a valid amount of cases please & thanks : "<<endl;
		cin>>caseAmount;
	}
	
	int numRounds= readFiles(cases, caseAmount, rounds);
	cout<<"\n\t\tNumber of rounds: "<<numRounds<<endl<<endl;
	
	initialize(cases, caseAmount);
	
	shuffleValues(cases, caseAmount);
	
	//printStruct(cases, caseAmount);

	playGame( cases, caseAmount, numRounds, rounds);
	
	return 0;
}
