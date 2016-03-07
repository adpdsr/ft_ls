//
// HEADER
//

#include "libft.h"

void	ft_freetab(char **tab)
{
	int i;
	int len;

	i = 0;
	len = ft_tablen(tab);
	while (i < len)
	{
		ft_putstr("free : ");
		ft_putendl(tab[i]);
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}
