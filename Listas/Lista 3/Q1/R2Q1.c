#include <string.h>
#include "R2Q1.h"
#include "Q1InGenerator.h"

int main()
{
  // L2Q1_in_generator();
  str *firstStr = get_lines_from_file();
  numbers *firstNumber = create_numbers_list(firstStr);
  show_lines_like_numbers_list(firstNumber);

  puts("end execution");
  return EXIT_SUCCESS;
}
str *get_lines_from_file()
{
  FILE *fileInPtr = fopen(R2Q1_file_in_path, "r");

  str *firstStr = NULL;
  str *lastStr = NULL;
  str *currStr = NULL;
  str *newStr = NULL;

  char line[MAX_SIZE_LINE];

  if (fileInPtr)
  {
    if (fgets(line, MAX_SIZE_LINE, fileInPtr))
    {
      line[strlen(line) - 1] = '\0';
      newStr = new_str();
      newStr->content = new_char_vector(MAX_SIZE_LINE);
      strcpy(newStr->content, line);
      newStr->next = NULL;

      firstStr = newStr;
      lastStr = newStr;

      while (fgets(line, MAX_SIZE_LINE, fileInPtr))
      {
        line[strlen(line) - 1] = '\0';
        newStr = new_str();
        newStr->content = new_char_vector(MAX_SIZE_LINE);
        strcpy(newStr->content, line);
        newStr->next = NULL;

        currStr = lastStr;
        currStr->next = newStr;
        lastStr = newStr;
      }
    }
  }
  return firstStr;
}
numbers *create_numbers_list(str *firstsStrValues)
{
  str *currStr = firstsStrValues;

  numbers *firstN = NULL;
  numbers *currN = NULL;
  numbers *newN = NULL;
  numbers *lastN = NULL;

  str *firstStrKey = break_line_in_str_list(currStr->content);

  str *currStrKey = firstStrKey;

  newN = new_numbers();
  newN->keyQTY = get_size_str_linked_list(currStrKey);
  newN->keys = new_int_vector(newN->keyQTY);
  newN->next = NULL;
  int i = 0;

  while (i < newN->keyQTY && currStrKey)
  {
    newN->keys[i] = atoi(currStrKey->content);
    i++;
    currStrKey = currStrKey->next;
  }

  delete_str_list(&firstStrKey);

  firstN = newN;
  lastN = newN;

  currStr = currStr->next;

  while (currStr)
  {
    firstStrKey = break_line_in_str_list(currStr->content);

    str *currStrKey = firstStrKey;

    newN = new_numbers();
    newN->keyQTY = get_size_str_linked_list(currStrKey);
    newN->keys = new_int_vector(newN->keyQTY);
    newN->next = NULL;

    int i = 0;

    while (i < newN->keyQTY && currStrKey)
    {
      newN->keys[i] = atoi(currStrKey->content);
      i++;
      currStrKey = currStrKey->next;
    }

    delete_str_list(&firstStrKey);

    currN = lastN;
    currN->next = newN;
    lastN = newN;

    currStr = currStr->next;
  }
  return firstN;
}
str *break_line_in_str_list(char *line)
{
  str *firstS = NULL;
  str *currS = NULL;
  str *newS = NULL;
  str *lastS = NULL;

  char *middleWhere = NULL;

  middleWhere = strtok(line, " ");
  int sizeStr = strlen(middleWhere);

  if (sizeStr)
  {
    newS = new_str();
    newS->content = new_char_vector(sizeStr);
    newS->next = NULL;
    strcpy(newS->content, "");
    strcpy(newS->content, middleWhere);
    firstS = newS;
    lastS = newS;
  }

  middleWhere = strtok(NULL, " ");
  while (middleWhere)
  {
    sizeStr = strlen(middleWhere);
    if (sizeStr)
    {
      newS = new_str();
      newS->content = new_char_vector(sizeStr);
      newS->next = NULL;
      strcpy(newS->content, "");
      strcpy(newS->content, middleWhere);
      currS = lastS;
      currS->next = newS;
      lastS = newS;
    }
    middleWhere = strtok(NULL, " ");
  }
  return firstS;
}
numbers *new_numbers()
{
  return (numbers *)malloc(sizeof(numbers));
}
str *new_str()
{
  return (str *)malloc(sizeof(str));
}
int get_size_str_linked_list(str *start)
{
  str *curr = start;
  int i = 0;
  while (curr)
  {
    i++;
    curr = curr->next;
  }
  return i;
}
int *new_int_vector(int size)
{
  if (size < 1)
  {
    return NULL;
  }

  return (int *)malloc(sizeof(int) * size);
}
void delete_str_list(str **firstStr)
{
  str *curr = *firstStr;
  str *prev = NULL;

  while (curr)
  {
    prev = curr;
    curr = curr->next;
    free(prev);
    prev = NULL;
  }
  *firstStr = NULL;
}
char *new_char_vector(int size)
{
  if (size < 1)
  {
    return NULL;
  }
  return (char *)malloc(sizeof(char) * size);
}
void show_lines_content(str *firstStr)
{
  int i = 1;
  while (firstStr)
  {
    printf("Linha[%d] -> %s\n", i, firstStr->content);
    i++;
    firstStr = firstStr->next;
  }
}
void show_lines_like_numbers_list(numbers *firstNumbers)
{
  while (firstNumbers)
  {
    int i = 0;

    while (i < firstNumbers->keyQTY)
    {
      printf("%d ", firstNumbers->keys[i]);
      i++;
    }
    putchar('\n');
    firstNumbers = firstNumbers->next;
  }
}