//
// HEADER
//

#include "libft.h"

char	*ft_strcdup(char *str, char c)
{
	int i;

	if (str && c)
	{
		i = 0;
		while (str[i] && str[i] != c)
			i++;
		return (ft_strndup(str, i));
	}
	return (NULL);
}
