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

#ifndef __XDEBUG_PROFILER_H__
#define __XDEBUG_PROFILER_H__

#include "php.h"
#include "TSRM.h"
#include "lib/private.h"

typedef struct _xdebug_profiler_globals_t {
	double        profiler_start_time;
	zend_bool     profiler_enabled;
	FILE         *profile_file;
	char         *profile_filename;
	xdebug_hash  *profile_filename_refs;
	int           profile_last_filename_ref;
	xdebug_hash  *profile_functionname_refs;
	int           profile_last_functionname_ref;

	/* aggregate profiling */
	HashTable  aggr_calls;
} xdebug_profiler_globals_t;

typedef struct _xdebug_profiler_settings_t {
	zend_bool     profiler_enable;
	char         *profiler_output_dir;
	char         *profiler_output_name; /* "pid" or "crc32" */
	zend_bool     profiler_enable_trigger;
	char         *profiler_enable_trigger_value;
	zend_bool     profiler_append;
	zend_bool     profiler_aggregate;
} xdebug_profiler_settings_t;

void xdebug_init_profiler_globals(xdebug_profiler_globals_t *xg);
void xdebug_profiler_minit(void);
void xdebug_profiler_mshutdown(void);
void xdebug_profiler_rinit(void);
void xdebug_profiler_post_deactivate(void);

void xdebug_profiler_pcntl_exec_handler(void);
void xdebug_profiler_exit_handler(void);

void xdebug_profiler_init_if_requested(zend_op_array *op_array);
void xdebug_profiler_execute_ex(function_stack_entry *fse, zend_op_array *op_array);
void xdebug_profiler_execute_ex_end(function_stack_entry *fse);
void xdebug_profiler_execute_internal(function_stack_entry *fse);
void xdebug_profiler_execute_internal_end(function_stack_entry *fse);

void xdebug_profiler_add_aggregate_entry(function_stack_entry *fse);

void xdebug_profiler_init(char *script_name);
void xdebug_profiler_deinit();
int xdebug_profiler_output_aggr_data(const char *prefix);

void xdebug_profiler_add_function_details_user(function_stack_entry *fse, zend_op_array *op_array);
void xdebug_profiler_add_function_details_internal(function_stack_entry *fse);
void xdebug_profiler_free_function_details(function_stack_entry *fse);

void xdebug_profiler_function_begin(function_stack_entry *fse);
void xdebug_profiler_function_end(function_stack_entry *fse);

void xdebug_profile_call_entry_dtor(void *dummy, void *elem);
void xdebug_profile_aggr_call_entry_dtor(void *elem);

char *xdebug_get_profiler_filename(void);

PHP_FUNCTION(xdebug_get_profiler_filename);
PHP_FUNCTION(xdebug_dump_aggr_profiling_data);
PHP_FUNCTION(xdebug_clear_aggr_profiling_data);
#endif
