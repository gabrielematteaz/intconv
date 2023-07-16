#include "../mttlib/mttopt/mttopt.h"
#include "../mttlib/mttstr/mttstr.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	struct mttopt_opt_t optv[] = {
		{ 'f', 0, MUST_HAVE_ARG, 0 },
		{ 't', 0, MUST_HAVE_ARG, 0 },
		{ 'u', IGNORE_COPIES, HAS_NO_ARG, 0 },
	};

	int avoff, frombase, fromplus, fromminus, fromflags, tobase, tominus;
	size_t width, ival;
	char *fstr, **av, *arg;
	
	avoff = mttopt_extract_optv(argc, argv, sizeof(optv) / sizeof(*optv), optv);
	frombase = mttstr_fstr_to_ival(optv[0].arg, NULL, 10, '+', '-', ' ', LEFT, 0);

	if (frombase < 2 || frombase > 36) frombase = 10;

	if (frombase == 10)
	{
		fromplus = '+';
		fromminus = '-';
		fromflags = 0;
	}
	else
	{
		fromplus = 0;
		fromminus = 0;
		fromflags = MCASE;	
	}

	tobase = mttstr_fstr_to_ival(optv[1].arg, NULL, 10, '+', '-', ' ', LEFT, 0);

	if (tobase < 2 || tobase > 36) tobase = 16;

	if (tobase == 10 && optv[2].status == NOT_FOUND)
	{
		tominus = '-';
		width = mttstr_ival_to_fstr(NULL, ((size_t)1 << (sizeof(size_t) * CHAR_BIT - 1)), 10, '+', '-', 0, 0, 0, 0);
	}
	else
	{
		tominus = 0;
		width = mttstr_ival_to_fstr(NULL, ~0, tobase, 0, 0, 0, 0, 0, 0);
	}

	fstr = malloc(width + 1);

	if (fstr != NULL)
	{
		av = argv + avoff;
		arg = *av;

		while (arg != NULL)
		{
			ival = mttstr_fstr_to_ival(arg, NULL, frombase, fromplus, fromminus, ' ', LEFT, fromflags);
			mttstr_ival_to_fstr(fstr, ival, tobase, 0, tominus, ' ', LEFT, width, NULL_TERM);
			puts(fstr);
			av++;
			arg = *av;
		}

		free(fstr);
	}

	return 0;
}