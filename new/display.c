/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 09:49:07 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/10 14:33:47 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	put_total(t_lst *lst)
{
	int res;

	res = 0;
	while (lst)
	{
		res += lst->blok;
		lst = lst->next;
	}
	ft_putstr("total ");
	ft_putnbr_endl(res);
}

static void	put_long(t_lst *lst)
{
	ft_putstr_s(lst->perm);
	ft_putstr_s(lst->link);
	ft_putstr_s(lst->user_id);
	ft_putstr_s(lst->group_id);
	ft_putstr_s(lst->size);
	ft_putstr_s(lst->date);
	ft_putendl(lst->name);
}

void	display_lst(t_lst *lst, int hidd)
{
	if (!hidd)
	{
		while (tmp)
		{
			if (ft_strncmp(tmp->name, ".", 1))
				ft_putendl(tmp->name);
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp)
		{
			ft_putendl(tmp->name);
			tmp = tmp->next;
		}
	}
	lst->next = NULL; // ?
}

void	display_llst(t_lst *lst, int hidd)
{
	put_total(lst);
	if (!hidd)
	{
		while (lst)
		{
			if (ft_strncmp(lst->name, ".", 1))
				put_long(lst);
			lst = lst->next;
		}
	}
	else
	{
		while (lst)
		{
			put_long(lst);
			lst = lst->next;
		}
	}
	lst->next = NULL; // ?
}

void	display_rlst(t_lst *lst, int hidd)
{
	if (!hidd)
	{
		if (lst)
		{
			display_rlst(lst->next, hidd);
			ft_putendl(lst->name);
		}
	}
	else
	{
		if (lst)
		{
			display_rlst(lst->next, hidd);
			if (ft_strncmp(lst->name, ".", 1))
				ft_putendl(lst->name);	
		}
	}
}

void	display_rllst(t_lst *lst, int hidd)
{
	put_total(lst);
	if (!hidd)
	{
		if (lst)
		{
			display_rllst(lst->next, hidd);
			put_long(lst);
		}
	}
	else
	{
		if (lst)
		{
			display_rllst(lst->next, hidd);
			if (ft_strncmp(lst->name, ".", 1))
				put_long(lst);
		}
	}
}
