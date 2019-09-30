#ifndef _do_env_h_
#define _do_env_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crc.h"
#include "environment.h"
#include "do_env.h"

int do_open_env(env_t *env_buf, char *env_path, unsigned int env_offset, unsigned int env_data_size);
int do_print_env(env_t *env_buf, unsigned int env_data_size);
int do_del_env(env_t *env_buf, unsigned int env_data_size, char * env_name);
int do_set_env(env_t *env_buf, unsigned int env_data_size, char * env_name, char * env_value);
int do_save_env(env_t *env_buf, char *env_path, unsigned int env_offset, unsigned int env_data_size);

#endif

