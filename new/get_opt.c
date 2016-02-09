/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 09:51:23 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/09 17:38:59 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_opt(t_opt *opt)
{
	opt->l = 0;
	opt->R = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
}

static void	err_opt(char *err)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putendl_fd(err, 2);
	ft_putstr_fd("usage: ft_ls [-Ralrt] [file ...]\n", 2);
	exit(EXIT_FAILURE);
}

static int 	valid_opt(char c)
{
	return ((c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't'));
}

int			get_opt(char *str, t_opt *opt)
{
	int i;

	i = 1;
	while (str[i] && valid_opt(str[i]))
	{
		if (str[i] == 'l')
			opt->l = 1;
		if (str[i] == 'R')
			opt->R = 1;
		if (str[i] == 'a')
			opt->a = 1;
		if (str[i] == 'r')
			opt->r = 1;
		if (str[i] == 't')
			opt->t = 1;
		i++;
	}
	if (str[i])
		err_opt(&str[i]);
	return (0);
}
