/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 09:49:07 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/01/28 18:51:30 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h> // printf

char	*add_slash(char *path)
{
	int i;

	i = ft_strlen(path);
	i--;
	if (path[i] != '/')
		path = ft_strjoin(path, "/");
	ft_putendl(path); // test
	return (path);
}

static void get_perm(struct stat *st, t_lst *elem)
{
	ft_memset(elem->perm, 0, 11);
	elem->perm[0] = (S_ISDIR(st->st_mode)) ? 'd' : '-';
	elem->perm[1] = (st->st_mode & S_IRUSR) ? 'r' : '-';
	elem->perm[2] = (st->st_mode & S_IWUSR) ? 'w' : '-';
	elem->perm[3] = (st->st_mode & S_IXUSR) ? 'x' : '-';
	elem->perm[4] = (st->st_mode & S_IRGRP) ? 'r' : '-';
	elem->perm[5] = (st->st_mode & S_IWGRP) ? 'w' : '-';
	elem->perm[6] = (st->st_mode & S_IXGRP) ? 'x' : '-';
	elem->perm[7] = (st->st_mode & S_IROTH) ? 'r' : '-';
	elem->perm[8] = (st->st_mode & S_IWOTH) ? 'w' : '-';
	elem->perm[9] = (st->st_mode & S_IXOTH) ? 'x' : '-';
}

t_lst	*get_info(t_lst *start, char *file, char *path)
{
	struct stat st;
	t_lst	*tmp;
	t_lst	*ptr;

	tmp = (t_lst *)malloc(sizeof(t_lst));
	ptr = start;
	if (stat(path, &st) == 1)
	{	
		ft_putendl("fail to get stats");
		exit(EXIT_FAILURE);
	}
	if (lstat(path, &st) <= 0)
	{
		//get_perm(st, tmp);
		tmp->date = ctime(&st.st_mtime);
		ft_putendl(tmp->date);
		//ft_putendl(tmp->perm);
		ft_putchar('\n');
	}
	if (start == NULL)
		return (tmp);
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = tmp;
	return (tmp);
}

void	get_param(char *path)
{
	DIR 			*dir;
	struct dirent	*ret;
	t_lst 			*lst;

	if (!(dir = opendir(path)))
	{
		ft_putendl("error opening file");
		exit(EXIT_FAILURE);
	}
	if (!(lst = (t_lst *)malloc(sizeof(t_lst))))
	{
		ft_putendl("error malloc lst");
		exit(EXIT_FAILURE);
	}
	lst = NULL;
	while ((ret = readdir(dir)))
	{
		printf ("name = %s\n", ret->d_name);
		printf("path = %s\n", ft_strjoin(path, ret->d_name));
		lst = get_info(lst, ret->d_name, ft_strjoin(path, ret->d_name));
	}
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
	{
		ft_putendl("--- AC = 0 ---");
		get_param("./"); // add opt
	}
	return (0);
}
