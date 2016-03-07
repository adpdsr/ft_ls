/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 09:49:07 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/02 14:51:02 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	get_file_type(struct stat *st)
{
	char c;

	if (S_ISDIR(st->st_mode))
		c = 'd';
	else if (S_ISLNK(st->st_mode))
		c = 'l';
	else if (S_ISCHR(st->st_mode))
		c = 'c';
	else if (S_ISBLK(st->st_mode))
		c = 'b';
	else if (S_ISFIFO(st->st_mode))
		c = 'p';
	else if (S_ISSOCK(st->st_mode))
		c = 's';
	else
		c = '-';
	return (c);
}

static void	get_perm(struct stat *st, t_lst *lst)
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

static char	*last_word(char *s)
{
	char	*ptr;
	int		is_word;

	ptr = NULL;
	is_word = 0;
	while (*s)
	{
		if (!ft_isspace(*s) && !is_word)
		{
			ptr = s;
			is_word = 1;
		}
		else if (ft_isspace(*s))
			is_word = 0;
		s++;
	}
	return (ptr);
}

static char	*get_time(const long *f_time)
{
	char	*tmp;
	char	*prev;
	char	*new;
	time_t	today;

	time(&today);
	tmp = ctime(f_time);
	if (today - 15724800 > *f_time || today < *f_time)
	{
		prev = ft_strsub(tmp, 4, 7);
		new = ft_strjoin(prev, last_word(tmp) - 1);
		new[ft_strlen(new)] = '\0';
		ft_strdel(&prev);
	}
	else
		new = ft_strsub(tmp, 4, 12);
	if (ft_strchr(new, '\n'))
		(ft_strchr(new, '\n'))[0] = '\0';
	return (new);
}

void		fill_info(struct stat st, t_lst *new, char *file)
{
	struct passwd	*user_name;
	struct group	*group_name;

	new->blok = st.st_blocks;
	get_perm(&st, new);
	new->link = ft_itoa(st.st_nlink);
	if ((user_name = getpwuid(st.st_uid)))
		new->user_id = ft_strdup(user_name->pw_name);
	else
		new->user_id = ft_itoa(st.st_uid);
	if ((group_name = getgrgid(st.st_gid)))
		new->group_id = ft_strdup(group_name->gr_name);
	else
		new->group_id = ft_itoa(st.st_gid);
	new->size = format_size(ft_itoa(st.st_size));
	new->date = get_time(&st.st_mtime);
	new->date_id = (int)(st.st_mtime);
	new->name = ft_strdup(file);
	new->min = ft_itoa(minor(st.st_rdev));
	new->maj = ft_strjoin(ft_itoa(major(st.st_rdev)), ",");
	new->is_dir = (new->perm[0] == 'd' && ft_strcmp(new->name, ".")
			&& ft_strcmp(new->name, ".."));
	new->next = NULL;
}
