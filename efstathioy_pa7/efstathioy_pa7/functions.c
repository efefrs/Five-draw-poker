/*
Author: Niko D Efstathioy

Class CptS 121, Fall 2020; Lab Section 1

Programming Assignment: Lab1PA7

Date: November 28, 2020

Description: This program runs the game poker
*/

#include "functions.h"


/* card initializating */
/*
Function: shuffle_deck()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: Shuffles the cards in deck
Input Parameters: the deck array
Returns: N/A
Preconditions: N/A
Postconditions: N/A
*/

void shuffle_deck(int wDeck[][13]) {
	int row = 0, /* row number */
		column = 0, /* column number */
		card = 0; /* card number */

	/* initializes/resets the deck before "shuffling" */
	for (int r = 0; r < 4; r++) { /* r is row */
		for (int c = 0; c < 13; c++) { /* c is column */
			wDeck[r][c] = 0;
		}
	}

	/* for each of the 52 cards, choose the slot of the deck randomly */
	for (card = 1; card <= 52; card++) {

		/* choose new random location until unoccupied slot found */
		do {
			row = rand() % 4;
			column = rand() % 13;
		} while (wDeck[row][column] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][column] = card;
	}
}

/*
Function: deal_cards()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: Deals the cards in deck
Input Parameters: the deck, face, and suit array as well as the given players hand
Returns: N/A
Preconditions: N/A
Postconditions: N/A
*/

void deal_cards(int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* player_hand) {
	int row = 0, /* row number */
		column = 0, /* column number */
		card = 0, /* card number */
		i = 0; /* count number for loop */

	for (i = 0; i < POKER_HAND_SIZE; i++) {

		/* checks the face value to see if there is a card in that slot (-1 means there is not) */
		if ((*player_hand).hand_array[i].face_index == -1) {

			/* continues to search until a card is found */
			do {
				row = rand() % 4;
				column = rand() % 13;
			} while (wDeck[row][column] == 0);

			/* sets the current hand slot to the found card */
			(*player_hand).hand_array[i].face_index = column;
			(*player_hand).hand_array[i].suit_index = row;

			/* removes that card from the deck */
			wDeck[row][column] = 0;
		}
	}

}

/* home screens */
/*
Function: print_home_screen()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: Prints welcome screen as well as options for the player to choose from
Input Parameters: N/A
Returns: Anything, we are using return to exit the function
Preconditions: N/A
Postconditions: N/A
*/

int print_home_screen(int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* dealer_hand_ptr, Hand dealer_hand) {

	int choice = 0;

	system("cls");
	printf("<<<Welcome to simplified five card draw poker!>>>\n");
	printf("Please input a number from the options below:\n");
	printf("1 Play game\n2 Show rules\n3 Test AI\n4 Exit\n");
	printf("Waiting for user input...\n");

	/* do while statement that checks for a correct option for the choices printed */
	do {
		scanf("%d", &choice);
	} while (choice < 1 || choice > 4);

	/* play game */
	if (choice == 1) {
		return 0;
	}
	/* show rules */
	else if (choice == 2) {
		print_poker_rules(wDeck, wFace, wSuit, dealer_hand_ptr, dealer_hand);
		return 0;
	}
	else if (choice == 3) {
		test_dealer_intelligence(wDeck, wFace, wSuit, dealer_hand_ptr, dealer_hand);
		return 0;
	}
	/* exit */
	else if (choice == 4) {
		exit(0);
	} 

	return 0;
}

/*
Function: print_poker_rules()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: Prints the rules of our game
Input Parameters: N/A
Returns: N/A
Preconditions: N/A
Postconditions: N/A
*/

void print_poker_rules(int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* dealer_hand_ptr, Hand dealer_hand) {

	system("cls");
	printf("<<<Rules of poker>>>\n");
	printf("At the start of the game you and the dealer will each draw %d cards\n", POKER_HAND_SIZE);
	printf("You and the dealer then get to decide what cards to replace out of your hand\n");
	printf("You can discard no more than 3 cards\n");
	printf("Then you compare hands and move on to the next round\n");
	printf("There are many special types of hands in poker:\n");
	printf("Pair: two cards of the same face value\n");
	printf("Two pair: two different pairs\n");
	printf("Three of a kind: three cards of the same face value\n");
	printf("Straight: cards in order such as 2 3 4 5 6 or 10 J Q K A. You'll notice that ace can be treated as a 1 or a 14.\n");
	printf("Flush: all cards have the same suit type\n");
	printf("Four of a kind: four cards of the same face value\n");
	printf("Two pair is the worst and four of a kind is the best (the rest are in order as well from top to bottom)\n");
	printf("When comparing hands you first must see if you have different hand types,\n");
	printf("if your hand types are different then the person with the best hand type wins\n");
	printf("If you have the same hand type you then must compare cards!\n");
	printf("If the two hands are identical then you each get half a point\n");
	printf("Otherwise, the person with the higher valued cards gets the point\n");
	printf("Ace is the highest value followed by king, queen, jack, ten, ..., ending with 2 as the worst\n");
	printf("You now know how to play poker!\n");
	printf("Press any key to return to the home screen...\n");
	getch();
	print_home_screen(wDeck, wFace, wSuit, dealer_hand_ptr, dealer_hand);
}

/* card actions */
/*
Function: print_poker_hand()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: Prints the given hand
Input Parameters: player_hand
Returns: N/A
Preconditions: N/A
Postconditions: N/A
*/

void print_poker_hand(const char* wFace[], const char* wSuit[], Hand* player_hand) {

	for (int i = 0; i < POKER_HAND_SIZE; i++) {
		printf("[%d]%s of %s     ", i + 1, wFace[(*player_hand).hand_array[i].face_index], wSuit[(*player_hand).hand_array[i].suit_index]);
	}
	printf("\n");
}

/*
Function: compare_poker_hands()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: sees which hand was better
Input Parameters: the two scores
Returns: N/A
Preconditions: N/A
Postconditions: N/A
*/

int compare_poker_hands(int user_score, int dealer_score) {

	/* player wins */
	if (user_score > dealer_score) {
		return 1; 
	}
	/* dealer wins */
	else if (dealer_score > user_score) {
		return 2;
	}
	/* tie */
	else {
		return 3;
	}
}

/*
Function: discard_cards_user()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: discards user cards (dealer does it in evaluate_dealer_hand())
Input Parameters: the player hand
Returns: N/A
Preconditions: N/A
Postconditions: N/A
*/

void discard_cards_user(Hand* player_hand_ptr) {

	int discard_amount = -1, chosen_card = -1;

	/* asks the player how many cards to discard*/
	printf("\nHow many cards would you like to discard? Please pick a number between 0 and 3\n");
	do {
		scanf("%d", &discard_amount);
	} while (discard_amount > 3 || discard_amount < 0);
	
	/* asks the player to discard until the amount given above is discarded */
	for (int i = 0; i < discard_amount; i++) {
		/* asks the player to give a card to discard */
		do {
			printf("Please pick a card to discard\n");
			scanf("%d", &chosen_card);
		} while (chosen_card < 1 || chosen_card > POKER_HAND_SIZE || (*player_hand_ptr).hand_array[chosen_card - 1].face_index == -1);
		/* discards to the chosen card and resets for next iteration */
		(*player_hand_ptr).hand_array[chosen_card - 1].face_index = -1;
		printf("Card %d discarded successfully\n", chosen_card);
		chosen_card = -1;
	}
}

/*
Function: evaluate_dealer_hand()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: This massive function looks at the dealers hand and decides what to do from there, the logic should be easy enough to follow
Input Parameters: face array, suit array, hand as pointer, and hand
Returns: N/A
Preconditions: N/A
Postconditions: N/A
*/

void evaluate_dealer_hand(const char* wFace[], const char* wSuit[], Hand* dealer_hand_ptr, Hand dealer_hand) {

	/* initializing a parallel array to tell the ai to avoid any special case cards */
	int special_case_array[POKER_HAND_SIZE] = { 0 };
	initialize_integer_array(special_case_array, POKER_HAND_SIZE);

	int check_special_case = 0, discard_amount = 0, target_one = 0, target_two = 1, target_three = 2, no_special_case = 0, temp_target = 0;

	/* checking if dealer has a special case hand */
	check_special_case = check_poker_hand(dealer_hand_ptr);

	/* four of a kind */
	if (check_special_case >= 6000) {
		/* always keep four of a kind, last card doesn't matter */
		discard_amount = 0;
	}
	/* flush */
	else if (check_special_case >= 5000) {
		/* always keep the flush */
		discard_amount = 0;
	}
	/* straight */
	else if (check_special_case >= 4000) {
		/* always keep the straight */
		discard_amount = 0;
	}



	/* three of a kind */
	else if (check_special_case >= 3000) {
		/* keep three, discard rest */
		check_dealer_three_kind(special_case_array, dealer_hand_ptr);
		discard_amount = 2;
	}
	/* two pairs */
	else if (check_special_case >= 2000) {
		/* always keep two pairs, discard rest */
		check_dealer_two_pairs(special_case_array, dealer_hand_ptr);
		discard_amount = 1;
	}
	/* pair */
	else if (check_special_case >= 1000) {
		/* keep pair, discard rest */
		check_dealer_pair(special_case_array, dealer_hand_ptr);
		discard_amount = 3;
	}
	/* no special cases */
	else {
		no_special_case = 1;
		discard_amount = 3; // only this needs logic
	}
	/* does suit logic if there is no special case */
	/* if the dealer has a majority one suit, the dealer will try and find a flush */
	/* the dealer will NEVER acknowledge an almost straight, this my own deliberate choice as I never go for straights personally */
	 if (no_special_case == 1) {
		 discard_amount = discard_amount - check_dealer_suits(special_case_array, dealer_hand_ptr) + POKER_HAND_SIZE;
		 if (discard_amount < 0) {
			 discard_amount = 0;
		 }
	}

	 if (special_case_array[target_one] == 1) {
		 for (int r = 0; r < POKER_HAND_SIZE; r++) {
			 if (special_case_array[r] == 0 && r != target_two && r != target_three) {
				 target_one = r;
				 break;
			 }
		 }
	 }

	 if (special_case_array[target_two] == 1) {
		 for (int r = 0; r < POKER_HAND_SIZE; r++) {
			 if (special_case_array[r] == 0 && r != target_one && r != target_three) {
				 target_two = r;
				 break;
			 }
		 }
	 }

	 if (special_case_array[target_three] == 1) {
		 for (int r = 0; r < POKER_HAND_SIZE; r++) {
			 if (special_case_array[r] == 0 && r != target_one && r != target_two) {
				 target_three = r;
				 break;
			 }
		 }
	 }

	if (discard_amount > 0) {
		for (int card = 0; card < POKER_HAND_SIZE; card++) {
			/* I made a deliberate choice to always discard to search for three/four of kind, dealer will never hold onto a high value card in hopes of a two pair */
			/* if the chosen card isn't protected */
			if (special_case_array[card] == 0) {
				/* finds the highest value card to replace in the discard list */
				/* by the end of the for loop our three target variables will contain our lowest non-protected card values */
				if (check_for_ace((*dealer_hand_ptr).hand_array[card].face_index) < check_for_ace((*dealer_hand_ptr).hand_array[target_one].face_index) && check_for_ace((*dealer_hand_ptr).hand_array[target_one].face_index) >= check_for_ace((*dealer_hand_ptr).hand_array[target_two].face_index)
					&& check_for_ace((*dealer_hand_ptr).hand_array[target_one].face_index) >= check_for_ace((*dealer_hand_ptr).hand_array[target_three].face_index) && card != target_one && card != target_two && card != target_three) {
					target_one = card;
				}
				else if (check_for_ace((*dealer_hand_ptr).hand_array[card].face_index) < check_for_ace((*dealer_hand_ptr).hand_array[target_two].face_index) && check_for_ace((*dealer_hand_ptr).hand_array[target_two].face_index) >= check_for_ace((*dealer_hand_ptr).hand_array[target_one].face_index)
					&& check_for_ace((*dealer_hand_ptr).hand_array[target_two].face_index) >= check_for_ace((*dealer_hand_ptr).hand_array[target_three].face_index) && card != target_one && card != target_two && card != target_three) {
					target_two = card;
				}
				else if (check_for_ace((*dealer_hand_ptr).hand_array[card].face_index) < check_for_ace((*dealer_hand_ptr).hand_array[target_three].face_index) && check_for_ace((*dealer_hand_ptr).hand_array[target_three].face_index) >= check_for_ace((*dealer_hand_ptr).hand_array[target_one].face_index)
					&& check_for_ace((*dealer_hand_ptr).hand_array[target_three].face_index) >= check_for_ace((*dealer_hand_ptr).hand_array[target_two].face_index) && card != target_one && card != target_two && card != target_three) {
					target_three = card;
				}

			}
		}
	}


		/* reorders three discard targets from least to greatest in the case dealer is discarding less than three cards */
	if (check_for_ace((*dealer_hand_ptr).hand_array[target_one].face_index) > check_for_ace((*dealer_hand_ptr).hand_array[target_three].face_index)) {
		temp_target = target_one;
		target_one = target_three;
		target_three = temp_target;
	}
	if (check_for_ace((*dealer_hand_ptr).hand_array[target_two].face_index) > check_for_ace((*dealer_hand_ptr).hand_array[target_three].face_index)) {
			temp_target = target_two;
			target_two = target_three;
			target_three = temp_target;
	}
	if (check_for_ace((*dealer_hand_ptr).hand_array[target_one].face_index) > check_for_ace((*dealer_hand_ptr).hand_array[target_two].face_index)) {
			temp_target = target_two;
			target_two = target_one;
			target_one = temp_target;
	}


		/* discards the lowest cards after ensuring those cards aren't protected */
	if (special_case_array[target_one] == 0 && discard_amount > 0) {
			discard_amount -= 1;
			(*dealer_hand_ptr).hand_array[target_one].face_index = -1;
	}
	if (special_case_array[target_two] == 0 && discard_amount > 0) {
			discard_amount -= 1;
			(*dealer_hand_ptr).hand_array[target_two].face_index = -1;
			(*dealer_hand_ptr).hand_array[target_two].suit_index = -1;
	}
	if (special_case_array[target_three] == 0 && discard_amount > 0) {
			discard_amount -= 1;
			(*dealer_hand_ptr).hand_array[target_three].face_index = -1;
			(*dealer_hand_ptr).hand_array[target_three].suit_index = -1;
	}


}

/* poker hand checks*/
/*
Function: check_poker_pair()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: checks the given hand for a pair
Input Parameters: player_hand
Returns: score
Preconditions: N/A
Postconditions: N/A
*/

int check_poker_pair(Hand* player_hand_ptr) {

	int check_card = 0, card = 0, score = 0;

	for (card = 0; card < POKER_HAND_SIZE; card++) {
		for (check_card = 0; check_card < POKER_HAND_SIZE; check_card++) {
			/* checks if the two cards match */
			if ((*player_hand_ptr).hand_array[card].face_index == (*player_hand_ptr).hand_array[check_card].face_index && card != check_card) {
				/* returns 1000 which means they got a pair plus the value of the two cards in the pair */
				return 1000 + check_for_ace((*player_hand_ptr).hand_array[card].face_index) ;
			}

		}
	}

	return 0;
}

/*
Function: check_poker_two_pairs()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: Finds two pairs in the players hands
Input Parameters: player_hand
Returns: score
Preconditions: N/A
Postconditions: N/A
*/

int check_poker_two_pairs(Hand* player_hand_ptr) {

	int check_card = 0, card = 0, pair_flagger = -1, highest_pair = 0;

	for (card = 0; card < POKER_HAND_SIZE; card++) {
		for (check_card = 0; check_card < POKER_HAND_SIZE; check_card++) {
			/* checks if a pair is found and that pair has not been found before */
			if ((*player_hand_ptr).hand_array[card].face_index == (*player_hand_ptr).hand_array[check_card].face_index && card != check_card && pair_flagger != (*player_hand_ptr).hand_array[card].face_index) {
				
				/* checks if this is the highest valued pair we have found */
				if (highest_pair < check_for_ace((*player_hand_ptr).hand_array[card].face_index)) {
					highest_pair = check_for_ace((*player_hand_ptr).hand_array[card].face_index);
				}

				/* checks if two pairs have been found */
				if (pair_flagger != -1) {
					/* returns 2000 which indicates two pairs and adds the highest value pair in the case all players have a two pair hand */
					return 2000 + highest_pair;
				}

				/* flags the pair so we dont find the same pair twice */
				pair_flagger = (*player_hand_ptr).hand_array[card].face_index;
			}

		}
	}

	return 0;
}

/*
Function: check_poker_three_kind()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: checks the given hand for a three of a kind
Input Parameters: player_hand
Returns: score
Preconditions: N/A
Postconditions: N/A
*/

int check_poker_three_kind(Hand* player_hand_ptr) {

	int check_card = 0, card = 0, pairs_found = 0;

	for (card = 0; card < POKER_HAND_SIZE; card++) {
		for (check_card = 0; check_card < POKER_HAND_SIZE; check_card++) {
			/* looks for a pair */
			if ((*player_hand_ptr).hand_array[card].face_index == (*player_hand_ptr).hand_array[check_card].face_index && card != check_card) {
				/* if a pair is found we add to the pair count */
				pairs_found += 1;
				/* once we have found two pairs with the same card value we have found our three of a kind */
				if (pairs_found == 2) {
					return 3000 + check_for_ace((*player_hand_ptr).hand_array[card].face_index);
				}
			}
			
		}
		/* resets pair count after each card */
		pairs_found = 0;
	}

	return 0;
}

/*
Function: check_poker_four_kind()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: checks given hand for a four of a kind
Input Parameters: player_hand
Returns: score
Preconditions: N/A
Postconditions: N/A
*/

int check_poker_four_kind(Hand* player_hand_ptr) {

	int check_card = 0, card = 0, pairs_found = 0;

	for (card = 0; card < POKER_HAND_SIZE; card++) {
		for (check_card = 0; check_card < POKER_HAND_SIZE; check_card++) {
			/* looks for a pair */
			if ((*player_hand_ptr).hand_array[card].face_index == (*player_hand_ptr).hand_array[check_card].face_index && card != check_card) {
				/* if a pair is found we add to the pair count */
				pairs_found += 1;
				/* once we have found three pairs with the same card value we have found our four of a kind */
				if (pairs_found == 3) {
					return 6000 + check_for_ace((*player_hand_ptr).hand_array[card].face_index);
				}
			}

		}
		/* resets pair count after each card */
		pairs_found = 0;
	}

	return 0;
}

/*
Function: check_poker_flush()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: checks the given hand for a flush
Input Parameters: player_hand
Returns: score
Preconditions: N/A
Postconditions: N/A
*/

int check_poker_flush(Hand* player_hand_ptr) {

	int card = 0, hearts = 0, diamonds = 0, clubs = 0, spades = 0;

	/* counts the amount of each suit in hand */
	for(card = 0; card < POKER_HAND_SIZE; card++) {
		if ((*player_hand_ptr).hand_array[card].suit_index == 0) {
			hearts += 1;
		}
		else if ((*player_hand_ptr).hand_array[card].suit_index == 1) {
			diamonds += 1;
		}
		else if ((*player_hand_ptr).hand_array[card].suit_index == 2) {
			clubs += 1;
		}
		else if ((*player_hand_ptr).hand_array[card].suit_index == 3) {
			spades += 1;
		}
	}

	/* checks if there is a flush after counting up the suits */
	if (hearts == POKER_HAND_SIZE) {
		return 5000 + check_poker_highest_value(player_hand_ptr);
	}
	else if (diamonds == POKER_HAND_SIZE) {
		return 5000 + check_poker_highest_value(player_hand_ptr);
	}
	else if (clubs == POKER_HAND_SIZE) {
		return 5000 + check_poker_highest_value(player_hand_ptr);
	}
	else if (spades == POKER_HAND_SIZE) {
		return 5000 + check_poker_highest_value(player_hand_ptr);
	}
	
	return 0;
}

/*
Function: check_poker_straight()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: checks the given hand for a straight
Input Parameters: player_hand
Returns: score
Preconditions: N/A
Postconditions: N/A
*/

int check_poker_straight(Hand* player_hand_ptr) {
	
	int straight_count = 0, chain_started = 1;

	int card_count_array[14] = { 0 };
	initialize_integer_array(card_count_array, 14);

	for (int current_card = 0; current_card < POKER_HAND_SIZE; current_card++) {
		/* checks if the given card is not an ace */
		if ((*player_hand_ptr).hand_array[current_card].face_index != 0) {
			card_count_array[(*player_hand_ptr).hand_array[current_card].face_index] += 1;
		}
		/* if it is an ace then it adds to both 1 and 14 since ace can be both */
		else {
			card_count_array[0] += 1;
			card_count_array[13] += 1;
		}
	}

	/* checks the array to see if there is any straights */
	for (int r = 0; r < 14; r++) {

		if (card_count_array[r] == 1 && card_count_array[r - 1] == 1 && r != 0) {
				straight_count += 1;
		}
		else if (card_count_array[r] == 1 && card_count_array[r + 1] == 1 && straight_count == 0) {
			straight_count += 1;
		}
	}

	/* if there is a straight then we return our score */
	if (straight_count == POKER_HAND_SIZE) {
		return 4000 + check_poker_highest_value(player_hand_ptr);
	}

	return 0;
}

/*
Function: check_poker_highest_value()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: Finds the highest value card in the given hand
Input Parameters: player_hand
Returns: score
Preconditions: N/A
Postconditions: N/A
*/

int check_poker_highest_value(Hand* player_hand_ptr) {

	int highest_value = 0;

	/* compares card values to find the highest value card in hand */
	for (int i = 0; i < POKER_HAND_SIZE; i++) {
		if (check_for_ace((*player_hand_ptr).hand_array[i].face_index) > highest_value) {
			highest_value = check_for_ace((*player_hand_ptr).hand_array[i].face_index);
		}
	}

	return highest_value;
}


/*
Function: check_poker_hand()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: checks the given players hand for all of the different possible poker hands using a different function to test each type
Input Parameters: player_hand
Returns: score
Preconditions: N/A
Postconditions: N/A
*/

int check_poker_hand(Hand* player_hand_ptr) {

	int score = 0;

	/* below is the different check cases, the order in which we do the if statements matters! Flush must be the first check, etc */

	/* poker flush case */
	if (check_poker_flush(player_hand_ptr) != 0) {
		printf("Hand contains a flush!\n");
		return check_poker_flush(player_hand_ptr);
	}
	/* poker four of a kind case */
	else if (check_poker_four_kind(player_hand_ptr) != 0) {
		printf("Hand contains a four of a kind!\n");
		return check_poker_four_kind(player_hand_ptr);
	}
	/* poker three of a kind case*/
	else if (check_poker_three_kind(player_hand_ptr) != 0) {
		printf("Hand contains a three of a kind!\n");
		return check_poker_three_kind(player_hand_ptr);
	}
	/* poker two pair case */
	else if (check_poker_two_pairs(player_hand_ptr) != 0) {
		printf("Hand contains two pairs!\n");
		return check_poker_two_pairs(player_hand_ptr);
	}
	/* poker pair case */
	else if (check_poker_pair(player_hand_ptr) != 0) {
		printf("Hand contains a pair!\n");
		return check_poker_pair(player_hand_ptr);
	}
	/* poker straight case */
	else if (check_poker_straight(player_hand_ptr) != 0) {
		printf("Hand contains a straight!\n");
		return check_poker_straight(player_hand_ptr);
	}
	/* if there are no special types in hand then just find the highest value card in hand */
	else {
		printf("Hand contains no special types\n");
		return check_poker_highest_value(player_hand_ptr);
	}
}

/* dealer hand checks */
/*
Function: check_dealer_three_kind()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: checks for a three of kind by iterating through the hand, protects any three of kinds found
Input Parameters: case array and dealer hand
Returns: N/A
Preconditions: N/A
Postconditions: N/A
*/

void check_dealer_three_kind(int case_array[], Hand* dealer_hand_ptr) {

	int check_card = 0, card = 0, pairs_found = 0, card_one = -1, card_two = -1, card_three = -1;

	for (card = 0; card < POKER_HAND_SIZE; card++) {
		for (check_card = 0; check_card < POKER_HAND_SIZE; check_card++) {
			/* looks for a pair */
			if ((*dealer_hand_ptr).hand_array[card].face_index == (*dealer_hand_ptr).hand_array[check_card].face_index && card != check_card) {
				/* if a pair is found we add to the pair count */
				pairs_found += 1;
				/* once we have found two pairs with the same card value we have found our three of a kind */
				if (pairs_found == 2) {
					card_three = check_card;
					/* sets the three cards to "protected" so the dealer won't discard them */
					case_array[card_one] = 1;
					case_array[card_two] = 1;
					case_array[card_three] = 1;
				}
				else {
					card_one = card;
					card_two = check_card;
				}
			}
		}
		/* resets pair count and card trackers after each card */
		pairs_found = 0;
		card_one = -1;
		card_two = -1;
		card_three = -1;
	}
}

/*
Function: check_dealer_two_pairs()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: looks for two pairs and protects those cards if found
Input Parameters: 
Returns: N/A
Preconditions: N/A
Postconditions: N/A
*/

void check_dealer_two_pairs(int case_array[], Hand* dealer_hand_ptr) {
	int check_card = 0, card = 0, pair_flagger = -1, highest_pair = 0, pair_one_card_one = 0, pair_one_card_two = 0, avoid_duplicate = 0;

	for (card = 0; card < POKER_HAND_SIZE; card++) {
		for (check_card = 0; check_card < POKER_HAND_SIZE; check_card++) {
			/* checks if a pair is found and that pair has not been found before */
			if ((*dealer_hand_ptr).hand_array[card].face_index == (*dealer_hand_ptr).hand_array[check_card].face_index && card != check_card && pair_flagger != (*dealer_hand_ptr).hand_array[card].face_index) {

				/* checks if two pairs have been found */
				if (pair_flagger != -1 && avoid_duplicate == 0) {
					avoid_duplicate = 1;
					case_array[pair_one_card_one] = 1;
					case_array[pair_one_card_two] = 1;
					case_array[card] = 1;
					case_array[check_card] = 1;
				}
				else if (pair_flagger == -1) {
					/* flags the pair so we dont find the same pair twice */
					pair_flagger = (*dealer_hand_ptr).hand_array[card].face_index;
					pair_one_card_one = card;
					pair_one_card_two = check_card;
				}
			}
		}
	}
}

/*
Function: check_dealer_pair()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: looks for pair and protects pair if found
Input Parameters: case array and dealer hand
Returns: N/A
Preconditions: N/A
Postconditions: N/A
*/

void check_dealer_pair(int case_array[], Hand* dealer_hand_ptr) {

	int check_card = 0, card = 0, score = 0, pair_found = 0;
	for (card = 0; card < POKER_HAND_SIZE; card++) {
		for (check_card = 0; check_card < POKER_HAND_SIZE; check_card++) {
			/* checks if the two cards match */
			if ((*dealer_hand_ptr).hand_array[card].face_index == (*dealer_hand_ptr).hand_array[check_card].face_index && card != check_card && pair_found == 0) {
				pair_found = 1;
				case_array[card] = 1;
				case_array[check_card] = 1;
			}

		}
	}
}

/*
Function: check_dealer_suits()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: if no special cases are found then this function is used to see if the hand has a majority of one suit, protecting that suit if it does
Input Parameters: case array and dealer hand
Returns: N/A
Preconditions: N/A
Postconditions: N/A
*/

int check_dealer_suits(int case_array[], Hand* dealer_hand_ptr) {

	int straight_count = 0, amount_to_discard = 0;

	int suit_count_array[4] = { 0 };
	initialize_integer_array(suit_count_array, 4);

	for (int current_card = 0; current_card < POKER_HAND_SIZE; current_card++) {
		/* adds the cards suit value to the count array */
			suit_count_array[(*dealer_hand_ptr).hand_array[current_card].suit_index] += 1;
	}

	/* if there is a majority of one suit then we tell the dealer to protect cards of that suit to find a flush */
	if (suit_count_array[0] > (POKER_HAND_SIZE / 2)) {
		protect_dealer_suits(case_array, dealer_hand_ptr, 0);
		return suit_count_array[0];
	}
	else if (suit_count_array[1] > (POKER_HAND_SIZE / 2)) {
		protect_dealer_suits(case_array, dealer_hand_ptr, 1);
		return suit_count_array[1];
	}
	else if (suit_count_array[2] > (POKER_HAND_SIZE / 2)) {
		protect_dealer_suits(case_array, dealer_hand_ptr, 2);
		return suit_count_array[2];
	}
	else if (suit_count_array[3] > (POKER_HAND_SIZE / 2)) {
		protect_dealer_suits(case_array, dealer_hand_ptr, 3);
		return suit_count_array[3];
	}

	/* if no high suit amounts were found then return 0 */
	return 0;

}

/*
Function: protect_dealer_suits()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: used to protect a specific suit
Input Parameters: case array, dealer hand, and the suit to be protected
Returns: N/A
Preconditions: N/A
Postconditions: N/A
*/

void protect_dealer_suits(int case_array[], Hand* dealer_hand_ptr, int protected_suit) {
	/* checks if the current card is of the protected suit and protects it if it is */
	for (int current_card = 0; current_card < POKER_HAND_SIZE; current_card++) {
		if ((*dealer_hand_ptr).hand_array[current_card].suit_index == protected_suit) {
			case_array[current_card] = 1;
		}
	}
}

/*
Function: test_dealer_intelligence()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: interactive program to test the AI and our special case checking functions. This function is why all other functions are using pointer structs instead of just normal structs
Input Parameters: deck, face, and suit array as well as the dealer hand ptr and dealer hand
Returns: N/A
Preconditions: N/A
Postconditions: N/A
*/

void test_dealer_intelligence(int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* dealer_hand_ptr, Hand dealer_hand) {

	int face_value = -1, suit_value = -1;

	shuffle_deck(wDeck);

	system("cls");
	printf("Hello! We are going to give the dealer a hand to see what the dealer will do\n");
	printf("You can also use this as a way to test different poker hands!\n");
	printf("The current poker hand size is 5, this can be changed in functions.h under POKER_HAND_SIZE\n");
	printf("If you are curious about what code this specific page is running then check test_dealer_intelligence() in functions.c\n");
	printf("PLEASE NOTE: You can give this hand multiple of the same card, don't do that by accident!\n");
	printf("Press any key to start...\n");
	getch();

	/* for each card we will ask the user for a face and suit value */
	for (int card = 0; card < POKER_HAND_SIZE; card++) {

		system("cls");

		/* asks for a face value */
		printf("Please input a face value for the [%d] card\n", card + 1);
		printf("Face cards go as follows: 1 for ace, 2 for deuce, 3 for three..., 10 for ten, 11 for jack, 12 for queen, and 13 for king\n");

		do {
			printf("Please input a value...\n");
			scanf("%d", &face_value);

		} while (face_value > 13 || face_value < 1);

		face_value -= 1;

		/* sets the face value to that */
		(*dealer_hand_ptr).hand_array[card].face_index = face_value;
		printf("Card [%d] now has a face value of %s (%d)\n", card + 1, wFace[face_value], (*dealer_hand_ptr).hand_array[card].face_index);

		printf("Now on to the suit for card [%d]\n", card + 1);

		/* asks for a suit value */
		printf("Please input a suit value for the [%d] card\n", card + 1);
		printf("Suit cards go as follows: 1 Hearts, 2 for Diamonds, 3 for Clubs, and 4 for Spades\n");
		do {
			printf("please input a value...\n");
			scanf("%d", &suit_value);

		} while (suit_value > 4 || suit_value < 1);

		suit_value -= 1;

		/* sets the suit value to that */
		(*dealer_hand_ptr).hand_array[card].suit_index = suit_value;
		printf("card [%d] now has a face value of %s (%d)\n", card + 1, wSuit[suit_value], (*dealer_hand_ptr).hand_array[card].suit_index);

		wDeck[suit_value][face_value] = 0;

		face_value = -1;
		suit_value = -1;
		printf("Press any key to start the next card...\n");
		getch();
	}

	/* prints generated hand */
	system("cls");
	printf("We are now done picking cards! Here is the dealers given hand:\n");
	print_poker_hand(wFace, wSuit, dealer_hand_ptr);

	/* dealer evaluates */
	evaluate_dealer_hand(wFace, wSuit, dealer_hand_ptr, dealer_hand);
	deal_cards(wDeck, wFace, wSuit, dealer_hand_ptr);

	/* prints new hand */
	printf("\nHere is what the dealer has after discarding and drawing:\n");
	print_poker_hand(wFace, wSuit, dealer_hand_ptr);
	check_poker_hand(dealer_hand_ptr);


	printf("\nPress any key to return to the home screen...\n");
	getch();
	print_home_screen(wDeck, wFace, wSuit, dealer_hand_ptr, dealer_hand);
}

/* misc functions */
/*
Function: initialize_integer_array()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: initializes all the values of an integer array to 0
Input Parameters: player_hand
Returns: N/A
Preconditions: N/A
Postconditions: N/A
*/

void initialize_integer_array(int integer_array[], int size) {
	for (int i = 0; i < (size - 1); i++) {
		integer_array[i] = 0;
	}
}

/*
Function: check_for_ace()
Date Created: 12/1/2020
Date Last Modified: 12/1/2020
Description: Checks the given card value and sets it to 13 (highest possible value) if the given card is a 0 (ace)
Input Parameters: card value
Returns: card value, either the normal value or 13 if it was an ace
Preconditions: N/A
Postconditions: N/A
*/

int check_for_ace(int card_value) {
	if (card_value == 0) {
		return 13;
	}

	return card_value;
}