/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 11:16:26 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/10 17:46:38 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	put_path(char **dirs, char *path, int i)
{
	ft_putchar('\n');
	ft_putstr(ft_strjoin(path, dirs[i]));
	ft_putstr(":\n");
}

static void	cpy_dir(char **dirs, t_lst *lst, t_opt *opt)
{
	int i;

	i = 0;
	while (lst)
	{
		if (lst->is_dir == 1)
		{
			if (opt->a == 0 && lst->name[0] != '.')
			{
				dirs[i] = ft_strdup(lst->name);
				i++;
			}
			else if (opt->a != 0)
			{
				dirs[i] = ft_strdup(lst->name);
				i++;
			}
		}
		lst = lst->next;
	}
	dirs[i] = NULL;
}

static void	r_on(char **dirs, char *path, int nb_dir, t_opt *opt)
{
	int j;

	j = nb_dir - 1;
	while (j > -1)
	{
		if (dirs[j] != NULL)
		{
			put_path(dirs, path, j);
			get_param(ft_strjoin(path, add_slash(dirs[j])), opt);
		}
		j--;
	}
}

void		recursive(char *path, t_lst *lst, t_opt *opt)
{
	char			**dirs;
	int				i;
	int				nb_dir;

	i = -1;
	nb_dir = count_dir(lst, opt);
	if (!(dirs = (char **)malloc(sizeof(char *) * (nb_dir + 1))))
		exit(1);
	cpy_dir(dirs, lst, opt);
	if (opt->r == 0)
		while (++i < nb_dir)
		{
			if (dirs[i])
			{
				put_path(dirs, path, i);
				get_param(ft_strjoin(path, add_slash(dirs[i])), opt);
			}
			else
				break ;
		}
	else if (opt->r == 1)
		r_on(dirs, path, nb_dir, opt);
	ft_freetab(dirs);
	opt->big_r = 1;
}
