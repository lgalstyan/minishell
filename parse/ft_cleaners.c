/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleaners.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyenokya <tyenokya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:33:18 by lgalstya          #+#    #+#             */
/*   Updated: 2023/03/21 16:33:36 by tyenokya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_clean(char **str, t_env **envir)
{
	int	i;
	int	f;
	int	t;

	i = 0;
	f = 0;
	t = 0;
	while (str && str[i])
	{
		str[i] = change_doll(str[i], envir);
		str[i] = ft_strtrim(str[i], SPACES, &f);
		str[i] = ft_strtrim(str[i], "\'", &t);
		if (t)
		{
			++i;
			continue ;
		}
		str[i] = ft_strtrim(str[i], "\"", &f);
		i++;
	}
	return (str);
}

t_node	*ft_clean_spasec(t_node *head, t_env **envir)
{
	t_node	*node;

	node = head;
	if (node->cmd)
		node->cmd = ft_clean(node->cmd, envir);
	if (node->infile[0])
		node->infile = ft_clean(node->infile, envir);
	if (node->outfile[0])
		node->outfile = ft_clean(node->outfile, envir);
	if (node->append[0])
		node->append = ft_clean(node->append, envir);
	if (node->heredoc[0])
		node->heredoc = ft_clean(node->heredoc, envir);
	return (node);
}

char	*ft_clean_spase_between(char *str)
{
	int		i;
	char	*res;
	char	*res_temp;
	char	*temp;

	i = -1;
	temp = NULL;
	res = NULL;
	while (str && str[++i])
	{
		while (str[i] && !is_space(str[i]))
			i++;
		res_temp = ft_substr(str, 0, i);
		while (str[i] && is_space(str[i]))
			i++;
		temp = ft_substr(str, i, ft_strlen(str) - i);
		while (str[i] && !is_space(str[i]))
			i++;
		res = ft_strjoin(res_temp, temp);
		if (res && str[i] && str[i + 1])
			free(res);
		free(temp);
		free(res_temp);
	}
	return (res);
}
