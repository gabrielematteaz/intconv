#include "mtt/cmdline.h"
#include "mtt/str.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	struct mtt_cmdline_opt_t optv[] = {
		{ 'f', REQUIRED_ARG },
		{ 's', NO_ARG },
		{ 'l', NO_ARG },
		{ 't', REQUIRED_ARG }
	};

	struct mtt_str_fmt_t fromfmt = { '+', '-', ' ', 10, MIXED, LEFT }, tofmt = { 0, 0, ' ', .ltrcase = UPPER, LEFT, 0, 0 };
	struct mtt_str_fmt_t optfmt = { '+', 0, ' ', 10, .fillmode = LEFT };

	while (1)
	{
		struct mtt_cmdline_opt_t *opt = mtt_cmdline_extr_opt(argc, argv, 4,  optv);

		if (opt == NULL) break;

		int alias = opt->alias;

		switch (alias)
		{
		case 'f':
			fromfmt.base = mtt_str_fstr_to_ival(opt->arg, NULL, optfmt);

			break;
		case 's':
			tofmt.minus = '-';

			break;
		case 'l':
			tofmt.ltrcase = LOWER;

			break;
		case 't':
			tofmt.base = mtt_str_fstr_to_ival(opt->arg, NULL, optfmt);

			break;
		}
	}

	if (fromfmt.base < 2 || fromfmt.base > 36) fromfmt.base = 10;

	if (tofmt.base < 2 || tofmt.base > 36) tofmt.base = 16;

	char **av = not_opt, **avc = argv + argc;

	while (av < avc)
	{
		size_t ival = mtt_str_fstr_to_ival(*av, NULL, fromfmt);

		av++;

		char fstr[128];

		mtt_str_ival_to_fstr(fstr, ival, tofmt);
		puts(fstr);
	}

	return 0;
}