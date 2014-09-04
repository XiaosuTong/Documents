# include <stdio.h>

int main(void){
  
  char mystring [8];
  FILE *input = fopen("dataFile.txt","r");
  if(input == NULL){
    perror ("Error opening data file");
    return 1;
  }
  
  /* Reading one character at a time using fgetc can be a little
     inefficient, so we can use fgets to read 1 line at a time. */ 
  
  /* fgets takes three arguments. The first, has to be a char* or the
     name of a sized char array. The second is an int - the maximum
     number of characters read per line. The third and last, is a
     FILE* */ 
  
  /* fgets reads characters from FILE* and stores them as a C string into
     str until (num-1) characters have been read or either a newline or
     a the End-of-File is reached, whichever comes first.  It returns
     NULL if the end of the file is reached. */
  
  /* A newline character makes fgets stop reading, but it is considered
     a valid character and therefore it is included in the string copied
     to str. */
  
  /* A '\0' character is automatically appended in str after the
     characters are read to signal the end of the C string. */
  
  /* fputs is the output counterpart of fgets */
  while(fgets (mystring, 8, input) != NULL){
    fputs(mystring, stdout);
    printf( "\n" );
  }

  /* reset file position indicator to start of the file. */
  rewind(input);
  /* Now everything starts from the beginning of the file again */
  while(fgets (mystring, 8, input) != NULL){
    fputs(mystring, stdout);
  }
  
  fclose (input);
  
  return 0;
}
