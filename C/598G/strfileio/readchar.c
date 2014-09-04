#include <stdio.h>
int main (){
  
  FILE * input;
  char c;
  int n = 0;
  input = fopen ("dataFile.txt","r");
  if(input == NULL){
    perror ("Error opening data file");
    return 1;
  }
  
  /* EOF is the end of file marker */
  do{
    c = fgetc (input);
    /* Note the single quotes ' '. If you use " " then it is a string! */
    if (c == '5') n++;
  }while (c != EOF);
  
  /* Always remember to close the file */
  fclose (input);
  printf ("5 occurs %d times in the file.\n",n);
  
  return 0;
}
