/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 13:03:15 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/02 14:22:57 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h> // test

static void	swap_content(t_lst *dst, t_lst *src)
{
	dst->name = src->name;
	dst->chem = src->chem;
	dst->perm = src->perm;
	dst->user_id = src->user_id;
	dst->group_id = src->group_id;
	dst->date = src->date;
	dst->blok = src->blok;
	dst->link = src->link;
	dst->size = src->size;
}

static void	swap_node(t_lst **p1, t_lst **p2)
{
	t_lst tmp;

	tmp = **p1;
	swap_content(p1, *p2);
	swap_content(p2, &tmp);
}

void	sort(t_lst **lst, int (*f)(t_lst *lst1, t_lst *lst2))
{
	t_lst *start;

	start = lst;
	while (lst)
	{
		if (f(lst, lst->next) > 0)
		{
			swap_node(&lst, &(lst->next));
			lst = start;
		}
		lst = lst->next;
	}
}
