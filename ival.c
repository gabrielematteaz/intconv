#include "mtt/cmd_line.h"
#include "mtt/str.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	struct mtt_opt_t optv[] = {
		{ 'f', OPT_FS_REQUIRED_ARG, NULL },
		{ 's', OPT_FS_NO_ARG, NULL },
		{ 'l', OPT_FS_NO_ARG, NULL },
		{ 't', OPT_FS_REQUIRED_ARG, NULL }
	};

	char **av = argv + mtt_extr_optv(argc, argv, 4, optv);
	struct mtt_fmt_t fromfmt = { '+', '-', ' ', 10, FMT_FS_LEFT_FILL | FMT_FS_UNK_CASE, 0 };
	struct mtt_fmt_t optfmt = { '+', 0, ' ', 10, FMT_FS_LEFT_FILL, 0 };

	fromfmt.base = mtt_fstr_to_ival(optv[0].arg, NULL, optfmt);

	if (fromfmt.base < 2 || fromfmt.base > 36) fromfmt.base = 10;

	struct mtt_fmt_t tofmt = { 0, 0, ' ', 16, FMT_FS_LEFT_FILL, 0 };

	if (optv[1].arg) tofmt.minus = '-';

	tofmt.fs |= optv[2].arg ? FMT_FS_LOWERCASE : FMT_FS_UPPERCASE;
	tofmt.base = mtt_fstr_to_ival(optv[3].arg, NULL, optfmt);

	if (tofmt.base < 2 || tofmt.base > 36) tofmt.base = 16;

	char **avc = argv + argc, fstr[128];

	while (av < avc)
	{
		mtt_ival_to_fstr(fstr, mtt_fstr_to_ival(*av, NULL, fromfmt), tofmt);
		av++;
		puts(fstr);
	}

	return 0;
}