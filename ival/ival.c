#include "..\mttopt\mttopt.h"
#include "..\mttstr\mttstr.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	struct mttopt_opt_t optv[] = {
		{ 'f', REQUIRED_ARG },
		{ 'u', NO_ARG },
		{ 't', REQUIRED_ARG }
	};

	struct mttstr_fmt_t fmtfrom = { '+', '-', ' ', .ltrcase = MIXED, LEFT }, fmtto = { 0, '-', .ltrcase = 0, LEFT, 0, 0 };
	struct mttstr_fmt_t fmtopt = { '+', 0, ' ', 10, 0, LEFT };

	while (1)
	{
		struct mttopt_opt_t *opt = mttopt_extr_opt(argc, argv, 3, optv);

		if (opt == NULL) break;

		int alias = opt->alias;

		switch (alias)
		{
		case 'f':
			fmtfrom.base = mttstr_fstr_to_ival(opt->arg, NULL, fmtopt);

			break;
		case 'u':
			fmtto.minus = 0;

			break;
		case 't':
			fmtto.base = mttstr_fstr_to_ival(opt->arg, NULL, fmtopt);

			break;
		}
	}

	if (fmtfrom.base < 2 || fmtfrom.base > 36) fmtfrom.base = 10;

	if (fmtto.base < 2 || fmtto.base > 36) fmtto.base = 16;

	char **av = notopt, **avc = argv + argc;

	while (av < avc)
	{
		size_t ival = mttstr_fstr_to_ival(*av, NULL, fmtfrom);

		av++;
		
		char fstr[128];

		mttstr_ival_to_fstr(fstr, ival, fmtto);
		puts(fstr);
	}

	return 0;
}