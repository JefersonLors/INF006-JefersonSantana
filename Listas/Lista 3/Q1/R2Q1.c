#include <string.h>
#include "R2Q1.h"
#include "Q1InGenerator.h"

int main()
{
  // L2Q1_in_generator();
  str *firstStr = get_lines_from_file();
  numbers *firstNumber = create_numbers_list(firstStr);
  delete_str_list(&firstStr);
  lineResult *firstLineResult = create_line_result_list(firstNumber);
  delete_numbers_list(&firstNumber);
  write_result_in_file(firstLineResult);
  delete_line_result_list(&firstLineResult);
  puts("end execution");

  return EXIT_SUCCESS;
}
void write_result_in_file(lineResult *firstLineResult)
{
  FILE *fileOutPtr = fopen(R2Q1_file_out_path, "w");

  while (firstLineResult)
  {
    int i = 0;

    while (i < firstLineResult->hQty)
    {
      fprintf(fileOutPtr, "%d ", firstLineResult->heights[i]);
      i++;
    }
    fprintf(fileOutPtr, "max %d alt %d pred ", firstLineResult->max, firstLineResult->maxH);
    if (firstLineResult->maxPred != EMPTY)
    {
      fprintf(fileOutPtr, "%d\n", firstLineResult->maxPred);
    }else{
      fprintf(fileOutPtr, "%s\n", "NaN");
    }

    firstLineResult = firstLineResult->next;
  }
  fclose(fileOutPtr);
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
void delete_line_result_list(lineResult **firstlineResult)
{
  lineResult *curr = *firstlineResult;
  lineResult *prev = NULL;

  while (curr)
  {
    prev = curr;
    curr = curr->next;
    free(prev);
    prev = NULL;
  }
  *firstlineResult = NULL;
}
lineResult *create_line_result_list(numbers *values)
{
  lineResult *first = NULL;

  if (values)
  {
    lineResult *new = new_line_result();
    lineResult *curr = NULL;
    lineResult *last = NULL;

    int *heights = (int *)malloc(sizeof(int) * values->keyQTY);

    node *tree = create_tree(values, heights);
    new->heights = heights;
    new->hQty = values->keyQTY;
    node *max = maximum(tree);
    new->max = max->key;
    node *pred = predecessor(max);
    new->maxPred = pred->key;
    new->maxH = calculate_height(max);

    new->next = NULL;

    first = new;
    last = new;

    values = values->next;

    int line = 2;
    while (values)
    {
      lineResult *new = new_line_result();
      int *heights = (int *)malloc(sizeof(int) * values->keyQTY);
      node *tree = create_tree(values, heights);
      new->heights = heights;
      new->hQty = values->keyQTY;
      node *max = maximum(tree);
      new->max = max->key;
      node *pred = predecessor(max);
      new->maxPred = (pred ? pred->key : EMPTY);
      new->maxH = calculate_height(max);

      new->next = NULL;

      curr = last;
      curr->next = new;
      last = new;
      line++;
      values = values->next;
    }
  }
  return first;
}
lineResult *new_line_result()
{
  lineResult *new = (lineResult *)malloc(sizeof(lineResult));
  new->heights = NULL;
  new->hQty = -1;
  new->max = -1;
  new->maxH = -1;
  new->maxPred = -1;
  new->next = NULL;
  return new;
}
lineResult *create_line_result()
{
  lineResult *new = (lineResult *)malloc(sizeof(lineResult));
  new->heights = NULL;
  new->hQty = -1;
  new->max = -1;
  new->maxH = -1;
  new->maxPred = -1;
  new->next = NULL;

  return new;
}
node *create_tree(numbers *values, int *heights)
{
  node *root = NULL;

  int i = 0;
  while (i < values->keyQTY)
  {
    heights[i] = insert_node(&root, create_node(values->keys[i]));
    i++;
  }
  return root;
}
int insert_node(node **root, node *newNode)
{
  if (!(*root))
  {
    newNode->height = calculate_height(newNode);
    (*root) = newNode;
    return (*root)->height;
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
        newNode->height = calculate_height(newNode);
        return newNode->height;
      }
    }
    else if ((*root)->key <= newNode->key)
    {
      if ((*root)->right)
      {
        insert_node(&(*root)->right, newNode);
      }
      else
      {
        (*root)->right = newNode;
        newNode->p = (*root);
        newNode->height = calculate_height(newNode);
        return newNode->height;
      }
    }
  }
}
int calculate_height(node *subRoot)
{
  int h = 0;

  while (subRoot->p)
  {
    h++;
    subRoot = subRoot->p;
  }
  return h;
}
node *predecessor(node *root)
{
  node *parent;

  if (root->left)
  {
    return maximum(root->left);
  }
  parent = root->p;

  while (parent && root == parent->left)
  {
    root = parent;
    parent = parent->p;
  }
  return parent;
}
node *maximum(node *root)
{
  while (root->right)
  {
    root = root->right;
  }
  return root;
}
void show_in_order(node *root)
{
  if (root)
  {
    show_in_order(root->left);
    printf("%d -> [%d]\t", root->key, root->height);
    show_in_order(root->right);
  }
}
node *create_node(int value)
{
  node *new = (node *)malloc(sizeof(node));
  new->key = value;
  new->height = -1;
  new->p = NULL;
  new->left = NULL;
  new->right = NULL;
}

// SEÇÃO DE RECUPERAÇÃO DE DADOS DO ARQUIVO DE ENTRADA
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

  int line = 2;
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
    line++;
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