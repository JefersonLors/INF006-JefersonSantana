#include "Q3InGenerator.h"
#include "R2Q3.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
  // L2Q3_in_generator();
  str *firstStr = get_lines_from_file();
  numbers *firstNumbers = create_numbers_list(firstStr);
  delete_str_list(&firstStr);
  lineResult *firstLineResult = create_line_result_list(firstNumbers);
  delete_numbers_list(&firstNumbers);
  write_result_in_file(firstLineResult);
  delete_line_result_list(&firstLineResult);
  puts("end execution");
  return EXIT_SUCCESS;
}
lineResult *create_line_result_list(numbers *firstNumbers)
{
  lineResult *first = NULL;

  if (firstNumbers)
  {
    lineResult *curr = NULL;
    lineResult *last = NULL;
    lineResult *new = new_line_result();

    new->root = create_tree(firstNumbers);
    new->next = NULL;

    calculate_height(new->root);

    first = new;
    last = new;

    firstNumbers = firstNumbers->next;

    while (firstNumbers)
    {
      new = new_line_result();
      new->root = create_tree(firstNumbers);
      new->next = NULL;

      calculate_height(new->root);

      curr = last;
      curr->next = new;
      last = new;
      firstNumbers = firstNumbers->next;
    }
  }
  return first;
}
void write_result_in_file(lineResult *firstLineResult)
{
  FILE *fileOutPtr = fopen(R2Q3_file_out_path, "w");
  char resultLine[MAX_SIZE_LINE];

  while (firstLineResult)
  {
    strcpy(resultLine, "");
    create_string_result_in_order(firstLineResult->root, resultLine);
    resultLine[strlen(resultLine) - 1] = '\0';
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
    sprintf(tempLine, "%d (%d) ", root->key, root->height);
    strcat(string, tempLine);
    create_string_result_in_order(root->right, string);
  }
}
node *create_tree(numbers *values)
{
  node *root = NULL;

  int i = 0;
  while (i < values->keyQTY)
  {
    if (values->ops[i] == 'a')
    {
      insert_node(&root, new_node(values->keys[i]));
    }
    else if (values->ops[i] == 'r')
    {
      node *toDelete = search_node(root, values->keys[i]);
      if (toDelete)
      {
        delete_node(&root, toDelete);
      }
      else
      {
        insert_node(&root, new_node(values->keys[i]));
      }
    }
    i++;
  }
  return root;
}
void delete_node(node **root, node *toDelete)
{
  node *sucessorNode = NULL;
  node *parent = NULL;

  if (toDelete->left == NULL || toDelete->right == NULL)
  {
    sucessorNode = toDelete;
  }
  else
  {
    sucessorNode = sucesssor_node(toDelete);
  }

  if (sucessorNode->left != NULL)
  {
    parent = sucessorNode->left;
  }
  else
  {
    parent = sucessorNode->right;
  }

  if (parent != NULL)
  {
    parent->p = sucessorNode->p;
  }

  if (sucessorNode->p == NULL)
  {
    (*root) = parent;
  }
  else
  {
    if (sucessorNode->p->left == sucessorNode)
    {
      sucessorNode->p->left = parent;
    }
    else
    {
      sucessorNode->p->right = parent;
    }
  }
  if (sucessorNode != toDelete)
  {
    toDelete->key = sucessorNode->key;
  }
}
node *search_node(node *root, int key)
{
  if (!root)
  {
    return NULL;
  }
  else
  {
    if (root->key > key)
    {
      return search_node(root->left, key);
    }
    else if (root->key < key)
    {
      return search_node(root->right, key);
    }
    else
    {
      return root;
    }
  }
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
      }
    }
  }
}
node *sucesssor_node(node *_node)
{
  node *parent;

  if (_node->right != NULL)
  {
    return minimum(_node->right);
  }
  parent = _node->p;
  while (parent != NULL && _node == parent->right)
  {
    _node = parent;
    parent = parent->p;
  }
  return parent;
}
node *minimum(node *_node)
{
  while (_node->left != NULL)
  {
    _node = _node->left;
  }
  return _node;
}
void calculate_height(node *root)
{
  if (root)
  {
    int h = 0;
    node *parent = root;
    while (parent->p)
    {
      h++;
      parent = parent->p;
    }
    root->height = h;
    calculate_height(root->left);
    calculate_height(root->right);
  }
}
node *new_node(int value)
{
  node *new = (node *)malloc(sizeof(node));
  new->key = value;
  new->height = -1;
  new->p = NULL;
  new->left = NULL;
  new->right = NULL;
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
lineResult *new_line_result()
{
  lineResult *new = (lineResult *)malloc(sizeof(lineResult));
  new->next = NULL;
  new->root = NULL;
  return new;
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
  FILE *fileInPtr = fopen(R2Q3_file_in_path, "r");

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

  str *currStrKey = break_line_in_str_list(currStr->content);

  newN = new_numbers();
  newN->keyQTY = get_size_str_linked_list(currStrKey) / 2;
  newN->ops = (char *)malloc(sizeof(char) * newN->keyQTY);
  newN->keys = (int *)malloc(sizeof(int) * newN->keyQTY);
  newN->next = NULL;

  strcpy(newN->ops, "");
  get_operations_from_string(currStrKey, newN->ops, newN->keyQTY);
  get_values_from_string(currStrKey, newN->keys, newN->keyQTY);

  delete_str_list(&currStrKey);

  firstN = newN;
  lastN = newN;

  currStr = currStr->next;

  while (currStr)
  {
    currStrKey = break_line_in_str_list(currStr->content);
    newN = new_numbers();
    newN->keyQTY = get_size_str_linked_list(currStrKey) / 2;
    newN->ops = (char *)malloc(sizeof(char) * newN->keyQTY + 1);
    newN->keys = (int *)malloc(sizeof(int) * newN->keyQTY);
    newN->next = NULL;

    strcpy(newN->ops, "");

    get_operations_from_string(currStrKey, newN->ops, newN->keyQTY);
    get_values_from_string(currStrKey, newN->keys, newN->keyQTY);

    delete_str_list(&currStrKey);

    currN = lastN;
    currN->next = newN;
    lastN = newN;

    currStr = currStr->next;
  }

  return firstN;
}
void get_operations_from_string(str *start, char *list, int size)
{
  int i = 0;

  while (i < size)
  {
    strcat(list, start->content);
    start = start->next;
    if (start)
    {
      start = start->next;
    }
    i++;
  }
  strcat(list, "\0");
}
void get_values_from_string(str *start, int *list, int size)
{
  int i = 0;
  start = start->next;

  while (i < size && start)
  {
    list[i] = atoi(start->content);

    start = start->next;
    if (start)
    {
      start = start->next;
    }
    i++;
  }
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