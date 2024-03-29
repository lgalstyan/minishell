/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyenokya <tyenokya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:42:54 by lgalstya          #+#    #+#             */
/*   Updated: 2023/03/21 16:22:58 by tyenokya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_no_infile(char *file, t_node *node)
{
	int	fd;

	fd = open(++file, O_RDONLY, 0644);
	if (fd < 0)
	{
		if (node->inf_stat != 1)
		{
			write(2, "No such file or directory\n", 27);
			node->inf_err_code = -1;
			return ;
		}
	}
	close(fd);
}

void	cmd_infile(char *file, t_node *node)
{
	int	fd;

	fd = open(++file, O_RDONLY, 0644);
	if (fd < 0)
	{
		if (node->inf_err_code != 1)
		{
			node->inf_stat = -1;
			perror("minishell ");
			return ;
		}
	}
	dup2(fd, 0);
	close(fd);
}

void	cmd_outfile(char *file, int flag)
{
	int		fd;
	char	*tmp;

	tmp = ft_strtrim_red(file + 1, " ");
	fd = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(tmp);
	if (flag == 1)
		dup2(fd, 1);
	close(fd);
}

void	cmd_append(char *file, int flag)
{
	int	fd;

	fd = open(file + 2, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (flag == 1)
		dup2(fd, 1);
	close(fd);
}
