/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 14:35:11 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/01/21 18:51:55 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h> // test

t_lst		*lstnew(char *path)
{
	t_lst *new;

	if (!(new = malloc(sizeof(t_lst))))
		return (NULL);
	new->name = path;
	new->next = NULL;
	return (new);
}

static void	err_illegal_opt(t_opt *flags)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(flags->error, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("usage: ft_ls [-Ralrt] [file ...]\n", 2);
	exit(2); // 0 if everything ok, > 0 when error
}

static void	init_struct_opt(t_opt *flags)
{
	ft_putendl("--- INIT OPT STRUCT ---\n"); // test
	flags->l = 0;
	flags->R = 0;
	flags->a = 0;
	flags->r = 0;
	flags->t = 0;
	flags->error = 0;
}

static int	is_valid_opt(char c)
{
	if (c)
		if (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't')
			return (0);
	return (1);
}

static int	get_opt(char *input, t_opt *opt)
{
	int i;

	ft_putstr("--- OPTIONS INPUT ---\n\n"); // test
	ft_putendl(&input[i]); // test
	ft_putstr("\n"); // test
	if (input[0] == '-' && is_valid_opt(input[1]) == 0)
	{
		i = 1;
		init_struct_opt(opt);
		while (input[i] && is_valid_opt(input[i]) == 0)
		{
			if (input[i] == 'l')
				opt->l = 1;
			if (input[i] == 'R')
				opt->R = 1;
			if (input[i] == 'a')
				opt->a = 1;
			if (input[i] == 'r')
				opt->r = 1;
			if (input[i] == 't')
				opt->t = 1;
			i++;
		}
	}
	else
		return (1);
	ft_putendl("--- STRUCT OPT FILLED ---\n"); // test
	if (input[i])
	{
		opt->error = input[i];
		err_illegal_opt(opt);
	}
	return (0);
}

static void	get_path(int i, int ac, char **av, t_lst **start)
{
	int j;

	ft_putendl("--- PATH SAVED ---\n"); // test
	if (i == 1 && ac >= 3) // i = 1 = opt
	{
		j = 2;
		while (j < ac)
		{
			ft_putendl(av[j]); // test
			*start = lstnew(av[j]);
			j++;
		}
	}
	if (i == 0 && ac >= 2)
	{
		j = 1;
		while (j < ac)
		{
			ft_putendl(av[j - 1]); // test
			*start = lstnew(av[j]);
			j++;
		}
	}
	ft_putendl(""); // test
	if ((i == 1 && ac < 3) || (i == 0 && ac < 2)) // test
		ft_putendl("--- NO PATH TO GET ---\n"); // test
}

static void	print_opt(t_opt *opt) // test
{
	ft_putendl("--- OPT SAVED  ---\n");
	printf("l is : %d\n", opt->l);
	printf("R is : %d\n", opt->R);
	printf("a is : %d\n", opt->a);
	printf("r is : %d\n", opt->r);
	printf("t is : %d\n", opt->t);
}

void	print_lst(t_lst **begin_lst) // test
{
	t_lst *tmp;

	tmp = *begin_lst;
	while (tmp)
	{
		printf("\n%s\n", tmp->name);
		tmp = tmp->next;
	}
}

int		main(int ac, char **av)
{
	int		i;
	char 	*input;
	t_opt 	opt;
	t_lst	*start;

	i = 0;
	start = NULL;
	opt = (t_opt){0, 0, 0, 0, 0};
	if (ac > 1)
	{
		if (av[1][0] == '-')
		{
			i = 1;
			if (get_opt(av[1], &opt) == 1)
			{
				err_illegal_opt(&opt);
				return (1);
			}
		}
		get_path(i, ac, av, &start);
	}
	else
		ft_putendl("--- NO ARGS ---\n"); // test
	print_opt(&opt); // test
	print_lst(&start);
	return (0);
}
