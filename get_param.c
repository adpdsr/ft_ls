/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 16:21:37 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/10 17:52:16 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		error(char *path)
{
	ft_putstr_fd("ft_ls: ", 2);
	path = get_path(path);
	perror(path);
	return (1);
}

static int		error_r(char *path)
{
	ft_putstr_fd("ft_ls: ", 2);
	path = get_path(path);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": Permission denied", 2);
	return (1);
}

static void		do_get_info(DIR *dir, t_lst **lst, char *path)
{
	struct dirent *ret;

	while ((ret = readdir(dir)))
	{
		(*lst) = get_info((*lst), ret->d_name,
				ft_strjoin(path, ret->d_name));
	}
	closedir(dir);
}

static void		suite(t_lst *lst, char *path, t_pad *pad, t_opt *opt)
{
	if (opt && opt->l)
		padding(&lst, pad);
	manage_opt(lst, opt, path);
	if (!opt->big_r && !lst->next)
		free_lst(&lst);
	else if (!opt->big_r && lst)
		free_lst(&lst);
}

void			get_param(char *path, t_opt *opt)
{
	DIR		*dir;
	t_lst	*lst;
	t_pad	*pad;
	int		is_file;

	is_file = 0;
	pad = (t_pad *)malloc(sizeof(t_pad));
	lst = (t_lst *)malloc(sizeof(t_lst));
	lst = NULL;
	if (!(dir = opendir(path)))
	{
		lst = manage_av_file(path, lst, dir);
		if (!lst && error(path))
			return ;
		else if (lst->perm[0] == 'd' &&
				lst->perm[1] == '-' && error_r(path))
			return ;
		is_file = 1;
	}
	else if (is_file == 0)
	{
		path = add_slash(path);
		do_get_info(dir, &lst, path);
	}
	suite(lst, path, pad, opt);
}
