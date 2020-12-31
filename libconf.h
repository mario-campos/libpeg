#ifndef LIBCONF_H
#define LIBCONF_H

#include <setjmp.h>
#include <stdio.h>
#include <stdbool.h>

#define LIBCONF_SUCCESS 		0x0001
#define LIBCONF_ERR_EOF			0x0002
#define LIBCONF_ERR_UNEXPECTED_TOKEN 	0x0002
#define LIBCONF_ERR_READ		0x0003

struct conf_ctx {
	jmp_buf jump;
	FILE *file;
	char buf[1024];
	size_t buf_index;
	size_t buf_size;
	int err_code;
	const char *err_text;
};

void conf_init(struct conf_ctx *);
bool conf_parse(struct conf_ctx *, void (*)(struct conf_ctx *, void *), FILE *, void *);

bool conf_eof(struct conf_ctx *);
bool conf_next(struct conf_ctx *, const char *);
void conf_error(struct conf_ctx *, int, const char *);
size_t conf_expect(struct conf_ctx *, const char *);
size_t conf_accept(struct conf_ctx *, const char *);
size_t conf_string(struct conf_ctx *, char *, size_t);

#endif /* LIBCONF_H */
