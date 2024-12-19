#define _LARGEFILE64_SOURCE 
#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


int main(int argc , char *argv[]) {

if( argc < 6 ) {
	printf(" Usage : %s <filename> <searchlineindex> <stringoffset> <stringlength> <substringsearch>\n", argv[0] );
	return 0;
}

FILE *f;
printf(" Reading from file : %s \n", argv[1] );
f  = fopen(argv[1], "r");
int lineNumber = 0;

char fline[127];
fline[0] =0;
//fscanf( stdin, "%108s", fline );
fline[108]= 0;



int first = 0;
int readline = atoi ( argv[2] );
int offset = atoi( argv[3] );
int length = atoi( argv[4] );
int substring = atoi( argv[5] );
int matches = 0;
int submatches = 0;
printf(" Searching for string on line %d, at offset %d and of length %d \n", readline, offset, length );
printf(" Substring search %s \n", substring?"ON":"OFF" );

for(;;) {
    char line[127];
    fgets(line, 127, f);
    lineNumber++;
    line[108] = 0;
    if (!feof(f)) {
    } else {
        break;
    }
    if( lineNumber % 1000000 == 0 ){
	    printf(" Searched %d lines  <<  %s  >> submatches=%d matches=%d\n", lineNumber, fline, submatches, matches );
		printf(" String = %s \n", line );
    }

    if( lineNumber == readline  ){
	    first = 1;
	    strcpy( fline, line );
	    fline[108] = 0;
		printf(" Line to scan for = '%s'\n", fline );

    } else if ( first ==  1 ) {
		int j = 0;
		while( j < 108-length ) {
    			if( strncmp ( &line[j] , &fline[offset], length ) == 0 ){
	    			printf(" Matching string found at line : %d , %d\n", lineNumber, offset+j);
				printf(" Matching string = %s \n", line );
				//fclose(f);
				//return 0;
				submatches++;
    			} 
			j++;
		}
		if( j == 0 ){
			//printf(" %s =? %s \n", line, fline );
    			if( strncmp ( &line[j] , &fline[offset], length ) == 0 ){
	    			printf(" Matching string found at line : %d , %d\n", lineNumber, offset+j);
				printf(" Matching string = %s \n", line );
				matches++;
				//fclose(f);
				//return 0;
    			} 
			j++;
		}
	}
}

printf(" Looping from begining \n");
fseek( f, SEEK_SET, 0 );
int ln = lineNumber;
lineNumber=0;

int n = 0;
for(;n<readline;) {
    char line[127];
    fgets(line, 127, f);
	ln++;
    lineNumber++;
    line[108] = 0;
    if (!feof(f)) {
    } else {
        break;
    }
    if( ln % 1000000 == 0 ){
	    printf(" Searched %d lines  <<  %s  >> submatches=%d matches=%d\n", ln, fline, submatches, matches );
		printf(" String = %s \n", line );
    }

    if( lineNumber == readline  ){
	    first = 1;
	    strcpy( fline, line );
	    fline[108] = 0;
		break;
    } else {
		int j = 0;
		while( j < 108-length ) {
	    		if( strncmp ( &line[j] , &fline[offset], length ) == 0 ){
		    		printf(" Matching string found at line : %d , %d\n", lineNumber, offset+j);
				printf(" Matching string = %s \n", line );
				submatches++;
				//fclose(f);
				//return 0;
    			} 
			j++;
		}
		if( j == 0 ){
			//printf(" %s =? %s \n", line, fline );
    			if( strncmp ( &line[j] , &fline[offset], length ) == 0 ){
	    			printf(" Matching string found at line : %d , %d\n", lineNumber, offset+j);
				printf(" Matching string = %s \n", line );
				matches++;
				//fclose(f);
				//return 0;
    			} 
			j++;
		}
	}
	n++;
}
printf(" Substring matches = %d \n", submatches );
printf(" String matches = %d \n", matches );
printf(" No matching string found \n");

fclose(f);

return(0);
}
