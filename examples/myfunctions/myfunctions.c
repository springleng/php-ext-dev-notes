/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_myfunctions.h"

/* If you declare any globals in php_myfunctions.h uncomment this: */
ZEND_DECLARE_MODULE_GLOBALS(myfunctions)

/* True global resources - no need for thread safety here */
static int le_myfunctions;

int time_of_minit;
int time_of_rinit;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini */
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("myfunctions.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_myfunctions_globals, myfunctions_globals)
    STD_PHP_INI_ENTRY("myfunctions.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_myfunctions_globals, myfunctions_globals)
PHP_INI_END()
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string helloWorld(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(helloWorld)
{
	char *arg = NULL;
	size_t arg_len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Hello, %.78s!", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/

/* {{{ proto string myConcat(string str, int n)
    */
PHP_FUNCTION(myConcat)
{
	char *str = NULL;
	char *result, *ptr;
	int argc = ZEND_NUM_ARGS();
	size_t str_len;
	zend_long n, result_len;
	zend_string *strg;

	if (zend_parse_parameters(argc, "sl", &str, &str_len, &n) == FAILURE) 
		return;

	result_len = str_len * n;

	result = emalloc(result_len + 1);

	ptr = result;

	while (n--) {
		memcpy(ptr, str, str_len);
		ptr += str_len;
	}

	*ptr = '\0';

	RETURN_STRINGL(result, result_len);
}
/* }}} */

/* {{{ proto string phpStartupAndShutdown(string arg)
    */
PHP_FUNCTION(phpStartupAndShutdown)
{
	char *arg = NULL;
	size_t arg_len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Hello, %.78s! time_of_minit = %d, time_of_rinit = %d", arg, time_of_minit, time_of_rinit);

	RETURN_STR(strg);
}
/* }}} */

/* {{{ php_myfunctions_init_globals
 */
/* Uncomment this function if you have INI entries */
static void php_myfunctions_init_globals(zend_myfunctions_globals *myfunctions_globals)
{
	myfunctions_globals->global_value = 0;
	myfunctions_globals->global_string = NULL;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(myfunctions)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	time_of_minit = time(NULL);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(myfunctions)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	FILE *fp = fopen("/tmp/time_mshutdown.txt", "a+");
	fprintf(fp, "%d\n", time(NULL));
	fclose(fp);
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(myfunctions)
{
	time_of_rinit = time(NULL);
#if defined(COMPILE_DL_MYFUNCTIONS) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(myfunctions)
{
	FILE *fp = fopen("/tmp/time_rshutdown.txt", "a+");
	fprintf(fp, "%d\n", time(NULL));
	fclose(fp);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(myfunctions)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "myfunctions support", "enabled");
	php_info_print_table_row(2, "version", PHP_MYFUNCTIONS_VERSION);
	php_info_print_table_row(2, "author", "silen <silence.lc@gmail.com>");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ myfunctions_functions[]
 *
 * Every user visible function must have an entry in myfunctions_functions[].
 */
const zend_function_entry myfunctions_functions[] = {
	PHP_FE(helloWorld, NULL)		/* For testing, remove later. */
	PHP_FE(myConcat, NULL)
	PHP_FE(phpStartupAndShutdown, NULL)
	PHP_FE_END	/* Must be the last line in myfunctions_functions[] */
};
/* }}} */

/* {{{ myfunctions_module_entry
 */
zend_module_entry myfunctions_module_entry = {
	STANDARD_MODULE_HEADER,
	"myfunctions",
	myfunctions_functions,
	PHP_MINIT(myfunctions),
	PHP_MSHUTDOWN(myfunctions),
	PHP_RINIT(myfunctions),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(myfunctions),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(myfunctions),
	PHP_MYFUNCTIONS_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MYFUNCTIONS
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(myfunctions)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
