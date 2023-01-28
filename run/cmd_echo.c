/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyenokya <tyenokya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:57:27 by lgalstya          #+#    #+#             */
/*   Updated: 2023/01/28 14:12:19 by tyenokya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_option_check(char *str)
{
	int	i;

	i = 1;
	while (str && str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_wait_n(char **cmd)
{
	int	flag;
	int	i;

	i = 1;
	flag = 0;
	while (cmd[i][0] == '-')
	{
		if (ft_option_check(cmd[i]) == 0)
			return (i * (-1));
		i++;
	}
	return (i);
}

static void	ft_print_echo(t_node	node, int i, t_env **en)
{
	while (node.cmd && node.cmd[i])
	{
		ft_strfind(node.cmd[i], en);
		i++;
		if (node.cmd[i])
			printf(" ");
	}
}

static int	check_index(int i, t_node node, int *flag)
{
	i = ft_wait_n(node.cmd);
	if (i < -1)
	{
		i *= (-1);
		*flag = 1;
	}	
	else if (i > 0)
		*flag = 1;
	else if (i < 0)
		i *= (-1);
	return (i);
}

void	cmd_echo(t_node node, t_env **en)
{
	int		flag;
	int		i;

	flag = 0;
	i = 1;
	if (!node.cmd[i])
	{
		printf("\n");
		return ;
	}
	if (node.cmd[i][0] == '-')
	{
		i = check_index(i, node, &flag);
		if (!node.cmd[i])
			return ;
	}
	ft_print_echo(node, i, en);
	if (!flag)
		printf("\n");
}
