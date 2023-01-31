#include "minishell.h"

static int	 ft_find(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[0] == '\0')
        return (0);
	if (str[0] == '\0')
		return (0);
	while (str[i])
	{
		j = 0;
		while (str[i + j] == to_find[j])
		{
			if (!(to_find[j + 1]))
                return (i);
			j++;
		}
		i++;
	}
	return (0);
}

char    *ft_strcut(char *readline, char *str)
{
    int     i;
    int     k;
    int     find;
    char    *cmdline;

    i = 0;
    k = 0;
    if (!readline || !str)
        return (NULL);
    if (!(find = ft_find(readline, str)))
        return (0);
    cmdline = ft_calloc(sizeof(char), (ft_strlen(readline) - ft_strlen(str)) + 1);
    while (readline[i] && i < find)
    {
        cmdline[i] = readline[i];
        i++;
    }
    k = i + ft_strlen(str);
    while (readline[k] && i < ft_strlen(readline) - ft_strlen(str))
    {
        cmdline[i] = readline[k];
        i++;
        k++;
    }
    cmdline[i] = '\0';
    free(readline);
    return (cmdline);
}