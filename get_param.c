
#include "ft_ls.h"

void	fill_lst(t_lst *lst, struct stat st)
{

}

void	get_param(char *path) // need opt
{
	DIR 		*dir;
	t_lst		*lst;
	struct dirent 	*ret;

	if (!(dir = opendir(path)) = NULL)
	{
		ft_putendl("error opendir");
		exit(EXIT_FAILURE);
	}
	if (!(lst = (t_lst *)malloc(sizeof(t_lst))))
	{
		ft_putendl("error malloc lst");
		exit(EXIT_FAILURE);
	}
	lst = NULL;
	while (ret = readdir(dir))
	{
		lst = fill_lst(file->d_name, )
	}
}
