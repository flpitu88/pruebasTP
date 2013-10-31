#include "./commons/log.h"

t_log* log_i;
t_log* log_d;
t_log* log_t;
t_log* log_w;
t_log* log_e;

void inicializar_log(char* file_name, char *app_name);
void finalizar_log();
void log_debug_message (const char* message);
void log_info_message (const char* message);
void log_trace_message (const char* message);
void log_warning_message (const char* message);
void log_error_message (const char* message);


