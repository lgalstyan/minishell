/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalstya <lgalstya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:02:06 by lgalstya          #+#    #+#             */
/*   Updated: 2023/01/20 16:02:54 by lgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_valid_identif(char *str)
{
	int		i;
	char	**array;

	i = 0;
	if (ft_strnstr(str, "+=", ft_strlen(str)))
	{
		array = ft_split(str, '+');
		printf("hello_%s_\n", array[1]);
		++i;
	}
	else
		array = ft_split(str, '=');
	while (array[0][i])
	{
		if (!check_valid(array[0][i]))
			return (0);
		++i;
	}
	return (1);
}
