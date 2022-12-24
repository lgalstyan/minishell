/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalstya <lgalstya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 12:55:07 by lgalstya          #+#    #+#             */
/*   Updated: 2022/12/24 17:41:26 by lgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(char c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

char	*ft_strnstr(char *str, char *to_find, int len)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	if (str[0] == '\0')
		return (0);
	while (str[i] && i < len && len > 0)
	{
		j = 0;
		while (str[i + j] == to_find[j] && len > i + j)
		{
			if (!(to_find[j + 1]))
				return ((char *)(str + i));
			j++;
		}
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc (ft_strlen (s1) + ft_strlen (s2) + 1);
	if(!str)
		return (0);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	// if (s1)
		// free(s1);
	return (str);
}

// char	*ft_strdup(char *src)
// {
// 	int		i;
// 	char	*tox;

// 	i = 0;
// 	if (!src)
// 		return (0);
// 	tox = (char *)malloc(ft_strlen(src) + 1);
// 	if (!tox)
// 		return (0);
// 	while (src[i])
// 	{
// 		tox[i] = src[i];
// 		i++;
// 	}
// 	tox[i] = 0;
// 	return (tox);
// }