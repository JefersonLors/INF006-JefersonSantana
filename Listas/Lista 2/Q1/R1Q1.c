#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "R1Q1.h"
#include "Q1InGenerator.h"

int main()
{
  L1Q1_in_generator();
  str *firstLine = get_lines_from_file();

  while( firstLine ){
    firstLine = firstLine->next;
  }
  puts("fim");
  return EXIT_SUCCESS;
}

str *get_lines_from_file()
{
  FILE *fileInPtr = fopen(R1Q1_file_in_path, "r");
  
  str *firstStr = NULL;
  str *lastStr = NULL;
  str *actStr = NULL;
  str *newStr = NULL;

  char line[MAX_SIZE_LINE];

  if( fileInPtr )  
  {
    if( fgets(line, MAX_SIZE_LINE, fileInPtr ) ){
      line[strlen(line)-1] = '\0';
      newStr = (str*)malloc(sizeof(str));
      newStr->line = line;
      newStr->next = NULL;

      firstStr = newStr;
      lastStr = newStr;
      
      while( fgets(line, MAX_SIZE_LINE, fileInPtr ) ){
        line[strlen(line)-1] = '\0';
        newStr = (str*)malloc(sizeof(str));
        newStr->line = line;
        newStr->next = NULL;
        actStr = lastStr;
        actStr->next = newStr;
        lastStr = newStr;
      }
    }
  }
  return firstStr;
}