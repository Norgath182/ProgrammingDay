/*File Name: HW2Ladley (BlackJack)
 *Student Name: Ryan Ladley
 *Date: 8 February 2015
 *Purpose: To make a blackjack game
 *How to use: Run the .exe and know blackjack. The program prompts properly.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*Function Name: poulateDeck
 *Prototype: void populateDeck(int *deck)
 *How To Use: Used at the begining of program to create new deck
 *Purpose: Adds the 52 standard card values to the deck
 */
void populateDeck(int *deck){
    int card_count;
    
    //add non-face cards to deck
    for(int i = 0; i < 4; i++){
        for(int n = 2; n < 12 ;n++){
            deck[card_count] = n;
            card_count++;
        }
    }
    //add face cards to deck
    for(int i = 0; i < 12; i++){
        deck[card_count] = 10;
        card_count++;
    }
}

/*Function Name: shuffleDeck
 *Prototype: void shuffleDeck(int *deck)
 *How To Use: Shuffles the given array
 *Purpose: Shuffles the deck into a random order
 *Uses Fisher-Yates Shuffle*/
void shuffleDeck(int *deck){
    srand(time(NULL));
    int random_number, temp;
    
    for( int i = 0; i < 52; i++){
        random_number = rand()%52;
        
        temp = deck[i];
        deck[i] = deck[random_number];
        deck[random_number] = temp;
    }
}

/*Function Name: checkGarbage
 *Prototype: int checkGarbage()
 *How To Use: Place in a confition statement after scanner. If comes back true, resart the scanner loop
 *Purpose: Checks for unwanted char input
 */
int checkGarbage(){
    char garbage;
    int counter = 0;
    while((garbage = getchar()) != EOF && garbage != '\n'){
        counter++;
    }
    if(counter){
        printf("Bets are usually numbers.");
    }
    return counter;
}

/*Function Name: initiateHand
 *Prototype: void initiateHand(int *player)
 *How To Use: Used once for each player the begining of the program to properly start there hand
 *Purpose: Populates hand for first time, which includes initial credit amouny
 */
void initiateHand(int *player){
    //Element 0 shows how many cards the player has in hand;
    for(int i = 0; i<12; i++){
        player[i] = 0;
    }
    player[13] = 100; // Total Credits
    player[14] = 0;  //Current Bet
}

/*Function Name: resetHand
 *Prototype: void resetHand(int *player)
 *How To Use: Used at the end of each round to zero the indicated players hand, but keep the current credit
 *Purpose: Populated hand for new round
 */
void resetHand(int *player){
    //Element 0 shows how many cards the player has in hand;
    for(int i = 0; i<12; i++){
        player[i] = 0;
    }
    player[14] = 0; // Current Bet
}

/*Function Name: dealCard
 *Prototype: void dealCard(int *deck, int *player, int *dealt_count)
 *How To Use: Call when a player needs a new card in their hand
 *Purpose: Deals Card to indicated player
 */
void dealCard(int *deck, int *player, int *dealt_count){
    if(!(player[0] >= 11)){
        player[0]++;//player[0] shows how many cards the player has in his hand
        player[player[0]] = deck[dealt_count[0]];
        dealt_count[0]++;
    }
}

/*Function Name: checkWild
 *Prototype: int checkWild(int * player)
 *How To Use: Call when players hand is greater than 21. Returns true if hand contains wild
 *Purpose: Checks for an 11 and changes it to a one
 */
int checkWild(int * player){
    for(int i = 0; i<= player[0]; i++){
        if(player[i] == 11){
            player[i] = 1;
            printf("\nLet me change that 11 for you.\n");
            return 1;
        }
    }
    return 0;
}

/*Function Name: displayPlayer
 *Prototype: void displayPlayer(int *player)
 *How To Use: Call when you want to see the indicated players hand
 *Purpose: Shows Players current hand
 */
void displayPlayer(int *player){
    printf("\n");
    for(int i = 1; i <=player[0]; i++){
        printf("%d ", player[i]);
    }
}

/*Function Name: calculateTotal
 *Prototype: int calculateTotal(int *player)
 *How To Use: Call when you want recalcuate the indicated players total hand 
 *Purpose: Calculates the total value of a players hand
 */
void calculateTotal(int *player){
    player[12] = 0; //player[12] shows the value of all cards in hand
    //Element 0 shows how many cards the player has in hand;
    for(int i = 1; i <=player[0]; i++){
        player[12] += player[i];
    }
}

/*Function Name: promptPlayer
 *Prototype: int playerPrompt(int *player))
 *How To Use: Call when you need human players interaction. Returns True if player wants to hit 
 *Purpose: Contains all prompts that requires user input (Bet/Hit)
 */
int playerPrompt(int *player){
    char  response;
    int current_bet;
    
    displayPlayer(player);
    printf("\n\nCredit Total: %d", player[13]);
    printf("\nCurrent Bet: %d", player[14]);
    while(1){
        printf("\n\nHow many credits would you like to bet? ");
        scanf("%d", &current_bet);
        if(checkGarbage() != 0){
            continue;
        }
        else{
            if((current_bet + player[14] > player[13])){
                printf("You're not that rich, try again.");
                continue;
            }
            else{
                if(current_bet < 0){
                    printf("Look at the brains on this one. A positive bet is probably best");
                }
                player[14] += current_bet;
                break;
            } 
        }
        
    }
    while(1){
        printf("\nWill you hit? (y/n) ");
        scanf(" %c", &response);
        if(response == 'y'){
            return 1;
        }
        else{
            if(response == 'n'){
                return 0;
            }
            else{
                printf("\nYou're not very smart are you? Enter 'y' to hit or 'n' to stand.");
                continue;
            }

        }
    }
    
}

/*Function Name: playersTurn
 *Prototype: void playersTurn(int *deck, int *player, int *dealt_count, int * dealer)
 *How To Use: Call on given players turn. Variables include current deck, player, the number of cards dealt from deck, and dealer
 *Purpose: Contains all actions that happen during human players turn
 */
void playersTurn(int *deck, int *player, int *dealt_count, int * dealer){
    int hit_boolean = 1;
    int wild_boolean = 0;
    
    dealCard(deck, player, dealt_count);
    
    while(hit_boolean){//Player Ones Loop
            dealCard(deck, player, dealt_count);
            calculateTotal(player);
            
            if(player[12] > 21){
                int wild_boolean = checkWild(player) ;
                
                if(wild_boolean){
                    printf("\nDealer:");
                    printf("\n------------");
                    displayPlayer(dealer);
                    printf(" ?\n");
                    printf("\nPlayer:");
                    printf("\n------------");
                    hit_boolean = playerPrompt(player);
                }
                else{
                    break;
                }
            }
            else{
                printf("\nDealer:");
                printf("\n------------");
                displayPlayer(dealer);
                printf(" ?\n");
                printf("\nPlayer:");
                printf("\n------------");
                hit_boolean = playerPrompt(player);
            }
        }
}

/*Function Name: dealersTurn
 *Prototype: void dealersTurn(int *deck, int * dealer, int *dealt_count, int *player)
 *How To Use: Call on dealers. Variables include current deck, dealer, the number of cards dealt from deck, and the opponent player,  
 *Purpose: Contains all actions for the computer (Dealers) turn
 */
void dealersTurn(int *deck, int * dealer, int *dealt_count, int *player){
    int hit_boolean = 1;
    int wild_boolean;
    
    dealCard(deck, dealer, dealt_count);
    if(player[12] <= 21){
            calculateTotal(dealer);
            
            while(hit_boolean){//dealer goes
                if((dealer[12] > player[12]) && (dealer[12] <21)){
                    printf("\nDealer:");
                    printf("\n------------");
                    displayPlayer(dealer);
                    
                    hit_boolean = 0;
                }
                else{
                    dealCard(deck, dealer, dealt_count);
                    calculateTotal(dealer);
                    if(dealer[12] >=21){
                        wild_boolean = checkWild(dealer);
                        if(wild_boolean){
                            continue;
                        }
                        else{
                            printf("\nDealer:");
                            printf("\n------------");
                            displayPlayer(dealer);
                            hit_boolean = 0;
                        }
                    }
                }
            }
        }
    calculateTotal(dealer);
    //This section would be used for dealer to make sure the dealer only hits up to 17
    //However since there is no split, and no other player, that would just be silly 
    /*while(hit_boolean){
        if((dealer[12] < 17)){
            dealCard(deck, dealer, dealt_count);
            calculateTotal(dealer);
            if(dealer[12] > 21){
                wild_boolean = checkWild(dealer);
                if(wild_boolean){
                    continue;
                }
            }
        }
        else{
            hit_boolean = 0;
        }
    }*/
}

/*Function Name: displayFinal
 *Prototype: int displayFinal(int *player, int *dealer)
 *How To Use: Call when all players have gone. Variables include Player and  Dealer 
 *Purpose: Shows end of round statistics
 */
int displayFinal(int *player, int *dealer){
    printf("\n\nFINAL SCORES:");
    printf("\n-------------");        
    
    printf("\nPlayer:");;
    displayPlayer(player);
    printf("\nTotal: %d", player[12]);
    
    printf("\n-------------");
    
    printf("\nDealer:");
    displayPlayer(dealer);
    printf("\nTotal: %d ", dealer[12]);
    printf("\n-------------");
}
 
/*Function Name: calculateWinner
 *Prototype: int calculateWinner(int *player, int *dealer)
 *How To Use: Call when all players have gone. Variables include PLayer and Dealer
 *Purpose: Determines who won the round
 */
int calculateWinner(int *player, int *dealer){
    if((player[12] <= 21)&& (dealer[12] > 21)){
        player[13]+= player[14];
        printf("\nYou won.");
        printf("\nIt's almost like this is your job or something.");
    }
    else{
        player[13] -= player[14];
        printf("\nHah! Loser.");
    }
    printf("\nCredit Total: %d", player[13]);
}

/*Function Name: Play Again
 *Prototype: int playAgain(int *player)
 *How To Use: Call when a game needs to be restarted. If the given player has no more credits, the game ends. Return true if a new round is to be played
 *Purpose: To determine if game is to be replayed
 */
int playAgain(int *player){
    char again;
    
    
    while(1){
        if (player[13] == 0){
            printf("\nLosers don't get to play. Bye.");
            return 0;
        }
        else{
            printf("\nWant to play again? (y/n) ");
            scanf(" %c", &again);
            if(again == 'y'){
                return 1;
            }
            else{
                if(again == 'n'){
                    return 0;
                }
                else{
                    printf("This isn't that hard. Type 'y' to keep going or 'n' to stop.");
                    continue;
                }
            }
        }
    }
    
}

/*Function Name: main()
 *Prototype: int main()
 *How To Use: The Main Function
 *Purpose: To run all functions required for the black jack game.
 */
int main() {
    //Create, populate,  and shuffle deck
    int * deck = NULL;
    deck = (int*)malloc(52 * sizeof(int));
    populateDeck(deck);
    shuffleDeck(deck);
    int dealt_count = 0;
    
    //Create Player Hand Arrays
    //Element 0 shows how many cards the player has in hand (Up to 11);
    //Element 12 shows the total value of all cards
    //Element 13 acts as a total "credit" amount. 
    //Element 14 acts as current bet amount;
    int * dealer = NULL;
    dealer = (int*)malloc(15 * sizeof(int));
    initiateHand(dealer);
    dealer[13] = -1; //The dealer doesnt have credit. This distiguishes it from player;
    
    int * player_one = NULL;
    player_one = (int*)malloc(15 * sizeof(int));
    initiateHand(player_one);
    
    //Other Variables
    int continue_boolean = 1;
    
    //Play Game
    printf("***********************************************");
    printf("\n*-----------------Almost----------------------*");
    printf("\n*---------------BlackJack!--------------------*");
    printf("\n***********************************************\n");
    
    while (continue_boolean){
        dealCard(deck, dealer, &dealt_count);
        
        playersTurn(deck, player_one, &dealt_count, dealer);
        dealersTurn(deck, dealer, &dealt_count, player_one);
        
        displayFinal(player_one, dealer);
        calculateWinner(player_one, dealer);
        
        continue_boolean = playAgain(player_one);
        if(continue_boolean){//Resets Game
            resetHand(player_one);
            resetHand(dealer);
            if(dealt_count >= 30){//If to many cards have been used, reshuffle deck.
                shuffleDeck(deck);
                dealt_count = 0;
            }
        }
    }
    
    return (0);
}
