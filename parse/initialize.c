/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyenokya <tyenokya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:34:10 by tyenokya          #+#    #+#             */
/*   Updated: 2023/03/10 14:26:40 by tyenokya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '>' || str[i] == '<')
			return (0);
		i++;
	}
	return (1);
}

void	ignor(char *s, int *i)
{
	while (s[*i] && s[*i] != '<' && s[*i] != '>')
	{
		if (s[*i] == '\'' || s[*i] == '\"')
			ignore_quotes(s, i);
		if (!s[*i])
			break ;
		++*i;
	}
}

int	initial_nodes(t_node *node, int i)
{
	node->cmd = NULL;
	if (!check_redir(node->readline))
		ignor(node->readline, &i);
	while (node->readline && node->readline[i])
	{
		if (node->readline[i] == '\"' || node->readline[i] == '\'')
			ignore_quotes(node->readline, &i);
		if (!node->readline[i])
			break ;
		if (node->readline[i] == '>' && node->readline[i + 1] == '>')
			put_hd_app(node, '>', i);
		else if (node->readline[i] == '<' && node->readline[i + 1] == '<')
			put_hd_app(node, '<', i);
		else if (node->readline[i] == '>' && node->readline[i + 1] != '>')
			put_in_out(node, '>', i);
		else if (node->readline[i] == '<' && node->readline[i + 1] != '<')
			put_in_out(node, '<', i);
		++i;
	}
	node = cut_redir(node);
	if (node->readline && node->readline[0])
		node->cmd = pars_ft_split(node->readline, ' ');
	return (1);
}
