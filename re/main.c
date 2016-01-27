//
// HEADER
//

#include "ft_ls.h"
#include <stdio.h> // test

int	main(int ac, char **av)
{
	int i;
	t_list *arg;
	t_opt *opt;

	if (ac)
	{
		i = 1;
		if (av[i][0] == '-' && av[i][1])
			if (get_opt(av[i]))
				return (1);
		while (av[i++])
			get_param(av[i]);
	}
	else
	{
		printf("--- AC = 0 ---\n");
		return (0);
	}
	return (0);
}
