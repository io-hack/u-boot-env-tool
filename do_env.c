#include "do_env.h"

int do_open_env(env_t *env_buf, char *env_path, unsigned int env_offset, unsigned int env_data_size)
{
	FILE *env_fp = NULL;
	unsigned int check_crc;
	
	env_buf->crc = 0x00000000;
	env_buf->data = (char *)malloc(env_data_size  - ENV_HEADER_SIZE);
	
	env_fp = fopen(env_path, "r");
	
	if(env_fp == NULL)
	{
		return 1;
	}
	
	if(fseek(env_fp, env_offset, SEEK_SET) != 0)
	{
		return 2;
	}
	
	printf("read env CRC size %lu bytes.\r\n", fread(&env_buf->crc, 1, ENV_HEADER_SIZE, env_fp));
	printf("read env CRC value 0x%08X.\r\n", env_buf->crc);
	printf("read env data size %lu bytes.\r\n", fread(env_buf->data, 1, env_data_size - ENV_HEADER_SIZE, env_fp));
	
	check_crc = crc32(0, env_buf->data, env_data_size - ENV_HEADER_SIZE);
	printf("count CRC value 0x%08X.\r\n", check_crc);
	
	if(check_crc == env_buf->crc)
	{
		printf("check CRC ok.\r\n");
	}
	else
	{
		printf("check CRC bad.\r\n");
	}
	
	fclose(env_fp);
	printf("do_open_env finish.\r\n");
	return 0;
}

int do_print_env(env_t *env_buf, unsigned int env_data_size)
{
	int i;
	for(i = 0; i < env_data_size - ENV_HEADER_SIZE - 1; i++ )
	{
		if(*(env_buf->data + i) == '\0')
		{
			if(*(env_buf->data + i + 1) == '\0')
			{
				break;
			}
			else
			{
				printf("\r\n");
			}
		}
		else
		{
			printf("%c", *(env_buf->data + i));
		}
	}
}

int do_set_env(env_t *env_buf, unsigned int env_data_size, char * env_name, char * env_value)
{

}

int do_del_env(env_t *env_buf, unsigned int env_data_size, char * env_name)
{
	int i, j, k, count;
	char *search_str;
	char **env_list;
	char *temp_env_data;
	
	//seatch_str = env_name + '=' + '\0'
	search_str = (char *)malloc(strlen(env_name) + 1 + 1);
	strcpy(search_str, env_name);
	search_str[strlen(env_name)] = '=';
	search_str[strlen(env_name) + 1] = '\0';
	
	//get count of env list
	count = 0;
	for(i = 0; i < env_data_size - ENV_HEADER_SIZE - 1; i++ )
	{
		if(*(env_buf->data + i) == '\0')
		{
			count++;
			if(*(env_buf->data + i + 1) == '\0')
			{
				break;
			}
		}
	}
	env_list = (char **)malloc(sizeof(char *) * count);
	
	//get env list
	j = 0;
	for(i = 0; i < env_data_size - ENV_HEADER_SIZE - 1; i++ )
	{
		if(*(env_buf->data + i) == '\0')
		{
			if(*(env_buf->data + i + 1) == '\0')
			{
				break;
			}
			else
			{
				env_list[++j] = env_buf->data + i + 1;
			}
		}
		else
		{
			if(i == 0)
			{
				env_list[j] = env_buf->data;
			}
		}
	}
	
	for(i=0; i<count; i++)
	{
		if(strstr(env_list[i], search_str) != NULL &&
			strstr(env_list[i], search_str) == env_list[i])
		{
			printf("found %s", env_name);
			
			//delete one
			count--;
			for(j=i; j<count; j++)
			{
				env_list[j] = env_list[j + 1];
			}
			
			//save on ram
			temp_env_data = (char *)malloc(env_data_size - ENV_HEADER_SIZE);
			memset(temp_env_data, 0, env_data_size - ENV_HEADER_SIZE);
			k = 0;
			for(i=0; i<count; i++)
			{
				for(j=0; j<strlen(env_list[i])+1; j++)
				{
					temp_env_data[k] = env_list[i][j];
					k++;
				}
			}
			memcpy(env_buf->data, temp_env_data, env_data_size - ENV_HEADER_SIZE);
			
			free(search_str);
			free(env_list);
			free(temp_env_data);
			return 0;
		}
	}

	printf("none %s", env_name);

	free(search_str);
	free(env_list);
	free(temp_env_data);
	return 1;
}

int do_save_env(env_t *env_buf, char *env_path, unsigned int env_offset, unsigned int env_data_size)
{
	FILE *env_fp = NULL;

	env_fp = fopen(env_path, "w");
	
	if(env_fp == NULL)
	{
		return 1;
	}
	
	if(fseek(env_fp, env_offset, SEEK_SET) != 0)
	{
		return 2;
	}
	
	env_buf->crc = crc32(0, env_buf->data, env_data_size - ENV_HEADER_SIZE);
	printf("count CRC value 0x%08X.\r\n", env_buf->crc);
	
	printf("write env CRC size %lu bytes.\r\n", fwrite(&env_buf->crc, 1, ENV_HEADER_SIZE, env_fp));
	printf("write env data size %lu bytes.\r\n", fwrite(env_buf->data, 1, env_data_size - ENV_HEADER_SIZE, env_fp));

	fclose(env_fp);
	printf("do_save_env finish.\r\n");
	return 0;	
}

