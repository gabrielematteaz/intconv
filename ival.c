#include "mtt/cmd_line.h"
#include "mtt/str.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	struct mtt_opt_t optv[] = {
		{ 'f', OPT_REQUIRED_ARG, NULL },
		{ 's', OPT_NO_ARG, NULL },
		{ 't', OPT_REQUIRED_ARG, NULL },
		{ 'l', OPT_NO_ARG, NULL }
	};

	char **av = argv + mtt_extr_optv(argc, argv, 4, optv);
	struct mtt_fstr_to_ival_fmt_t optfmt = { '+', 0, ' ', 10, FMT_FILL_MODE_LEFT };
	struct mtt_fstr_to_ival_fmt_t fromfmt = { '+', '-', ' ', mtt_fstr_to_ival(optv[0].arg, NULL, optfmt), FMT_FILL_MODE_LEFT | FSTR_TO_IVAL_FMT_LTR_CASE_MIXED };

	if (fromfmt.base < 2 || fromfmt.base > 36) fromfmt.base = 10;

	struct mtt_ival_to_fstr_fmt_t tofmt = { { 0, optv[1].arg ? '-' : 0, ' ', mtt_fstr_to_ival(optv[2].arg, NULL, optfmt), FMT_FILL_MODE_LEFT | (optv[3].arg ? FMT_LTR_CASE_LOWER : FMT_LTR_CASE_UPPER) }, 0 };

	if (tofmt.from.base < 2 || tofmt.from.base > 36) tofmt.from.base = 16;

	char **avc = argv + argc;

	while (av < avc)
	{
		char fstr[128];

		mtt_ival_to_fstr(fstr, mtt_fstr_to_ival(*av, NULL, fromfmt), tofmt);
		av++;
		puts(fstr);
	}

	return 0;
}