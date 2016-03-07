/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 09:49:07 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/07 14:37:15 by adu-pelo         ###   ########.fr       */
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

static void		put_path(char **dirs, char *path, t_opt *opt, int i)
{
	ft_putchar('\n');
	ft_putstr(ft_strjoin(path, dirs[i]));
	ft_putstr(":\n");
}

static void		recursive(char *path, t_lst *lst, t_opt *opt)
{
	char			**dirs;
	int				i;
	int				j;
	int				nb_dir;

	i = 0;
	nb_dir = count_dir(&lst);
	if (!(dirs = (char **)malloc(sizeof(char *) * (nb_dir + 1))))
		exit(1);
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
	if (opt->r == 0)
	{
		i = -1;
		while (++i < nb_dir)
		{
			if (dirs[i])
			{
				put_path(dirs, path, opt, i);
				get_param(ft_strjoin(path, add_slash(dirs[i])), opt);
			}
			else
				break ;
		}
	}
	else if (opt->r == 1)
	{
		j = nb_dir - 1;
		if (j > -1)
		{
			while (j > -1)
			{
				if (dirs[j] != NULL)
				{
					put_path(dirs, path, opt, j);
					get_param(ft_strjoin(path, add_slash(dirs[j])), opt);
				}
				j--;
			}
		}
	}
	free_tab(dirs);
	opt->R = 1;
}

void			manage_opt(t_lst *lst, t_opt *opt, char *path)
{
	int hidd;

	hidd = 0;
	lst = lst_sort_ascii(lst);
	if (!opt || (opt->l == 0 && opt->R == 0 && opt->a == 0 && opt->r == 0 && opt->t == 0))
		display_lst(lst, hidd);
	else
	{
		if (opt->a)
			hidd = 1;
		if (opt->t)
			lst = lst_sort_time(lst);
		if (opt->r && opt->l)
		{
			if (lst->next)
				put_total(lst, hidd);
			display_rllst(lst, hidd);
		}
		else if (opt->r)
			display_rlst(lst, hidd);
		if (opt->l && (!opt->r))
		{
			if (lst->next)
				put_total(lst, hidd);
			display_llst(lst, hidd);
		}
		else if (lst && opt->a && (!opt->r))
			display_lst(lst, hidd);
		else if (lst && (!opt->a) && (!opt->r))
			display_lst(lst, hidd);
		if (lst && opt->R)
			recursive(path, lst, opt);
	}
}

void			get_param(char *path, t_opt *opt)
{
	DIR 			*dir;
	struct dirent	*ret;
	t_lst 			*lst;
	t_pad			*pad;
	int				is_file;

	is_file = 0;
	if (!(pad = (t_pad *)malloc(sizeof(t_pad))))
		exit(1);
	if (!(lst = (t_lst *)malloc(sizeof(t_lst))))
		exit(1);
	lst = NULL;
	if (!(dir = opendir(path)))
	{
		lst = manage_av_file(path, lst, dir);
		if (!lst)
		{
			ft_putstr("error : ");
			ft_putendl(path);
			ft_putstr("ft_ls: ");
			perror(path);
			return ;
		}
		else if (lst->perm[0] == 'd' && lst->perm[1] == '-')
		{
			ft_putstr("ft_ls: ");
			ft_putstr(path);
			ft_putendl(": Permission denied");
			return ;
		}
		is_file = 1;
	}
	else if (is_file == 0)
	{
		while ((ret = readdir(dir)))
			lst = get_info(lst, ret->d_name, ft_strjoin(add_slash(path), ret->d_name));
		closedir(dir);
	}
	padding(&lst, pad);
	manage_opt(lst, opt, path);
	if (!opt->R && !lst->next)
		free_lst(&lst);
	else if (!opt->R && lst)
		free_lst(&lst);
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
		i = 0;
		if (ac > 1)
		{
			while (i < ac - flag)
			{
				if (!ft_strcmp(av[i], ""))
				{
					ft_putendl("ft_ls: fts_open: No such file or directory");
					exit(0);
				}
				i++;
			}
			i = 0;
			while (i < ac - flag)
			{
				path = av[i];
				if (ac - flag > 1 && is_what(path) == 1)
				{
					if (put_space)
						ft_putchar('\n');
					ft_putstr(path);
					ft_putendl(":");
				}
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
