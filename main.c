/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 09:49:07 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/22 17:00:39 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*add_slash(char *path)
{
	if (path[ft_strlen(path) - 1] != '/')
		path = ft_strjoin(path, "/");
	return (path);
}

char	*remove_slash(char *path)
{
	if (path[ft_strlen(path) - 1] == '/')
		path[ft_strlen(path) - 1] = '\0';
	return (path);
}

static char	get_file_type(struct stat *st)
{
	char c;

	if (S_ISDIR(st->st_mode)) // directory
		c = 'd';
	else if (S_ISLNK(st->st_mode)) // sym link
		c = 'l';
	else if (S_ISCHR(st->st_mode)) // character special
		c = 'c';
	else if (S_ISBLK(st->st_mode)) // block special
		c = 'b';
	else if (S_ISFIFO(st->st_mode)) // named pipe (fifo)
		c = 'p';
	else if (S_ISSOCK(st->st_mode)) // socket
		c = 's';
	else
		c = '-';
	return (c);
}

static void get_perm(struct stat *st, t_lst *lst)
{
	ft_bzero(lst->perm, 11);
	lst->perm[0] = get_file_type(st);
	lst->perm[1] = (st->st_mode & S_IRUSR) ? 'r' : '-';
	lst->perm[2] = (st->st_mode & S_IWUSR) ? 'w' : '-';
	lst->perm[3] = (st->st_mode & S_IXUSR) ? 'x' : '-';
	lst->perm[4] = (st->st_mode & S_IRGRP) ? 'r' : '-';
	lst->perm[5] = (st->st_mode & S_IWGRP) ? 'w' : '-';
	lst->perm[6] = (st->st_mode & S_IXGRP) ? 'x' : '-';
	lst->perm[7] = (st->st_mode & S_IROTH) ? 'r' : '-';
	lst->perm[8] = (st->st_mode & S_IWOTH) ? 'w' : '-';
	lst->perm[9] = (st->st_mode & S_IXOTH) ? 'x' : '-';
}

static void	fill_info(struct stat st, t_lst *new, char *file)
{
	new->name = ft_strdup(file);
	new->date = ft_strsub(ctime(&st.st_mtime), 4, 12);
	new->date_id = (int)st.st_mtime;
	new->link = ft_itoa(st.st_nlink);
	new->size = format_size(ft_itoa(st.st_size));
	new->blok = st.st_blocks;
	new->maj = ft_itoa(major(st.st_rdev));
	new->maj = ft_strjoin(new->maj, ",");
	new->min = ft_itoa(minor(st.st_rdev));
	get_perm(&st, new);
	new->is_dir = (new->perm[0] == 'd' && ft_strcmp(new->name, ".") && ft_strcmp(new->name, ".."));
	new->next = NULL;
}

static int	count_dir(t_lst **lst)
{
	int i;
	t_lst *tmp;

	i = 0;
	tmp = *lst;
	while (tmp)
	{
		if (tmp->is_dir)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_lst	*get_info(t_lst *head, char *file, char *path)
{
	struct stat		st;
	t_lst			*new;
	t_lst			*ptr;

	if (!(new = (t_lst *)malloc(sizeof(t_lst)))) // protect
		return (NULL);
	ptr = head;
	if (lstat(path, &st) <= 0)
	{
		printf("start fill info\n");
		fill_info(st, new, file);
		printf("end fill info\n");
		//if (getpwuid(st.st_uid))
		//	new->user_id = ft_strdup(getpwuid(st.st_uid)->pw_name);
		//if (getgrgid(st.st_gid))
		//	new->group_id = ft_strdup(getgrgid(st.st_gid)->gr_name);
	}
	printf("start add node\n");
	if (head == NULL)
{
		printf("end add node\n");
		return (new);
}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	printf("end add node\n");
	//new->next = NULL; //
	return (head);
}

static void recursive(char *path, t_lst *lst, t_opt *opt, int nb_dir)
{
	char			**dirs;
	int				i;
	int				j;

	i = 0;
	if (!(dirs = (char **)malloc(sizeof(char *) * nb_dir + 1)))
		exit(1);
	while (lst)
	{
		if (lst->is_dir == 1)
		{
			if (opt->a == 0 && lst->name[0] != '.')
			{
				dirs[i] = ft_strdup(lst->name);
				i++;
			}
			else if (opt->a != 0)
			{
				dirs[i] = ft_strdup(lst->name);
				i++;	
			}
		}
		lst = lst->next;
	}
	dirs[i] = NULL;
	if (opt->r == 0)
	{
		i = -1;
		while (++i < nb_dir)
		{
			if (dirs[i])
			{
				ft_putchar('\n');
				ft_putstr(ft_strjoin(path, dirs[i]));
				ft_putstr(":\n");
				get_param(ft_strjoin(path, add_slash(dirs[i])), opt);
			}
		}
	}
	else if (opt->r == 1)
	{
		j = nb_dir;
		while (j > -1)
		{
			if (dirs[j])
			{
				ft_putchar('\n');
				ft_putstr(ft_strjoin(path, dirs[j]));
				ft_putstr(":\n");
				get_param(ft_strjoin(path, add_slash(dirs[j])), opt);
			}
			j--;
		}
	}
}

void	manage_opt(t_lst *lst, t_opt *opt, char *path)
{
	int hidd;

	hidd = 0;
	t_lst *tmp;
	tmp = lst;
	tmp = lst_sort_ascii(lst);
	if (!opt || (opt->l == 0 && opt->R == 0 && opt->a == 0 && opt->r == 0 && opt->t == 0))
		display_lst(tmp, 0);
	else if (tmp)
	{
		if (opt->a)
			hidd = 1;
		if (opt->t)
			tmp = lst_sort_time(tmp);
		if (opt->r && opt->l)
		{
			if (tmp->next != NULL)
				put_total(tmp, hidd);
			display_rllst(tmp, hidd);
		}
		else if (opt->r)
			display_rlst(tmp, hidd);
		if (opt->l && (!opt->r))
		{
			if (tmp->next != NULL)
				put_total(tmp, hidd);
			display_llst(tmp, hidd);
		}
		else if (opt->a && (!opt->r))
			display_lst(tmp, hidd);
		else if ((!opt->a) && (!opt->r))
			display_lst(tmp, hidd);
		if (opt->R)
			recursive(path, tmp, opt, count_dir(&lst));
	}
}

void	dsp_lst(t_lst *lst)
{
	while (lst)
	{
	printf("lst->name == %s\n", lst->name);
	lst = lst->next;
	}
}

void	free_lst(t_lst *lst)
{
	int cnt; // test
	t_lst *tmp;

	cnt = 0;
tmp = NULL;
	tmp = lst;
	dsp_lst(tmp);
	printf("start free lst\n");
	while (tmp)
	{
		cnt++;
		//printf("lst = tmp1\n");
		if (tmp->name)
		{
			printf("free : %s\n", tmp->name);
			free(tmp->name);
			tmp->name = NULL;
		}
		//printf("lst = tmp2\n");
		if (tmp->date)
		{
			//	printf("free : %s\n", lst->date);
			free(tmp->date);
			tmp->date = NULL;
		}
		//printf("lst = tmp3\n");
		if (tmp->link)
		{
			//	printf("free : %s\n", lst->link);
			free(tmp->link);
			tmp->link = NULL;
		}
	//	printf("lst = tmp4\n");
		if (tmp->size)
		{
	//		printf("free : %s\n", lst->size);
			free(tmp->size);
			tmp->size = NULL;
		}
	//	printf("lst = tmp5\n");
		if (tmp->maj)
		{
			//	printf("free : %s\n", lst->maj);
			free(tmp->maj);
			tmp->maj = NULL;
		}
	//	printf("lst = tmp6\n");
		if (tmp->min)
		{
			//	printf("free : %s\n", lst->min);
			free(tmp->min);
			tmp->min = NULL;
		}
	//	printf("lst = tmp7\n");
		if (tmp->majmin)
		{
			//	printf("free : %s\n", lst->majmin);
			free(lst->majmin);
			tmp->majmin = NULL;
		}
		//	free(lst);
	//	printf("lst = tmp8\n");
		lst = tmp;
		tmp = tmp->next;
	}
	//printf("name === %s\n", tmp->name);	
	printf("nb nodes deleted : %d\n", cnt);
	printf("end free lst\n");
	//free(lst);
	//lst = NULL;
}

void	get_param(char *path, t_opt *opt)
{
	DIR 			*dir;
	struct dirent	*ret;
	t_lst 			*lst;
	int				is_file;

	is_file = 0;
	if (!(lst = (t_lst *)malloc(sizeof(t_lst))))
		exit(1);
	lst = NULL;
	if (!(dir = opendir(path)))
	{
		lst = manage_av_file(path, lst, dir);
		if (lst == NULL)
		{
			ft_putstr("ft_ls: ");
			perror(path);
			return ;
		}
		is_file = 1;
	}
	else if (is_file == 0)
	{
		path = add_slash(path);
		while ((ret = readdir(dir)))
{
			printf("start get info\n");
			printf("ret->d_name = %s\n", ret->d_name);
			lst = get_info(lst, ret->d_name, ft_strjoin(path, ret->d_name));
			printf("end get info\n");
}
		closedir(dir);
	}
	if (opt && opt->l)
		padding(lst);
	manage_opt(lst, opt, path);
	free_lst(lst);
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	printf("start free tab\n");
	while (tab[i] != NULL)
	{
		free(tab[i]);
	//	tab[i] = NULL;
		i++;
	}
	printf("end free tab\n");
	//free(tab);
	//tab = NULL;
}

int		main(int ac, char **av)
{
	int		i;
	int		flag;
	char	*path;
	char 	**args;
	t_opt	opt;

	i = 1;
	flag = 1;
	path = NULL;
	init_opt(&opt);
	if (ac > 1)
	{
		while (av[i] && av[i][0] == '-')
		{
			printf("start get opt\n");
			get_opt(av[i], &opt);
			printf("end get opt\n");
			flag++;
			i++;
		}
		if (ac > flag)
			args = create_tab(av, &opt, ac, flag);
		i = 0;
		if (ac > 1)
		{
			printf("i = %d | ac - flag = %d\n", i, ac - flag - 1);
			while (i < (ac - flag))
			{
			printf("args[i] = %s\n", args[i]);
				path = args[i];
				get_param(path, &opt);
				i++;
			}
			//free(path);
			//path = NULL;
		}
	}
	if (path == NULL)
		get_param("./", &opt);
	else
		free_tab(args);
	return (0);
}
