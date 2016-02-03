//
// HEADER
//

#include <stdlib.h>
#include <stdio.h>

char	*add_unit(char *s, int size)
{
	if (size >= 1 && size <= 3)
		return (" O");
	if (size >= 4 && size <= 6)
		return ("KO");
	if (size >= 7 && size <= 9)
		return ("MO");
	if (size >= 10 && size <= 13)
		return ("GO");
}

char	*add_dot(char *s, size_t size)
{
	size_t toput;
	char *tmp;

	tmp = s;
	toput = size % 3;
	tmp = ft_strsub(s, 0, toput);
	ft_strjoin(tmp, ".");
	return (tmp);
}

// 1 000 000 000

char	*format_size(char *s)
{
	size_t size;
	char *formated;
	char *end;
	//char end[2];

	size = ft_strlen(s);
	if (!(formated = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_bzero(formated, size + 1);
	if (size >= 4)
	{
		end = add_unit(formated, size);
		formated = add_dot(s, size);
		ft_strjoin(formated, end); // cast char en char*
		return (formated);
	}
	else
		return (s);
}

int	main(void)
{
char s1[] = "123456";

printf("\ninput :  %s\n\n result : %s\n\n", s1, format_size(s1));
return (0);
}
