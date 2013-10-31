#include "log_app.h"

void inicializar_log(char* file_name, char *app_name)
{

	log_i = log_create(file_name, app_name, false, LOG_LEVEL_INFO);
	log_d = log_create(file_name, app_name, false, LOG_LEVEL_DEBUG);
	log_t = log_create(file_name, app_name, false, LOG_LEVEL_TRACE);
	log_w = log_create(file_name, app_name, false, LOG_LEVEL_WARNING);
	log_e = log_create(file_name, app_name, false, LOG_LEVEL_ERROR);
}

void finalizar_log()
{
	log_destroy(log_i);
	log_destroy(log_d);
	log_destroy(log_t);
	log_destroy(log_w);
	log_destroy(log_e);
}

void log_debug_message (const char* message)
{
	log_debug(log_d, message);
}
void log_info_message (const char* message)
{
	log_info(log_i, message);
}
void log_trace_message (const char* message)
{
	log_trace(log_t, message);
}
void log_warning_message (const char* message)
{
	log_warning(log_w, message);
}
void log_error_message (const char* message)
{
	log_error(log_e, message);
}
