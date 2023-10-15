#include "mtt\cmdline.h"
#include "mtt\fmt.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	struct mtt_opt_t optv[] = {
		{ 'f', OPT_ARG_TYPE_REQUIRED, NULL },
		{ 's', OPT_ARG_TYPE_NONE, NULL },
		{ 't', OPT_ARG_TYPE_REQUIRED, NULL },
		{ 'l', OPT_ARG_TYPE_NONE, NULL }
	};

	int i = mtt_extr_optv(argc, argv, sizeof(optv) / sizeof(optv[0]), optv);
	struct mtt_ival_fmt_t fromfmt = { '+', '-', ' ', 10, FMT_FILLING_LEFT | VALFMT_LTR_CASE_UNK, 0 }, optfmt = { '+', '\0', ' ', 10, FMT_FILLING_LEFT, 0 }, tofmt = { '\0', '\0', '\0', 16, FMT_NULL_TERM | VALFMT_LTR_CASE_UPPER, 0 };

	fromfmt.base = mtt_fstr_to_ival(optv[0].arg, NULL, optfmt);

	if (fromfmt.base < 2 || fromfmt.base > 36)
	{
		fromfmt.base = 10;
	}

	if (optv[1].arg)
	{
		tofmt.minus = '-';
	}

	tofmt.base = mtt_fstr_to_ival(optv[2].arg, NULL, optfmt);

	if (tofmt.base < 2 || tofmt.base > 36)
	{
		tofmt.base = 16;
	}

	if (optv[3].arg)
	{
		tofmt.fs |= VALFMT_LTR_CASE_LOWER;
	}

	while (i < argc)
	{
		char fstr[128];

		mtt_ival_to_fstr(fstr, mtt_fstr_to_ival(argv[i], NULL, fromfmt), tofmt);
		i++;
		puts(fstr);
	}

	return 0;
}