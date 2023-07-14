#include "../mttlib/mttopt/mttopt.h"
#include "../mttlib/mttstr/mttstr.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	struct mttopt_opt_t optv[] = { { 'f', HAS_ARG, NOT_FOUND, NULL }, { 't', HAS_ARG, 0, NULL }, { 'l', 0, 0 } };
	struct mttstr_fmt_t fmtopt = { '+', '-', .base = 10, .fill_mode = 0 }, fmtfrom = { .fill_mode = 0 }, fmtto = { .plus = 0, .fill_mode = 0, .flags = NULL_TERM, .width = 0 };
	char *fstr, **av, *arg;
	int argvoff = mttopt_extract_optv(argc, argv, sizeof(optv) / sizeof(*optv), optv);
	size_t ival;

	fmtfrom.base = mttstr_fstr_to_ival(optv[0].arg, NULL, fmtopt);

	if (fmtfrom.base < 2 || fmtfrom.base == 10 || fmtfrom.base > 36)
	{
		fmtfrom.plus = '+';
		fmtfrom.minus = '-';
		fmtfrom.base = 10;
	}
	else
	{
		fmtfrom.plus = 0;
		fmtfrom.minus = 0;
		fmtfrom.flags = MCASE;
	}

	fmtto.base = mttstr_fstr_to_ival(optv[1].arg, NULL, fmtopt);

	if (fmtto.base < 2 || fmtto.base > 36)
	{
		fmtto.minus = 0;
		fmtto.base = 16;
	}
	else fmtto.minus = fmtto.base == 10 ? '-' : 0;

	if (optv[2].status == FOUND) fmtto.flags |= LCASE;

	fmtto.width = mttstr_ival_to_fstr(NULL, ~0, fmtto);
	fstr = malloc(fmtto.width + 1);

	if (fstr != NULL)
	{
		fmtto.width = 0;
		av = argv + argvoff;

		while (1)
		{
			arg = *av;

			if (arg == NULL) break;

			ival = mttstr_fstr_to_ival(arg, NULL, fmtfrom);
			mttstr_ival_to_fstr(fstr, ival, fmtto);
			puts(fstr);
			av++;
		}

		free(fstr);
	}

	return 0;
}