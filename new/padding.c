/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 14:09:37 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/09 10:21:06 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	init_pad(t_pad *pad)
{
	pad->len_usr = 0;
	pad->len_grp = 0;
	pad->len_lnk = 0;
	pad->len_siz = 0;
}

static char	*modif_str(char *str, int max)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	j = max - (int)ft_strlen(str);
	if (!(tmp = malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	if (j > 0)
	{
		while (i < max)
		{
			while (i < j)
				tmp[i++] = ' ';
			k = 0;
			while (i < max)
				tmp[i++] = str[k++];
			i++;
		}
		return (tmp);
	}
	else
		return (str);
}

static void	apply_padding(t_pad *pad, t_lst *lst)
{
	t_lst *tmp;

	tmp = lst;
	while (tmp)
	{
		tmp->link = modif_str(tmp->link, pad->len_lnk);
		tmp->user_id = modif_str(tmp->user_id, pad->len_usr);
		tmp->group_id = modif_str(tmp->group_id, pad->len_grp);
		tmp->size = modif_str(tmp->size, pad->len_siz);
		tmp = tmp->next;
	}
}

void		padding(t_lst *lst)
{
	t_lst	*tmp;
	t_pad	pad;

	tmp = lst;
	init_pad(&pad);
	while (tmp->next)
	{
		if (pad.len_usr < ft_strlen(tmp->next->user_id))
			pad.len_usr = ft_strlen(tmp->next->user_id);
		if (pad.len_grp < ft_strlen(tmp->next->group_id))
			pad.len_grp = ft_strlen(tmp->next->group_id);
		if (pad.len_lnk < ft_strlen(tmp->next->link))
			pad.len_lnk = ft_strlen(tmp->next->link);
		if (pad.len_siz < ft_strlen(tmp->next->size))
			pad.len_siz = ft_strlen(tmp->next->size);
		tmp = tmp->next;
	}
	apply_padding(&pad, lst);
}
