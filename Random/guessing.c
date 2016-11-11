#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void clearBuffer(){
	char ch;
	while((ch=getchar()) != '\n' && ch != EOF);
}

void promptUser(int * gus){
	while(1){
		printf("Pick a card: ");
		scanf("%d", gus);
		clearBuffer();
		if((*gus < 2)||(*gus > 11)){
			printf("That isn't a card.\n");
			continue;
		}
		else{
			break;
		}
	}
}

int deal(){
	int deck[]={2,3,4,5,6,7,8,9,10,10,10,10,11};
	return deck[rand() %13];
}

int checkAce(int * hand,int total){
	int i;
	for(i=0; i<10; i++){
		if(hand[i]==11){
			puts("found 11");
			total-=10;
			return 1;
		}
	}
	return 0;
}

int main(){
	srand(time(NULL));
	int gus,total=0;
	int hand[10];
	
	int i;
	for(i=0;i<3;i++){
		hand[i]=deal();
		printf("%d ",hand[i]);
		total+=hand[i];
	}
	while(1){
		if(total>21){
			if(checkAce(hand,total)){
				continue;
			}
			printf("You lose with %d\n",total);
			break;
		}else{
			printf("You may win with %d\n",total);
			break;
		}
	}
	
	return 0;
}