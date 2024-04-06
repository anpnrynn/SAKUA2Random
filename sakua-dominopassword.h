//copyright Anoop Kumar Narayanan 2023 anoop.kumar.narayanan@gmail.com
#ifndef SAKUA_DOMINOPASSWORD_H
#define SAKUA_DOMINOPASSWORD_H

#include <string.h>
#include <malloc.h>

struct domino_password* domino_password_new ();

enum domino_password_gen {
	gen1   = 0, //Prototype Crypto function
	gen1_1 = 1, //Crypto function
	gen2   = 2, //Password gen algo
	gen2_1 = 3, //For future use...
	gen4   = 4,
	gen5   = 5,
	gen6   = 6,
	gen7   = 7,
	gen8   = 8,
	gen9   = 9,
	gen10  = 10,
	gen11  = 11,
	gen12  = 12
};

#define DP_SEED_LEN 108

struct domino_password_algo;

typedef void (*algo_init)     ( struct domino_password_algo *algo_info );
typedef void (*set_get_seed)  ( struct domino_password_algo *algo_info, char **seed );
typedef void (*set_pin)       ( struct domino_password_algo *algo_info, int n );
typedef int  (*get_pin)       ( struct domino_password_algo *algo_info );
typedef void (*set_random)    ( struct domino_password_algo *algo_info, int *random );
typedef void (*rotate)        ( char *data, int count, int n );
typedef void (*swapchars)     ( char *data, int i, int j, int n );
typedef void (*shuffle)       ( struct domino_password_algo *algo_info, char *data );


struct domino_password_algo {
	//domino_password_gen gen;
	int   gen;
	int   pin;
	//char  seed[128];
	char *seed;
	int  *random;
	algo_init    function_algo_init;
	set_get_seed function_set_get_seed;
	set_pin      function_set_pin;
	get_pin      function_get_pin;
	set_random   function_set_random;
	rotate       function_rotate;
	swapchars    function_swapchars;
	shuffle      function_shuffle;
};


extern struct domino_password_algo *gen2_algo;
extern struct domino_password_algo *gen2_1_algo;
extern struct domino_password_algo *gen1_algo;
extern struct domino_password_algo *gen1_1_algo;

struct domino_password;

typedef void  (*domino_init)    ( struct domino_password* );
typedef void  (*algo_setup)     ( struct domino_password*, int );
typedef void  (*set_gen_seed)   ( struct domino_password*, char * );
typedef char* (*get_gen_seed)   ( struct domino_password* );
typedef const struct domino_password_algo * (*get_algo)   ( struct domino_password*  );
typedef void  (*gen_shuffled)   ( struct domino_password*);
typedef char* (*get_shuffled)   ( struct domino_password*  );
typedef void  (*set_n_activated)( struct domino_password*, int n );
typedef int   (*get_n_activated)( struct domino_password* );
typedef void  (*set_activated)  ( struct domino_password*, int *array );
typedef int * (*get_activated)  ( struct domino_password*, int *n );
typedef char* (*get_domino_key) ( struct domino_password* );

struct domino_password {
	struct domino_password_algo *algo;
	char gen_seed[128];
	char shuffled[128];
       	int  n_activated;
	int  activated[108];
	char key[1024];	

	domino_init function_init;
	algo_setup function_algo_setup;
	set_gen_seed function_set_gen_seed;
	get_gen_seed function_get_gen_seed;
	get_algo     function_get_algo;
	gen_shuffled function_gen_shuffled;
	get_shuffled function_get_shuffled;
	set_n_activated function_set_n_activated;
	get_n_activated function_get_n_activated;
	set_activated function_set_activated;
	get_activated function_get_activated;
	get_domino_key function_get_domino_key;
};


void  dp_domino_init    ( struct domino_password* );
void  dp_algo_setup     ( struct domino_password*, int );
void  dp_set_gen_seed   ( struct domino_password*, char * );
char* dp_get_gen_seed   ( struct domino_password* );
const struct domino_password_algo * dp_get_algo   ( struct domino_password*  );
void  dp_gen_shuffled   ( struct domino_password*);
char* dp_get_shuffled   ( struct domino_password*  );
void  dp_set_n_activated( struct domino_password*, int n );
int   dp_get_n_activated( struct domino_password* );
void  dp_set_activated  ( struct domino_password*, int *array );
int * dp_get_activated  ( struct domino_password*, int *n );
char* dp_get_domino_key ( struct domino_password* );


#define SAKUA_DOMINO_PASSWORD_NEW() \
	struct domino_password *dp = (struct domino_password *) malloc ( sizeof( struct domino_password ) ); \
	dp->function_init = dp_domino_init; \
	dp->function_init ( dp );


#endif
