/*
   +----------------------------------------------------------------------+
   | Xdebug                                                               |
   +----------------------------------------------------------------------+
   | Copyright (c) 2002-2019 Derick Rethans                               |
   +----------------------------------------------------------------------+
   | This source file is subject to version 1.01 of the Xdebug license,   |
   | that is bundled with this package in the file LICENSE, and is        |
   | available at through the world-wide-web at                           |
   | https://xdebug.org/license.php                                       |
   | If you did not receive a copy of the Xdebug license and are unable   |
   | to obtain it through the world-wide-web, please send a note to       |
   | derick@xdebug.org so we can mail you a copy immediately.             |
   +----------------------------------------------------------------------+
   | Authors: Derick Rethans <derick@xdebug.org>                          |
   +----------------------------------------------------------------------+
 */

#ifndef __XDEBUG_CODE_COVERAGE_PRIVATE_H__
#define __XDEBUG_CODE_COVERAGE_PRIVATE_H__

#include "php.h"

#include "branch_info.h"
#include "code_coverage.h"

#include "lib/private.h"
#include "lib/compat.h"
#include "lib/hash.h"
#include "lib/mm.h"

typedef struct xdebug_coverage_line {
	int lineno;
	int count;
	int executable;
} xdebug_coverage_line;

typedef struct xdebug_coverage_function {
	char               *name;
	xdebug_branch_info *branch_info;
} xdebug_coverage_function;

#define XG_COV(v)      (XG(globals.coverage.v))
#define XINI_COV(v)    (XG(settings.coverage.v))

void xdebug_coverage_line_dtor(void *data);

xdebug_coverage_file *xdebug_coverage_file_ctor(char *filename);
void xdebug_coverage_file_dtor(void *data);

char* xdebug_func_format(xdebug_func *func);
void xdebug_build_fname_from_oparray(xdebug_func *tmp, zend_op_array *opa);

xdebug_coverage_function *xdebug_coverage_function_ctor(char *function_name);
void xdebug_coverage_function_dtor(void *data);
void xdebug_print_opcode_info(char type, zend_execute_data *execute_data, const zend_op *cur_opcode);
void xdebug_code_coverage_start_of_function(zend_op_array *op_array, char *function_name);
void xdebug_code_coverage_end_of_function(zend_op_array *op_array, char *file_name, char *function_name);

int xdebug_check_branch_entry_handler(zend_execute_data *execute_data);
int xdebug_common_override_handler(zend_execute_data *execute_data);

void xdebug_count_line(char *file, int lineno, int executable, int deadcode);

PHP_FUNCTION(xdebug_start_code_coverage);
PHP_FUNCTION(xdebug_stop_code_coverage);
PHP_FUNCTION(xdebug_get_code_coverage);
PHP_FUNCTION(xdebug_code_coverage_started);

PHP_FUNCTION(xdebug_get_function_count);

#endif

