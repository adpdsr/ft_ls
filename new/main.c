/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 09:49:07 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/10 14:33:47 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h> // test

static void	count_total(t_lst *lst)
{
	int res;

	res = 0;
	while (lst)
	{
		res += lst->blok;
		lst = lst->next;
	}
	ft_putstr("total ");
	ft_putnbr_endl(res);
}

void	display_llst(t_lst *lst, int ghost)
{
	t_lst *tmp;

	tmp = lst;
	count_total(lst);
	if (!ghost)
	{
		while (tmp)
		{
			if (ft_strncmp(tmp->name, ".", 1))
			{
				ft_putstr_s(tmp->perm);
				ft_putstr_s(tmp->link);
				ft_putstr_s(tmp->user_id);
				ft_putstr_s(tmp->group_id);
				ft_putstr_s(tmp->size);
				ft_putstr_s(tmp->date);
				ft_putendl(tmp->name);
			}
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp)
		{
			ft_putstr_s(tmp->perm);
			ft_putstr_s(tmp->link);
			ft_putstr_s(tmp->user_id);
			ft_putstr_s(tmp->group_id);
			ft_putstr_s(tmp->size);
			ft_putstr_s(tmp->date);
			ft_putendl(tmp->name);
			tmp = tmp->next;
		}
	}
	lst->next = NULL;
}

static void	display_rlst(t_lst *lst, int ghost)
{
	if (ghost)
	{
		if (lst)
		{
			display_rlst(lst->next, ghost);
			ft_putendl(lst->name);
		}
	}
	else
	{
		if (lst)
		{
			display_rlst(lst->next, ghost);
			if (ft_strncmp(lst->name, ".", 1))
				ft_putendl(lst->name);	
		}
	}
}

static void	display_rllst(t_lst *lst, int ghost)
{
	if (ghost)
	{
		if (lst)
		{
			display_rllst(lst->next, ghost);
			ft_putstr_s(lst->perm);
			ft_putstr_s(lst->link);
			ft_putstr_s(lst->user_id);
			ft_putstr_s(lst->group_id);
			ft_putstr_s(lst->size);
			ft_putstr_s(lst->date);
			ft_putendl(lst->name);
		}
	}
	else
	{
		if (lst)
		{
			display_rllst(lst->next, ghost);
			if (ft_strncmp(lst->name, ".", 1))
			{	
				ft_putstr_s(lst->perm);
				ft_putstr_s(lst->link);
				ft_putstr_s(lst->user_id);
				ft_putstr_s(lst->group_id);
				ft_putstr_s(lst->size);
				ft_putstr_s(lst->date);
				ft_putendl(lst->name);
			}
		}
	}
}

void	display_lst(t_lst *lst, int ghost)
{
	t_lst *tmp;

	tmp = lst;
	if (!ghost)
	{
		while (tmp)
		{
			if (ft_strncmp(tmp->name, ".", 1))
				ft_putendl(tmp->name);
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp)
		{
			ft_putendl(tmp->name);
			tmp = tmp->next;
		}
	}
	lst->next = NULL;
}

char	*add_slash(char *path)
{
	if (path[ft_strlen(path) - 1] != '/')
		path = ft_strjoin(path, "/");
	return (path);
}

static void get_perm(struct stat *st, t_lst *lst)
{
	ft_bzero(lst->perm, 11);
	lst->perm[0] = (S_ISDIR(st->st_mode)) ? 'd' : '-';
	lst->perm[1] = (st->st_mode & S_IRUSR) ? 'r' : '-';
	lst->perm[2] = (st->st_mode & S_IWUSR) ? 'w' : '-';
	lst->perm[3] = (st->st_mode & S_IXUSR) ? 'x' : '-';
	lst->perm[4] = (st->st_mode & S_IRGRP) ? 'r' : '-';
	lst->perm[5] = (st->st_mode & S_IWGRP) ? 'w' : '-';
	lst->perm[6] = (st->st_mode & S_IXGRP) ? 'x' : '-';
	lst->perm[7] = (st->st_mode & S_IROTH) ? 'r' : '-';
	lst->perm[8] = (st->st_mode & S_IWOTH) ? 'w' : '-';
	lst->perm[9] = (st->st_mode & S_IXOTH) ? 'x' : '-';
}

static void	fill_info(struct stat st, t_lst *new, char *file)
{
	new->name = file;
	new->date = ft_strsub(ctime(&st.st_mtime), 4, 12);
	new->date_id = (int)st.st_mtime;
	new->link = ft_itoa(st.st_nlink);
	new->size = format_size(ft_itoa(st.st_size));
	new->blok = st.st_blocks;
	get_perm(&st, new);
	new->next = NULL;
}

t_lst	*get_info(t_lst *head, char *file, char *path)
{
	struct stat		st;
	t_lst			*new;
	t_lst			*ptr;

	new = (t_lst *)malloc(sizeof(t_lst));
	ptr = head;
	if (lstat(path, &st) <= 0)
	{
		fill_info(st, new, file);
		if (getpwuid(st.st_uid))
			new->user_id = ft_strdup(getpwuid(st.st_uid)->pw_name);
		if (getgrgid(st.st_gid))
			new->group_id = ft_strdup(getgrgid(st.st_gid)->gr_name);
	}
	if (head == NULL)
		return (new);
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	return (head);
}

void	manage_opt(t_lst *lst, t_opt *opt)
{
	int ghost;

	if (!opt || (opt->l == 0 && opt->R == 0 && opt->a == 0 && opt->r == 0 && opt->t == 0))
		display_lst(lst, 0);
	else
	{
		if (opt->t)
			lst = lst_sort_time(lst);
		if (opt->a)
			ghost = 1;
		if (opt->r && opt->l)
		{
			printf("r + l\n");
			count_total(lst);
			display_rllst(lst, ghost);
			printf("END\n");
		}
		else if (opt->r)
		{
			printf("r\n");
			display_rlst(lst, ghost);
			printf("END\n");
		}
		if (opt->l && (!opt->r))
		{
			printf("l\n");
			display_llst(lst, ghost);
			printf("END\n");
		}
		else if (lst && opt->a && (!opt->r))
		{
			printf("lst && a\n");
			display_lst(lst, ghost);
			printf("END\n");
		}
		else if (lst && (!opt->a) && (!opt->r))
		{
			printf("lst && !a\n");
			display_lst(lst, ghost);
			printf("END\n");
		}
	}
}

void	get_param(char *path, t_opt *opt)
{
	DIR 			*dir;
	struct dirent	*ret;
	t_lst 			*lst;

	if (!(dir = opendir(path)))
		exit(1);
	if (!(lst = (t_lst *)malloc(sizeof(t_lst))))
		exit(1);
	lst = NULL;
	while ((ret = readdir(dir)))
		lst = get_info(lst, ret->d_name, ft_strjoin(path, ret->d_name));
	lst_sort_ascii(lst);
	if (opt && opt->l)
		padding(lst);
	manage_opt(lst, opt);
	closedir(dir);
}

int		main(int ac, char **av)
{
	int		i;
	char	*path;
	t_opt	opt;

	i = 1;
	path = NULL;
	init_opt(&opt);
	while (i < ac)
	{
		if (av[i][0] == '-')
			get_opt(av[i], &opt);
		else
		{
			path = av[i];
			get_param(add_slash(path), &opt);
			if (av[i + 1])
				ft_putchar('\n');
		}
		i++;
	}
	if (path == NULL)
		get_param("./", &opt);
	return (0);
}
