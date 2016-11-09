/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 09:49:07 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/10 17:18:55 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		check_void_av(int ac, char **av, int flag)
{
	int i;

	i = 0;
	while (i < ac - flag)
	{
		if (!ft_strcmp(av[i], ""))
		{
			ft_putendl_fd("ft_ls: fts_open: No such file or directory", 2);
			exit(0);
		}
		i++;
	}
}

static void		put_head(char *path, int ac, int flag, int put_space)
{
	if (ac - flag > 1 && is_what(path) == 1)
	{
		if (put_space)
			ft_putchar('\n');
		ft_putstr(path);
		ft_putendl(":");
	}
}

static int		check_opt(char **av, t_opt *opt, int flag)
{
	int i;

	i = 1;
	while (av[i] && av[i][0] == '-' && av[i][1] != '\0')
	{
		get_opt(av[i], opt);
		flag++;
		i++;
	}
	return (flag);
}

int				main(int ac, char **av)
{
	int		i;
	int		flag;
	char	*path;
	t_opt	opt;

	flag = 1;
	path = NULL;
	init_opt(&opt);
	if (ac > 1)
	{
		flag = check_opt(av, &opt, flag);
		if ((i = -1) && ac > flag)
			av = create_tab(av, &opt, ac, flag);
		check_void_av(ac, av, flag);
		while (++i < ac - flag && (path = av[i]))
		{
			put_head(path, ac, flag, i);
			get_param(path, &opt);
		}
	}
	if (!path)
		get_param("./", &opt);
	else
		ft_freetab(av);
	return (0);
}
