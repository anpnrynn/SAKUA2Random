//copyright Anoop Kumar Narayanan 2023 anoop.kumar.narayanan@gmail.com
#ifndef SAKUA_DOMINOPASSWORDGEN2
#define SAKUA_DOMINOPASSWORDGEN2

#include "sakua-dominopassword.h"

void gen2_algo_init   ( struct domino_password_algo *algo_info );
void gen2_set_get_seed    ( struct domino_password_algo *algo_info, char **seed );
void gen2_set_pin     ( struct domino_password_algo *algo_info, int n );
int  gen2_get_pin     ( struct domino_password_algo *algo_info );
void gen2_set_random  ( struct domino_password_algo *algo_info, int *random );
void gen2_rotate      ( char *data, int count, int n );
void gen2_swapchars   ( char *data, int i, int j, int n );
void gen2_shuffle     ( struct domino_password_algo *algo_info, char *data );


//extern struct domino_password_algo gen2_algo;

#endif

