//
// HEADER
//

#include "libft.h"

int	ft_cntc(char *str, char c)
{
	int i;
	int cnt;

	if (str && c)
	{
		i = 0;
		cnt = 0;
		while (str[i])
		{
			if (str[i] == c)
				cnt++;
			i++;
		}
		return (cnt);
	}
	return (0);
}
