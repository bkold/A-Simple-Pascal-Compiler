/*
 * rulefuncs.c
 *
 * Implements all functions that assist in developing the yacc rules
 */

#include "rulefuncs.h"

/* -----------------------------------------------------------------------
 * Returns a pointer to a new identifier_list
 * -----------------------------------------------------------------------
 */
struct identifier_list_t *new_identifier_list()
{
	struct identifier_list_t *il;

	il = (struct identifier_list_t *) malloc(sizeof(struct identifier_list_t));
	CHECK_MEM_ERROR(il)
	il->id = NULL;
	il->next = NULL;

	return il;
}



/* -----------------------------------------------------------------------
 * Adds an identifier to the end of the identifier_list
 * -----------------------------------------------------------------------
 */
void add_to_identifier_list(struct identifier_list_t **il, char *id)
{
	if (*il == NULL) {
	*il = new_identifier_list();
	(*il)->id = id;
	}
	else {
	struct identifier_list_t *temp;

	temp = *il;

	GOTO_END_OF_LIST(temp)
	temp->next = new_identifier_list();
	temp->next->id = id;
	}
}



/* -----------------------------------------------------------------------
 * Returns the number of identifiers in an identifier list
 * -----------------------------------------------------------------------
 */
long identifier_list_count(struct identifier_list_t *il)
{
	struct identifier_list_t *temp_il;
	long count = 0;

	temp_il = il;
	while (temp_il != NULL){
	count++;
	temp_il = temp_il->next;
	}

	return count;
}


/* -----------------------------------------------------------------------
 * Returns a pointer to a new identifier
 * -----------------------------------------------------------------------
 */
char *new_identifier(char *text)
{
 char *id;

 id = (char *) malloc(strlen(text) + 1); /* +1 for '\0' */
 CHECK_MEM_ERROR(id)
 strcpy(id, text);

 return id;
}



/* -----------------------------------------------------------------------
 * Adds a class_identification and block to the end of the class_list
 * -----------------------------------------------------------------------
 */
void add_to_class_list(struct class_list_t **cl, struct class_identification_t *ci, struct class_block_t *cb)
{
	if (*cl == NULL) {
	*cl = new_class_list();
	(*cl)->ci = ci;
	(*cl)->cb = cb;
	(*cl)->parent = NULL;
	}
	else {
	struct class_list_t *temp;

	temp = *cl;

	GOTO_END_OF_LIST(temp)
	temp->next = new_class_list();
	temp->next->ci = ci;
	temp->next->cb = cb;
	temp->next->parent = NULL;

	}
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new identifier
 * -----------------------------------------------------------------------
 */
struct class_list_t *new_class_list()
{
	struct class_list_t *cl;

	cl = (struct class_list_t *) malloc(sizeof(struct class_list_t));
	CHECK_MEM_ERROR(cl)
	cl->ci = NULL;
	cl->cb = NULL;
	cl->next = NULL;

	return cl;
}


/* -----------------------------------------------------------------------
 * Returns a pointer to a new class_identification
 * -----------------------------------------------------------------------
 */
struct class_identification_t *new_class_identification()
{
	struct class_identification_t *ci;

	ci = (struct class_identification_t*) malloc(sizeof(struct class_identification_t));
	CHECK_MEM_ERROR(ci)
	ci->id = NULL;
	ci->extend = NULL;

	return ci;
}

/* -----------------------------------------------------------------------
 * Returns a pointer to a new actual_parameter_list
 * -----------------------------------------------------------------------
 */
struct actual_parameter_list_t *new_actual_parameter_list()
{
	struct actual_parameter_list_t *apl;

	apl = (struct actual_parameter_list_t *)
	malloc(sizeof(struct actual_parameter_list_t));
	CHECK_MEM_ERROR(apl)
	apl->ap = NULL;
	apl->next = NULL;

	return apl;
}


/* -----------------------------------------------------------------------
 * Adds an actual_parameter to the end of the actual_parameter_list
 * -----------------------------------------------------------------------
 */
void add_to_actual_parameter_list(struct actual_parameter_list_t **apl,
								struct actual_parameter_t *ap)
{
	if (*apl == NULL) {
	*apl = new_actual_parameter_list();
	(*apl)->ap = ap;
	}
	else {
	struct actual_parameter_list_t *temp;

	temp = *apl;

	GOTO_END_OF_LIST(temp)
	temp->next = new_actual_parameter_list();
	temp->next->ap = ap;
	}
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new type_denoter
 * -----------------------------------------------------------------------
 */
struct type_denoter_t *new_type_denoter()
{
	struct type_denoter_t *td;

	td = (struct type_denoter_t *)
	malloc(sizeof(struct type_denoter_t));
	CHECK_MEM_ERROR(td)
	td->type = -1;
	td->name = NULL;

	return td;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new variable_declaration_list
 * -----------------------------------------------------------------------
 */
struct variable_declaration_list_t *new_variable_declaration_list()
{
	struct variable_declaration_list_t *vdl;

	vdl = (struct variable_declaration_list_t *)
	malloc(sizeof(struct variable_declaration_list_t));
	CHECK_MEM_ERROR(vdl)
	vdl->vd = NULL;
	vdl->next = NULL;

	return vdl;
}



/* -----------------------------------------------------------------------
 * Adds a variable_declaration to the end of the variable_declaration_list
 * -----------------------------------------------------------------------
 */
void add_to_variable_declaration_list(struct variable_declaration_list_t **vdl,
					struct variable_declaration_t *vd)
{
 if (*vdl == NULL) {
	*vdl = new_variable_declaration_list();
	(*vdl)->vd = vd;
	}
	else {
	struct variable_declaration_list_t *temp;

	temp = *vdl;

	GOTO_END_OF_LIST(temp)

	temp->next = new_variable_declaration_list();
	temp->next->vd = vd;
	}
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new range_t
 * -----------------------------------------------------------------------
 */
struct range_t *new_range()
{
	struct range_t *r;

	r = (struct range_t *) malloc(sizeof(struct range_t));
	CHECK_MEM_ERROR(r)
	r->min = NULL;
	r->max = NULL;

	return r;
}


/* -----------------------------------------------------------------------
 * Returns a pointer to a new function_designator_t
 * -----------------------------------------------------------------------
 */
struct function_designator_t *new_function_designator()
{
	struct function_designator_t *fd;

	fd = (struct function_designator_t *) malloc(sizeof(struct function_designator_t));
	CHECK_MEM_ERROR(fd)
	fd->id = NULL;
	fd->apl = NULL;

	return fd;
}


/* -----------------------------------------------------------------------
 * Returns a pointer to a new formal_parameter_section_list
 * -----------------------------------------------------------------------
 */
struct formal_parameter_section_list_t *new_formal_parameter_section_list()
{
	struct formal_parameter_section_list_t *fpsl;

	fpsl = (struct formal_parameter_section_list_t *)
	malloc(sizeof(struct formal_parameter_section_list_t));
	CHECK_MEM_ERROR(fpsl)
	fpsl->fps = NULL;
	fpsl->next = NULL;

	return fpsl;
}



/* -----------------------------------------------------------------------
 * Adds a formal_parameter_section to the end of the formal_parameter_section_list
 * -----------------------------------------------------------------------
 */
void add_to_formal_parameter_section_list(struct formal_parameter_section_list_t **fpsl,
					struct formal_parameter_section_t *fps)
{
 if (*fpsl == NULL) {
	*fpsl = new_formal_parameter_section_list();
	(*fpsl)->fps = fps;
	}
	else {
	struct formal_parameter_section_list_t *temp;

	temp = *fpsl;

	GOTO_END_OF_LIST(temp)

	temp->next = new_formal_parameter_section_list();
	temp->next->fps = fps;
	}
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new variable_access
 * -----------------------------------------------------------------------
 */
struct variable_access_t *new_variable_access()
{
	struct variable_access_t *va;

	va = (struct variable_access_t *)
	malloc(sizeof(struct variable_access_t));
	CHECK_MEM_ERROR(va)
	va->type = -1;
	va->recordname = NULL;

	return va;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new object_instantiation
 * -----------------------------------------------------------------------
 */
struct object_instantiation_t *new_object_instantiation()
{
	struct object_instantiation_t *os;

	os = (struct object_instantiation_t *)
	malloc(sizeof(struct object_instantiation_t));
	CHECK_MEM_ERROR(os)
	os->id = NULL;
	os->apl = NULL;

	return os;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new assignment_statement
 * -----------------------------------------------------------------------
 */
struct assignment_statement_t *new_assignment_statement()
{
	struct assignment_statement_t *as;

	as = (struct assignment_statement_t *)
	malloc(sizeof(struct assignment_statement_t));
	CHECK_MEM_ERROR(as)
	as->va = NULL;
	as->e = NULL;

	return as;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new print_statement
 * -----------------------------------------------------------------------
 */
struct print_statement_t *new_print_statement()
{
	struct print_statement_t *ps;

	ps = (struct print_statement_t *) malloc(sizeof(struct print_statement_t));
	CHECK_MEM_ERROR(ps)
	ps->va = NULL;

	return ps;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new expression
 * -----------------------------------------------------------------------
 */
struct expression_t *new_expression()
{
	struct expression_t *e;

	e = (struct expression_t *) malloc(sizeof(struct expression_t));
	CHECK_MEM_ERROR(e)
	e->se1 = NULL;
	e->relop = -1;
	e->se2 = NULL;

	return e;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new statement
 * -----------------------------------------------------------------------
 */
struct statement_t *new_statement()
{
	struct statement_t *s;

	s = (struct statement_t*) malloc(sizeof(struct statement_t));
	CHECK_MEM_ERROR(s)
	s->type = -1;
	s->line_number = -1;

	return s;
}


/* -----------------------------------------------------------------------
 * Returns a pointer to a new statement_sequence
 * -----------------------------------------------------------------------
 */

struct statement_sequence_t *new_statement_sequence()
{
	struct statement_sequence_t *ss;

	ss = (struct statement_sequence_t *)
	malloc(sizeof(struct statement_sequence_t));
	CHECK_MEM_ERROR(ss)
	ss->s = NULL;
	ss->next = NULL;

	return ss;
}



/* -----------------------------------------------------------------------
 * Adds a statement to the end of the statement_sequence
 * -----------------------------------------------------------------------
 */
void add_to_statement_sequence(struct statement_sequence_t **ss,
					struct statement_t *s)
{
 if (*ss == NULL) {
	*ss = new_statement_sequence();
	(*ss)->s = s;
	}
	else {
	struct statement_sequence_t *temp;

	temp = *ss;

	GOTO_END_OF_LIST(temp)

	temp->next = new_statement_sequence();
	temp->next->s = s;
	}
}


struct function_block_t *new_function_block()
{
	struct function_block_t *fb;

	fb = (struct function_block_t *) malloc(sizeof(struct function_block_t));
	CHECK_MEM_ERROR(fb)
	fb->vdl = NULL;
	fb->ss = NULL;

	return fb;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new if_statement
 * -----------------------------------------------------------------------
 */
struct if_statement_t *new_if_statement()
{
	struct if_statement_t *is;

	is = (struct if_statement_t *) malloc(sizeof(struct if_statement_t));
	CHECK_MEM_ERROR(is)
	is->e = NULL;
	is->s1 = NULL;
	is->s2 = NULL;

	return is;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new while_statement
 * -----------------------------------------------------------------------
 */
struct while_statement_t *new_while_statement()
{
	struct while_statement_t *ws;

	ws = (struct while_statement_t *) malloc(sizeof(struct while_statement_t));
	CHECK_MEM_ERROR(ws)
	ws->e = NULL;
	ws->s = NULL;

	return ws;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new indexed_variable
 * -----------------------------------------------------------------------
 */
struct indexed_variable_t *new_indexed_variable()
{
	struct indexed_variable_t *iv;

	iv = (struct indexed_variable_t *) malloc(sizeof(struct indexed_variable_t));
	CHECK_MEM_ERROR(iv)
	iv->va = NULL;
	iv->iel = NULL;

	return iv;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new attribute_designator
 * -----------------------------------------------------------------------
 */
struct attribute_designator_t *new_attribute_designator()
{
	struct attribute_designator_t *fd;

	fd = (struct attribute_designator_t *) malloc(sizeof(struct attribute_designator_t));
	CHECK_MEM_ERROR(fd)
	fd->va = NULL;
	fd->id = NULL;

	return fd;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new method_designator
 * -----------------------------------------------------------------------
 */
struct method_designator_t *new_method_designator()
{
	struct method_designator_t *md;

	md = (struct method_designator_t *) malloc(sizeof(struct method_designator_t));
	CHECK_MEM_ERROR(md)
	md->va = NULL;
	md->fd = NULL;

	return md;
}


/* -----------------------------------------------------------------------
 * Returns a pointer to a new index_expression_list
 * -----------------------------------------------------------------------
 */
struct index_expression_list_t *new_index_expression_list()
{
	struct index_expression_list_t *iel;

	iel = (struct index_expression_list_t *)
	malloc(sizeof(struct index_expression_list_t));
	CHECK_MEM_ERROR(iel)
	iel->e = NULL;
	iel->next = NULL;

	return iel;
}



/* -----------------------------------------------------------------------
 * Adds a index_expression to the end of the index_expression_list
 * -----------------------------------------------------------------------
 */
void add_to_index_expression_list(struct index_expression_list_t **iel,
				struct expression_t *e)
{
 if (*iel == NULL) {
	*iel = new_index_expression_list();
	(*iel)->e = e;
	}
	else {
	struct index_expression_list_t *temp;

	temp = *iel;

	GOTO_END_OF_LIST(temp)

	temp->next = new_index_expression_list();
	temp->next->e = e;
	}
}


/* -----------------------------------------------------------------------
 * Returns the number of index_expression_list items that are nested
 * (pointing to each other)
 * -----------------------------------------------------------------------
 */
long index_expression_list_count(struct index_expression_list_t *iel)
{
	struct index_expression_list_t *temp_iel;
	long count = 0;

	temp_iel = iel;
	while (temp_iel != NULL){
	count++;
	temp_iel = temp_iel->next;
	}

	return count;

}

/* -----------------------------------------------------------------------
 * Returns a pointer to a new actual_parameter
 * -----------------------------------------------------------------------
 */
struct actual_parameter_t *new_actual_parameter()
{
	struct actual_parameter_t *ap;

	ap = (struct actual_parameter_t *) malloc(sizeof(struct actual_parameter_t));
	CHECK_MEM_ERROR(ap)
	ap->e1 = NULL;
	ap->e2 = NULL;
	ap->e3 = NULL;

	return ap;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new simple_expression
 * -----------------------------------------------------------------------
 */
struct simple_expression_t *new_simple_expression()
{
	struct simple_expression_t *se;

	se = (struct simple_expression_t *)
	malloc(sizeof(struct simple_expression_t));
	CHECK_MEM_ERROR(se)
	se->t = NULL;
	se->addop = -1;
	se->next = NULL;

	return se;
}



/* -----------------------------------------------------------------------
 * Adds a term to the end of the simple_expression
 * -----------------------------------------------------------------------
 */
void add_to_simple_expression(struct simple_expression_t **se,
				int addop,
				struct term_t *t)
{
 if (*se == NULL) {
	*se = new_simple_expression();
	(*se)->t = t;
	}
	else {
	struct simple_expression_t *temp;

	temp = *se;

	GOTO_END_OF_LIST(temp)

	temp->next = new_simple_expression();
	temp->next->t = t;
	temp->addop = addop;
	}
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new term
 * -----------------------------------------------------------------------
 */
struct term_t *new_term()
{
	struct term_t *t;

	t = (struct term_t *)
	malloc(sizeof(struct term_t));
	CHECK_MEM_ERROR(t)
	t->f = NULL;
	t->mulop = -1;
	t->next = NULL;

	return t;
}



/* -----------------------------------------------------------------------
 * Adds a factor to the end of the term
 * -----------------------------------------------------------------------
 */
void add_to_term(struct term_t **t, int mulop, struct factor_t *f)
{
 if (*t == NULL) {
	*t = new_term();
	(*t)->f = f;
	}
	else {
	struct term_t *temp;

	temp = *t;

	GOTO_END_OF_LIST(temp)

	temp->next = new_term();
	temp->next->f = f;
	temp->mulop = mulop;
	}
}



/* -----------------------------------------------------------------------
 * Returns a pointer to the new factor
 * -----------------------------------------------------------------------
 */
struct factor_t *new_factor()
{
	struct factor_t *f;

	f = (struct factor_t *)
	malloc(sizeof(struct factor_t));
	CHECK_MEM_ERROR(f)
	f->type = -1;

	return f;
}

/* -----------------------------------------------------------------------
 * Returns a pointer to a new sign
 * -----------------------------------------------------------------------
 */
int *new_sign()
{
 int *s;

 s = (int *) malloc(sizeof(int));
 CHECK_MEM_ERROR(s)

 return s;
}


/* -----------------------------------------------------------------------
 * Returns a pointer to the new primary
 * -----------------------------------------------------------------------
 */
struct primary_t *new_primary()
{
 struct primary_t *p;

 p = (struct primary_t *) malloc(sizeof(struct primary_t));
 CHECK_MEM_ERROR(p)
 p->type = -1;

 return p;
}

//Very new
/* -----------------------------------------------------------------------
 * Adds data to a primary
 * -----------------------------------------------------------------------
 */
void add_to_primary_data(struct primary_t **t, int data, struct primary_t *p)
{
 //need to implement this
 //add the data to the primary
}


/* -----------------------------------------------------------------------
 * Returns a pointer to a new unsigned_number
 * -----------------------------------------------------------------------
 */
struct unsigned_number_t *new_unsigned_number()
{
 struct unsigned_number_t *un;

 un = (struct unsigned_number_t *) malloc(sizeof(struct unsigned_number_t));
 CHECK_MEM_ERROR(un)

 return un;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new array_type
 * -----------------------------------------------------------------------
 */
struct array_type_t *new_array_type()
{
 struct array_type_t *at;

 at = (struct array_type_t *) malloc(sizeof(struct array_type_t));
 CHECK_MEM_ERROR(at)

 return at;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new class_block
 * -----------------------------------------------------------------------
 */
struct class_block_t *new_class_block()
{
 struct class_block_t *cb;

 cb = (struct class_block_t *) malloc(sizeof(struct class_block_t));
 CHECK_MEM_ERROR(cb)
 cb->vdl = NULL;
 cb->fdl = NULL;

 return cb;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new primitive_type
 * -----------------------------------------------------------------------
 */
char *new_primitive_type(char *type)
{
	char *t;
	t = (char *) malloc(strlen(type) + 1); /* +1 for '\0' */
	CHECK_MEM_ERROR(t)
	strcpy(t, type);

	return t;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new func_declaration_list
 * -----------------------------------------------------------------------
 */
struct func_declaration_list_t *new_func_declaration_list()
{
	struct func_declaration_list_t *fdl;

	fdl = (struct func_declaration_list_t *)
	malloc(sizeof(struct func_declaration_list_t));
	CHECK_MEM_ERROR(fdl)
	fdl->fd = NULL;
	fdl->next = NULL;

	return fdl;
}



/* -----------------------------------------------------------------------
 * Adds a function_declaration to the end of the func_declaration_list
 * -----------------------------------------------------------------------
 */
void add_to_func_declaration_list(struct func_declaration_list_t **fdl,
				struct function_declaration_t *fd)
{
 if (*fdl == NULL) {
	*fdl = new_func_declaration_list();
	(*fdl)->fd = fd;
	}
	else {
	struct func_declaration_list_t *temp;

	temp = *fdl;

	GOTO_END_OF_LIST(temp)

	temp->next = new_func_declaration_list();
	temp->next->fd = fd;
	}
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new function_declaration
 * -----------------------------------------------------------------------
 */
struct function_declaration_t *new_function_declaration()
{
 struct function_declaration_t *fd;

 fd = (struct function_declaration_t *)
	malloc(sizeof(struct function_declaration_t));
 CHECK_MEM_ERROR(fd)
 fd->fh = NULL;
 fd->fb = NULL;
 fd->line_number = -1;

 return fd;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new function_heading
 * -----------------------------------------------------------------------
 */
struct function_heading_t *new_function_heading()
{
 struct function_heading_t *fh;

 fh = (struct function_heading_t *)
	malloc(sizeof(struct function_heading_t));
 CHECK_MEM_ERROR(fh)
 fh->id = NULL;
 fh->res = NULL;
 fh->fpsl = NULL;

 return fh;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new variable_declaration
 * -----------------------------------------------------------------------
 */
struct variable_declaration_t *new_variable_declaration()
{
 struct variable_declaration_t *vd;

 vd = (struct variable_declaration_t *)
	malloc(sizeof(struct variable_declaration_t));
 CHECK_MEM_ERROR(vd)
 vd->il = NULL;
 vd->tden = NULL;
 vd->line_number = -1;

 return vd;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new formal_parameter_section
 * -----------------------------------------------------------------------
 */
struct formal_parameter_section_t *new_formal_parameter_section()
{
 struct formal_parameter_section_t *fps;

 fps = (struct formal_parameter_section_t *)
	malloc(sizeof(struct formal_parameter_section_t));
 CHECK_MEM_ERROR(fps)
 fps->il = NULL;
 fps->id = NULL;
 fps->is_var = -1;

 return fps;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new program
 * -----------------------------------------------------------------------
 */
struct program_t *new_program()
{
 struct program_t *p;

 p = (struct program_t *) malloc(sizeof(struct program_t));
 CHECK_MEM_ERROR(p)
 p->ph = NULL;
 p->cl = NULL;

 return p;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new program_heading
 * -----------------------------------------------------------------------
 */
struct program_heading_t *new_program_heading()
{
 struct program_heading_t *ph;

 ph = (struct program_heading_t *) malloc(sizeof(struct program_heading_t));
 CHECK_MEM_ERROR(ph)
 ph->id = NULL;
 ph->il = NULL;

 return ph;
}



/* -----------------------------------------------------------------------
 * Returns a pointer to a new expression_data
 * -----------------------------------------------------------------------
 */
struct expression_data_t *new_expression_data()
{
 struct expression_data_t *ed;

 ed = (struct expression_data_t *) malloc(sizeof(struct expression_data_t));
 CHECK_MEM_ERROR(ed)
 ed->val = -1;
 ed->type = NULL;

 return ed;
}

/* -----------------------------------------------------------------------
 * Returns a pointer to a the parent of a class_list
 * -----------------------------------------------------------------------
 */
struct class_list_t *locate_parent(struct class_list_t **cl, char *name)
{
	struct class_list_t *temp = *cl;

	while(temp != NULL){
	if(strcmp(temp->ci->id, name) == 0){
		return temp;
	}
	temp = temp->next;
	}
	return NULL;
}

/* -----------------------------------------------------------------------
 * Returns 1 if *id is primative and 0 if not
 * -----------------------------------------------------------------------
 */
int builtin_type(char *id){

	if(
	strcmp(id, PRIMITIVE_TYPE_NAME_INTEGER) == 0 ||
	strcmp(id, PRIMITIVE_TYPE_NAME_BOOLEAN) == 0 ||
	strcmp(id, PRIMITIVE_TYPE_NAME_POINTER) == 0 ||
	strcmp(id, PRIMITIVE_TYPE_NAME_UNKNOWN) == 0)
	{
	return 1;
	}
	return 0;

}


/* -----------------------------------------------------------------------
 * returns class_list if class node is found based on name
 * -----------------------------------------------------------------------
 */
struct class_list_t *lookup_in_class_list(struct class_list_t **list, char *name){
	struct class_list_t *temp = *list;

	while(temp != NULL){
		if(strcmp(temp->ci->id, name) == 0){
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

/* -----------------------------------------------------------------------
 * returns 1 if a variable is declared, 0 if o.w.
 * -----------------------------------------------------------------------
 */
struct variable_declaration_t *find_variable_in_class(struct class_list_t *current_scope, char *id, int line_number, int mode){
	while(current_scope != NULL){ //loop through the class linked_list
		struct variable_declaration_list_t *temp_vdl = current_scope->cb->vdl;
		while(temp_vdl != NULL){ //loop through the vdl linked_list
			struct identifier_list_t *temp_il = temp_vdl->vd->il;
			while(temp_il != NULL){ //loop through the vd linked_list, comparing temp_il's id to the test id
				if(strcmp(temp_il->id, id) == 0){
					if(mode == 1){
					error_variable_already_declared(line_number, id, temp_vdl->vd->line_number);
					}
					return temp_vdl->vd;
				}
				temp_il = temp_il->next;
			}
			temp_vdl = temp_vdl->next;
		}
		current_scope = current_scope->parent;
	}
	return NULL;
}

/* -----------------------------------------------------------------------
 * returns 1 if a variable is declared, 0 if o.w.
 * -----------------------------------------------------------------------
 */
struct variable_declaration_t *find_variable_in_vdl(struct variable_declaration_list_t *current_list, char *id, int line_number, int mode){
	while(current_list != NULL){ //loop through the vdl linked_list
	struct identifier_list_t *temp_il = current_list->vd->il;
	while(temp_il != NULL){ //loop through the vd linked_list, comparing temp_il's id to the test id
	if(temp_il->id != NULL){
	if(strcmp(temp_il->id, id) == 0){
			if(mode == 1){
			error_variable_already_declared(line_number, id, current_list->vd->line_number);
			}
			return current_list->vd;
	}
	}
	temp_il = temp_il->next;
	}
	current_list = current_list->next;
	}
	return 0;
}

/* -----------------------------------------------------------------------
 * returns the location offset of a variable
 * -----------------------------------------------------------------------
 */
unsigned int get_offset_from_il(struct identifier_list_t *il, char *id){ 
	while(il != NULL){ //loop through the vdl linked_list
		if(strcmp(il->id, id) == 0){
			return il->location;
		}
		il = il->next;
	}
	return 0;
}

/* -----------------------------------------------------------------------
 * returns the index of a variable in the vdl
 * -----------------------------------------------------------------------
 */
long get_variable_index(struct variable_declaration_list_t *current_list, char *id){
	long index = 0;
	while(current_list != NULL){ //loop through the vdl linked_list
	struct identifier_list_t *temp_il = current_list->vd->il;
	while(temp_il != NULL){ //loop through the vd linked_list, comparing temp_il's id to the test id
		if(temp_il->id != NULL){
			if(strcmp(temp_il->id, id) == 0){
				return index;
			}
			if(index != LONG_MAX){
				index++;
			}else{
				puts("TOO MANY VARIABLES");
				exit(-1);
			}
		}
		temp_il = temp_il->next;
	}
	current_list = current_list->next;
	}
	return -1;
}
/* -----------------------------------------------------------------------
 * throws error if finds duplicate variable declaration
 * -----------------------------------------------------------------------
 */
void check_variable_declaration_id_list(struct identifier_list_t *il, int line_number){
	struct identifier_list_t *iter_1 = il;
	while(iter_1 != NULL){
	struct identifier_list_t *iter_2 = iter_1->next;
	while(iter_2 != NULL){
		if(strcmp(iter_1->id, iter_2->id) == 0){
			error_variable_already_declared(line_number, iter_1->id, line_number);
		}
		iter_2 = iter_2->next;
	}
	iter_1 = iter_1->next;
	}
}

//added after My commit messed things up
/* -----------------------------------------------------------------------
 * throws error if function declared
 * -----------------------------------------------------------------------
 */
int find_function_in_fdl(struct func_declaration_list_t *list, char *id, int line_number, int mode){
	while(list != NULL){
	if(strcmp(list->fd->fh->id, id) == 0){
		if(mode == 1)
			error_function_already_declared(line_number, list->fd->fh->id, list->fd->line_number);
		return 1;
	}
	list = list->next;
	}
	return 0;
}

int is_keyword(struct identifier_list_t *il, int line_number){
	struct identifier_list_t *iter_1 = il;
	while(iter_1 != NULL){
	if(builtin_type(iter_1->id) || strcmp(iter_1->id, BOOLEAN_VALUE_TRUE) == 0 || strcmp(iter_1->id, BOOLEAN_VALUE_FALSE) == 0){
		error_variable_name_invalid(line_number, iter_1->id);
	}
	iter_1 = iter_1->next;
	}

	return 0;
}

/* -----------------------------------------------------------------------
 * Allocates a new code_t struct
 * -----------------------------------------------------------------------
 */
struct code_t *new_code(){
	struct code_t *code_block;

	code_block = (struct code_t *) malloc(sizeof(struct code_t));
	CHECK_MEM_ERROR(code_block)
	code_block->var1 = 0;
	code_block->var1_const = 0;
	code_block->var2 = 0;
	code_block->var2_const = 0;
	code_block->op = UNKNOWN_OP;
	code_block->target = NULL;
	code_block->next = NULL;
	code_block->lvalue = 0;

	return code_block;
}


/* -----------------------------------------------------------------------
 * appends an allocated code_t to arg1 code_t
 * -----------------------------------------------------------------------
 */
void add_to_code(struct code_t **cl, struct code_t *ci){
	if (*cl == NULL) {
	*cl = ci;
	}
	else {
	struct code_t *temp = *cl;

	GOTO_END_OF_LIST(temp)
	temp->next = ci;
	}
}

long new_lvalue(long *lvalue_count){
	*lvalue_count = *lvalue_count - 1;
	return *lvalue_count;
}

/* -----------------------------------------------------------------------
 * Allocates a new code_t struct for labels
 * -----------------------------------------------------------------------
 */
struct code_t *new_label(){
	struct code_t *code_block;

	code_block = (struct code_t *) malloc(sizeof(struct code_t));
	CHECK_MEM_ERROR(code_block);
	code_block->var1 = 0;
	code_block->var1_const = 0;
	code_block->var2 = 0;
	code_block->var2_const = 0;
	code_block->op = LABEL_OP; //op code for labels, jumps will be 15
	code_block->next = NULL;
	code_block->target = NULL;
	code_block->lvalue = 0;

	return code_block;
}

//NEW STUFF FOR BASIC BLOCKS
/* -----------------------------------------------------------------------
 * Allocates a new bb_t struct for basic blocks
 * -----------------------------------------------------------------------
 */
struct bb_t *new_bb(){
	struct bb_t *basic_block;

	basic_block = (struct bb_t *) malloc(sizeof(struct bb_t));
	CHECK_MEM_ERROR(basic_block);
	basic_block->leader = NULL;//* to first TAC in block
	basic_block->exit = NULL;//* to last TAC in block
	basic_block->next = NULL;//* to next basic block
	basic_block->vt = NULL;//* to next basic block
	basic_block->child = NULL;//* to head of child cfg list
	basic_block->parent = NULL;//* to head of parent cfg list

	return basic_block;
}
/* -----------------------------------------------------------------------
 * Allocates a new cfg_t struct for basic block connection
 * -----------------------------------------------------------------------
 */
struct cfg_t *new_cfg_t(){
	struct cfg_t *cfg_node;

	cfg_node = (struct cfg_t *) malloc(sizeof(struct cfg_t));
	CHECK_MEM_ERROR(cfg_node);

	cfg_node->link_to_bb = NULL;//* to bb member of list
	cfg_node->next = NULL;//* to the next cfg in the member list

	return cfg_node;
}

/* -----------------------------------------------------------------------
 * Adds an Edge between two provided basic blocks
 * -----------------------------------------------------------------------
 */
void add_edge(struct bb_t *parent, struct bb_t *child){
	struct cfg_t *cfg_iter = new_cfg_t();//cfg iter

	if(parent->child == NULL){
	struct cfg_t *added_cfg = new_cfg_t();//make a new cfg
	parent->child = added_cfg;//add cfg node as head of child list
	added_cfg->link_to_bb = child; //link the cfg node to correct bb
	//printf("child (line # %d) added to parent (line # %d)\n", added_cfg->link_to_bb->leader->tac_line, parent->leader->tac_line);
	}else{
	struct cfg_t *added_cfg = new_cfg_t();//make a new cfg
	parent->child->next = added_cfg;//add cfg node as next of head of child list
	added_cfg->link_to_bb = child; //link the cfg node to correct bb
	//printf("child (line # %d) added to parent (line # %d)\n", added_cfg->link_to_bb->leader->tac_line, parent->leader->tac_line);
	}

	if(child->parent == NULL){
	struct cfg_t *added_cfg = new_cfg_t();//make a new cfg
	child->parent = added_cfg;//add cfg node as head of parent list
	added_cfg->link_to_bb = parent; //link the cfg node to correct bb
	//printf("parent (line # %d) added to child (line # %d)\n", added_cfg->link_to_bb->leader->tac_line, child->leader->tac_line);
	}else{
	struct cfg_t *added_cfg = new_cfg_t();//make a new cfg
	cfg_iter = child->parent;//first element in parent list
	while(cfg_iter->next != NULL){//loop to the last element of list
		cfg_iter = cfg_iter->next;
	}
	//child->parent->next = added_cfg;
	cfg_iter->next = added_cfg;//add to the last element of the list
	added_cfg->link_to_bb = parent;
	//printf("2parent (line # %d) added to child (line # %d)\n", added_cfg->link_to_bb->leader->tac_line, child->leader->tac_line);
	}
	//puts("....END OF WHILE....");
}

/* -----------------------------------------------------------------------
* Finds Leaders for Basic Blocks
* -----------------------------------------------------------------------
*/
void find_leaders(struct code_t *first_code_block, struct bb_t *bb_head){
	//struct bb_t *bb_head = new_bb();         //bb head
	struct bb_t *bb_iter = new_bb();         //bb iter
	//struct bb_t *bb_iter2 = new_bb();        //bb iter2 for linking BBs together
	struct code_t *code_iter = first_code_block;     //used to iterate through TAC blocks
	bb_head->leader = code_iter;             //leader of BB0, first instruction
	//puts("....First Leader added....");
	{
	bb_iter = bb_head;                      //iter is head at first
	code_iter = code_iter->next;            //start loop on second instruction

	while(code_iter != NULL){               //While there are still code blocks
		//leader = code after jump statement
		if(code_iter->op == JUMP_OP){              //if code is a jump
		//puts("....IN THE IF....");
			struct bb_t *added_bb = new_bb();   //create new bb to add to list

			added_bb->leader = code_iter->next; //add code after jump statement to new bb
			//puts("....ADDED LEADER1....");

			bb_iter->next = added_bb;           //link basic blocks
			bb_iter = bb_iter->next;            //move to next basic block

			code_iter = code_iter->next->next;  //Skips the next instruction that we already know is a leader
		}else{
		//puts("....IN THE ELSE....");
			if(code_iter->op == LABEL_OP){         //find labels//leader = target of jump statement, or just label
					struct bb_t *added_bb = new_bb();   //create new bb to add to list

					added_bb->leader = code_iter;       //add label code as leader to new block
					//puts("....ADDED LEADER2....");

					bb_iter->next = added_bb;           //link leader basic blocks
					bb_iter = bb_iter->next;            //iterate to next basic block
					}
					code_iter = code_iter->next;          //iterate code_iter in the else
			}
	}
	}
}
/* -----------------------------------------------------------------------
* count for finding the exits
* -----------------------------------------------------------------------
*/
void count_code_blocks(struct code_t *first_code_block){
	{
	int count = 1;
	//struct bb_t *bb_iter = new_bb();         //bb iter
	//bb_iter = bb_list_Head;                      //bb_iter is bb_head at first
	struct code_t *count_iter = first_code_block;      //used to iterate through TAC blocks

	//puts("....BEFORE COUNTING....");
	//loop through TAC code to number each line
		while(count_iter != NULL){
			count_iter->tac_line = count;
			//printf("tac line number: %d\n", count_iter->tac_line);//testing that the values are being read in
			count_iter = count_iter->next; //iterate count_iter
			count++;                       //iterate count
		}
	//puts("....COUNTING FINISHED....");
	}
}
/* -----------------------------------------------------------------------
* Finds Exits for Basic Blocks
* -----------------------------------------------------------------------
*/
void find_exits(struct code_t *first_code_block, struct bb_t *bb_head){
	{
	struct bb_t *bb_iter = new_bb();
	struct code_t *code_iter = new_code();
	bb_iter = bb_head;                      //bb_iter is bb_head at first
	code_iter = first_code_block;                  //used to iterate through TAC blocks

	//puts("....BEFORE FINDING EXITS....");
	while(code_iter->next != NULL && bb_iter->next != NULL){//loop through all code blocks and basic blocks
		//exits are instructions right before a leader
		if(code_iter->next->tac_line == bb_iter->next->leader->tac_line){
			bb_iter->exit = code_iter;          //This should take care of it

			//puts("....ADDED EXIT....");

			bb_iter = bb_iter->next;            //iterate the bb_iter

		}
		code_iter = code_iter->next;          //iterate code_iter
	}

	bb_iter->exit = code_iter;            //last tac instruction is an exit
	//puts("....ADDED LAST INSTRUCTION AS EXIT....");
	}
	//puts("....AFTER FINDING EXITS....");
}
/* -----------------------------------------------------------------------
 * Build CFG
 * -----------------------------------------------------------------------
 */
 void build_cfg(struct code_t *first_code_block, struct bb_t *bb_head){
	//puts("....BEFORE BUILDING CFG....");
	struct bb_t *bb_iter = new_bb();
	struct bb_t *bb_iter2 = new_bb();
	bb_iter = bb_head;                        //reset bb iter to head
	bb_iter2 = bb_head->next;                 //bb_iter2 is after bb_iter initially

	while(bb_iter->next != NULL){             //loops through the list of bb's only once

		if(bb_iter->exit->op == JUMP_OP){
			//exitA is a jump

			bb_iter2 = bb_head;                   //Reset bb_iter2 to head to make sure traverse entire list
			//add target of jump to child of bb_iter

			//ITERATE THROUGH ALL BLOCKS TO FIND THE LEADER THAT MATCHES TARGET OF JUMP
			//Add target of jump unconditional or conditinol
			while(bb_iter2 != NULL){              //This is for jump targets
				if(bb_iter->exit->target->tac_line == bb_iter2->leader->tac_line){
					add_edge(bb_iter, bb_iter2);       //function that adds edge
				}
				bb_iter2 = bb_iter2->next;
			}//END OF FINDING TARGET

			if(bb_iter->exit->var1 != LONG_MAX || bb_iter->exit->var2 != LONG_MAX){      //If it's a conditional jump
				add_edge(bb_iter, bb_iter->next);    //parent, child
			}

		}else if(bb_iter->exit->next->tac_line == bb_iter->next->leader->tac_line){
			//exitA is not a jump
			//add edge between bb_iter and bb_iter->next
			add_edge(bb_iter, bb_iter->next);       //parent, child
		}
		bb_iter = bb_iter->next;//iterate bb_iter

	}//END OF OUTER WHILE
	//puts("....AFTER BUILDING CFG....");
 }//last bracket of building CFG
/* -----------------------------------------------------------------------
* PRINT THE BUILT CFG TREE
* -----------------------------------------------------------------------
*/
void print_cfg(struct bb_t *bb_head){
	{
	int bb_count = 0;
	struct bb_t *bb_iter = new_bb();
	bb_iter = bb_head;//start on first bb
	struct cfg_t *cfg_iter = new_cfg_t();//create new cfg node

	while(bb_iter != NULL){
			printf("BB%d-------------------\n", bb_count);//which basic block we are
			printf("LEADER line number: %d\n", bb_iter->leader->tac_line);
			printf("EXIT line number: %d\n", bb_iter->exit->tac_line);

			//Check for parents
			if(bb_iter->parent != NULL){              //check to see if its the first bb
				cfg_iter = bb_iter->parent;             //initialize cfg iter to head of bb parent list
				while(cfg_iter != NULL){

					printf("Element of parent list, leader line #: %d\n", cfg_iter->link_to_bb->leader->tac_line);//causing a seg fault

					cfg_iter = cfg_iter->next;//increment
				}
			}else{
				puts("First member of CFG, No Parent Element");
			}

			//Check for children
			if(bb_iter->child != NULL){              //check to see if its the first bb
				printf("First element of child list, leader line #: %d\n", bb_iter->child->link_to_bb->leader->tac_line);
				if(bb_iter->child->next != NULL){
					printf("Second element of child list, leader line #: %d\n", bb_iter->child->next->link_to_bb->leader->tac_line);
				}
			}else{
				puts("last member of CFG, No Child Element");
			}
			//line_count++;
			bb_iter = bb_iter->next;//increment bb_iter
			bb_count++;//increment for printing
	}
	}
}

/* -----------------------------------------------------------------------
* initial value numbering of the basic blocks
* -----------------------------------------------------------------------
*/
void value_number_bb(struct bb_t *code_block, long *lvalue_count){
	for(struct bb_t *cursor = code_block; cursor != NULL; cursor = cursor->next){
		value_number(cursor, lvalue_count, NULL);
	}
}

/* -----------------------------------------------------------------------
 * Prints 3AC of a code_block
 * -----------------------------------------------------------------------
 */
 void print_3AC(struct variable_declaration_list_t *current_variable_list, struct code_t *cursor, FILE *program){
	char *name1;
	char *name2;
	char *name3;
	char name_buffer1[30];
	char name_buffer2[30];
	char name_buffer3[30];
	char *op_char;

	switch (cursor->op){
		case ASSIGNMENT_OP:
			op_char = ":=";
			break;
		case ADDITION_OP:
			op_char = "+";
			break;
		case SUBTRACTION_OP:
			op_char = "-";
			break;
		case OR_OP:
			op_char = "or";
			break;
		case MULTIPLY_OP:
			op_char = "*";
			break;
		case DIVISION_OP:
			op_char = "/";
			break;
		case MOD_OP:
			op_char = "mod";
			break;
		case AND_OP:
			op_char = "and";
			break;
		case EQUALS_OP:
			op_char = "=";
			break;
		case NOT_EQUAL_OP:
			op_char = "/=";
			break;
		case LESS_THAN_OP:
			op_char = "<";
			break;
		case GREATER_THAN_OP:
			op_char = ">";
			break;
		case LESS_THAN_EQUAL_TO_OP:
			op_char = "<=";
			break;
		case GREATER_THAN_EQUAL_TO_OP:
			op_char = ">=";
			break;
		default:
			op_char = "unknown";
			break;
	}
	
	//names to strings
	{
		//VarConst1
		if(cursor->var1_const == 0){
			name1 = get_variable_name(current_variable_list, cursor->var1);
			if(name1 == NULL){
				name1 = name_buffer1;
				sprintf(name1, "temp_%ld", LONG_MAX-1-cursor->var1);
			}
		}else if(cursor->var1_const == -1){
			name1 = name_buffer1;
			name1[0] = '\0';
		}else{
				name1 = name_buffer1;
				sprintf(name1, "%ld", cursor->var1);
		}

		//VarConst2
		if(cursor->var2_const == 0){
			name2 = get_variable_name(current_variable_list, cursor->var2);
			if(name2 == NULL){
				name2 = name_buffer2;
				sprintf(name2, "temp_%ld", LONG_MAX-1-cursor->var2);
			}
		}else if(cursor->var2_const == -1){
			name2 = name_buffer2;
			name2[0] = '\0';
		}else{
				name2 = name_buffer2;
				sprintf(name2, "%ld", cursor->var2);
		}

		//varName
		name3 = get_variable_name(current_variable_list, cursor->lvalue);
		if(name3 == NULL){
			name3 = name_buffer3;
			sprintf(name3, "temp_%ld", LONG_MAX-1-cursor->lvalue);
		}
	}

	//PRINT
	{
		if(cursor->op == ASSIGNMENT_OP){
			fprintf(program, "# %s %s %s%s :: %ld\n",
				name3, op_char, name1, name2, cursor->lvalue);

			if(cursor->var2_const == 0){
				if(get_variable_name(current_variable_list, cursor->var2) == NULL){
					fputs(POP_FUNC_WORD_1, program);
				}else{
					fprintf(program, "\tlw $t1, %s\n", name2);
				}
			}else if(cursor->var2_const == 1){
				fprintf(program, "\tli $t1, %s\n", name2);			
			}

			if(cursor->var1_const == 0){
				if(get_variable_name(current_variable_list, cursor->var1) == NULL){
					fputs(POP_FUNC_WORD_0, program);
				}else{
					fprintf(program, "\tlw $t0, %s\n", name1);
				}
			}else if(cursor->var1_const == 1){
				fprintf(program, "\tli $t0, %s\n", name1);			
			}

			if(get_variable_name(current_variable_list, cursor->lvalue) == NULL){
				fputs(PUSH_FUNC_WORD, program);
			}else{
				fprintf(program, "\tsw $t0, %s\n", name3);
			}
		}else if(cursor->op == LABEL_OP){
			fprintf(program, "# LABEL : %s\n", name3);
			fprintf(program, "%s:\n", name3);
		}else if(cursor->op == JUMP_OP){
			char target_buffer[30];
			char *target_name = target_buffer;
			sprintf(target_name, "temp_%ld", LONG_MAX-1-(cursor->target->lvalue));
			if(strcmp(name1, "temp_-1") == 0){
				fprintf(program, "# JUMP -> %s\n", target_name);
				fprintf(program, "\tj %s\n", target_name);
			}else{
				fprintf(program, "# JUMP -> %s if %s = FALSE\n",
					target_name, name1);
				fputs(POP_FUNC_WORD_0, program);
				fprintf(program, "\tbeq $0, $t0, %s\n", target_name);
			}
		}else if(cursor->op == STORE_OP){
			if(name2[0] == '\0'){
				name2[0] = '0'; name2[1] = '\0';
			}
			fprintf(program, "# %s.All := %s\n",
				name3, name1);


			if(cursor->var1_const == 0){
				if(get_variable_name(current_variable_list, cursor->var1) == NULL){
					fputs(POP_FUNC_WORD_0, program);
				}else{
					fprintf(program, "\tlw $t0, %s\n", name1);
				}
			}else if(cursor->var1_const == 1){
				fprintf(program, "\tli $t0, %s\n", name1);			
			}
			fputs(POP_FUNC_WORD_1, program);

			fprintf(program, "\tsw $t0, 0($t1)\n");
		}else if(cursor->op == LOAD_OP){
			if(name2[0] == '\0'){
				name2[0] = '0'; name2[1] = '\0';
			}
			fprintf(program, "# %s := (%s + %s).All\n",
				name3, name1, name2);

			if(cursor->var1_const == 0){
				if(get_variable_name(current_variable_list, cursor->var1) == NULL){
					fputs(POP_FUNC_WORD_0, program);
					fprintf(program, "\tlw $t0, 0($t0)\n");
				}else{
					fprintf(program, "\tlw $t0, %s\n", name1);
					fprintf(program, "\taddi $t0, $t0, %s\n", name2);
				}
				
			}else if(cursor->var1_const == 1){
				fprintf(program, "\tli $t0, %s\n", name1);			
			}


			fputs(PUSH_FUNC_WORD, program);
		}else if(cursor->op == PRINT_OP){
			fprintf(program, "# PRINT(%s)\n\tli $v0, 1\n", name1);

			if(cursor->var1_const == 0){
				if(get_variable_name(current_variable_list, cursor->var1) == NULL){
					fputs(POP_FUNC_WORD_0, program);
					fprintf(program, "\tlw $a0, 0($t0)\n\tsyscall\n");
				}else{
					fprintf(program, "\tlw $a0, %s\n\tsyscall\n", name1);
				}
			}else if(cursor->var1_const == 1){
				fprintf(program, "\tli $a0, %s\n\tsyscall\n", name1);			
			}

			fprintf(program, "\tli $v0, 4\n\tla $a0, NEW_LINE_CONSTANT\n\tsyscall\n");
		}else if(cursor->op == NEG_OP){
			fprintf(program, "# %s := -%s\n",
				name3, name1);

			if(cursor->var1_const == 0){
				if(get_variable_name(current_variable_list, cursor->var2) == NULL){
					fputs(POP_FUNC_WORD_1, program);
				}else{
					fprintf(program, "\tlw $t0, %s\n", name1);
				}
			}else if(cursor->var2_const == 1){
				fprintf(program, "\tli $t0, %s\n", name1);			
			}

			fprintf(program, "\tneg $t0, $t0\n");
			fputs(PUSH_FUNC_WORD, program);
		}else if(cursor->op == SHIFT_ADDRESS){
			fprintf(program, "# %s := %s'Address + %s\n",
				name3, name1, name2);

			if(cursor->var2_const == 0){
				if(get_variable_name(current_variable_list, cursor->var2) == NULL){
					fputs(POP_FUNC_WORD_1, program);
				}else{
					fprintf(program, "\tlw $t1, %s\n", name2);
				}
			}else if(cursor->var2_const == 1){
				fprintf(program, "\tli $t1, %s\n", name2);			
			}

			if(cursor->var1_const == 0){
				if(get_variable_name(current_variable_list, cursor->var1) == NULL){
					fputs(POP_FUNC_WORD_0, program);
				}else{
					fprintf(program, "\tla $t0, %s\n", name1);
				}
			}else if(cursor->var1_const == 1){
				fprintf(program, "\tli $t0, %s\n", name1);			
			}

			print_arithmatic(ADDITION_OP, program);

			if(get_variable_name(current_variable_list, cursor->lvalue) == NULL){
				fputs(PUSH_FUNC_WORD, program);
			}else{
				fprintf(program, "\tsw $t0, %s\n", name3);
			}
		}else if(cursor->op == ALLOCATE_OP){
			fprintf(program, "# Allocate %s blocks for %s\n",
				name1, name3);

			fprintf(program, "\tli $v0, 9\n\tli $a0, %s\n\tsyscall\n", name1);

			if(get_variable_name(current_variable_list, cursor->lvalue) == NULL){
				fputs(POP_FUNC_WORD_1, program);
				fprintf(program, "\tsw $v0, 0($t1)\n");
			}else{
				fprintf(program, "\tsw $v0, %s\n", name3);
			}
		}else{
			if(cursor->var2 == REG_FP){
				name2 = "$fp";
			}
			fprintf(program, "# %s := %s %s %s\n",
				name3, name1, op_char, name2);

			if(cursor->var2_const == 0){
				if(get_variable_name(current_variable_list, cursor->var2) == NULL){
					fputs(POP_FUNC_WORD_1, program);
				}else{
					fprintf(program, "\tlw $t1, %s\n", name2);
				}
			}else if(cursor->var2_const == 1){
				fprintf(program, "\tli $t1, %s\n", name2);			
			}

			if(cursor->var1_const == 0){
				if(get_variable_name(current_variable_list, cursor->var1) == NULL){
					fputs(POP_FUNC_WORD_0, program);
				}else{
					fprintf(program, "\tlw $t0, %s\n", name1);
				}
			}else if(cursor->var1_const == 1){
				fprintf(program, "\tli $t0, %s\n", name1);			
			}

			print_arithmatic(cursor->op, program);

			if(get_variable_name(current_variable_list, cursor->lvalue) == NULL){
				fputs(PUSH_FUNC_WORD, program);
			}else{
				fprintf(program, "\tsw $t0, %s\n", name3);
			}
		}
	}
}

/* -----------------------------------------------------------------------
* companion function to print_3AC. Prints the desired function to file
* -----------------------------------------------------------------------
*/
void print_arithmatic(enum operations op, FILE *program){
	switch(op){
		case ADDITION_OP:
			fputs("\tadd $t0, $t0, $t1\n", program);
			break;
		case SUBTRACTION_OP:
			fputs("\tsub $t0, $t0, $t1\n", program);
			break;
		case OR_OP:
			fputs("\tor $t0, $t0, $t1\n", program);
			break;
		case MULTIPLY_OP:
			fputs("\tmult $t0, $t1\n\tmflo $t0\n", program);
			break;
		case DIVISION_OP:
			fputs("\tdiv $t0, $t1\n\tmflo $t0\n", program);
			break;
		case MOD_OP:
			fputs("\tdiv $t0, $t1\n\tmfhi $t0\n", program);
			break;
		case AND_OP:
			fputs("\tand $t0, $t0, $t1\n", program);
			break;
		case EQUALS_OP:
			fputs("\tsub $t0, $t0, $t1\n\tseq $t0, $0, $t0\n", program);
			break;
		case NOT_EQUAL_OP:
			fputs("\tsub $t0, $t0, $t1\n\tsne $t0, $0, $t0\n", program);
			break;
		case LESS_THAN_OP:
			fputs("\tslt $t0, $t0, $t1\n", program);
			break;
		case GREATER_THAN_OP:
			fputs("\tslt $t0, $t1, $t0\n", program);
			break;
		case LESS_THAN_EQUAL_TO_OP:
			fputs("\tsle $t0, $t0, $t1\n", program);
			break;
		case GREATER_THAN_EQUAL_TO_OP:
			fputs("\tsge $t0, $t0, $t1\n", program);
			break;
		default:
			break;
	}
}

 /* -----------------------------------------------------------------------
 * returns the name fromthe index of a variable in the vdl
 * -----------------------------------------------------------------------
 */
char *get_variable_name(struct variable_declaration_list_t *current_list, long number){
	long index = 0;
	struct variable_declaration_list_t *temp_list = current_list;
	while(temp_list != NULL){ //loop through the vdl linked_list
	struct identifier_list_t *temp_il = temp_list->vd->il;
	while(temp_il != NULL){ //loop through the vd linked_list, comparing temp_il's id to the test id
		if(temp_il->id != NULL){
			if(index == number){
				return temp_il->id;
			}
			if(index != LONG_MAX){
				index++;
			}else{
				puts("TOO MANY VARIABLES");
				exit(-1);
			}

		}
		temp_il = temp_il->next;
	}
	temp_list = temp_list->next;
	}
	return NULL;
}

/* -----------------------------------------------------------------------
* Allocates new memory_map_list_t
* -----------------------------------------------------------------------
*/
struct memory_map_list_t *new_memory_map(){
	struct memory_map_list_t *mm;

	mm = (struct memory_map_list_t *) malloc(sizeof(struct memory_map_list_t));
	CHECK_MEM_ERROR(mm)
	mm->id = NULL; 
	mm->offset = 0;
	mm->tden = NULL;
	mm->next = NULL;

	return mm;
}

 /* -----------------------------------------------------------------------
 * returns the size of the tden
 * -----------------------------------------------------------------------
 */
int get_size(struct type_denoter_t *tden){
	switch (tden->type){
		case 1: //array
			tden->size = get_size(tden->data.at->td) * (tden->data.at->r->max->ui - tden->data.at->r->min->ui + 1); //updates the size variable in the TDen's
			break;
		case 2: //object
			//sum all children sizes	
			tden->size = 0;	
			int size_counter = 0;						
			for(struct variable_declaration_list_t *cursor = tden->data.cl->cb->vdl; cursor != NULL; cursor = cursor->next){
				size_counter = get_size(cursor->vd->tden);
				for(struct identifier_list_t *il = cursor->vd->il; il != NULL; il = il->next){
					tden->size += size_counter;
				}
			}
			tden->data.cl->cb->size = tden->size;
			tden->size = 4;
			break;
		default: //base
			tden->size = 4;
			break;
	}
	return tden->size; 
}


 /* -----------------------------------------------------------------------
 * creates the table for offsets and sizes of variables
 * -----------------------------------------------------------------------
 */
void build_memory_map(struct variable_declaration_list_t* vdl){
	unsigned int memory_location_counter = 0;

	for(struct variable_declaration_list_t *cursor = vdl; cursor != NULL; cursor = cursor->next){
		cursor->vd->tden->size = get_size(cursor->vd->tden);
		for(struct identifier_list_t *il = cursor->vd->il; il != NULL; il = il->next){
			//set locations, based on size on memory_location_counter
			il->location = memory_location_counter;
			memory_location_counter += cursor->vd->tden->size;
		}
	}
}