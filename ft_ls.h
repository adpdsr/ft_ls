/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 14:59:58 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/07 18:25:29 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "./libft/libft.h"

# include <unistd.h> // write, readlink
# include <dirent.h> // opendir, readdir, closedir
# include <sys/stat.h> // stat, lstat
# include <pwd.h> // getpwuid
//# include <uuid/uuid.h> // getpwuid, getgrgid
# include <grp.h> // getgrgid
# include <sys/xattr.h> // listxattr, getxattr
# include <time.h> // time, ctime
# include <stdlib.h> // malloc, free, exit
# include <stdio.h> // perror, strerror

typedef struct		s_pad
{
	size_t			len_usr;
	size_t			len_grp;
	size_t			len_lnk;
	size_t			len_siz;
	size_t			len_maj;
	size_t			len_min;
	size_t			len_majmin;
}					t_pad;

typedef struct 		s_opt
{
	int				l;
	int				R;
	int				a;
	int				r;
	int				t;
}					t_opt;

typedef struct		s_lst
{
	char			*name;
	char			*chem;
	char			perm[11];
	char			*user_id;
	char			*group_id;
	char			*date;
	int				date_id;
	int				blok;
	int				is_dir; // bool
	char			*link;
	char			*size;
	char			*maj;
	char			*min;
	char			*majmin;
	struct s_lst 	*next;
}					t_lst;

void	free_lst(t_lst **lst);
void	free_tab(char **tab);

int		is_what(char *tab);
int		count_dir(t_lst **lst);
void	fill_info(struct stat st, t_lst *new, char *file);

char	*add_slash(char *path);
char	*remove_slash(char *path);

void	ft_putnbr_endl(int n);
void	ft_putstr_s(char *s);
void	put_total(t_lst *lst, int hidd);

char	**create_tab(char **av, t_opt *opt, int ac, int flag);
char	**sort_tab_time(char **tab, t_opt *opt, int len);
char	**reverse_tab(char **tab);
char	**sort_tab_time(char **tab, t_opt *opt, int len);

void	get_param(char *path, t_opt *opt);

void	padding(t_lst **lst, t_pad *pad);

char	*format_size(char *s);
char	*join_maj_min(dev_t device_id);

void	display_rllst(t_lst *lst, int hidd);
void	display_llst(t_lst *lst, int hidd);
void	display_rlst(t_lst *lst, int hidd);
void	display_lst(t_lst *lst, int hidd);

int		get_opt(char *str, t_opt *opt);
void	init_opt(t_opt *opt);

t_lst	*lst_sort_ascii(t_lst *lst);
t_lst	*lst_sort_time(t_lst *lst);

t_lst	*manage_av_file(char *path, t_lst *lst, DIR *dir);
t_lst	*get_info(t_lst *head, char *file, char *path);

#endif
