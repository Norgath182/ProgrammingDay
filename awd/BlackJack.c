/**
 * BlackJack.c
 * Eric Voigt
 * CS 2060
 * 9.2.15
 * purpose: a terminal version of the Black Jack card game
 * to use: run the executable or ./BlackJack
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void clearBuffer(){
	char ch;
	while((ch=getchar()) != '\n' && ch != EOF);
}

int deal(){
	int deck[]={2,3,4,5,6,7,8,9,10,10,10,10,11};
	return deck[rand() %13];
}

int dealerCheckAce(int * dealerHand,int dealerTotal){
	for(int i=0; i<10; i++){
		if(dealerHand[i]==11){
			return dealerTotal-=10;
		}
	}
	return dealerTotal;
}

int playerCheckAce(int * playerHand,int playerTotal){
	for(int i=0; i<10; i++){
		if(playerHand[i]==11){
			return playerTotal-=10;
		}
	}
	return playerTotal;
}

int main(){
	srand(time(NULL));
	int playerTotal=0, dealerTotal=0,
	      points=100,input=0,
	      playerCardLoc=0,dealerCardLoc,
	      playerBet,dealerBet,totalBet,
	      game=1;
	int playerHand[10], dealerHand[10];
	char gus;
	
	

	while(game){
		playerTotal=0;
		playerBet=0;
		playerCardLoc=0;
		dealerTotal=0;
		dealerBet=10;
		dealerCardLoc=0;
		totalBet=0;				

		for(playerCardLoc; playerCardLoc<2; playerCardLoc++){
			playerHand[playerCardLoc]=deal();
			dealerHand[playerCardLoc]=deal();
			playerTotal+=playerHand[playerCardLoc];
			dealerTotal+=dealerHand[playerCardLoc];
		}

		dealerCardLoc=playerCardLoc;
		while(dealerTotal<17){
			dealerCardLoc++;
			dealerHand[dealerCardLoc]=deal();
			dealerTotal+=dealerHand[dealerCardLoc];
			dealerTotal=dealerCheckAce(dealerHand,dealerTotal);
		}

		if(dealerTotal==17)
			dealerBet=10;
		else if(dealerTotal==18)
			dealerBet=20;
		else if(dealerTotal==19)
			dealerBet=30;
		else if(dealerTotal==20)
			dealerBet=40;
		else if(dealerTotal==21)
			dealerBet=50;
		else
			dealerBet=0;

		printf("Welcome to BlackJack!\n\tDealer:\n\t\t[] %d\n\n\tYou:\n\t\t%d %d\n\tYour total: %d\nWhat, if anything, would you like to bet?.\n",
			   dealerHand[1],playerHand[0],playerHand[1],playerTotal);
		clearBuffer();
		scanf("%d",&input);
		playerBet+=input;

		printf("You bet: %d. The total bet is now %d.\nWould you like to hit or stay? Press 'h' to hit or 's' to stay.\n",
			   input,playerBet+dealerBet);

		clearBuffer();
		scanf(" %c",&gus);
		while(!(gus=='h' || gus=='s')){
			printf("Please enter a valid option.\n");
			clearBuffer();
			scanf("%c",&gus);
		}
		
		while(gus!='s'){
			playerCardLoc++;
			playerHand[playerCardLoc]=deal();
			playerTotal+=playerHand[playerCardLoc];
			playerTotal=playerCheckAce(playerHand,playerTotal);
			printf("You got a: %d. Your total is now %d.\n",playerHand[playerCardLoc],playerTotal);
			if(playerTotal>21){
				printf("You went over 21 and lose.\n");
				break;
			}else{
				printf("What, if anything (including but not limited to your life), more would you like to bet?\n");
				clearBuffer();
				scanf("%d",&input);
				playerBet+=input;
				printf("You bet: %d. The total bet is now %d.\nPress 'h' to bet and hit again or 's' to stay.\n",
					   input,playerBet+dealerBet);
				clearBuffer();
				scanf("%c",&gus);
				while(!(gus=='h' || gus=='s')){
					printf("Please enter a valid option.\n");
					clearBuffer();
					scanf("%c",&gus);
				}
			}
		}

		if(dealerTotal>21 || (playerTotal<22 && playerTotal>dealerTotal)){
			points+=dealerBet;
			printf("You win %d points against the dealer with %d, while the dealer had %d.\nYour point total is now %d.\n",
				   dealerBet,playerTotal,dealerTotal,points);
		}else if(dealerTotal==playerTotal){
			printf("You tied against the dealer at %d. You don't get sh*t points.\n",playerTotal);
		}else{
			points-=playerBet;
			printf("You lost %d points against the dealer with %d, while the dealer had %d.\nYour point total is now %d.\n",
				   playerBet,playerTotal,dealerTotal,points);
		}
		if(points<=0){
			printf("You went and spent your life away on a card game. Way to go, loser. You have no more points.\n");
			break;
		}
		
		printf("Would you like to continue? Enter 'y' to continue or 'n' to stop.\n");
		clearBuffer();
		scanf("%c",&gus);

		while(!(gus=='y' || gus=='n')){
			printf("Please enter a valid option.\n");
			clearBuffer();
			scanf("%c",&gus);
		}
		game=(gus=='y');
	}
	
	printf("Good bye. Come again!\n");	

	return 0;
}