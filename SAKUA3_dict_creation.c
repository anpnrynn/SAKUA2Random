#include <stdio.h>
#include <string.h>

int main (int argc , char *argv[]) {
	if( argc < 3 ){
		printf(" %s <original dict> index <output filename> \n", argv[0]);
	} 

	char *f1 = argv[1];
	char *f2 = argv[3];
	int startindex = atoi(argv[2]);

	char *ur = "/dev/urandom";

	FILE *ff1 = fopen(argv[1], "r");
	FILE *ff2 = fopen(argv[3], "w+");	
	FILE *fur = fopen(ur , "r" );

	if( ! ff1  || !ff2 || !fur )
		return;

	char data[256];
	char changeddata[256];
	char value[12];
	
	printf(" Reached here \n");
	while( 1 ){
		char *datai = fgets( data, 256, ff1 );
		if( feof( ff1 ) )
			return;
		//printf("%s", data);
		int n = fread(value, 8, 1, fur);
		value[8] = 0;
		//printf("%s", value);
		//if( n > 0 ){
			int *value1 = (int*)value;
			int valuei = *value1;
			printf(" %s - %d \n", value, valuei );
			int pos = valuei % strlen( data );
			int valueii  = valuei % 1000000;

			if( valueii < 0 ){
				valueii = valueii * -1;
			}
			if ( valueii < 100 ) {
				valueii += 100;
			}	
			strncpy( changeddata, data, pos );
			changeddata[pos] = 0;
			char changeddata2[256]; 
			strncpy( changeddata2, &data[pos], strlen( data) - pos );
			changeddata2[strlen( data) - pos] = 0;
			fprintf( ff2, "%s%d%s",  changeddata, valueii, changeddata2 ); 
	}
	return 0;
}
