/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 13:13:24 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/01/21 18:51:49 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h> // test

void	error(char *ft, char *cause)
{
	ft_putstr(ft);
	ft_putstr(": ");
	perror(cause);
	exit(EXIT_FAILURE);
}

void	error_opt(t_opt *opt)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(opt->error, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("usage: ft_ls [-Ralrt] [file ...]\n", 2);
	exit(EXIT_FAILURE);
}

t_opt	*init_opt(t_opt *option)
{
	//if (!(option = (t_opt *)ft_memalloc(sizeof(t_opt))))
	//	error("ft_ls", "malloc");
	option->l = 0;
	option->R = 0;
	option->a = 0;
	option->r = 0;
	option->t = 0;
	option->error = '0';
	return (option);
}

// ADD INIT INFO

void		get_opt(int ac, char *av, t_opt *option)
{
	int i;

	i = 1;
	option = init_opt(option);
	while (av[i])
	{
		if (av[i] == 'l')
			option->l = 1;
		else if (av[i] == 'R')
			option->R = 1;
		else if (av[i] == 'a')
			option->a = 1;
		else if (av[i] == 'r')
			option->r = 1;
		else if (av[i] == 't')
			option->t = 1;
		else
		{
			option->error = av[i];
			error_opt(option);
		}
		i++;
	}
}

void	get_info(struct dirent *read)
{
	ft_putstr("object name : "); // test
	ft_putendl(read->d_name); // test
}

void	get_dir(DIR *dir)
{
	int cnt_obj;
	int cnt_gho;
	struct dirent *read;

	cnt_obj = 0; // count objects except ghost
	cnt_gho = 0; // count ghosts
	while ((read = readdir(dir)) != NULL)
	{
		if (ft_strcmp(read->d_name, ".") != 0 && ft_strcmp(read->d_name, "..") != 0)
		{
			get_info(read); // test
			ft_putendl(read->d_name);
			cnt_obj += 1;
		}
		else
		{
			get_info(read); // test
			cnt_gho += 1;
		}
	}
	ft_putstr("\ncnt objects : "); // test
	ft_putnbr(cnt_obj);
	ft_putstr("\n");
	ft_putstr("cnt ghost : "); // test
	ft_putnbr(cnt_gho);
	ft_putstr("\n");
	ft_putstr("cnt total : "); // test
	ft_putnbr(cnt_gho + cnt_obj);
	ft_putstr("\n");
}

void	get_path(int i, int ac, char **av)
{
	int j;

	ft_putendl("\n--- PATH SAVED ---\n"); // test
	// launch this ft if directory is valid -> use S_ISDIR(st->st_mode) ?
	if (i == 1 && ac > 3) // if opt found & at least 1 arg
	{
		j = 2;
		while (j <= ac - 1)
		{
			ft_putendl(av[j]);
			j++;
		}
	}
	if (i == 0 && ac >= 2) // if no opt found & at least 1 arg
	{
		j = 1;
		while (j < ac)
		{
			ft_putendl(av[j]);
			j++;
		}
	}
	ft_putstr("\n"); // test
	if ((i == 1 && ac < 3) || (i == 0 && ac < 2)) // test
		ft_putendl("--- NO PATH SPECIFIED ---");
}

static void get_permissions(char *path, struct stat *st) // NOT USED YET
{
	if (stat(path, st) == -1)
	{
		ft_putendl("cant get stat info"); // tmp
		exit(EXIT_FAILURE);
	}
	ft_putendl("\n--- PERMISSIONS ---\n");
	printf((S_ISDIR(st->st_mode)) ? "d" : "-");
	printf((st->st_mode & S_IRUSR) ? "r" : "-");
	printf((st->st_mode & S_IWUSR) ? "w" : "-");
	printf((st->st_mode & S_IXUSR) ? "x" : "-");
	printf((st->st_mode & S_IRGRP) ? "r" : "-");
	printf((st->st_mode & S_IWGRP) ? "w" : "-");
	printf((st->st_mode & S_IXGRP) ? "x" : "-");
	printf((st->st_mode & S_IROTH) ? "r" : "-");
	printf((st->st_mode & S_IWOTH) ? "w" : "-");
	printf((st->st_mode & S_IXOTH) ? "x\n" : "-\n"); // remove \n, for test
}



int		main(int ac, char **av)
{
	int 	i;
	DIR		*dir;
	t_opt	option;

	i = 0;
	dir = NULL;
	option = (t_opt){0, 0, 0, 0, 0};
	if (ac)
	{
		if (ac == 1)
		{
			ft_putendl("--- ONLY 1 ARG, MAKE ls on '.' ---"); // test
			exit(EXIT_SUCCESS);
		}
		else if (ac > 1)
		{
			if (av[1][0] == '-' && av[1][1])
			{
				i = 1; // means opt found
				ft_putendl("\n--- OPTIONS DETECTED ---\n"); // test
				get_opt(ac, av[1], &option);
			}
			if (i == 1)
			{
				dir = opendir(av[2]);
				get_dir(dir);
				get_path(i, ac, av);
			}
			if (i == 0)
			{
				dir = opendir(av[1]);
				get_dir(dir);
				get_path(i, ac, av);
			}
		}
	}
	ft_putendl("--- OPTIONS SAVED ---\n"); // test
	printf("l : %d\n", option.l); // test
	printf("R : %d\n", option.R); // test
	printf("a : %d\n", option.a); // test
	printf("r : %d\n", option.r); // test
	printf("t : %d\n", option.t); // test
	exit(EXIT_SUCCESS);
}
