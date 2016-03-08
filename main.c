/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 09:49:07 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/08 14:33:12 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_lst			*get_info(t_lst *head, char *file, char *path)
{
	struct stat		st;
	t_lst			*new;
	t_lst			*ptr;

	if (!(new = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	ptr = head;
	if (lstat(path, &st) <= 0)
		fill_info(st, new, file);
	if (head == NULL)
		return (new);
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	return (head);
}

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

static void		put_head(char *path, int ac, int flag, int flag)
{
	if (ac - flag > 1 && is_what(path) == 1)
	{
		if (put_space)
			ft_putchar('\n');
		ft_putstr(path);
		ft_putendl(":");
	}

}

int				main(int ac, char **av)
{
	int		i;
	int		flag;
	int		put_space;
	char	*path;
	t_opt	opt;

	i = 1;
	flag = 1;
	path = NULL;
	put_space = 0;
	init_opt(&opt);
	if (ac > 1)
	{
		while (av[i] && av[i][0] == '-' && av[i][1])
		{
			get_opt(av[i], &opt);
			flag++;
			i++;
		}
		if (ac > flag)
			av = create_tab(av, &opt, ac, flag);
		if (ac > 1)
		{
			i = 0;
			check_void_av(ac, av, flag);
			while (i < ac - flag)
			{
				path = av[i];
				put_head(path, ac, flag, put_space);
				get_param(path, &opt);
				put_space = 1;
				i++;
			}
		}
	}
	if (!path)
		get_param("./", &opt);
	else
		free_tab(av);
	return (0);
}
