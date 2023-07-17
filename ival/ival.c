#include "../mttlib/mttopt/mttopt.h"
#include "../mttlib/mttstr/mttstr.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	struct mttopt_opt_t optv[] = {
		{ 'f', 0, MUST_HAVE_ARG, 0 },
		{ 't', 0, MUST_HAVE_ARG, 0 },
		{ 'u', IGNORE_COPIES, 0, 0 }
	};

	int avoff = mttopt_extract_optv(argc, argv, sizeof(optv) / sizeof(*optv), optv);
	struct mttstr_fmt_t optfmt = { '+', '-', ' ', 10, 0, 0 }, tofmt, fromfmt;
	size_t maxival, ival;
	char *fstr, **av, *arg;

	if (optv[1].status == FOUND)
	{
		tofmt.base = mttstr_fstr_to_ival(optv[1].arg, NULL, optfmt);

		if (tofmt.base < 2 || tofmt.base > 36) goto default_tofmt;

		if (tofmt.base == 10 && optv[2].status == NOT_FOUND)
		{
			tofmt.minus = '-';
			tofmt.flags = NULL_TERM;
			maxival = (size_t)1 << (sizeof(size_t) * CHAR_BIT - 1);
		}
		else goto not_signed_decimal_tofmt;
	}
	else
	{
	default_tofmt:
		tofmt.base = 16;
	not_signed_decimal_tofmt:
		tofmt.minus = 0;
		tofmt.flags = NULL_TERM;
		maxival = -1;
	}

	tofmt.plus = 0;
	tofmt.fillmode = 0;
	tofmt.width = 0;
	tofmt.width = mttstr_ival_to_fstr(NULL, maxival, tofmt);
	fstr = malloc(tofmt.width + 1);

	if (fstr != NULL)
	{
		if (optv[0].status == FOUND)
		{
			fromfmt.base = mttstr_fstr_to_ival(optv[0].arg, NULL, optfmt);

			if (fromfmt.base < 2 || fromfmt.base > 36) goto default_fromfmt;

			if (fromfmt.base == 10)	goto signed_decimal_fromfmt;

			fromfmt.plus = 0;
			fromfmt.minus = 0;
		}
		else
		{
		default_fromfmt:
			fromfmt.base = 10;
		signed_decimal_fromfmt:
			fromfmt.plus = '+';
			fromfmt.minus = '-';
			fromfmt.flags = MCASE;
		}

		fromfmt.fill = ' ';
		fromfmt.fillmode = 0;
		av = argv + avoff;
		arg = *av;

		while (arg != NULL)
		{
			av++;
			ival = mttstr_fstr_to_ival(arg, NULL, fromfmt);
			mttstr_ival_to_fstr(fstr, ival, tofmt);
			puts(fstr);
			arg = *av;
		}

		free(fstr);
	}

	return 0;
}