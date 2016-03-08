/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 09:49:07 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/08 16:22:30 by adu-pelo         ###   ########.fr       */
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
			ft_putendl("ft_ls: fts_open: No such file or directory");
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
	while (av[i] && av[i][0] == '-' && av[i][1])
	{
		get_opt(av[i], opt);
		flag++;
		i++;
	}
	return (flag);
}

static void		get_args(int ac, char *path, int flag, t_opt *opt)
{
	int i;

	i = 0;
	put_head(path, ac, flag, i);
	if (i == 0)
		i = 1;
	get_param(path, opt);
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
		if (ac > flag)
			av = create_tab(av, &opt, ac, flag);
		i = -1;
		check_void_av(ac, av, flag);
		while (++i < ac - flag && (path = av[i]))
			get_args(ac, path, flag, &opt);
	}
	if (!path)
		get_param("./", &opt);
	else
		free_tab(av);
	return (0);
}
