#include "mttopt.h"
#include "mttstr.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	struct mttopt_opt_t opts[] = {
		'f', 0, NULL,
		't', 0, NULL,
	};

	char **args = argv + 1, **as = args + mttopt_exctr_opts(argc - 1, args, 2, opts), *arg, *fstr;
	struct mttstr_fmt_t optfmt, ftivfmt, ivtffmt;
	size_t frombase, tobase, ival, fstrsize;

	optfmt.plusc = '+';
	optfmt.minusc = '-';
	optfmt.base = 10;
	optfmt.fill_mode = no_fill;
	optfmt.flags = 0;
	frombase = opts[0].arg == NULL ? 10 : mttstr_fstr_to_ival(opts[0].arg, NULL, optfmt);
	tobase = opts[1].arg == NULL ? 16 : mttstr_fstr_to_ival(opts[1].arg, NULL, optfmt);
	ftivfmt.fill_mode = no_fill;
	ivtffmt.plusc = 0;
	ivtffmt.fill_mode = 0;
	ivtffmt.flags = FMT_FLAGS_NULL_TERM;
	ivtffmt.width = 0;
	arg = *as;

	if (frombase < 2 || frombase == 10 || frombase > 36)
	{
		ftivfmt.plusc = '+';
		ftivfmt.minusc = '-';
		ftivfmt.base = 10;
		ftivfmt.flags = 0;
	}
	else
	{
		ftivfmt.plusc = 0;
		ftivfmt.minusc = 0;
		ftivfmt.base = frombase;
		ftivfmt.flags = FMT_FLAGS_MCASE;
	}

	if (tobase < 2 || tobase > 36)
	{
		ivtffmt.minusc = 0;
		ivtffmt.base = 16;
	}
	else
	{
		ivtffmt.minusc = tobase == 10 ? '-' : 0;
		ivtffmt.base = tobase;
	}

	while (arg != NULL)
	{
		as++;
		ival = mttstr_fstr_to_ival(arg, NULL, ftivfmt);
		arg = *as;
		fstrsize = mttstr_ival_to_fstr(NULL, ival, ivtffmt);
		fstr = malloc(fstrsize + 1);

		if (fstr)
		{
			mttstr_ival_to_fstr(fstr, ival, ivtffmt);
			puts(fstr);
			free(fstr);
		}
	}

	return 0;
}