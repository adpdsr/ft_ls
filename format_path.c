/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 11:35:54 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/17 15:02:51 by adu-pelo         ###   ########.fr       */
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
		i = ft_strlen(path) - 1;
		if (path[i] == '/')
			return (NULL);
		else
		{
			tmp = ft_strdup(path);
			printf("tmp : %s\n", tmp);
			while (tmp[i] != '/' && i > 0)
				i--;
			printf("i = %d\n", i);
			if (i == 0)
			{
				tmp = ft_strdup("./");
				//tmp = ft_strdup(path);
				printf("ret1 : %s\n", tmp);	
				//tmp = ft_strjoin(tmp, path);
				//free(path);
				return (tmp);
			}
			else
			{
				tmp = add_slash(ft_strndup(path, i));
				printf("ret2 : %s\n", tmp);	
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

	printf("path     : %s\n", path);
	formated = format_path(path);
	printf("formated : %s\n", formated);
	if (formated != NULL)
	{
		printf("formated != NULL\n");
		formated = ft_strdup(format_path(path));
	}
	if (formated == NULL)
	{
		printf("formated is NULL\n");
		ft_putstr("ft_ls: ");
		perror(remove_slash(path));
		exit(1);
	}
	if (!(dir = opendir(formated)))
	{
		printf("opendir failed\n");
		ft_putstr("ft_ls: ");
		perror(remove_slash(path));
		exit(1);
	}
	else
	{
		file_name = get_file_name(path);
		printf("file name : %send\n", file_name);
		while ((ret = readdir(dir)))
		{
			printf("BOUCLE\n");
			if ((ft_strcmp(ret->d_name, file_name) == 0)) // si match
			{
				lst = get_info(lst, ret->d_name, path);
				printf("lst : %s\nuid : %s\n", lst->name, lst->user_id);
				break;
			}
		}
		if (!lst)
		{
			printf("lst is NULL\n");
			return (NULL);
		}
		return (lst);
	}
	return (NULL);
}
