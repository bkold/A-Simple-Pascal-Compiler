/*
 * rulefuncs.h
 *
 */

#ifndef RULEFUNCS_H
#define RULEFUNCS_H

#include "shared.h"
#include "valuenumbering.h"
#include "usrdef.h"
#include "symtab.h"
#include "y.tab.h"
#include "error.h"
#include <limits.h>

/* ----------------------------------------------------------------
 * Function declarations
 * ----------------------------------------------------------------
 */
struct identifier_list_t *new_identifier_list();
void add_to_identifier_list(struct identifier_list_t **il, char *id);
long identifier_list_count(struct identifier_list_t *il);
char *new_identifier(char *text);
struct class_list_t *new_class_list();
void add_to_class_list(struct class_list_t **cl, struct class_identification_t *ci, struct class_block_t *b);
struct class_identification_t *new_class_identification();
struct actual_parameter_list_t *new_actual_parameter_list();
void add_to_actual_parameter_list(struct actual_parameter_list_t **apl,
				struct actual_parameter_t *ap);
struct record_section_t *new_record_section();
struct record_section_list_t *new_record_section_list();
void add_to_record_section_list(struct record_section_list_t **rsl,
				struct record_section_t *rs);
struct type_denoter_t *new_type_denoter();
struct variable_declaration_list_t *new_variable_declaration_list();
void add_to_variable_declaration_list(struct variable_declaration_list_t **vdl,
				struct variable_declaration_t *vd);
struct function_designator_t *new_function_designator();
struct function_identifier_list_t *new_function_identifier_list();
struct range_t *new_range();
struct formal_parameter_section_list_t *new_formal_parameter_section_list();
void add_to_formal_parameter_section_list(struct formal_parameter_section_list_t **fpsl,
					struct formal_parameter_section_t *fps);
struct variable_access_t *new_variable_access();
struct assignment_statement_t *new_assignment_statement();
struct object_instantiation_t *new_object_instantiation();
struct print_statement_t *new_print_statement();
struct expression_t *new_expression();
struct statement_t *new_statement();
struct statement_sequence_t *new_statement_sequence();
void add_to_statement_sequence(struct statement_sequence_t **ss,
			struct statement_t *s);
struct function_block_t *new_function_block();
struct if_statement_t *new_if_statement();
struct while_statement_t *new_while_statement();
struct indexed_variable_t *new_indexed_variable();
struct attribute_designator_t *new_attribute_designator();
struct method_designator_t *new_method_designator();
struct index_expression_list_t *new_index_expression_list();
void add_to_index_expression_list(struct index_expression_list_t **iel,
				struct expression_t *ie);
long index_expression_list_count(struct index_expression_list_t *iel);
struct actual_parameter_t *new_actual_parameter();
struct simple_expression_t *new_simple_expression();
void add_to_simple_expression(struct simple_expression_t **se,
			int addop,
			struct term_t *t);
struct term_t *new_term();
void add_to_term(struct term_t **t, int mulop, struct factor_t *f);
struct factor_t *new_factor();
void add_to_factor_data(struct factor_t **t, int data, struct factor_t *f); //Newly added
int *new_sign();
struct primary_t *new_primary();
void add_to_primary_data(struct primary_t **t, int data, struct primary_t *p); //Newly added
struct unsigned_number_t *new_unsigned_number();
struct array_type_t *new_array_type();
struct class_block_t *new_class_block();
char *new_primitive_type(char *type);
struct func_declaration_list_t *new_func_declaration_list();
void add_to_func_declaration_list(struct func_declaration_list_t **fdl,
				struct function_declaration_t *fd);
struct function_declaration_t *new_function_declaration();
struct function_heading_t *new_function_heading();
struct variable_declaration_t *new_variable_declaration();
struct formal_parameter_section_t *new_formal_parameter_section();
struct program_t *new_program();
struct program_heading_t *new_program_heading();
struct expression_data_t *new_expression_data();
struct class_list_t *locate_parent(struct class_list_t **cl, char *name);
int builtin_type(char *id);
struct class_list_t *lookup_in_class_list(struct class_list_t **list, char *name);
struct variable_declaration_t *find_variable(struct class_list_t *current_scope, char *id);
void check_variable_declaration_id_list(struct identifier_list_t *il, int line_number);
struct variable_declaration_t *find_variable_in_vdl(struct variable_declaration_list_t *current_list,
					char *id,
					int line_number,
					int mode);
long get_variable_index(struct variable_declaration_list_t *current_list,
					char *id);
char *get_variable_name(struct variable_declaration_list_t *current_list, long number);
struct variable_declaration_t *find_variable_in_class(struct class_list_t *current_scope,
					char *id,
					int line_number,
					int mode);
int find_function_in_fdl(struct func_declaration_list_t *list,
					char *id,
					int line_number,
					int mode);
int is_keyword(struct identifier_list_t *il, int line_number);

struct code_t *new_code();
struct code_t *new_label();
void add_to_code(struct code_t **cl, struct code_t *ci);
long new_lvalue(long *lvalue_count);
struct bb_t *new_bb();
struct cfg_t *new_cfg_t();
void add_edge(struct bb_t *parent, struct bb_t *child);
void find_leaders(struct code_t *first_code_block, struct bb_t *bb_head);
void count_code_blocks(struct code_t *first_code_block);
void find_exits(struct code_t *first_code_block, struct bb_t *bb_head);
void build_cfg(struct code_t *first_code_block, struct bb_t *bb_head);
void print_cfg(struct bb_t *bb_head);
void value_number_bb(struct bb_t *code_block, long *lvalue_count);
void print_3AC(struct variable_declaration_list_t *current_variable_list, struct code_t *cursor, FILE *program);
struct memory_map_list_t *new_memory_map();
int get_size(struct type_denoter_t *tden);
void build_memory_map(struct variable_declaration_list_t* vdl);
void print_arithmatic(enum operations op, FILE *program);
unsigned int get_offset_from_il(struct identifier_list_t *il, char *id);
#endif
