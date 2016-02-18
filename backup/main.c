/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 09:49:07 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/18 11:18:17 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h> // test

char	*add_slash(char *path)
{
	if (path[ft_strlen(path) - 1] != '/')
		path = ft_strjoin(path, "/");
	return (path);
}

char	*remove_slash(char *path)
{
	if (path[ft_strlen(path - 1)] == '/')
		path[ft_strlen(path) - 1] = '\0';
	return (path);
}

static char	get_file_type(struct stat *st, t_lst *lst)
{
	char c;

	if (S_ISDIR(st->st_mode)) // directory
		c = 'd';
	else if (S_ISLNK(st->st_mode)) // sym link
		c = 'l';
	else if (S_ISCHR(st->st_mode)) // character special
		c = 'c';
	else if (S_ISBLK(st->st_mode)) // block special
		c = 'b';
	else if (S_ISFIFO(st->st_mode)) // named pipe (fifo)
		c = 'p';
	else if (S_ISSOCK(st->st_mode)) // socket
		c = 's';
	else
		c = '-';
	return (c);
}

static void get_perm(struct stat *st, t_lst *lst)
{
	ft_bzero(lst->perm, 11);
	lst->perm[0] = get_file_type(st, lst);
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
	new->maj = ft_strjoin(ft_itoa(major(st.st_rdev)), ",");
	new->min = ft_itoa(minor(st.st_rdev));
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
	int hidd;

	hidd = 0;
	if (!opt || (opt->l == 0 && opt->R == 0 && opt->a == 0 && opt->r == 0 && opt->t == 0))
		display_lst(lst, 0);
	else
	{
		if (opt->a)
			hidd = 1;
		if (opt->t)
			lst = lst_sort_time(lst);
		if (opt->r && opt->l)
		{
			put_total(lst, hidd);
			display_rllst(lst, hidd);
		}
		else if (opt->r)
			display_rlst(lst, hidd);
		if (opt->l && (!opt->r))
		{
			put_total(lst, hidd);
			display_llst(lst, hidd);
		}
		else if (lst && opt->a && (!opt->r))
			display_lst(lst, hidd);
		else if (lst && (!opt->a) && (!opt->r))
			display_lst(lst, hidd);
	}
}

void	get_param(char *path, t_opt *opt)
{
	DIR 			*dir;
	struct dirent	*ret;
	t_lst 			*lst;

	if (!(dir = opendir(path)))
	{
		ft_putstr("ls: ");
		perror(remove_slash(path));
		exit(1);
	}
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

/*
void	sort_args(int ac, char **av)
{
	int i;
	int j;
	char *tmp;

	j = 0;
	while (j < ac)
	{
		i = 0;
		while ((i + 1)  < ac)
		{
			if (ft_strcmp(*(av[i]), *(av[i + 1])) > 0)
			{
				tmp = ft_strdup(*(av[i]));
				free(*(av[i]));
				*(av[i]) = ft_strdup(*(av[i + 1]));
				free(*(av[i + 1]));
				*(av[i + 1]) = ft_strdup(tmp);
				free(tmp);
			}
			i++;
		}
		j++;
	}
}
*/

int		main(int ac, char **av)
{
	int	i;
	char	*path;
	t_opt	opt;

	i = 1;
	path = NULL;
	init_opt(&opt);
	// sort_args(int ac, char **av)
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
