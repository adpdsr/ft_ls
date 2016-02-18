/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 11:35:54 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/17 18:26:27 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h> // test

static char *get_file_name(char *path)
{
	int end;
	int start;
	char *tmp;

	end = ft_strlen(path) - 1;
	start = end;
	while (path[start] != '/' && start > 0)
		start--;
	if (start == 0)
		tmp = ft_strsub(path, start, end + 1);
	else
		tmp = ft_strsub(path, start + 1, end);
	return (tmp);
}

static char *format_path(char *path)
{
	int	i;
	char	*tmp;

	if (path)
	{
		//printf("path = %s\n", path);
		//remove_slash(path);
		//printf("path = %s\n", path);
		i = ft_strlen(path) - 1;
		if (path[i] == '/')
		{
		//	printf("slash a la fin\n");
			return (NULL);
		}
		else
		{
			tmp = ft_strdup(path);
			while (tmp[i] != '/' && i > 0)
				i--;
			if (i == 0)
			{
				tmp = ft_strdup("./");
				//free(path);
				return (tmp);
			}
			else
			{
				tmp = add_slash(ft_strndup(path, i));
				//free(path);
				return (tmp);
			}
		}
	}
	else
		return (NULL);
}

t_lst	*manage_av_file(char *path, t_lst *lst, DIR *dir)
{
	char *formated;
	char *file_name;
	struct dirent *ret;

	//printf("path im manage file : %s\n", path);
	formated = format_path(path);
	//printf("formated : %s\n", formated);
	if (formated == NULL)
	{
		ft_putstr("ft_ls: ");
		perror(remove_slash(path));
		exit(1);
	}
	else
		formated = ft_strdup(format_path(path));
	if (!(dir = opendir(formated)))
	{
	//	printf("test\n");
		ft_putstr("ft_ls: ");
		perror(remove_slash(path));
	//	printf("test2\n");
		exit(1);
	}
	file_name = get_file_name(path);
	//printf("file_name : %s\n", file_name);
	while ((ret = readdir(dir)))
	{
	//printf("\n");
	//printf("ret->d_name : %s\nfile_name : %s\n", ret->d_name, file_name);
	//printf("\n");
		if ((ft_strcmp(ret->d_name, file_name) == 0)) // si match
		{
			lst = get_info(lst, ret->d_name, path);
	//		printf("lst : %s\n", lst->name);
			break;
		}
	}
	if (!lst)
	{
	//	printf("lst is NULL\n");
		return (NULL);
	}
	//printf("ret list\n");
	return (lst);
}
