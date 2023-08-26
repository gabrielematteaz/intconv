#ifndef MTTOPT_H
#define MTTOPT_H

#include <stddef.h>

enum mttopt_opt_fs_t
{
	NO_ARG,
	OPTIONAL_ARG,
	REQUIRED_ARG
};

struct mttopt_opt_t
{
	int alias;
	enum mttopt_opt_fs_t fs;
	char *arg;
};

extern char *curopt, **curarg, **notopt;

struct mttopt_opt_t *mttopt_extr_opt(int argc, char *argv[], int optc, struct mttopt_opt_t *optv);

#endif