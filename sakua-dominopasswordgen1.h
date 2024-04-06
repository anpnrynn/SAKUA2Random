//copyright Anoop Kumar Narayanan 2023 anoop.kumar.narayanan@gmail.com
#ifndef SAKUA_DOMINOPASSWORDGEN2
#define SAKUA_DOMINOPASSWORDGEN2

#include "sakua-dominopassword.h"

void gen1_algo_init   ( struct domino_password_algo *algo_info );
void gen1_set_get_seed    ( struct domino_password_algo *algo_info, char **seed );
void gen1_set_pin     ( struct domino_password_algo *algo_info, int n );
int  gen1_get_pin     ( struct domino_password_algo *algo_info );
void gen1_set_random  ( struct domino_password_algo *algo_info, int *random );
void gen1_rotate      ( char *data, int count, int n );
void gen1_swapchars   ( char *data, int i, int j, int n );
void gen1_shuffle     ( struct domino_password_algo *algo_info, char *data );


//extern struct domino_password_algo gen1_algo;

#endif

