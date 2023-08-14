#include "../mttlib/mttopt/mttopt.h"
#include "../mttlib/mttstr/mttstr.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	struct mttopt_opt_t optv[] = {
		{ 'f', OPT_FLAGS_MUST_HAVE_ARG, 0, NULL },
		{ 't', OPT_FLAGS_MUST_HAVE_ARG, 0, NULL },
		{ 'u', OPT_FLAGS_HAS_NO_ARG, 0, NULL },
	};

	char **av = argv + mttopt_extr_optv(argc, argv, 3, optv), **avc = argv + argc, fstr[64 + 1];
	struct mttstr_fmt_t optfmt = { 10, '+', '-', ' ', FMT_FLAGS_LEFT_FILL }, fromfmt = { .plus = '+', '-', ' ', FMT_FLAGS_MCASE | FMT_FLAGS_LEFT_FILL }, tofmt = { .flags = FMT_FLAGS_LEFT_FILL | FMT_FLAGS_NULL_TERM, 0 };

	fromfmt.base = mttstr_fstr_to_ival(optv[0].arg, NULL, optfmt);

	if (fromfmt.base < 2 || fromfmt.base > 36) fromfmt.base = 10;

	tofmt.base = mttstr_fstr_to_ival(optv[1].arg, NULL, optfmt);

	if (tofmt.base < 2 || tofmt.base > 36)
	{
		tofmt.base = 16;

		goto uns;
	}

	if (tofmt.base == 10 && optv[2].found == 0)
	{
		tofmt.plus = '+';
		tofmt.minus = '-';
	}
	else
	{
	uns:
		tofmt.plus = 0;
		tofmt.minus = 0;
	}

	while (av < avc)
	{
		mttstr_ival_to_fstr(fstr, mttstr_fstr_to_ival(*av, NULL, fromfmt), tofmt);
		av++;
		puts(fstr);
	}

	return 0;
}