#include <stdlib.h>
#include <stdio.h>

#ifndef R1Q3_h
#define R1Q3_h

#define MAX_SIZE_LINE 5000
#define KEY_WORD1 "LE"
#define KEY_WORD2 "LI"

typedef struct value
{
  float content;
  struct value *next;
} value;

typedef struct pack
{
  int key;
  int valuesQTY;
  value *floats;
  struct pack *prev;
  struct pack *next;
} pack;

typedef struct packBase
{
  pack *packs;
  struct packBase *next;
} packBase;

typedef struct numbers
{
  int keyQTY;
  int *keys;
  int valuesQTY;
  float *values;
  struct numbers *next;
} numbers;

typedef struct string
{
  char *content;
  struct string *next;
} str;

typedef struct strValues
{
  char *intStrList;
  char *floatStrList;
  struct strValues *next;
} strV;

const char R1Q3_file_in_path[] = "L1Q3.in";
const char R1Q3_file_out_path[] = "L1Q3.out";

str *get_lines_from_file();
str *break_line_in_str_list(char *line);
strV *create_strV_list(str *firstLine);
strV *break_in_two_lists(str *line);
pack *create_number_pack(numbers *firstsNumbers);
value *get_values(int key, float *values, int valuesQTY, int *sizeList);
numbers *create_numbers_list(strV *firstsStrValues);
packBase *create_packBase_list(numbers *firstNumbers);

void write_result_in_file( packBase *firstPackBase );
void sort_pack_list( pack *firstPack );
void sort_value_list( value *firstValue, int sizeList );
void remove_non_numeric_characters_from_string(char *string);
void delete_str_list(str **firstStr);
void delete_numbers_list(numbers **firstNumbers);
void delete_strV_list(strV **firstStrV);
void delete_pack_list(pack **firstPack);
void delete_packBase_list(packBase **firstPackBase);
void show_packaBase_content(packBase *firstPack);
int get_size_str_linked_list(str *start);
#endif