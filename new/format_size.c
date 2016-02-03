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
		return (" Ko");
	if (size >= 7 && size <= 9)
		return (" Mo");
	if (size >= 10 && size <= 13)
		return (" Go");
}

char	*add_dot(char *s, size_t size)
{
	size_t toput;
	char *tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * size + 1))) // use strnew
		return (NULL);
	ft_bzero(tmp, size + 1);
	toput = size % 3; // ternaire pour les 3 lignes
	if (toput == 0)
		toput = 3;
	ft_strncpy(tmp, s, toput);
	ft_strcat(tmp, ".");
	tmp[toput + 1] = s[toput];
	tmp[toput + 2] = s[toput + 1];
	return (tmp);
}

char	*format_size(char *s)
{
	size_t size;
	char *formated;
	char *end;

	size = ft_strlen(s);
	if (!(formated = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_bzero(formated, size + 1);
	if (!(end = (char *)malloc(sizeof(char) * 4)))
		return (NULL);
	end = add_unit(formated, size);
	if (size >= 4)
	{
		formated = add_dot(s, size);
		ft_strcat(formated, end);
		return (formated);
	}
	ft_strcpy(formated, s);
	ft_strcat(formated, end);
	return (formated);
}

int	main(void) // sans arrondi
{
	char *s1;
	char *s2;
	char *s3;
	char *s4;
	char *s5;

	s1 = "123";
	s2 = "1234";
	s3 = "12345";
	s4 = "123456";
	s5 = "1234567";
	printf("\ninput :  %s\n\nresult : %s\n\n", s1, format_size(s1));
	printf("\ninput :  %s\n\nresult : %s\n\n", s2, format_size(s2));
	printf("\ninput :  %s\n\nresult : %s\n\n", s3, format_size(s3));
	printf("\ninput :  %s\n\nresult : %s\n\n", s4, format_size(s4));
	printf("\ninput :  %s\n\nresult : %s\n\n", s5, format_size(s5));
	return (0);
}
