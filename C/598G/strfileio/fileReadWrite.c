# include <stdio.h>

int main(void){
  
  int i, numExamples;
  float tempf;
  
  /* Open input file dataFile.txt. Note filenames are case sensitive! */
  /* Mode specifier "r" indicates that we only want to "read" the file */
  FILE *input = fopen("dataFile.txt","r");
  if (input == NULL) {
    perror ("Error opening data file");
    return 1;
  }

  /* Mode specifier "w" indicates that we want to "write" the file */
  FILE *output = fopen("outputFile.txt","w");
  
  if (output == NULL) {
    perror ("Error opening output file");
    fclose(input);
    return 1;
  }
  
  /* fscanf is very similar to scanf except that it reads from a file */
  /* if stdin is given as file pointer it reads from standard input */
  fscanf(input,"%d", &numExamples);
  
  printf("%d\n", numExamples);
  
  for (i=0; i<numExamples; i++) {
    fscanf(input,"%f", &tempf);
    /*    fprintf(output,"%f ", tempf*tempf);    */
    fprintf(stdout,"%f ", tempf*tempf);
    fprintf(output,"%6.2f", tempf*tempf);
  }

  /*  fprintf(output,"\n");*/
  fprintf(stdout,"\n");
  
  fclose(input);
  fclose(output);
  return 0;
}
