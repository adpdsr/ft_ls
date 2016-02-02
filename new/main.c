/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 09:49:07 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/02 12:26:13 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	display_llst(t_lst *lst)
{
	t_lst *tmp;

	tmp = lst->next;
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

static void	fill_info(struct stat st, t_lst *lst, char *path, char *file)
{
	struct passwd	*pwd;
	struct group	*grp;

	if ((pwd = getpwuid(st.st_uid)))
		lst->user_id = ft_strdup(pwd->pw_name);
	if ((grp = getgrgid(st.st_gid)))
		lst->group_id = ft_strdup(grp->gr_name);
	lst->chem = path;
	lst->name = file;
	lst->date = ft_strsub(ctime(&st.st_mtime), 4, 12);
	lst->link = ft_itoa(st.st_nlink);
	lst->size = ft_itoa(st.st_size);
	lst->blok = st.st_blocks;
	get_perm(&st, lst);
}

t_lst	*get_info(t_lst *start, char *file, char *path)
{
	struct stat	st;
	t_lst	*tmp;
	t_lst	*ptr;

	tmp = (t_lst *)malloc(sizeof(t_lst));
	tmp->next = NULL;
	ptr = start;
	if (stat(path, &st) == 1)
		exit(1);
	if (lstat(path, &st) <= 0)
		fill_info(st, tmp, path, file);
	if (start == NULL)
		return (tmp);
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = tmp;
	return (tmp);
}

void	get_param(char *path)
{
	int				total;
	DIR 			*dir;
	struct dirent	*ret;
	t_lst 			*lst;
	t_lst			*start;

	if (!(dir = opendir(path)))
	{
		ft_putendl("error opening file");
		exit(1);
	}
	if (!(lst = (t_lst *)malloc(sizeof(t_lst))))
	{
		ft_putendl("error malloc lst");
		exit(1);
	}
	start = lst;
	lst->next = NULL;
	while ((ret = readdir(dir)))
	{
		lst = get_info(lst, ret->d_name, ft_strjoin(path, ret->d_name));
		lst = start;
	}
	count_total(lst);
	padding(lst);
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
			i++;
		}
	}
	else
		get_param("./");
	return (0);
}
