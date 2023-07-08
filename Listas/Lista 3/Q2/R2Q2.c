#include <string.h>
#include "R2Q2.h"
#include "Q2InGenerator.h"

int main()
{
  // L2Q2_in_generator();
  str *firstStr = get_lines_from_file();
  numbers *firstNumber = create_numbers_list(firstStr);
  delete_str_list(&firstStr);
  lineResult *firstLineResult = create_line_result_list(firstNumber);
  delete_numbers_list(&firstNumber);
  write_result_in_file(firstLineResult);
  delete_line_result_list(&firstLineResult);
  puts("\nend execution");

  return EXIT_SUCCESS;
}
void write_result_in_file(lineResult *firstLineResult)
{
  FILE *fileOutPtr = fopen(R2Q2_file_out_path, "w");  
  char resultLine[MAX_SIZE_LINE];

  while (firstLineResult)
  {
    strcpy(resultLine, "");
    create_string_result_in_order(firstLineResult->root, resultLine);
    resultLine[strlen(resultLine)-1] = '\0';
    fprintf(fileOutPtr, "%s\n", resultLine);
    firstLineResult = firstLineResult->next;
  }
  fclose(fileOutPtr);
}
void create_string_result_in_order(node *root, char *string)
{
  if (root)
  {
    char tempLine[50];
    strcpy(tempLine, "");
    create_string_result_in_order(root->left, string);
    sprintf(tempLine, "%d (%d) ", root->key, root->subTRLessSubTL );
    strcat(string, tempLine);
    create_string_result_in_order(root->right, string);
  }
}
lineResult *create_line_result_list(numbers *firstNumbers)
{
  lineResult *first = NULL;

  if (firstNumbers)
  {
    lineResult *new = new_line_result();
    lineResult *curr = NULL;
    lineResult *last = NULL;

    new->next = NULL;
    new->root = create_tree(firstNumbers);

    calculate_subTR_less_subTL(new->root);

    first = new;
    last = new;

    firstNumbers = firstNumbers->next;

    while (firstNumbers)
    {
      new = new_line_result();
      new->next = NULL;
      new->root = create_tree(firstNumbers);

      calculate_subTR_less_subTL(new->root);

      curr = last;
      curr->next = new;
      last = new;

      firstNumbers = firstNumbers->next;
    }
  }
  return first;
}
void show_in_order(node *root)
{
  if (root)
  {
    show_in_order(root->left);
    printf("%d -> [%d]\t", root->key, root->subTRLessSubTL);
    show_in_order(root->right);
  }
}
node *create_tree(numbers *values)
{
  node *root = NULL;
  int i = 0;

  while (i < values->keyQTY)
  {
    insert_node(&root, new_node(values->keys[i]));

    i++;
  }
  return root;
}
void calculate_subTR_less_subTL(node *root)
{
  if (root)
  {
    root->subTRLessSubTL = calculate_tree_keys_sum(root->right) - calculate_tree_keys_sum(root->left);
    calculate_subTR_less_subTL(root->left);
    calculate_subTR_less_subTL(root->right);
  }
}
int calculate_tree_keys_sum(node *root)
{
  if (root)
  {
    return (root->key + calculate_tree_keys_sum(root->left) + calculate_tree_keys_sum(root->right));
  }
  return 0;
}
void insert_node(node **root, node *newNode)
{
  if (!(*root))
  {
    (*root) = newNode;
  }
  else
  {
    if ((*root)->key > newNode->key)
    {
      if ((*root)->left)
      {
        insert_node(&(*root)->left, newNode);
      }
      else
      {
        (*root)->left = newNode;
        newNode->p = (*root);
      }
    }
    else if ((*root)->key < newNode->key)
    {
      if ((*root)->right)
      {
        insert_node(&(*root)->right, newNode);
      }
      else
      {
        (*root)->right = newNode;
        newNode->p = (*root);
      }
    }
  }
}
node *new_node(int value)
{
  node *new = (node *)malloc(sizeof(node));
  new->key = value;
  new->left = NULL;
  new->right = NULL;
  new->p = NULL;
  new->subTRLessSubTL = EMPTY;
  return new;
}
lineResult *new_line_result()
{
  lineResult *new = (lineResult *)malloc(sizeof(lineResult));
  new->next = NULL;
  new->root = NULL;
  return new;
}
void delete_numbers_list(numbers **firstNumbers)
{
  numbers *curr = *firstNumbers;
  numbers *prev = NULL;

  while (curr)
  {
    prev = curr;
    curr = curr->next;
    free(prev);
    prev = NULL;
  }
  *firstNumbers = NULL;
}
void delete_line_result_list(lineResult **firstLineResult)
{
  lineResult *curr = *firstLineResult;
  lineResult *prev = NULL;

  while (curr)
  {
    prev = curr;
    curr = curr->next;
    free(prev);
    prev = NULL;
  }
  *firstLineResult = NULL;
}

// SEÇÃO DE RECUPERAÇÃO DE DADOS DO ARQUIVO DE ENTRADA
str *get_lines_from_file()
{
  FILE *fileInPtr = fopen(R2Q2_file_in_path, "r");

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