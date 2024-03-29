/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyenokya <tyenokya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:25:38 by tyenokya          #+#    #+#             */
/*   Updated: 2023/03/21 16:28:58 by tyenokya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	allocate_matrix(t_node	*head)
{
	head->counts.s_infile = ft_infile_count(head->readline);
	head->counts.s_outfile = ft_outfile_count(head->readline);
	head->counts.s_heredoc = ft_heredoc_count(head->readline);
	head->counts.s_append = ft_append_count(head->readline);
	head->counts.s_all = ft_wcount(head->readline, ' ');
	head->counts.s_cmd = head->counts.s_all - ft_all_redir_size(head);
	head->infile = ft_calloc((head->counts.s_infile + 1), sizeof(char *));
	head->outfile = ft_calloc((head->counts.s_outfile + 1), sizeof(char *));
	head->heredoc = ft_calloc((head->counts.s_heredoc + 1), sizeof(char *));
	head->append = ft_calloc((head->counts.s_append + 1), sizeof(char *));
}

void	initialize(t_node	*head)
{
	int	i;

	i = 0;
	while (head)
	{
		allocate_matrix(head);
		initial_nodes(head, i);
		head = head->next;
	}
}

t_node	*parser(t_node *head, t_env **envir)
{
	t_node	*node;

	node = head;
	if (check_quote_2(head, envir) || unexpected_tokens(head, envir) == 1)
	{
		free_node(head);
		return (0);
	}
	initialize(head);
	while (node)
	{
		node = ft_clean_sp_redir(node);
		node = ft_clean_spasec(node, envir);
		node = node->next;
	}
	return (head);
}

// void	print_node(t_node *node)
// {
// 	int	i;

// 	i = 0;
// 	if (node)
// 	{
// 		while (node->cmd && node->cmd[i])
// 		{
// 			printf("cmd%d=%s_\n", i, node->cmd[i]);
// 			i++;
// 		}
// 		i = 0; 
// 		while (node->heredoc && node->heredoc[i])
// 		{
// 			printf("heredoc = %s\n", node->heredoc[i]);
// 			i++;
// 		}
// 		i = 0; 
// 		while (node->append && node->append[i])
// 		{
// 			printf("append = %s\n", node->append[i]);
// 			i++;
// 		}
// 		i = 0; 
// 		while (node->outfile && node->outfile[i])
// 		{
// 			printf("outfile = %s\n", node->outfile[i]);
// 			i++;
// 		}
// 		i = 0; 
// 		while (node->infile && node->infile[i])
// 		{
// 			printf("infile = %s\n", node->infile[i]);
// 			i++;
// 		}
// 	}
// }