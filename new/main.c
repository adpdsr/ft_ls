/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 09:49:07 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/05 14:24:09 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	display_llst(t_lst *lst)
{
	t_lst *tmp;

	tmp = lst;
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
	lst->next = NULL;
}

char	*add_slash(char *path)
{
	if (path[ft_strlen(path) - 1] != '/')
		path = ft_strjoin(path, "/");
	return (path);
}

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
	//lst->chem = path;
	new->name = file;
	new->date = ft_strsub(ctime(&st.st_mtime), 4, 12);
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

void	get_param(char *path)
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
	count_total(lst);
	padding(lst);

	lst_sort_ascii(lst);

	display_llst(lst);
	closedir(dir);
}

int		main(int ac, char **av)
{
	int i;
	t_opt opt;

	if (ac > 1)
	{
		i = 1;
		if (av[i][0] == '-' && av[i][1])
		{
			get_opt(av[i], &opt);
			i = 2;
		}
		while (av[i])
		{
			get_param(add_slash(av[i])); // add opt
			if (av[i + 1])
				ft_putchar('\n');
			i++;
		}
	}
	else
		get_param("./");
	return (0);
}
