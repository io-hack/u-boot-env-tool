#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#define ENV_HEADER_SIZE (4)

typedef struct environment_s {
	uint32_t	crc;		/* CRC32 over data bytes	*/
	unsigned char	*data; /* Environment data		*/
} env_t;

#endif

