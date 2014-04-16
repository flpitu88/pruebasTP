#include "log_app.h"

int print_log_console = 1;
int enable_log_info = 1;
int enable_log_error = 1;
int enable_log_debug = 0;
int enable_log_trace = 1;
int enable_log_warn = 0;

void inicializar_log(char* file_name, char *app_name) {

	log_i = log_create(file_name, app_name, false, LOG_LEVEL_INFO);
	log_d = log_create(file_name, app_name, false, LOG_LEVEL_DEBUG);
	log_t = log_create(file_name, app_name, false, LOG_LEVEL_TRACE);
	log_w = log_create(file_name, app_name, false, LOG_LEVEL_WARNING);
	log_e = log_create(file_name, app_name, false, LOG_LEVEL_ERROR);
}

void finalizar_log() {
	log_destroy(log_i);
	log_destroy(log_d);
	log_destroy(log_t);
	log_destroy(log_w);
	log_destroy(log_e);
}
void ptr_msg(const char* message, int is_error) {
	if (print_log_console ){
			if(!is_error)
		puts(message);
	else
		perror(message);}
}
void log_debug_message(const char* message) {

	if (enable_log_debug) {
		log_debug(log_d, message);
		ptr_msg(message, 0);
	}

}
void log_info_message(const char* message) {
	if (enable_log_info) {
		log_info(log_i, message);
		ptr_msg(message, 0);
	}
}
void log_trace_message(const char* message) {
	if (enable_log_trace) {
		log_trace(log_t, message);
		ptr_msg(message, 0);
	}
}
void log_warning_message(const char* message) {
	if (enable_log_warn) {
		log_warning(log_w, message);
		ptr_msg(message, 0);
	}
}
void log_error_message(const char* message) {
	if (enable_log_error) {
		log_error(log_e, message);
		ptr_msg(message, 1);
	}
}

void habilitar_log_error (){enable_log_error = 1;}
void deshabilitar_log_error (){enable_log_error = 0;}

void habilitar_log_debug (){enable_log_debug = 1;}
void deshabilitar_log_debug (){enable_log_debug = 0;}

void habilitar_log_info (){enable_log_info = 1;}
void deshabilitar_log_info (){enable_log_info = 0;}

void habilitar_log_warn (){enable_log_warn = 1;}
void deshabilitar_log_warn (){enable_log_warn = 0;}

void habilitar_log_trace (){enable_log_trace = 1;}
void deshabilitar_log_trace (){enable_log_trace = 0;}

void habilitar_print_console (){print_log_console = 1;}
void deshabilitar_print_console (){print_log_console = 0;}
