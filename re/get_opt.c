//

// HEADER

//


// ls -lllRRRRRRR marche ?

#include "ft_ls.h"

void	init_opt(t_opt *opt)
{
	opt->l = 0;
	opt->R = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
}

void	print_opt(t_opt *opt) // test
{
	ft_putendl("--- OPT SAVED ---\n");
	printf("l is -> %d\n", opt->l);
	printf("R is -> %d\n", opt->R);
	printf("a is -> %d\n", opt->a);
	printf("r is -> %d\n", opt->r);
	printf("t is -> %d\n", opt->t);
	if (opt->err)
		printf("error is -> %d\n", opt->err);
}

static void err_opt(t_opt *opt)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(opt->err, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("usage: ft_ls [-Ralrt] [file ...]\n", 2);
	exit(EXIT_FAILURE);
}

static int valid_opt(char c)
{
	return ((c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't'));
}

int	get_opt(char *str, t_opt *opt)
{
	int i;

	i = 1;
	init_opt(opt);
	while (str[i] && valid_opt(str[i]))
	{
		if (str[i] == 'l')
			opt->l = 1;
		if (str[i] == 'R')
			opt->R = 1;
		if (str[i] == 'a')
			opt->a = 1;
		if (str[i] == 'r')
			opt->r = 1;
		if (str[i] == 't')
			opt->t = 1;
		i++;
	}
	if (str[i])
	{
		opt->err = str[i];
		err_opt(opt); // return (-1)
	}
	print_opt(opt);
	return (0);
}
