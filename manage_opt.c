/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_opt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 16:22:37 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/08 16:22:40 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		manage_opt_bis(t_lst *lst, t_opt *opt, char *path, int hidd)
{
	if (opt->l && (!opt->r))
	{
		if (lst->next)
			put_total(lst, hidd);
		display_llst(lst, hidd);
	}
	else if (lst && opt->a && (!opt->r))
		display_lst(lst, hidd);
	else if (lst && (!opt->a) && (!opt->r))
		display_lst(lst, hidd);
	if (lst && opt->R)
		recursive(path, lst, opt);
}

void			manage_opt(t_lst *lst, t_opt *opt, char *path)
{
	int hidd;

	hidd = 0;
	lst = lst_sort_ascii(lst);
	if (!opt || (opt->l == 0 && opt->R == 0 && opt->a == 0
				&& opt->r == 0 && opt->t == 0))
		display_lst(lst, hidd);
	else
	{
		if (opt->a)
			hidd = 1;
		if (opt->t)
			lst = lst_sort_time(lst);
		if (opt->r && opt->l)
		{
			if (lst->next)
				put_total(lst, hidd);
			display_rllst(lst, hidd);
		}
		else if (opt->r)
			display_rlst(lst, hidd);
		manage_opt_bis(lst, opt, path, hidd);
	}
}
