#include "mtt/cmd_line.h"
#include "mtt/str.h"
#include <iostream>

int main(int argc, char *argv[])
{
	mtt::opt_t optv[] = {
		{ 'f', mtt::opt_t::REQUIRED_ARG },
		{ 's', mtt::opt_t::NO_ARG },
		{ 'l', mtt::opt_t::NO_ARG },
		{ 't', mtt::opt_t::REQUIRED_ARG }
	};

	char **av = argv + mtt::extr_optv(argc, argv, 4, optv);
	mtt::fstr_to_ival_fmt_t opt('+', 0, ' ', 10, opt.LEFT_FILL);
	mtt::fstr_to_ival_fmt_t from('+', '-', ' ', 10, from.LEFT_FILL | from.UNK_CASE);
	mtt::ival_to_fstr_fmt_t to(0, 0, ' ', 16, to.LEFT_FILL | to.UPPERCASE, 0);

	from.set_base(opt.conv(optv[0].arg));

	if (optv[1].arg) to.minus = '-';

	if (optv[2].arg) to.fs |= to.LOWERCASE;

	to.set_base(opt.conv(optv[3].arg));

	char **avc = argv + argc;

	while (av < avc)
	{
		char fstr[128];

		to.conv(fstr, from.conv(*av));
		av++;
		std::cout << fstr << std::endl;
	}

	return 0;
}