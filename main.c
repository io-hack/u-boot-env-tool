#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crc.h"
#include "environment.h"
#include "do_env.h"

#define VERSION (1.0)

void show_logo(void);

int main(int argc, char *argv[]) {
	//env_path env_offset env_data_size
	env_t env_buf;
	char *env_path;
	unsigned int env_offset;
	unsigned int env_data_size;
	char cmd[1024], param0[1024], param1[1024];
	
	show_logo();

	if(argc < 4)
	{
		printf("Usage:%s <env_path> <env_offset> <env_data_size>\r\n", argv[0]);
		return 1;
	}
	
	env_path = (char *)malloc(strlen(argv[1])+1);
	strcpy(env_path, argv[1]);
	env_offset = strtoul(argv[2], 0, 0);
	env_data_size = strtoul(argv[3], 0, 0);
	
	printf("env_path: %s\r\nenv_offset: %lu bytes\r\nenv_data_size: %lu bytes\r\n",
		env_path,
		env_offset,
		env_data_size
		);
		
	
	if(do_open_env(&env_buf, env_path, env_offset, env_data_size) != 0)
	{
		perror("do_open_env error.\r\n");
		return 1;
	}
	
	for(;;)
	{
		printf(">");
		scanf("%s", cmd);
		
		if(strcmp(cmd, "print") == 0 || strcmp(cmd, "printenv") == 0)
		{
			do_print_env(&env_buf, env_data_size);
		}
		else if(strcmp(cmd, "set") == 0 || strcmp(cmd, "setenv") == 0)
		{
			printf("setenv_name:");
			scanf("%s", param0);
			printf("setenv_value:");
			scanf("%s", param1);
			printf("%s %s %s\r\n", cmd, param0, param1);
			do_set_env(&env_buf, env_data_size, param0, param1);
		}
		else if(strcmp(cmd, "del") == 0 || strcmp(cmd, "delenv") == 0)
		{
			printf("delenv_name:");
			scanf("%s", param0);
			printf("%s %s\r\n", cmd, param0);
			do_del_env(&env_buf, env_data_size, param0);
		}
		else if(strcmp(cmd, "save") == 0 || strcmp(cmd, "saveenv") == 0)
		{
			if(do_save_env(&env_buf, env_path, env_offset, env_data_size) != 0)
			{
				printf("do_save_env error.");
			}
		}
		else if(strcmp(cmd, "q") == 0)
		{
			return 0;
		}
		else
		{
			printf("Help:\r\nprint/printenv\r\nset/setenv\r\ndel/delenv\r\nsave/saveenv");
		}
		
		printf("\r\n");
	}
	
	return 0;
}

void show_logo(void)
{
	printf("          _____                    _____                _____          \r\n");
	printf("         /\    \                  /\    \              /\    \         \r\n");
	printf("        /::\____\                /::\    \            /::\    \        \r\n");
	printf("       /:::/    /               /::::\    \           \:::\    \       \r\n");
	printf("      /:::/    /               /::::::\    \           \:::\    \      \r\n");
	printf("     /:::/    /               /:::/\:::\    \           \:::\    \     \r\n");
	printf("    /:::/    /               /:::/__\:::\    \           \:::\    \    \r\n");
	printf("   /:::/    /               /::::\   \:::\    \          /::::\    \   \r\n");
	printf("  /:::/    /      _____    /::::::\   \:::\    \        /::::::\    \  \r\n");
	printf(" /:::/____/      /\    \  /:::/\:::\   \:::\    \      /:::/\:::\    \ \r\n");
	printf("|:::|    /      /::\____\/:::/__\:::\   \:::\____\    /:::/  \:::\____\\r\n");
	printf("|:::|____\     /:::/    /\:::\   \:::\   \::/    /   /:::/    \::/    /\r\n");
	printf(" \:::\    \   /:::/    /  \:::\   \:::\   \/____/   /:::/    / \/____/ \r\n");
	printf("  \:::\    \ /:::/    /    \:::\   \:::\    \      /:::/    /          \r\n");
	printf("   \:::\    /:::/    /      \:::\   \:::\____\    /:::/    /           \r\n");
	printf("    \:::\__/:::/    /        \:::\   \::/    /    \::/    /            \r\n");
	printf("     \::::::::/    /          \:::\   \/____/      \/____/             \r\n");
	printf("      \::::::/    /            \:::\    \                              \r\n");
	printf("       \::::/    /              \:::\____\                             \r\n");
	printf("        \::/____/                \::/    /                             \r\n");
	printf("         ~~                       \/____/                              \r\n");
	printf("                                                                       \r\n");
	printf("U-Boot Environment Tool (Version:%1.1f)                                \r\n", VERSION);
	printf("@else	zhenwenjin@gmail.com                                           \r\n");
	printf("https://io-hack.github.io/	https://github.com/io-hack/            \r\n\r\n");
}
