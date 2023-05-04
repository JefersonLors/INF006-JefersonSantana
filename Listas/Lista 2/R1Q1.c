#include <stdlib.h>
#include <stdio.h>
#include "R1Q1.h"
#include "Q1InGenerator.h"

int main()
{
  L1Q1_in_generator();
  str *firstLine = get_lines_from_file();

  while( firstLine ){
    printf("%s\n", firstLine->line);
    firstLine = firstLine->next;
  }

  return EXIT_SUCCESS;
}

str *get_lines_from_file()
{
  FILE *fileInPtr = fopen(R1Q1_file_in_path, "r");
  
  str *firstStr = NULL;
  str *lastStr = NULL;
  str *actStr = NULL;
  str *newStr = NULL;

  char *line = NULL;
 
  if( fileInPtr )  
  {
    fgets(line, MAX_SIZE_LINE, fileInPtr );
    if( line ){
      puts("aqui");
      printf("%s\n", line);
      newStr = (str*)malloc(sizeof(str));
      newStr->line = line;
      newStr->next = NULL;

      firstStr = newStr;
      lastStr = newStr;
      fgets(line, MAX_SIZE_LINE, fileInPtr );
      
      while( line ){
        newStr = (str*)malloc(sizeof(str));
        newStr->line = line;
        newStr->next = NULL;
        actStr = lastStr;
        actStr->next = newStr;
        lastStr = newStr;
        fgets(line, MAX_SIZE_LINE, fileInPtr );
      }
    }
  }
  return firstStr;
}