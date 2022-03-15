#include "scop.h"
#include <stdio.h>
#include <stdlib.h>

char *read_file(char *filename)
{
	FILE *fp;
	long lSize;
	char *buffer;

	fp = fopen (filename, "rb");
	if( !fp ) {
		perror(filename);
		return(0);
	} 

	fseek( fp , 0L , SEEK_END);
	lSize = ftell( fp );
	rewind( fp );

	buffer = calloc( 1, lSize+1 );
	if( !buffer ) {
		fclose(fp);
		fputs("read_file: memory alloc fails",stderr);
		return(0);
	} 

	/* copy the file into the buffer */
	if(1 != fread( buffer , lSize, 1 , fp)) {
		fclose(fp);
		free(buffer);
		fputs("read_file: entire read fails",stderr);
		return(0);
	}
	fclose(fp);
	return buffer;
}