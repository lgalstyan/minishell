/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyenokya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:32:22 by tyenokya          #+#    #+#             */
/*   Updated: 2022/11/13 17:18:43 by tyenokya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//heardock <<
//append >>
//infile >
//outfile <

int main(int argc, char **argv)
{
	int		i;
	char	*str;
	char	**sp;
	t_node	*node;
	t_node	new;

	i = 0;
	str = "";
	while (++i < argc)
		str = ft_strjoin(str, argv[i]);
	if (!checkquotes(str))
		return (0);
	sp = ft_split(str, '|');
	printf("aaaaaaaaaa: %s\n", sp[0]);
	i = 0;
	while (sp[i++])
	{
		new = initialize(sp[i]);
		ft_lstadd_back(&node, &new);
	}
	//printf("bbbbbbbb: %s\n", sp[0]);
}