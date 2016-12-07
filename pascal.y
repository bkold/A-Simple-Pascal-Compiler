%{
/*
 * grammar.y
 *
 * Pascal grammar in Yacc format, based originally on BNF given
 * in "Standard Pascal -- User Reference Manual", by Doug Cooper.
 * This in turn is the BNF given by the ANSI and ISO Pascal standards,
 * and so, is PUBLIC DOMAIN. The grammar is for ISO Level 0 Pascal.
 * The grammar has been massaged somewhat to make it LALR.
 */

#include "shared.h"
#include "rulefuncs.h"
#include "valuenumbering.h"
#include <strings.h>
#include <stdio.h>
#include <limits.h>

  int yylex(void);
  void yyerror(const char *error);

  extern char *yytext;          /* yacc text variable */
  extern int line_number;       /* Holds the current line number; specified
				   in the lexer */
  struct program_t *program;    /* points to our program */
  struct class_list_t *class_list_head;	/*points to class list */
  struct class_list_t *current_scope;	/*current class scope of program*/
  struct variable_declaration_list_t *current_variable_list;  /*points to the latest VAR block*/
  struct func_declaration_list_t *current_function_list;  /*points to the latest VAR block*/
  static long lvalue_count = LONG_MAX-1;
%}

%token AND ARRAY ASSIGNMENT CLASS COLON COMMA DIGSEQ
%token DO DOT DOTDOT ELSE END EQUAL EXTENDS FUNCTION
%token GE GT IDENTIFIER IF LBRAC LE LPAREN LT MINUS MOD NEW NOT
%token NOTEQUAL OF OR PBEGIN PLUS PRINT PROGRAM RBRAC
%token RPAREN SEMICOLON SLASH STAR THEN
%token VAR WHILE

%type <tden> type_denoter
%type <id> result_type
%type <id> identifier
%type <idl> identifier_list
%type <fdes> function_designator
%type <apl> actual_parameter_list
%type <apl> params
%type <ap> actual_parameter
%type <vd> variable_declaration
%type <vdl> variable_declaration_list
%type <r> range
%type <ic> unsigned_integer
%type <fpsl> formal_parameter_section_list
%type <fps> formal_parameter_section
%type <fps> value_parameter_specification
%type <fps> variable_parameter_specification
%type <va> variable_access
%type <as> assignment_statement
%type <os> object_instantiation
%type <ps> print_statement
%type <e> expression
%type <s> statement
%type <ss> compound_statement
%type <ss> statement_sequence
%type <ss> statement_part
%type <is> if_statement
%type <ws> while_statement
%type <e> boolean_expression
%type <iv> indexed_variable
%type <ad> attribute_designator
%type <md> method_designator
%type <se> simple_expression
%type <t> term
%type <f> factor
%type <i> sign
%type <p> primary
%type <at> array_type
%type <cb> class_block
%type <vdl> variable_declaration_part
%type <fdl> func_declaration_list
%type <funcd> function_declaration
%type <fb> function_block
%type <fh> function_heading
%type <id> function_identification
%type <fpsl> formal_parameter_list
%type <cl> class_list
%type <ci> class_identification
%type <program> program
%type <ph> program_heading
%type <op> relop
%type <op> addop
%type <op> mulop

%union {
  struct type_denoter_t *tden;
  char *id;
  int  ic;
  struct identifier_list_t *idl;
  struct function_designator_t *fdes;
  struct actual_parameter_list_t *apl;
  struct actual_parameter_t *ap;
  struct variable_declaration_list_t *vdl;
  struct variable_declaration_t *vd;
  struct range_t *r;
  struct formal_parameter_section_list_t *fpsl;
  struct formal_parameter_section_t *fps;
  struct variable_access_t *va;
  struct assignment_statement_t *as;
  struct object_instantiation_t *os;
  struct print_statement_t *ps;
  struct expression_t *e;
  struct simple_expression_t *se;
  struct statement_t *s;
  struct statement_sequence_t *ss;
  struct if_statement_t *is;
  struct while_statement_t *ws;
  struct indexed_variable_t *iv;
  struct attribute_designator_t *ad;
  struct method_designator_t *md;
  struct term_t *t;
  struct factor_t *f;
  int i;
  struct primary_t *p;
  struct array_type_t *at;
  struct class_block_t *cb;
  struct func_declaration_list_t *fdl;
  struct function_declaration_t *funcd;
  struct function_block_t *fb;
  struct function_heading_t *fh;
  struct class_identification_t *ci;
  struct class_list_t *cl;
  struct program_t *program;
  struct program_heading_t *ph;
  int op;
}

%%

program : program_heading semicolon class_list DOT
	{
		//nothing to do!
	}
 ;

program_heading : PROGRAM identifier
	{
		printf("PROG %s\n", $2);
		program = new_program();
		program->ph = new_program_heading();
		program->ph->id = $2;
	}
 ;

identifier_list : identifier_list comma identifier
	{
		$$ = $1;
		add_to_identifier_list(&$$, $3);
	}
 | identifier
	{
		$$ = NULL;
		add_to_identifier_list(&$$, $1);
	}
 ;

class_list: class_list class_identification PBEGIN class_block END
	{
		//nothing to do!
	}
 | class_identification PBEGIN class_block END
	{
		//nothing to do!
	}
 ;

class_identification : CLASS identifier
	{
		struct class_block_t *temp_cb = new_class_block();
		struct class_identification_t *temp_ci = new_class_identification();
		struct class_list_t *temp;

		temp_ci->id = $2;
		temp_ci->line_number = line_number;


		//check_class_name_errors($2);
		struct class_list_t *check = lookup_in_class_list(&class_list_head, $2);
		if(check != NULL){
			error_class_already_declared(line_number, check->ci->id, check->ci->line_number);
		}

		add_to_class_list(&class_list_head, temp_ci, temp_cb);

		temp = class_list_head;
		GOTO_END_OF_LIST(temp);
		current_scope = temp;
	}
 | CLASS identifier EXTENDS identifier
	{
		struct class_block_t *temp_cb = new_class_block();
		struct class_identification_t *temp_ci = new_class_identification();
		struct class_list_t *temp;

		temp_ci->id = $2;
		temp_ci->extend = $4;
		temp_ci->line_number = line_number;


		//check_class_name_errors($2); //Need to implement in rulefuncs.c


		add_to_class_list(&class_list_head, temp_ci, temp_cb);

		temp = class_list_head;
		GOTO_END_OF_LIST(temp);
		current_scope = temp;

		current_scope->parent = locate_parent(&class_list_head, temp_ci->extend);
	}
;

class_block: variable_declaration_part

	{
		current_scope->cb->vdl = current_variable_list;

	}func_declaration_list{
		//check function list
		current_scope->cb->fdl = current_function_list;
	}
 ;

type_denoter : array_type
	{
		$$ = new_type_denoter();
		$$->type = TYPE_DENOTER_T_ARRAY_TYPE;
		$$->name = NULL;
		$$->data.at = $1;
	}
 | identifier
	{
		$$ = new_type_denoter();
		$$->name = $1;
		if(builtin_type($1)){
			$$->type = TYPE_DENOTER_T_IDENTIFIER;
			$$->data.id = $1;
		}else{
			//check it's not reserved

			struct class_list_t *node = lookup_in_class_list(&class_list_head, $1);
			if(node != NULL){
				$$->type = TYPE_DENOTER_T_CLASS_TYPE;
				$$->data.cl = node;
			}else{
				error_type_not_defined(line_number, $1);
			}
		}
	}
 ;

array_type : ARRAY LBRAC range RBRAC OF type_denoter
	{
		$$ = new_array_type();
		$$->r = $3;
		$$->td = $6;
	}
 ;

range : unsigned_integer DOTDOT unsigned_integer
	{
		$$ = new_range();
		$$->min = new_unsigned_number();
		$$->max = new_unsigned_number();
		$$->min->ui = $1;
		$$->max->ui = $3;
		if($1 > $3){
			error_array_range_invalid(line_number, $1, $3);
		}
	}
 ;

variable_declaration_part : VAR variable_declaration_list semicolon
	{
		current_variable_list = $2;
		build_memory_map($2);
	}
 |
	{
		// current_variable_list = NULL;
		//nothing to do
	}
 ;

variable_declaration_list : variable_declaration_list semicolon variable_declaration
	{
		// we should add checks for the variables here
		check_variable_declaration_id_list($3->il, line_number);
		is_keyword($3->il, line_number);
		struct identifier_list_t *iter = $3->il;
		while(iter != NULL){
			find_variable_in_class(current_scope, iter->id, line_number, 1);
			find_variable_in_vdl($1, iter->id, line_number, 1);
			iter = iter->next;
		}
		$$ = $1;
		add_to_variable_declaration_list(&$$, $3);
	}
 | variable_declaration
	{
		// we should add checks for the variables here
		check_variable_declaration_id_list($1->il, line_number);
		is_keyword($1->il, line_number);
		struct identifier_list_t *iter = $1->il;
		while(iter != NULL){
			find_variable_in_class(current_scope, iter->id, line_number, 1);
			iter = iter->next;
		}
		$$ = NULL;
		add_to_variable_declaration_list(&$$, $1);
	}

 ;

variable_declaration : identifier_list COLON type_denoter
	{
		$$ = new_variable_declaration();
		$$->il = $1;
		$$->tden = $3;
		$$->line_number = line_number;
		// printf("\nFound Variables of type \"%s\" at line %d", $3->name, line_number);
	}
 ;

func_declaration_list : func_declaration_list semicolon function_declaration
	{
		$$ = $1;
		current_function_list = $$;
		find_function_in_fdl(current_function_list, $3->fh->id, line_number, 1);
		add_to_func_declaration_list(&$$, $3);
	}
 | function_declaration
	{
		$$ = NULL;
		current_function_list = $$;
		add_to_func_declaration_list(&$$, $1);
	}
 |
	{
		$$ = NULL;
		//?
	}
 ;

formal_parameter_list : LPAREN formal_parameter_section_list RPAREN
	{
		//Not very clear on this, I think this is correct
		$$ = $2;
	}
;

formal_parameter_section_list : formal_parameter_section_list semicolon formal_parameter_section
	{
		$$ = $1;
		add_to_formal_parameter_section_list(&$$, $3);
	}
 | formal_parameter_section
	{
		$$ = NULL;
		add_to_formal_parameter_section_list(&$$, $1);
	}
 ;

formal_parameter_section : value_parameter_specification
 | variable_parameter_specification
 ;

value_parameter_specification : identifier_list COLON identifier
	{
		$$ = new_formal_parameter_section();
		$$->il = $1;
		$$->id = $3;
	}
 ;

variable_parameter_specification : VAR identifier_list COLON identifier
	{
		$$ = new_formal_parameter_section();
		$$->il = $2;
		$$->id = $4;
		$$->is_var = 1;
	}
 ;

function_declaration : function_identification semicolon function_block
	{
		//we may need to check if the function exits before this
		$$ = new_function_declaration();
		$$->fh = new_function_heading();
		$$->fh->id = $1;
		$$->fb = $3;
		$$->line_number = line_number;

		$$->code = $3->code;
		//PRINTER
		{
			FILE *program_file;
			program_file = fopen("out.asm", "w+");
			if(program_file == NULL){
				puts("FILE I/O Error, could not create assembly file");
			}

			//print data section
			{
				fputs(".data\n", program_file);
				fputs("NEW_LINE_CONSTANT: .asciiz \"  \\n\"\n", program_file);
				for(struct variable_declaration_list_t *vdl = current_variable_list;
					vdl != NULL; vdl = vdl->next){
						for(struct identifier_list_t *id_list = vdl->vd->il;
							id_list != NULL; id_list = id_list->next){
								fprintf(program_file, "%s:", id_list->id);
								if(vdl->vd->tden->type == 2){
									fprintf(program_file, " .word 0 #%d\n ", vdl->vd->tden->data.cl->cb->size);
								}else{
									if(vdl->vd->tden->size == 4){
										fputs(" .word 0 ", program_file);
									}else{
										fprintf(program_file, " .space %d", vdl->vd->tden->size);
									}
								}
								fputs("\n", program_file);
						}
				}
			}
			
			//print text section
			{
				fputs("\n\n.text\n", program_file);
				fputs(".globl main\n\n", program_file);
				fputs("main:\n", program_file);
				struct code_t *cursor = $$->code;
				puts("....Full 3-address code....");
				while(cursor != NULL){
					//call print method on iterating cursor
					print_3AC(current_variable_list, cursor, program_file);
					cursor = cursor->next;
				}
				puts("###########\n\n");
			}
			fputs("# Exit\n\tli	$v0, 10\n\tsyscall\n", program_file);
			fclose(program_file);
		}//END PRINTER
	}
 | function_heading semicolon function_block
	{
		$$ = new_function_declaration();
		$$->fh = $1;
		$$->fb = $3;
		$$->line_number = line_number;
	}
 ;

function_heading : FUNCTION identifier COLON result_type
	{
		$$ = new_function_heading();
		$$->id = $2;
		$$->res = $4;
	}
 | FUNCTION identifier formal_parameter_list COLON result_type
	{
		$$ = new_function_heading();
		$$->id = $2;
		$$->fpsl = $3;
		$$->res = $5;
	}
 ;

result_type : identifier ;

function_identification : FUNCTION identifier
	{
		$$ = $2;
	}
;

function_block : variable_declaration_part statement_part
	{
		$$ = new_function_block();
		$$->vdl = $1;
		$$->ss = $2;
		add_to_code(&$$->code, $2->code);

	}
;

statement_part : compound_statement ;

compound_statement : PBEGIN statement_sequence END
	{
		$$ = $2;
	}
 ;

statement_sequence : statement
	{
		$$ = NULL;
		add_to_statement_sequence(&$$, $1);
		$$->code = $1->code;
	}
 | statement_sequence semicolon statement
	{
		$$ = $1;
		add_to_statement_sequence(&$$, $3);
		add_to_code(&($$->code), $3->code);
	}
 ;

statement : assignment_statement
	{
		$$ = new_statement();
		$$->type = 1;
		$$->data.as = $1;
		$$->line_number = line_number;
		$$->code = $1->code;
	}
 | compound_statement
	{
		$$ = new_statement();
		$$->type = 2;
		$$->data.ss = $1;
		$$->line_number = line_number;
		$$->code = $1->code;
	}
 | if_statement
	{
		$$ = new_statement();
		$$->type = 3;
		$$->data.is = $1;
		$$->line_number = line_number;
		$$->code = $1->code;
	}
 | while_statement
	{
		$$ = new_statement();
		$$->type = 4;
		$$->data.ws = $1;
		$$->line_number = line_number;
		$$->code = $1->code;
	}
 | print_statement
	{
		$$ = new_statement();
		$$->type = 5;
		$$->data.ps = $1;
		$$->line_number = line_number;
		$$->code = $1->code;
	}
 ;

while_statement : WHILE boolean_expression DO statement
	{
		$$ = new_while_statement();
		$$->e = $2;
		$$->s = $4;

		struct code_t *label1 = new_label(); //new start label
		label1->lvalue = new_lvalue(&lvalue_count);

		struct code_t *label2 = new_label(); //new end label
		label2->lvalue = new_lvalue(&lvalue_count);

		struct code_t *jump1 = new_label(); //new jump
		jump1->op = JUMP_OP;
		{
			struct code_t *cursor = $2->code;
			GOTO_END_OF_LIST(cursor);
			jump1->lvalue = new_lvalue(&lvalue_count); //set the condition to the last of $2
			jump1->var1 = cursor->lvalue; //set the condition to the last of $2
		}
		jump1->target = label2; //set label1 target to label1

		struct code_t *jump2 = new_label(); //new jump
		jump2->op = JUMP_OP;
		jump2->lvalue = new_lvalue(&lvalue_count);
		jump2->var1 = LONG_MAX; //unconditional
		jump2->target = label1; //set label2 target to label1

		$$->code = label1;
		add_to_code(&($$->code), $2->code);
		add_to_code(&($$->code), jump1);
		add_to_code(&($$->code), $4->code);
		add_to_code(&($$->code), jump2);
		add_to_code(&($$->code), label2);

		//debug code
		// {
		// 	struct code_t *cursor = $$->code;
		// 	puts("....WHILE....");
		// 	while(cursor != NULL){
		// 		puts("...........");
		// 		printf(".lvalue: %ld\n.var1: %ld\n.var1_const: %d\n.var2: %ld\n.var2_const: %d\n.OP: %d\n",
		// 			cursor->lvalue, cursor->var1, cursor->var1_const, cursor->var2, cursor->var2_const, cursor->op);
		// 		if(cursor->target != NULL){
		// 			printf(".target: %ld\n", cursor->target->lvalue);
		// 		}
		// 		cursor = cursor->next;
		// 	}
		// 	puts("###########");
		// }
	}
 ;

if_statement : IF boolean_expression THEN statement ELSE statement
	{
		$$ = new_if_statement();
		$$->e = $2;
		$$->s1 = $4;
		$$->s2 = $6;

		struct code_t *label1 = new_label();
		label1->lvalue = new_lvalue(&lvalue_count);

		struct code_t *label2 = new_label();
		label2->lvalue = new_lvalue(&lvalue_count);

		struct code_t *jump1 = new_label();
		jump1->op = JUMP_OP;
		{
			struct code_t *cursor = $2->code;
			GOTO_END_OF_LIST(cursor);
			jump1->lvalue = new_lvalue(&lvalue_count); //set the condition to the last of $2
			jump1->var1 = cursor->lvalue; //set the condition to the last of $2
		}
		jump1->target = label1; //set label1 target to label1

		struct code_t *jump2 = new_label();
		jump2->op = JUMP_OP;
		jump2->lvalue = new_lvalue(&lvalue_count);
		jump2->var1 = LONG_MAX; //unconditional
		jump2->target = label2; //set label2 target to label1

		$$->code = $2->code;
		add_to_code(&($$->code), jump1);
		add_to_code(&($$->code), $4->code);
		add_to_code(&($$->code), jump2);
		add_to_code(&($$->code), label1);
		add_to_code(&($$->code), $6->code);
		add_to_code(&($$->code), label2);

		//debug code
		// {
		// 	struct code_t *cursor = $$->code;
		// 	puts("...IF...");
		// 	while(cursor != NULL){
		// 		puts("...........");
		// 		printf(".lvalue: %ld\n.var1: %ld\n.var1_const: %d\n.var2: %ld\n.var2_const: %d\n.OP: %d\n",
		// 			cursor->lvalue, cursor->var1, cursor->var1_const, cursor->var2, cursor->var2_const, cursor->op);
		// 		if(cursor->target != NULL){
		// 			printf(".target: %ld\n", cursor->target->lvalue);
		// 		}
		// 		cursor = cursor->next;
		// 	}
		// 	puts("###########");
		// }

	}
 ;

assignment_statement : variable_access ASSIGNMENT expression
	{
		//check types match
		//add checks if class, currently fail class assignment

		// if(strcmp($3->expr->type, $1->expr->type) != 0){
		// 	error_type_mismatch(line_number, $3->expr->type, $1->expr->type);
		// }
		struct code_t *cursor = $1->code;
		long id_num;
		if(cursor != NULL){
			GOTO_END_OF_LIST(cursor);
			id_num = cursor->lvalue; 
		}

		$$ = new_assignment_statement();
		$$->va = $1;
		$$->e = $3;
		$$->code = $1->code;
		add_to_code(&$$->code, $3->code);

		cursor = $$->code;
		if(cursor != NULL){
			GOTO_END_OF_LIST(cursor);
			if(cursor->op != ASSIGNMENT_OP){
				cursor->next = new_code();
				cursor->next->var1 = cursor->lvalue;
				cursor->next->var1_const = 0;
				cursor->next->var2_const = -1;
				cursor->next->op = ASSIGNMENT_OP;
				switch ($$->va->type){
					case 1:
						id_num = get_variable_index(current_variable_list, $$->va->data.id);
						// if(cursor->op == NEG_OP || cursor->op == NOT_OP){
						// 	puts("HERE");
						// }
						break;
					case 2:
					case 3:
						cursor->next->op = STORE_OP;
						break;
					default:
						id_num = -10;
						break;
				}
				cursor->next->lvalue = id_num;
			}else{
				cursor->lvalue = get_variable_index(current_variable_list, $$->va->data.id);
				if($$->va->type == 2 || $$->va->type == 3){
					cursor->op = STORE_OP;
				}
				// puts("HERE");
				// printf("%d\n", $$->va->type);
				// //debug code
				// {
				// 	struct code_t *cursor = $$->code;
				// 	while(cursor != NULL){
				// 		puts("-----------");
				// 		printf("-lvalue: %ld\n-var1: %ld\n-var1_const: %d\n-var2: %ld\n-var2_const: %d\n-OP: %d\n",
				// 			cursor->lvalue, cursor->var1, cursor->var1_const, cursor->var2, cursor->var2_const, cursor->op);
				// 		cursor = cursor->next;
				// 	}
				// 	puts("###########");
				// }
			}
		}else{
			puts("PANIC");
			// cursor = new_code();
			// cursor->lvalue = get_variable_index(current_variable_list, $3->data.id);
			// cursor->var1 = $1->code->lvalue;
			// cursor->var1_const = 0;
			// cursor->var2_const = -1;
			// cursor->op = ASSIGNMENT_OP;
			// $$->code = cursor;
		}

		
		//debug code
		// {
		// 	struct code_t *cursor = $$->code;
		// 	while(cursor != NULL){
		// 		puts("-----------");
		// 		printf("-lvalue: %ld\n-var1: %ld\n-var1_const: %d\n-var2: %ld\n-var2_const: %d\n-OP: %d\n",
		// 			cursor->lvalue, cursor->var1, cursor->var1_const, cursor->var2, cursor->var2_const, cursor->op);
		// 		cursor = cursor->next;
		// 	}
		// 	puts("###########");
		// }
	}
 | variable_access ASSIGNMENT object_instantiation
	{
		//debug print statements

		if($1->td->type != 2){ //not even an object
			error_type_mismatch(line_number, $1->td->name, $3->id);
		}else if(strcmp($1->td->name, $3->id)){ //not the same object
			error_type_mismatch(line_number, $1->td->name, $3->id);
		}
		$$ = new_assignment_statement();
		$$->va = $1;
		$$->oe = $3;

		struct code_t *cursor = $1->code;
		long id_num;
		if(cursor != NULL){
			GOTO_END_OF_LIST(cursor);
			id_num = cursor->lvalue; 
		}else{
			id_num = get_variable_index(current_variable_list, $$->va->data.id); 
		}

		$$->code = $1->code;

		struct code_t *allocate_block = new_code();
		allocate_block->lvalue = id_num;
		allocate_block->var1 = lookup_in_class_list(&class_list_head, $3->id)->cb->size;
		allocate_block->var1_const = 1;
		allocate_block->op = ALLOCATE_OP;

		add_to_code(&$$->code, allocate_block);

	}
 ;

object_instantiation: NEW identifier
	{
		$$ = new_object_instantiation();
		$$->id = $2;
	}
 | NEW identifier params
	{
		$$ = new_object_instantiation();
		$$->id = $2;
		$$->apl = $3;
	}
;

print_statement : PRINT variable_access
	{
		$$ = new_print_statement();
		$$->va = $2;

		struct code_t *print_code = new_code();
		if($2->type != 1){
			struct code_t *temp = $2->code;
			if(temp != NULL){
				GOTO_END_OF_LIST(temp);
			}
			print_code->var1 = temp->lvalue;
			$$->code = $2->code;

		}else{
			print_code->var1 = get_variable_index(current_variable_list, $2->data.id);
		}
		print_code->lvalue = new_lvalue(&lvalue_count);
		print_code->var1_const = 0;
		print_code->var2_const = -1;
		print_code->op = PRINT_OP;
		add_to_code(&$$->code, print_code);
	}
;

variable_access : identifier
	{
		if(strcmp($1, BOOLEAN_VALUE_TRUE) == 0 || strcmp($1, BOOLEAN_VALUE_TRUE) == 0){
			$$ = new_variable_access();
			$$->expr = new_expression_data();
			$$->type = 1;
			$$->data.id = $1;
			$$->expr->type = "boolean";
		}else{
			$$ = new_variable_access();
			$$->expr = new_expression_data();
			//short circuit check if it is not found anywhere
			struct variable_declaration_t *var = find_variable_in_class(current_scope, $1, line_number, 0);
			if(var == NULL){
				var = find_variable_in_vdl(current_variable_list, $1, line_number, 0);
				if(var == NULL){
					error_variable_not_declared(line_number, $1);
					$$->td = NULL;
					$$->expr->type = "unknown";
					goto exit;
				}
			}
			//var holds the vd of the id ($1)
			$$->td = var->tden;
			$$->expr->type = $$->td->name;
			exit:
			$$->type = 1;
			$$->data.id = $1;
		}
	}
 | indexed_variable
	{
		$$ = new_variable_access();
		$$->expr = new_expression_data();
		$$->type = 2;
		$$->data.iv = $1;
		$$->td = $1->va->td->data.at->td; //variable access is now the type of the element in array
		$$->expr->type = $$->td->name;
		$$->code = $1->code;
	}
 | attribute_designator
	{
		$$ = new_variable_access();
		$$->expr = new_expression_data();
		$$->type = 3;
		$$->data.ad = $1;
		$$->td = $1->va->td;
		$$->expr->type = $$->td->name;
		$$->code = $1->code;
	}
 | method_designator
	{
		$$ = new_variable_access();
		$$->expr = new_expression_data();
		$$->type = 4;
		$$->data.md = $1;
		$$->expr->type = $$->td->name;
	}
 ;

indexed_variable : variable_access LBRAC expression RBRAC
	{

		$$ = new_indexed_variable();
		$$->va = $1;
		if(strcmp($3->expr->type, "integer") != 0){
			error_array_index_is_not_integer(line_number, $1->data.id);
		}
		if($1->td->type == 1){
			// $$->va->td = $1->td->data.at->td; //pass up the td for the component of the array
		}else{
			error_indexed_variable_not_an_array(line_number, $1->data.id);
		}
		struct code_t *code_1 = new_code();
		struct code_t *code_2 = new_code();
		struct code_t *code_3 = new_code();

		struct code_t *end_of_code = $3->code;
	    GOTO_END_OF_LIST(end_of_code);

		code_1->lvalue = new_lvalue(&lvalue_count);
		code_1->var1 = end_of_code->lvalue; // set var1 to result of expression
		code_1->var1_const = 0;
		code_1->var2 = $1->td->data.at->r->min->ui;
		code_1->var2_const = 1;
		code_1->op = SUBTRACTION_OP;
		code_1->next = code_2;

		code_2->lvalue = new_lvalue(&lvalue_count);
		code_2->var1 = code_1->lvalue;
		code_2->var1_const = 0;
		code_2->var2 = $1->td->data.at->td->size;
		// code_2->var2 = 4; //place holder
		code_2->var2_const = 1;
		code_2->op = MULTIPLY_OP;
		code_2->next = code_3;

		code_3->lvalue = new_lvalue(&lvalue_count);
		code_3->var2 = code_2->lvalue;
		code_3->var2_const = 0;

		//if $1 is also indexed_variable
		if($1->type == 2 || $1->type == 3){
			struct code_t *temp = $1->code;
			GOTO_END_OF_LIST(temp);
			code_3->var1 = temp->lvalue;
			code_3->var2_const = 0;
		}else{
			if($1->type == 1 && find_variable_in_vdl(current_variable_list, $1->data.id, line_number, 0) != 0){
					// code_3->var1 = REG_FP; //place holder
					code_3->var1 = get_variable_index(current_variable_list, $1->data.id);
					code_3->var1_const = 0;
			}else{
				// code_3->var2 = get_offset();
				code_3->var1 = 99; //place holder
				code_3->var1_const = 1;
			}
			
		}
		code_3->op = SHIFT_ADDRESS;
		$$->code = $1->code;
		add_to_code(&$$->code, $3->code);
		add_to_code(&$$->code, code_1);

	}
 ;

// index_expression : expression {
// 	$$ = $1;
// };

attribute_designator : variable_access DOT identifier
	{
		//$1 contains a valid id, or not...
		//check if it's an object
		$$ = new_attribute_designator();
		$$->va = new_variable_access();
		if($1->td->type != 2){
			error_variable_not_declared(line_number, $3);
		}else{
			//go to class, td has the class node ptr
			struct class_list_t *node = $1->td->data.cl;
			//find the identifier in the class
			struct variable_declaration_t *vd = find_variable_in_class(node, $3, line_number, 0);
			//if found, pass up
			if(vd == NULL){
				error_variable_not_declared(line_number, $3);
			}else{
				$$->va->td = vd->tden;

				//get address in last block of code in $1
				struct code_t *temp = $1->code;
				struct code_t *new_code_block = new_code();
				new_code_block->lvalue = new_lvalue(&lvalue_count);
				//get offset for indentifier
				if(temp == NULL){
					new_code_block->var1 = get_variable_index(current_variable_list, $1->data.id);
					new_code_block->var1_const = 0;
					new_code_block->var2 = get_offset_from_il(vd->il, $3);
					new_code_block->var2_const = 1;
				}else{
					GOTO_END_OF_LIST(temp);
					new_code_block->var1 = temp->lvalue;
					new_code_block->var1_const = 0;
					puts("HERE");
					// new_code_block->var2 = find_variable_offset(node, vd);
					new_code_block->var2 = get_offset_from_il(vd->il, $3);
					new_code_block->var2_const = 1;
				}
				new_code_block->op = LOAD_OP;

				//build code base
				$$->code = $1->code;
				add_to_code(&$$->code, new_code_block);
				
			}
		}
	}
;

method_designator: variable_access DOT function_designator
	{
		$$ = new_method_designator();
		$$->va = $1;
		$$->fd = $3;
	}
 ;


params : LPAREN actual_parameter_list RPAREN
	{
		$$ = $2;
	}
 ;

actual_parameter_list : actual_parameter_list comma actual_parameter
	{
		$$ = $1;
		add_to_actual_parameter_list(&$$, $3);
	}
 | actual_parameter
	{
		$$ = NULL;
		add_to_actual_parameter_list(&$$, $1);
	}
 ;

actual_parameter : expression
	{
		$$ = new_actual_parameter();
		$$->e1 = $1;
	}
 | expression COLON expression
	{
		$$ = new_actual_parameter();
		$$->e1 = $1;
		$$->e2 = $3;
	}
 | expression COLON expression COLON expression
	{
		$$ = new_actual_parameter();
		$$->e1 = $1;
		$$->e2 = $3;
		$$->e3 = $5;
	}
 ;

boolean_expression : expression {
	$$ = $1;
};

expression : simple_expression
	{
		
		$$ = new_expression();
		$$->se1 = $1;
		$$->expr = $1->expr;
		$$->code = $1->code;
	}
 | simple_expression relop simple_expression
	{
		

		if(strcmp($1->expr->type, $3->expr->type) != 0){
			error_type_mismatch(line_number, $1->expr->type, $3->expr->type);
		}
		$$ = new_expression();
		$$->se1 = $1;
		$$->relop = $2;
		$$->se2 = $3;
		$$->expr = $1->expr;
		$$->code = $1->code;
		{
			struct code_t *temp = $$->code;
			long last_var;
			GOTO_END_OF_LIST(temp);
			last_var = temp->lvalue;
			temp->next = $3->code;

			struct code_t *temp2 = $3->code;
			GOTO_END_OF_LIST(temp2);

			temp2->next = new_code();
			temp2->next->lvalue = new_lvalue(&lvalue_count);
			temp2->next->var1 = last_var;
			temp2->next->var1_const = 0;
			temp2->next->op = $2;
			temp2->next->var2 = $3->code->lvalue;
			temp2->next->var2_const = 0;
		}
	}
 ;

simple_expression : term
	{
		// debug code
		// {
		// 	struct code_t *cursor = $1->code;
		// 	int counter = 0;
		// 	while(cursor != NULL && counter < 5){
		// 		puts("///////////");
		// 		printf("/lvalue: %ld\n/var1: %ld\n/var1_const: %d\n/var2: %ld\n/var2_const: %d\n/OP: %d\n",
		// 			cursor->lvalue, cursor->var1, cursor->var1_const, cursor->var2, cursor->var2_const, cursor->op);
		// 		cursor = cursor->next;
		// 		counter++;
		// 	}
		// 	puts("###########");
		// }
		$$ = new_simple_expression();
		$$->expr = $1->expr;
		$$->t = $1;
		$$->code = $1->code;

		// debug code
		// {
		// 	struct code_t *cursor = $1->code;
		// 	int counter = 0;
		// 	while(cursor != NULL && counter < 5){
		// 		puts("///////////");
		// 		printf("/lvalue: %ld\n/var1: %ld\n/var1_const: %d\n/var2: %ld\n/var2_const: %d\n/OP: %d\n",
		// 			cursor->lvalue, cursor->var1, cursor->var1_const, cursor->var2, cursor->var2_const, cursor->op);
		// 		cursor = cursor->next;
		// 		counter++;
		// 	}
		// 	puts("~~~~~~~~~~~");
		// }
	}
 | simple_expression addop term
	{
		if(strcmp($1->expr->type, $3->expr->type) != 0){
			error_type_mismatch(line_number, $1->expr->type, $3->expr->type);
		}

		// debug code
		// {
		// 	struct code_t *cursor = $1->code;
		// 	while(cursor != NULL){
		// 		puts("<<<<<<<<<<<");
		// 		printf("<lvalue: %ld\n<var1: %ld\n<var1_const: %d\n<var2: %ld\n<var2_const: %d\n<OP: %d\n",
		// 			cursor->lvalue, cursor->var1, cursor->var1_const, cursor->var2, cursor->var2_const, cursor->op);
		// 		cursor = cursor->next;
		// 	}
		// 	puts("###########");
		// }

		//debug code
		// {
		// 	struct code_t *cursor = $3->code;
		// 	while(cursor != NULL){
		// 		puts(">>>>>>>>>>>");
		// 		printf(">lvalue: %ld\n>var1: %ld\n>var1_const: %d\n>var2: %ld\n>var2_const: %d\n>OP: %d\n",
		// 			cursor->lvalue, cursor->var1, cursor->var1_const, cursor->var2, cursor->var2_const, cursor->op);
		// 		cursor = cursor->next;
		// 	}
		// 	puts("###########");
		// }

		$$ = $1;
		add_to_simple_expression(&$$, $2, $3);

		struct code_t *temp = $$->code;
		if(temp != NULL){
			GOTO_END_OF_LIST(temp);
		}

		struct code_t *new_code_block = new_code();
		new_code_block->lvalue = new_lvalue(&lvalue_count);
		new_code_block->var1 = temp->lvalue;
		new_code_block->op = $2;
		new_code_block->var2 = $3->code->lvalue;
		new_code_block->var2_const = 0;

		add_to_code(&$$->code, $3->code);
		add_to_code(&$$->code, new_code_block);
	}
 ;

term : factor
	{
		$$ = new_term();
		$$->expr = $1->expr;
		$$->f = $1;

		//make code block
		if($1->code != NULL){
				$$->code = $1->code;
		}else{
			struct code_t *code = new_code();
			code->lvalue = new_lvalue(&lvalue_count);
			code->op = ASSIGNMENT_OP;
			code->var2_const = -1;

			if($1->type == 1){
				if($1->data.f.sign == -1){
					code->lvalue = new_lvalue(&lvalue_count);
					switch($1->data.f.next->data.p->type){
						case PRIMARY_T_UNSIGNED_CONSTANT:
							code->var1 = -($1->data.f.next->data.p->data.un->ui);
							code->var1_const = 1;
							break;
						case PRIMARY_T_VARIABLE_ACCESS: 
						default:
							code->var1 = get_variable_index(current_variable_list, $1->data.f.next->data.p->data.va->data.id);
							code->var1_const = 0;
							code->op = NEG_OP;
							break;
					}
				}else{
					code->var1 = get_variable_index(current_variable_list, $1->data.f.next->data.p->data.va->data.id);
				}
			}else{
				//primary
				switch($1->data.p->type){
					case 1:
						switch($1->data.p->data.va->type){
							case 1: 
								code->var1 = get_variable_index(current_variable_list, $1->data.p->data.va->data.id);
								break;

							case 2:
							case 3:
								{
									struct code_t *temp = code;
									code = new_code();
									code->next = temp;
									code->lvalue = new_lvalue(&lvalue_count);
									temp = $1->code;
									GOTO_END_OF_LIST(temp);
									code->var1 = temp->lvalue;
									code->var1_const = 0;
									code->var2_const = -1;
									code->op = LOAD_OP;
									code->next->var1 = code->lvalue;
								}
								break;
								
							default:
								code->var1 = -111;
								break;							
						}
						break;
					case 2:
						code->var1 = $1->data.p->data.un->ui;
						code->var1_const = 1;
						break;
					case 4:
						// code = $1->code;
						break;
					default :
						code->var2 = $1->data.p->type;
						code->var2_const = -123;
						break;
				}
				$$->code = $1->code;
			}
			add_to_code(&$$->code, code);

		}
	}
 | term mulop factor
	{
		if(strcmp($1->expr->type, $3->expr->type) != 0){
			error_type_mismatch(line_number, $1->expr->type, $3->expr->type);
		}
		$$ = $1;

		//make code block
		{
			struct code_t *code = new_code();
			struct code_t *temp = $1->code;
		    GOTO_END_OF_LIST(temp);
			code->lvalue = new_lvalue(&lvalue_count);
			code->var1 = temp->lvalue;
			code->op = $2;
			if($3->type == 1){
				code->var2 = get_variable_index(current_variable_list, $3->data.f.next->data.p->data.va->data.id);
			}else{
				switch($3->data.p->type){
					case 1:
						code->var2 = get_variable_index(current_variable_list, $3->data.p->data.va->data.id);
						break;
					case 2:
						code->var2 = $3->data.p->data.un->ui;
						code->var2_const = 1;
						break;
					case 4:
						// code = $1->code;
						break;
					default :
						code->var2 = -1;
						break;
				}
			}
			temp->next = code;

			// debug code
			// {
			// 	struct code_t *cursor = $$->code;
			// 	while(cursor != NULL){
			// 		puts("|||||||||||");
			// 		printf("|lvalue: %ld\n|var1: %ld\n|var1_const: %d\n|var2: %ld\n|var2_const: %d\n|OP: %d\n",
			// 			cursor->lvalue, cursor->var1, cursor->var1_const, cursor->var2, cursor->var2_const, cursor->op);
			// 		cursor = cursor->next;
			// 	}
			// 	puts("~~~~~~~~~~~");
			// }
		}
	}
 ;

sign : PLUS
	{
		$$ = 1;
	}
 | MINUS
	{
		$$ = -1;
	}
 ;

factor : sign factor
	{
		if($2->data.f.sign == 1 || $2->data.f.sign == -1){
			error_too_many_signs(line_number);
		}
		$$ = new_factor();
		$$->type = FACTOR_T_SIGNFACTOR;

		$$->data.f.sign = $1;
		$$->data.f.next = $2;
		$$->expr = $2->expr;
		$$->code = $2->code;
	}
 | primary
	{
		$$ = new_factor();
		$$->type = FACTOR_T_PRIMARY;
		$$->data.p = $1;
		$$->expr = $1->expr;
		$$->code = $1->code;
	}
 ;

primary : variable_access
	{
		
		$$ = new_primary();
		$$->type = 1;
		$$->data.va = $1;
		$$->expr = $1->expr;
		if($1->code != NULL){ //if array or object
			struct code_t *load_block = new_code();
			struct code_t *cursor = $1->code;
			GOTO_END_OF_LIST(cursor);

			load_block->lvalue = new_lvalue(&lvalue_count);
			load_block->var1 = cursor->lvalue;
			load_block->var1_const = 0;
			load_block->var2_const = -1;
			load_block->op = LOAD_OP;

			add_to_code(&$1->code, load_block);
		}

		$$->code = $1->code;
	}
 | unsigned_integer
	{
		
		$$ = new_primary();
		$$->expr = new_expression_data();
		$$->type = 2;
		$$->data.un = new_unsigned_number();
		$$->data.un->ui = $1;
		$$->expr->type = "integer";
		$$->code = NULL;
	}
 | function_designator
	{
		
		$$ = new_primary();
		$$->type = 3;
		$$->data.fd = $1;
		$$->code = NULL;
	}
 | LPAREN expression RPAREN
	{
		
		$$ = new_primary();
		$$->type = 4;
		$$->data.e = $2;
		$$->expr = $2->expr;
		$$->code = $2->code;
	}
 | NOT primary
	{
		
		if(strcmp($2->expr->type, "boolean") != 0){
			error_type_mismatch(line_number, $2->expr->type, "boolean");
		}
		$$ = $2;
	}
 ;

unsigned_integer : DIGSEQ
	{
		$$ = atoi(yytext);

	}
 ;

/* functions with no params will be handled by plain identifier */
function_designator : identifier params
	{
		if(find_function_in_fdl(current_function_list, $1, line_number, 0) == 0){
			error_function_not_declared(line_number, $1);
		}

		$$ = new_function_designator();
		$$->id = $1;
		$$->apl = $2;
	}
 ;

addop: PLUS
	{
		$$ = ADDITION_OP;
	}
 | MINUS
	{
		$$ = SUBTRACTION_OP;
	}
 | OR
	{
		$$ = OR_OP;
	}
 ;

mulop : STAR
	{
		$$ = MULTIPLY_OP;
	}
 | SLASH
	{
		$$ = DIVISION_OP;
	}
 | MOD
	{
		$$ = MOD_OP;
	}
 | AND
	{
		$$ = AND_OP;
	}
 ;

relop : EQUAL
	{
		$$ = EQUALS_OP;
	}
 | NOTEQUAL
	{
		$$ = NOT_EQUAL_OP;
	}
 | LT
	{
		$$ = LESS_THAN_OP;
	}
 | GT
	{
		$$ = GREATER_THAN_OP;
	}
 | LE
	{
		$$ = LESS_THAN_EQUAL_TO_OP;
	}
 | GE
	{
		$$ = GREATER_THAN_EQUAL_TO_OP;
	}
 ;

identifier : IDENTIFIER
	{
		$$ = strdup(yytext);

	}
 ;

semicolon : SEMICOLON ;

comma : COMMA ;

%%
