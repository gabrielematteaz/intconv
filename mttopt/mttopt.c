#include "mttopt.h"

char *curopt = NULL, **curarg = NULL, **notopt = NULL;

struct mttopt_opt_t *mttopt_extr_opt(int argc, char *argv[], int optc, struct mttopt_opt_t *optv)
{
	if (curopt)
	{
	parseopt:
		struct mttopt_opt_t *ov = optv, *ovc = ov + optc;

		while (ov < ovc)
		{
			if (*curopt == ov->alias)
			{
				enum mttopt_opt_fs_t fs = ov->fs;

				curopt++;

				if (fs == OPTIONAL_ARG)
				{
					ov->arg = *curopt ? curopt : NULL;
					curopt = NULL;
					curarg++;
				}
				else if (fs == REQUIRED_ARG)
				{
					if (*curopt) ov->arg = curopt;
					else
					{
						curarg++;

						if (curarg == argv + argc)
						{
							curopt = NULL;
							notopt = curarg;
							curarg = NULL;

							return NULL;
						}

						ov->arg = *curarg;
					}

					curopt = NULL;
					curarg++;
				}
				else if (*curopt == 0)
				{
					curopt = NULL;
					curarg++;
				}

				return ov;
			}

			ov++;
		}

		curopt++;

		if (*curopt) goto parseopt;

		curopt = NULL;
		curarg++;

		goto parsearg;
	}
	else if (curarg)
	{
	parsearg:
		if (curarg < argv + argc)
		{
			char *ca = *curarg;

			if (ca && *ca == '-')
			{
				ca++;

				if (*ca)
				{
					if (*ca == '-') curarg++;
					else
					{
						curopt = ca;

						goto parseopt;
					}
				}
			}
		}

		curopt = NULL;
		notopt = curarg;
		curarg = NULL;

		return NULL;
	}
	else
	{
		notopt = NULL;

		if (argv == NULL) return NULL;

		curarg = argv + 1;

		goto parsearg;
	}
}