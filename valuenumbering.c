#include "valuenumbering.h"

long *lvalue_counter;

void initilize_vn(long *vn, const int vars){
	int i;
	for(i = 0; i < vars; i++){
		vn[i] = i;
	}
}

void insert_to_var_list(struct var_list **var, long id, char const_flag){
	struct var_list *cursor = *var;
	if(cursor != NULL){
		GOTO_END_OF_LIST(cursor);
		cursor->next = malloc(sizeof(struct var_list));
		cursor->next->name = id;
		cursor->next->is_const = const_flag;
		cursor->next->count = cursor->count + 1;
		cursor->next->next = NULL;
	}else{
		*var = malloc(sizeof(struct var_list));
		(*var)->name = id;
		(*var)->is_const = const_flag;
		(*var)->count = 0;
		(*var)->next = NULL;
	}
}

int populate_var(struct code_t *code, struct var_list **var){
	int count = 0;
	while(code != NULL){
		if(find_in_var(*var, code->var1, code->var1_const) == -1){ //new variable
			insert_to_var_list(var, code->var1, code->var1_const);	
			count++;
		}
		if(find_in_var(*var, code->var2, code->var2_const) == -1){ //new variable
			insert_to_var_list(var, code->var2, code->var2_const);
			count++;
		}
		if(find_in_var(*var, code->lvalue, 0) == -1){ //new variable
			insert_to_var_list(var, code->lvalue, 0);
			count++;
		}

		code = code->next;
	}
	return count;
}

int get_vt_lines(struct code_t *code){
	int count = 0;
	while(code != NULL){
		count++;
		code = code->next;
	}
	return count;
}

long find_in_var(struct var_list *var, long id, char const_flag){
	if(id == -1){
		return -2;
	}
	//iterate linked list
	while(var != NULL){
		if(var->name == id && var->is_const == const_flag)
			return var->count;
		var = var->next;
	}

	//default
	return -1;
}

long find_count_of_id_in_var(struct var_list *var, int count){
	if(count == -1){
		return -1;
	}
	//iterate linked list
	while(var != NULL){
		if(var->count == count)
			return var->name;
		var = var->next;
	}

	//default
	return -1;
}

struct var_list *find_count_of_id_in_var_ref(struct var_list *var, int count){
	if(count == -1){
		return NULL;
	}
	//iterate linked list
	while(var != NULL){
		if(var->count == count)
			return var;
		var = var->next;
	}

	//default
	return NULL;
}

long get_max(long x, long y){
	if(x > y)
		return x;
	else 
		return y;
}

void order(struct var_table *vt, long *order_table, int lines){
	//initialize array
	for(int i = 0; i < lines; i++){
		order_table[i] = -1;
	}

	int order_count = 0;
	//find
	for(int i = 0; i < lines; i++){
		if(vt[i].op == 14){
			order_table[order_count] = i;
			order_count++;
		}
	}
	for(int i = 0; i < lines; i++){
		if(vt[i].op == -1){
			order_table[order_count] = i;
			order_count++;
		}
	}
	for(int i = 0; i < lines; i++){
		for(int j = 0; j < lines; j++){
			if(get_max(vt[j].vn1, vt[j].vn2) == i && vt[j].op != -1 && vt[j].op != 14 && vt[j].op != 15){
				order_table[order_count] = j;
				order_count++;
			}
		}
	}
	for(int i = 0; i < lines; i++){
		if(vt[i].op == 15){
			order_table[order_count] = i;
			order_count++;
		}
	}
}


int value_number(struct bb_t *code_block, long *lvalue_count, struct var_table *code_block_vt){
	//Create stack structures to save memory
	lvalue_counter = lvalue_count;

	struct code_t *code = code_block->leader;
	code_block->exit->next = NULL;

	//iterate through bar_declaration to get to get all vars
	struct var_list *var = NULL;
	const int vars = populate_var(code, &var);
	{
		long vn[vars];
		long vn_backup[vars];
		initilize_vn(vn, vars);
		memcpy(vn_backup, vn, sizeof(long)*vars);

		//iterate the code-list to aquire the number of lvalues
		const int lines = get_vt_lines(code);
		{
			struct var_table vt[lines*3];			
			//initalize vt
			memset(vt, 0xFF, sizeof(struct var_table)*lines*3);
			for(int i = 0; i < vars; i++){
				vt[i].flag = 0;
			}

			//BEGIN
			//iterate code
			{
				struct code_t *cursor = code;
				long vn_count = vars;
				while(cursor != code_block->exit->next){
	
					long vn1, vn2, lvalue;
					char op;
					lvalue = find_in_var(var, cursor->lvalue, 0);
					vn1 = find_in_var(var, cursor->var1, cursor->var1_const);
					vn2 = find_in_var(var, cursor->var2, cursor->var2_const);
					op = cursor->op;
	
					// printf("%ld, %ld, %ld\n", lvalue, vn1, vn2);
	
					long old_vn1 = vn[vn1];
					long old_vn2 = vn[vn2];
	
					if(vt[vn[lvalue]].flag == 1){
						vn[lvalue] = vn_count;
						vt[vn[lvalue]].flag = 0;
						vn_count++;
					}
	
					vt[vn[lvalue]].op = op;
					if(old_vn1 > old_vn2){
						vt[vn[lvalue]].vn1 = old_vn2;
						vt[vn[lvalue]].vn2 = old_vn1;
					}else{
						vt[vn[lvalue]].vn1 = old_vn1;
						vt[vn[lvalue]].vn2 = old_vn2;
					}
	
					vt[old_vn1].flag = 1;
					vt[old_vn2].flag = 1;
	
					cursor = cursor->next;
				}
			}

			//print vt
			{
				puts("\nVAR");
				struct var_list *var_cursor = var;
				while(var_cursor != NULL){
					printf("Pos: %d--Name: %ld\n", var_cursor->count, var_cursor->name);
					var_cursor = var_cursor->next;
				}
				puts("VN");
				for(int i = 0; i < vars; i++){
					printf("Pos: %d--Num: %ld\n", i, vn[i]);
				}
				puts("VT");
				for(int i = 0; i < (lines*3); i++){
					printf("i: %d - OP: %d, VN1: %ld, VN2: %ld, FLAG: %d\n", i, vt[i].op, vt[i].vn1, vt[i].vn2, vt[i].flag);
				}
			}

			struct code_t *better_code = NULL;
			//better the code
			{
				//build basic chunk
				{

					{
						long order_table[lines*3];
						order(vt, order_table, lines*3);
						{
							// puts("Order");
							// for(int i = 0; i < lines*3; i++){
							// 	printf("%ld\n", order_table[i]);
							// }
						}

						struct code_t *cursor;
						for(int i = 0; i < (lines*3); i++){
							if(vt[order_table[i]].op != -1){
								int var_name = -1;
								for(int vn_iter = 0; vn_iter < vars; vn_iter++){
									if(vn[vn_iter] == order_table[i]){
										// printf("vn_iter::%d\n", vn_iter);
										var_name = find_count_of_id_in_var(var, vn_iter);
										break;
									}
								}
								//useless block
								if(var_name == -1 && vt[order_table[i]].flag == 0 && vt[order_table[i]].op != 15 && vt[order_table[i]].op != 14){
									continue;
								}
								cursor = new_code();

								//Y := X - X; -> Y := 0;
								if(vt[order_table[i]].op == 2){
									//find equivalence
									//only checks the top layers, not worth going lower
									if(vt[vt[order_table[i]].vn1].vn1 == vt[vt[order_table[i]].vn2].vn1 && 
										vt[vt[order_table[i]].vn1].vn2 == vt[vt[order_table[i]].vn2].vn2 && 
										vt[vt[order_table[i]].vn1].op == vt[vt[order_table[i]].vn2].op){
											cursor->lvalue = (long)order_table[i];
											cursor->var1 = 0;
											cursor->var1_const = 1;
											cursor->var2 = -1;
											cursor->var2_const = -1;
											cursor->op = 0;	
											cursor->next = NULL;
											add_to_code(&better_code, cursor);
											goto END_INTERATION;	
									}
								}

								if(vt[order_table[i]].op == 4){
									for(struct code_t *temp_cursor = better_code; temp_cursor != NULL; temp_cursor = temp_cursor->next){
										if(temp_cursor->lvalue == vt[order_table[i]].vn1 && temp_cursor->var1 == 0 && temp_cursor->var1_const == 1){
											cursor->lvalue = (long)order_table[i];
											cursor->var1 = 0;
											cursor->var1_const = 1;
											cursor->var2 = -1;
											cursor->var2_const = -1;
											cursor->op = 0;	
											cursor->next = NULL;
											add_to_code(&better_code, cursor);
											goto END_INTERATION;			
										}
									}	
									for(struct code_t *temp_cursor = better_code; temp_cursor != NULL; temp_cursor = temp_cursor->next){
										if(temp_cursor->lvalue == vt[order_table[i]].vn2 && temp_cursor->var1 == 0 && temp_cursor->var1_const == 1){
											cursor->lvalue = (long)order_table[i];
											cursor->var1 = 0;
											cursor->var1_const = 1;
											cursor->var2 = -1;
											cursor->var2_const = -1;
											cursor->op = 0;	
											cursor->next = NULL;
											add_to_code(&better_code, cursor);
											goto END_INTERATION;			
										}
									}	
								}

								//find previous equivalence
								for(int vt_iter = 0; vt_iter < i; vt_iter++){
									if(vt[vt_iter].vn1 == vt[order_table[i]].vn1 &&
										vt[vt_iter].vn2 == vt[order_table[i]].vn2 &&
										vt[vt_iter].op == vt[order_table[i]].op){
											//find in code block
											for(struct code_t *temp_cursor = better_code; temp_cursor != NULL; temp_cursor = temp_cursor->next){
												if(temp_cursor->lvalue == vt_iter){
													struct code_t *temp = temp_cursor->next;
													temp_cursor->next = cursor;
													cursor->lvalue = (long)order_table[i];
													cursor->var1 = vt_iter;
													cursor->var1_const = 0;
													cursor->var2 = -1;
													cursor->var2_const = -1;
													cursor->op = 0;	
													cursor->next = temp;
													GOTO_END_OF_LIST(cursor);
													goto END_INTERATION;		
												}
											}											
									}
								}

								cursor->lvalue = (long)order_table[i];
								cursor->var1 = vt[order_table[i]].vn1;
								cursor->var1_const = 0;
								cursor->var2 = vt[order_table[i]].vn2;
								cursor->var2_const = 0;
								cursor->op = vt[order_table[i]].op;
								cursor->next = NULL;
								add_to_code(&better_code, cursor);

								END_INTERATION:
								NULL;
							}
						}
					}
				}

				//rename
				{
					for(struct code_t *cursor = better_code; cursor != NULL; cursor = cursor->next){

						//lvalue
						int found;
						found = -1;
						for(int i = 0; i < vars; i++){
							if(vn[i] == cursor->lvalue){
								found = i;
								break;
							}
						}
						if(found == -1){
							for(int i = 0; i < vars; i++){
								if(vn_backup[i] == cursor->lvalue){
									found = i;
									break;
								}
							}
						}

						if(found == -1){
							cursor->lvalue = new_lvalue(lvalue_counter);
						}else{
							cursor->lvalue = find_count_of_id_in_var(var, found);
						}

						// var 1
						if(cursor->var1_const == 0){
							found = -1;
							for(int i = 0; i < vars; i++){
								if(vn[i] == cursor->var1){
									found = i;
									break;
								}
							}
							if(found == -1){
								for(int i = 0; i < vars; i++){
									if(vn_backup[i] == cursor->var1){
										found = i;
										break;
									}
								}
							}

							if(found == -1){
								cursor->var1 = new_lvalue(lvalue_counter);
							}else{
								struct var_list *temp = find_count_of_id_in_var_ref(var, found);
								cursor->var1 = temp->name;
								cursor->var1_const = temp->is_const;
							}
						}

						//var 2
						if(cursor->var2_const == 0){
							found = -1;
							for(int i = 0; i < vars; i++){
								if(vn[i] == cursor->var2){
									found = i;
									break;
								}
							}
							if(found == -1){
								for(int i = 0; i < vars; i++){
									if(vn_backup[i] == cursor->var2){
										found = i;
										break;
									}
								}
							}

							if(found == -1){
								cursor->var2 = new_lvalue(lvalue_counter);
							}else{
								struct var_list *temp = find_count_of_id_in_var_ref(var, found);
								cursor->var2 = temp->name;
								cursor->var2_const = temp->is_const;
							}
						}
					}
				}

				//final print
				{
					puts("Old Code (With numbers corresponding to names)");
					for(struct code_t *cursor = code_block->leader; cursor != NULL; cursor = cursor->next){
						printf("lvalue: %ld \tvar1: %ld \tvar1_const: %d \tvar2: %ld \tvar2_const: %d \top: %d\n", 
							cursor->lvalue, 
							cursor->var1, 
							cursor->var1_const,
							cursor->var2,
							cursor->var2_const,
							cursor->op);
					}
					puts("");

					puts("New Code (With numbers corresponding to names)");
					for(struct code_t *cursor = better_code; cursor != NULL; cursor = cursor->next){
						printf("lvalue: %ld \tvar1: %ld \tvar1_const: %d \tvar2: %ld \tvar2_const: %d \top: %d\n", 
							cursor->lvalue, 
							cursor->var1, 
							cursor->var1_const,
							cursor->var2,
							cursor->var2_const,
							cursor->op);
					}
					puts("-------------------\n");

				}
			}

			//return
			struct code_t *end_of_better_code = better_code;
			GOTO_END_OF_LIST(end_of_better_code);

			//give new code_blocks
			code_block->leader = better_code;
			code_block->exit = end_of_better_code;

			//give vt
			code_block->vt = malloc(sizeof(vt));
			memcpy(code_block->vt, vt, sizeof(vt));

		}
	}
	return 0;
}