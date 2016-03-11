/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 11:35:54 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/10 17:16:44 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	put_error(char *path)
{
	ft_putstr_fd("ft_ls: ", 2);
	perror(remove_slash(path));
	exit(1);
}

static char	*get_file_name(char *path)
{
	int		end;
	int		start;
	char	*tmp;

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

static char	*format_path(char *path)
{
	int		i;
	char	*tmp;

	if (path)
	{
		i = ft_strlen(path) - 1;
		if (path[i] == '/')
			return (NULL);
		else
		{
			tmp = ft_strdup(path);
			while (tmp[i] != '/' && i > 0)
				i--;
			if (i == 0)
				tmp = ft_strdup("./");
			else
				tmp = add_slash(ft_strndup(path, i));
			return (tmp);
		}
	}
	else
		return (NULL);
}

t_lst		*manage_av_file(char *path, t_lst *lst, DIR *dir)
{
	char			*formated;
	char			*file_name;
	struct dirent	*ret;

	formated = format_path(path);
	if (!formated)
		return (NULL);
	if (!(dir = opendir(formated)))
		put_error(path);
	else
	{
		file_name = get_file_name(path);
		while ((ret = readdir(dir)))
			if ((ft_strcmp(ret->d_name, file_name) == 0))
			{
				lst = get_info(lst, ret->d_name, path);
				break ;
			}
		if (!lst)
			return (NULL);
		closedir(dir);
		return (lst);
	}
	return (NULL);
}
