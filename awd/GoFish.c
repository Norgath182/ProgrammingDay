/**
* GoFish.c
* Eric Voigt
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

void printPlayerHand(int *playerHand){
	int x=0;
	while(playerHand[x]!=0){
		printf("[%d]",playerHand[x]);
		x++;
	}
	printf("\n");
}

int find(int find,int arr[]){
	for(int x=0;x<20;x++)
		if(arr[x]==find)
			return 1;
	return 0;
}

void playerDoubles(int *playerHand,int *playerLoc){
	int x=0,t=0;
	int temp[20];
	while(playerHand[x]!=0){
		if(!find(playerHand[x],temp)){
			temp[t]=playerHand[x];
			t++;
		}else{
			playerLoc--;
			x--;
		}
		x++;
	}
}

int main(){
	srand(time(NULL));
	int playerLoc,opponentLoc,
		game=1;
	int playerHand[20], opponentHand[20];
	char gus;
	
	printf("----------Welcome to Go Fish!----------\n\n");
	
	for(int x=0;x<5;x++){
		playerHand[x]=deal();
		opponentHand[x]=deal();
	}
	playerLoc=5;
	playerLoc=5;
	for(int x=5;x<20;x++){
		playerHand[x]=0;
		opponentHand[x]=0;
	}
	
	printf("Your hand is:\n");
	printPlayerHand(playerHand);
	//printArray(opponentHand);
	
	while(game){
		/*
		if(
		
		*/
		
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
	
	return 0;
}
