#ifndef VALUENUMBERING_H
#define VALUENUMBERING_H

#include "shared.h"
#include "rulefuncs.h"

struct var_list;
struct var_list{
  long name;
  char is_const;
  int count;
  struct var_list *next;
};

void static_test();
void initilize_vn(long *vn, const int vars);
void insert_to_var_list(struct var_list **var, long id, char const_flag);
int populate_var(struct code_t *code, struct var_list **var);
int get_vt_lines(struct code_t *code);
long find_in_var(struct var_list *var, long id, char const_flag);
long find_count_of_id_in_var(struct var_list *var, int count);
struct var_list *find_count_of_id_in_var_ref(struct var_list *var, int count);
void order(struct var_table *vt, long *order_table, int lines);
int value_number(struct bb_t *code_block, long *lvalue_count, struct var_table *code_block_vt);

#endif