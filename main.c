/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 09:49:07 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/17 15:02:49 by adu-pelo         ###   ########.fr       */
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
	new->is_dir = (new->perm[0] == 'd' && ft_strcmp(new->name, ".") && ft_strcmp(new->name, ".."));
	new->next = NULL;
}

static int	count_dir(t_lst *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		if (lst->is_dir)
			i++;
		lst = lst->next;
	}
	return (i);
}

t_lst	*get_info(t_lst *head, char *file, char *path)
{
	struct stat		st;
	t_lst			*new;
	t_lst			*ptr;

	new = (t_lst *)malloc(sizeof(t_lst));
	ptr = head;
	printf("get info path :%s\n", path);
	printf("get info file :%s\n", file);
	if (lstat(path, &st) <= 0)
	{
		fill_info(st, new, file);
		printf("TEST7\n");
		if (getpwuid(st.st_uid))
			new->user_id = ft_strdup(getpwuid(st.st_uid)->pw_name);
		printf("TEST8\n");
		if (getgrgid(st.st_gid))
			new->group_id = ft_strdup(getgrgid(st.st_gid)->gr_name);
		printf("TEST9\n");
	}
	if (head == NULL)
		return (new);
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	return (head);
}

static void recursive(char *path, t_lst *lst, t_opt *opt, int nb_dir)
{
	char			**all_dir;
	int				i;

	i = 0;
	if (!(all_dir = (char **)malloc(sizeof(char *) * nb_dir + 1)))
		exit(1);
	all_dir[nb_dir + 1] = NULL;
	while (lst != NULL)
	{
		if (lst->is_dir == 1)
		{
			if (opt->a == 0)
			{
				all_dir[i] = ft_strdup(lst->name);
				i++;
			}
			//else if (opt->a != 0 && ft_strncmp(lst->name, ".", 1))
			//{

			//}
		}
		lst = lst->next;
	}
	// trier tableau par ordre en fn des options
	i = -1;
	while (++i < nb_dir)
	{
		if (all_dir[i][0] == '.' && opt->a)
		{
			ft_putchar('\n');
			ft_putstr(ft_strjoin(path, all_dir[i]));
			ft_putstr(":\n");
		}
		else if (all_dir[i][0] != '.')
		{
			ft_putchar('\n');
			ft_putstr(ft_strjoin(path, all_dir[i]));
			ft_putstr(":\n");
		}
		get_param(ft_strjoin(path, add_slash(all_dir[i])), opt);
	}
}

void	manage_opt(t_lst *lst, t_opt *opt, char *path)
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
		if (lst && opt->R)
			recursive(path, lst, opt, count_dir(lst));
	}
}

void	get_param(char *path, t_opt *opt)
{
	DIR 			*dir;
	struct dirent	*ret;
	t_lst 			*lst;
	int				is_file;

	is_file = 0;
	if (!(lst = (t_lst *)malloc(sizeof(t_lst))))
		exit(1);
	lst = NULL;
	if (!(dir = opendir(path)))
	{
		lst = manage_av_file(path, lst, dir);
		printf("asdasd\n");
		//printf("lst = %s\n", lst->name);
		//printf("asdasd\n");
		if (lst == NULL)
		{
			ft_putstr("ft_ls: ");
			perror(remove_slash(path));
			exit(1);
		}
		is_file = 1;
	}
	printf("TEST1\n");
	if (is_file == 0)
	{
	printf("TEST2\n");
		while ((ret = readdir(dir)))
			lst = get_info(lst, ret->d_name, ft_strjoin(add_slash(path), ret->d_name));
		lst_sort_ascii(lst);
	}
	printf("TEST3\n");
	if (opt && opt->l)
	{
		printf("lst : %s\nuid : %s\n", lst->name, lst->user_id);
		printf("TEST4\n");
		printf("TEST5\n");
	padding(lst);
	}
	printf("TEST6\n");
	manage_opt(lst, opt, path);
	//closedir(dir);
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
			get_param(path, &opt);
			if (av[i + 1])
				ft_putchar('\n');
		}
		i++;
	}
	if (path == NULL)
		get_param("./", &opt);
	return (0);
}
