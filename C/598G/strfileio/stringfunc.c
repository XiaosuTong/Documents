/* Written by S.V.N. Vishwanathan, modified by Sergey Kirshner */
#include <stdio.h>
#include <string.h>

/* In C, strings are arrays of characters with a special termination
   symbol '\0' */

int main(void){

  /* You can declare a string as follows */
  char mystring[40];
  /* It can then be initialized via */
  mystring[0] = 'S';
  mystring[1] = 'e';
  mystring[2] = 'r';
  mystring[3] = 'g';
  mystring[4] = 'e';
  mystring[5] = 'y';
  /* Remember to terminate the string! */
  mystring[6] = '\0';

  /* Alternatively */
  char mystring1[40] = {'h', 'e', 'l', 'l', 'o', '\0'};
  
  /* Third, common alternative. Note the use of " " instead of ' ' */
  /* The compiler automatically adds the '\0' character at the end */
  char mystring2[40] = "hello world";
  
  char mystring3[40];
  
  /* Print out a string */
  printf("my name is %s. \n", mystring);
  
  /* Query for the length of a string using strlen*/
  printf ("my name is %d characters long.\n", (int)strlen(mystring));
  
  /* Copy mystring2 to mystring3. Note order of arguments. */
  strcpy (mystring3, mystring2);
  printf("mystring3 is %s. \n", mystring3);
  
  /* Selectively copy the first 4 characters. */
  strncpy(mystring3, "some random string", 4);
  /* Does this append a '\0' to mystring3? No :( */

  puts(mystring3);
  mystring3[4] = '\0';
  puts(mystring3);
  printf("%s\n", mystring3);
  
  /* Concatenate strings */
  strcat(mystring3, " world!");
  puts(mystring3);
  
  /* Selectively concatenate the first 5 characters */
  strncat(mystring3, mystring1, 4);
  puts(mystring3);
  
  
  /* Compare two strings. Note you cannot use mystring1 == mystring2. That is wrong! */
  strcpy(mystring3, mystring1);
  if(mystring3 == mystring1)
    printf("Yes. \n");
  else
    printf("No. \n");
  
  /* strcmp returns 1 if strings are not the same and 0 otherwise. */
  if(strcmp(mystring3, mystring1)){
    printf("mystring3 and mystring1 are different. \n");
  }else{
    printf("mystring3 and mystring1 are the same. \n");
  }
  
  /* As you can imagine a strncmp also exists */

  /* Locate first instance of a character in a string */
  char* pch = strchr(mystring3, 'l');
  printf("In string %s, the character 'l' appears at positions ", mystring3);
  while (pch!=NULL){
    printf ("%ld ", pch-mystring3+1);
    pch=strchr(pch+1,'l');
  }
  printf("\n");

  /* Locate last instance of a character in a string */
  pch = strrchr(mystring3, 'l');
  printf("In string %s, the character 'l' appears for the last time at position %ld. \n",  
         mystring3, pch-mystring3+1);

  /* Split a string into tokens */
 
  /* A sequence of calls to strtok splits a given string into tokens,
     which are sequences of contiguous characters separated by any of
     the characters that are part of delimiters. */ 
  
  /* On a first call, strtok expects a C string as argument, whose first
     character is used as the starting location to scan for tokens. In
     subsequent calls, the function expects a null pointer and uses the
     position right after the end of last token as the new starting
     location for scanning. */
  strcpy(mystring3, "hello hello world!");
  pch = strtok(mystring3, " ");
  while (pch != NULL){
    printf ("%s\n",pch);
    pch = strtok (NULL, " ");
  }  
  return 0;
}
