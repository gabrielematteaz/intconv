#include "../mttopt/include/mttopt.h"
#include "../mttstr/include/mttstr.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	struct mttopt_opt_t optv[] = {
		{ 'f', OPT_FS_MUST_HAVE_ARG, 0 },
		{ 't', OPT_FS_MUST_HAVE_ARG, 0 },
		{ 'u', OPT_FS_HAS_NO_ARG, 0 }
	};

	struct mttstr_fmt_t from = { '+', '-', ' ', .fs = FMT_FS_MCASE | FMT_FS_LEFT_FILL };
	struct mttstr_fmt_t opt = { '+', '-', ' ', 10, FMT_FS_LEFT_FILL };
	struct mttstr_fmt_t to = { .fill = ' ', .fs = FMT_FS_LEFT_FILL | FMT_FS_NULL_TERM, 0 };
	char **av = argv + mttopt_extr_optv(argc, argv, 3, optv), **avc = argv + argc;

	from.base = optv[0].found ? mttstr_fstr_to_ival(optv[0].arg, NULL, opt) : 10;

	if (optv[1].found)
	{
		to.base = mttstr_fstr_to_ival(optv[1].arg, NULL, opt);

		if (to.base < 2 || to.base > 36)
		{
			to.plus = 0;
			to.minus = 0;
			to.base = 16;
		}
		else
		{
			if (optv[2].found)
			{
				to.plus = 0;
				to.minus = 0;
			}
			else if (to.base == 10)
			{
				to.plus = '+';
				to.minus = '-';
			}
			else
			{
				to.plus = 0;
				to.minus = 0;
			}
		}
	}
	else
	{
		to.plus = 0;
		to.minus = 0;
		to.base = 16;	
	}

	while (av < avc)
	{
		size_t ival = mttstr_fstr_to_ival(*av, NULL, from);

		av++;

		char fstr[64 + 1];

		mttstr_ival_to_fstr(fstr, ival, to);
		puts(fstr);
	}

	return 0;
}