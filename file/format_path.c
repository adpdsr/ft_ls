
//
// HEADER
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_file_name(char *path)
{
	int end;
	int start;
	char *tmp;

	end = ft_strlen(path) - 1;
	start = end;
	while (path[start] != '/' && start > 0)
		start--;
	tmp = ft_strsub(path, start, end);
	return (tmp);
	
}

char *format_path(char *path)
{
	int	i;
	char	*tmp;

	if (path)
	{
		printf("START %s\n", path);
		i = ft_strlen(path) - 1;
		if (path[i] == '/')
			return (NULL);
		else
		{
			tmp = strdup(path);
			while (tmp[i] != '/' && i > 0)
				i--;
			printf("\ni = %d\n", i);
			if (i == 0)
			{
				tmp = "./";
				// concat path a la suite de tmp => ft_strjoin(tmp, path);
				// free(path);
				return (tmp);
			}
			else
			{
				tmp = strndup(path, i + 1);
				//free(path);
				return (tmp);
			}
		}
	}
	else
		return (NULL);
}

t_lst	*manage_av_file(char *path)
{
	char *formated;
	char *file_name;

	if (!(formated = strdup(format_path(path))))
		exit(1); //=> error opening file
	if (opendir(formated) fail)
		exit(1); //=> error opening file
	else
	{
		file_name = get_file_name(path);
		while (read)
		{
			if (ft_strcmp(ret->d_name, file_name) == 0) // si match
				lst = ... // create 1 node
		}
		return (lst);
	}
}

int	main(void)
{
	char *s1; 
	s1 = "test1.c";
	char *s2; 
	s2 = "./libft/test2.c";
	char *s3; 
	s3 = "";
	char *s4; 
	s4 = ".libftest4/.c";

	printf("%s\n%s\n\n", s1, format_path(s1));
	printf("%s\n%s\n\n", s2, format_path(s2));
	printf("%s\n%s\n\n", s3, format_path(s3));
	printf("%s\n%s\n\n", s4, format_path(s4));
	return (0);
}
