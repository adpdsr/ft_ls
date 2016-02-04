/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 13:03:15 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/04 17:09:10 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h> // test

void	lst_add(t_lst **start, t_lst *new) // add end
{
	t_lst *ptr;

	if (*start == NULL)
		*start = new;
	else
	{
		ptr = *start;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

static t_lst	*lst_swap(t_lst *p1, t_lst *p2)
{
	p1->next = p2->next;
	p2->next = p1;
	return (p2);
}

t_lst	*lst_sort_ascii(t_lst *lst)
{
	lst = lst->next;
	printf("TEST1\n");
	if (lst == NULL)
		return (NULL);
	printf("TEST2\n");
	if (lst->next->next != NULL && printf("TEST3\n") && ft_strcmp(lst->name, lst->next->name) > 0 && printf("TEST4\n"))
	{
		printf("TEST5\n");
		lst = lst_swap(lst, lst->next);
	}
	printf("TEST6\n");
	lst->next = lst_sort_ascii(lst->next);
	if (lst->next != NULL && ft_strcmp(lst->name, lst->next->name) > 0)
	{
		lst = lst_swap(lst, lst->next);
		lst->next = lst_sort_ascii(lst->next);
	}
	return (lst);
}
