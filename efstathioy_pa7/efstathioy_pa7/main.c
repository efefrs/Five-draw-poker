/*
Author: Niko D Efstathioy

Class CptS 121, Fall 2020; Lab Section 1

Programming Assignment: Lab1PA7

Date: November 28, 2020

Description: This program runs the game poker
*/

#include "functions.h"

int main(void) {

	/* initialize suit array */
	const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	/* initialize face array */
	const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

	/* initialize deck array */
	int deck[4][13] = { 0 };

	/* initialize hands */
	Hand user_hand, dealer_hand;

	/* we cannot use a function to initialize these arrays */
	for (int i = 0; i < POKER_HAND_SIZE; i++) {
		user_hand.hand_array[i].face_index = -1;
		user_hand.hand_array[i].suit_index = -1;
	}
	for (int i = 0; i < POKER_HAND_SIZE; i++) {
		dealer_hand.hand_array[i].face_index = -1;
		dealer_hand.hand_array[i].suit_index = -1;
	}

	/* initializing pointers for primarily drawing cards (check deal_cards();) */
	Hand* user_hand_ptr = &user_hand, * dealer_hand_ptr = &dealer_hand;

	/* initializations  for scorekeeping*/
	int round_count = 1, user_score = 0, dealer_score = 0, compare_scores = 0;
	
	/* initializations for continued play */
	int continue_playing_check = 0;

	/* seed random-number generator */
	srand((unsigned)time(NULL));

	/* game loop */
	do {

		/* pre-game */
		print_home_screen(deck, face, suit, dealer_hand_ptr, dealer_hand);

		/* resets both hands */
		for (int i = 0; i < POKER_HAND_SIZE; i++) {
			user_hand.hand_array[i].face_index = -1;
			user_hand.hand_array[i].suit_index = -1;
		}
		for (int i = 0; i < POKER_HAND_SIZE; i++) {
			dealer_hand.hand_array[i].face_index = -1;
			dealer_hand.hand_array[i].suit_index = -1;
		}

		/* main game loop */
		do {
			/* main gameplay */
			/* setup */
			system("cls");
			continue_playing_check = 0;
			shuffle_deck(deck);
			deal_cards(deck, face, suit, user_hand_ptr);
			deal_cards(deck, face, suit, dealer_hand_ptr);

			/* print player hand */
			printf("Your hand:\n");
			print_poker_hand(face, suit, user_hand_ptr);
			check_poker_hand(user_hand_ptr);

			/* discard phase */
			discard_cards_user(user_hand_ptr);
			print_poker_hand(face, suit, dealer_hand_ptr);
			evaluate_dealer_hand(face, suit, dealer_hand_ptr, dealer_hand);
			deal_cards(deck, face, suit, user_hand_ptr);
			deal_cards(deck, face, suit, dealer_hand_ptr);


			/* end of round cleanup and scoring */
			compare_scores = compare_poker_hands(check_poker_hand(user_hand_ptr), check_poker_hand(dealer_hand_ptr));

			system("cls");
			printf("Round %d is over!\n\n", round_count);

			/* find round winner */
			if (compare_scores == 1) {
				printf("You won the round!\n");
				user_score += 1;
			}
			else if (compare_scores == 2) {
				printf("Dealer won the round!\n");
				dealer_score += 1;
			}
			else if (compare_scores == 3){
				printf("There was a tie!\n");
			}
			compare_scores = 0;

			/* print hands */
			printf("Final hands:\n\n");
			printf("Your hand:\n");
			print_poker_hand(face, suit, user_hand_ptr);
			check_poker_hand(user_hand_ptr);
			printf("\nDealers hand:\n");
			print_poker_hand(face, suit, dealer_hand_ptr);
			check_poker_hand(dealer_hand_ptr);

			/* print scores */
			printf("\nCurrent scores:\n");
			printf("Player: %d\n", user_score);
			printf("Dealer: %d\n", dealer_score);

			/* ask about ending game */
			printf("\nWould you like to keep playing? (input 1 for yes or n for 2)\n");
			do {
				scanf("%d", &continue_playing_check);
			} while (continue_playing_check < 1 || continue_playing_check > 2);

			/* setup for next round */
			/* we cannot use a function to reset these arrays */
			for (int i = 0; i < POKER_HAND_SIZE; i++) {
				user_hand.hand_array[i].face_index = -1;
				user_hand.hand_array[i].suit_index = -1;
			}
			for (int i = 0; i < POKER_HAND_SIZE; i++) {
				dealer_hand.hand_array[i].face_index = -1;
				dealer_hand.hand_array[i].suit_index = -1;
			}
			round_count++;
		} while (continue_playing_check != 2);

		/* we exit the program via exit(0) in print_home_screen() */
	} while (1 == 1);

	return 0;
}