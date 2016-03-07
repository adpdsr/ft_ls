/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:36:47 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/07 10:47:02 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	free_data(t_lst **lst)
{
	if ((*lst)->link)
		ft_strdel(&(*lst)->link);
	if ((*lst)->user_id)
		ft_strdel(&(*lst)->user_id);
	if ((*lst)->group_id)
		ft_strdel(&(*lst)->group_id);
	if ((*lst)->min)
		ft_strdel(&(*lst)->min);
	if ((*lst)->maj)
		ft_strdel(&(*lst)->maj);
	if ((*lst)->size)
		ft_strdel(&(*lst)->size);
	else
		ft_strdel(&(*lst)->majmin);
	if ((*lst)->name)
		ft_strdel(&(*lst)->name);
	if ((*lst)->date)
		ft_strdel(&(*lst)->date);
}

void		free_lst(t_lst **lst)
{
	while (*lst)
	{
		free_data(lst);
		*lst = (*lst)->next;
	}
	free((*lst));
	lst = NULL;
}

void		free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
}
