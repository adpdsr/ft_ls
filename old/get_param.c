/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 09:49:36 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/01/28 13:09:30 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	fill_lst(char *path, t_lst *curr, struct stat st)
{
	if (stat(path, &st) == -1)
	{
		ft_putendl("stat failed");
		exit(EXIT_FAILURE);
	}
	else
		curr->link = st.st_nlink;
}

static t_lst *add_node(t_lst **begin_lst, t_lst *new)
{
	t_lst *curr;

	if (!begin_lst)
	{
		begin_lst = &new;
		return (NULL);
	}
	curr = *begin_lst;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
	return (new);
}

void	get_param(char *path) // need opt
{
	DIR 			*dir;
	t_lst			*begin_lst;;
	t_lst			*curr;
	struct dirent 	*ret;
	struct stat		st;

	if (!(begin_lst = malloc(sizeof(t_lst))))
		return ;
	dir = opendir(path);
	while ((ret = readdir(dir)))
	{
		begin_lst->next = NULL;
		curr = add_node(&begin_lst, curr);
		ft_putendl("im in the while");
		fill_lst(ret->d_name, curr, st);
		printf("size : %d\n", curr->size);
	}
}
