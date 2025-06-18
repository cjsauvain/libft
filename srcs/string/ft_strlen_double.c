#include "libft.h"

int	ft_strlen_double(char **str)
{
	int	i;

	if (!str)
		return 0;
	i = 0;
	while (str[i])
		i++;

	return i;
}
