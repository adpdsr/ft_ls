/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 16:22:47 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/10 17:19:39 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		init_opt(t_opt *opt)
{
	opt->l = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
	opt->big_r = 0;
}

static void	err_opt(char *err)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putendl_fd(err, 2);
	ft_putstr_fd("usage: ft_ls [-Ralrt] [file ...]\n", 2);
	exit(1);
}

static int	valid_opt(char o)
{
	return ((o == 'l' || o == 'R' || o == 'a' || o == 'r' || o == 't'));
}

int			get_opt(char *opts, t_opt *opt)
{
	int i;

	i = 1;
	while (opts[i] && valid_opt(opts[i]))
	{
		if (opts[i] == 'l')
			opt->l = 1;
		if (opts[i] == 'R')
			opt->big_r = 1;
		if (opts[i] == 'a')
			opt->a = 1;
		if (opts[i] == 'r')
			opt->r = 1;
		if (opts[i] == 't')
			opt->t = 1;
		i++;
	}
	if (opts[i])
		err_opt(&opts[i]);
	return (0);
}
