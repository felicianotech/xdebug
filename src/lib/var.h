/*
   +----------------------------------------------------------------------+
   | Xdebug                                                               |
   +----------------------------------------------------------------------+
   | Copyright (c) 2002-2018 Derick Rethans                               |
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

#include "zend.h"
#include "php_xdebug.h"

#include "lib/compat.h"
#include "lib/private.h"
#include "lib/str.h"
#include "lib/xml.h"

#ifndef __HAVE_XDEBUG_VAR_H__
#define __HAVE_XDEBUG_VAR_H__

typedef struct
{
	int page; /* The number of the page to retrieve */
	int current_element_nr;
	int start_element_nr;
	int end_element_nr;
} xdebug_var_runtime_page;

typedef struct xdebug_var_export_options {
	int max_children;
	int max_data;
	int max_depth;
	int show_hidden;
	int extended_properties;         /* Whether the feature is enabled */
	int encode_as_extended_property; /* Whether the current node's elements need to be encoded */
	int show_location;
	xdebug_var_runtime_page *runtime;
	int no_decoration;
} xdebug_var_export_options;

#define XDEBUG_VAR_TYPE_NORMAL   0x00
#define XDEBUG_VAR_TYPE_STATIC   0x01
#define XDEBUG_VAR_TYPE_CONSTANT 0x02

void xdebug_dump_used_var_with_contents(void *htmlq, xdebug_hash_element* he, void *argument);
void xdebug_get_php_symbol(zval *retval, xdebug_str* name);

xdebug_var_export_options* xdebug_var_export_options_from_ini(TSRMLS_D);
xdebug_var_export_options* xdebug_var_get_nolimit_options(TSRMLS_D);

void xdebug_var_export(zval **struc, xdebug_str *str, int level, int debug_zval, xdebug_var_export_options *options TSRMLS_DC);
void xdebug_var_export_text_ansi(zval **struc, xdebug_str *str, int mode, int level, int debug_zval, xdebug_var_export_options *options TSRMLS_DC);
#define debug_var_export_text(struc, str, level, debug_zval, options) xdebug_var_export_text_ansi(struc, str, 0, level, debug_zval, options TSRMLS_CC);
#define debug_var_export_ansi(struc, str, level, debug_zval, options) xdebug_var_export_text_ansi(struc, str, 1, level, debug_zval, options TSRMLS_CC);
void xdebug_var_export_xml(zval **struc, xdebug_str *str, int level TSRMLS_DC);
void xdebug_var_export_fancy(zval **struc, xdebug_str *str, int level, int debug_zval, xdebug_var_export_options *options TSRMLS_DC);
void xdebug_var_export_xml_node(zval **struc, xdebug_str *name, xdebug_xml_node *node, xdebug_var_export_options *options, int level);

char* xdebug_xmlize(char *string, size_t len, size_t *newlen);
char* xdebug_error_type_simple(int type);
char* xdebug_error_type(int type);
zval *xdebug_get_zval(zend_execute_data *zdata, int node_type, const znode_op *node, int *is_var);
zval *xdebug_get_zval_with_opline(zend_execute_data *zdata, const zend_op *opline, int node_type, const znode_op *node, int *is_var);
xdebug_str* xdebug_get_zval_value(zval *val, int debug_zval, xdebug_var_export_options *options);
xdebug_str* xdebug_get_zval_value_text_ansi(zval *val, int mode, int debug_zval, xdebug_var_export_options *options);
#define xdebug_get_zval_value_text(v,d,o) xdebug_get_zval_value_text_ansi(v,0,d,o TSRMLS_CC);
#define xdebug_get_zval_value_ansi(v,d,o) xdebug_get_zval_value_text_ansi(v,1,d,o TSRMLS_CC);
xdebug_str* xdebug_get_zval_value_fancy(char *name, zval *val, int debug_zval, xdebug_var_export_options *options);
xdebug_str* xdebug_get_zval_value_serialized(zval *val, int debug_zval, xdebug_var_export_options *options);

void xdebug_attach_static_vars(xdebug_xml_node *node, xdebug_var_export_options *options, zend_class_entry *ce TSRMLS_DC);
void xdebug_attach_uninitialized_var(xdebug_var_export_options *options, xdebug_xml_node *node, xdebug_str *name);
void xdebug_attach_static_var_with_contents(zval **zv TSRMLS_DC, int num_args, va_list args, zend_hash_key *hash_key);
#define xdebug_get_zval_value_xml_node(name, val, options) xdebug_get_zval_value_xml_node_ex(name, val, XDEBUG_VAR_TYPE_NORMAL, options)
xdebug_xml_node* xdebug_get_zval_value_xml_node_ex(xdebug_str *name, zval *val, int var_type, xdebug_var_export_options *options);

xdebug_str* xdebug_get_zval_synopsis(zval *val, int debug_zval, xdebug_var_export_options *options);
xdebug_str* xdebug_get_zval_synopsis_text_ansi(zval *val, int mode, int debug_zval, xdebug_var_export_options *options);
xdebug_str* xdebug_get_zval_synopsis_fancy(const char *name, zval *val, int debug_zval, xdebug_var_export_options *options);

char* xdebug_show_fname(xdebug_func t, int html, int flags TSRMLS_DC);

#endif
