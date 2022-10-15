/*
Author: Niko D Efstathioy

Class CptS 121, Fall 2020; Lab Section 1

Programming Assignment: Lab1PA7

Date: November 28, 2020

Description: This program runs the game poker
*/

#ifndef LOOPS_H
#define LOOPS_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define POKER_HAND_SIZE 5

typedef struct card {

	/* a number between 0 and 3 that represents the suit and row */
	int suit_index;

	/* a number between 0 and 12 that represents the face value and column */
	int face_index;

} Card;

typedef struct hand {

	/* array stores the five cards currently in hand */
	Card hand_array[POKER_HAND_SIZE];

} Hand;

/* the below functions are ordered in the same way in functions.c */

/* card initializing */
void shuffle_deck(int wDeck[][13]);
void deal_cards(int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* player_hand);

/* home screens */
int print_home_screen(int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* dealer_hand_ptr, Hand dealer_hand);
void print_poker_rules(int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* dealer_hand_ptr, Hand dealer_hand);

/* card actions */
void print_poker_hand(const char* wFace[], const char* wSuit[], Hand* player_hand);
int compare_poker_hands(int user_score, int dealer_score);
void discard_cards_user(Hand* player_hand_ptr);
void evaluate_dealer_hand(const char* wFace[], const char* wSuit[], Hand* dealer_hand_ptr, Hand dealer_hand);

/* poker hand checks*/
int check_poker_pair(Hand* player_hand_ptr);
int check_poker_two_pairs(Hand* player_hand_ptr);
int check_poker_three_kind(Hand* player_hand_ptr);
int check_poker_four_kind(Hand* player_hand_ptr);
int check_poker_flush(Hand* player_hand_ptr);
int check_poker_straight(Hand* player_hand_ptr);
int check_poker_highest_value(Hand* player_hand_ptr);
int check_poker_hand(Hand* player_hand_ptr);

/* dealer hand checks */
void check_dealer_three_kind(int case_array[], Hand* dealer_hand_ptr);
void check_dealer_two_pairs(int case_array[], Hand* dealer_hand_ptr);
void check_dealer_pair(int case_array[], Hand* dealer_hand_ptr);
int check_dealer_suits(int case_array[], Hand* dealer_hand_ptr);
void protect_dealer_suits(int case_array[], Hand* dealer_hand_ptr, int protected_suit);

/* debugging */
void test_dealer_intelligence(int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* dealer_hand_ptr, Hand dealer_hand);

/* misc functions */
void initialize_integer_array(int integer_array[], int size);
int check_for_ace(int card_value);

#endif