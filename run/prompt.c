/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyenokya <tyenokya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:16:22 by lgalstya          #+#    #+#             */
/*   Updated: 2023/01/28 14:28:30 by tyenokya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*accses_to_exec(char *cmd, char *path)
{
	int		i;
	char	**token;
	char	*cmd_accs;

	i = 0;
	token = ft_split(path, ':');
	if (cmd[0] != '.')
		cmd = ft_strjoin("/", cmd);
	while (token[i])
	{
		cmd_accs = ft_strjoin(token[i], cmd);
		if (access(cmd_accs, 0) == 0)
			return (cmd_accs);
		i++;
	}
	return (cmd);
}

static int	child_proc(t_node node, t_env **envir, char **ch_env)
{
	char	*path;
	char	*cmd;
	int		status;

	path = search_list(*envir, "PATH");
	cmd = accses_to_exec(node.cmd[0], path);
	status = execve(cmd, node.cmd, ch_env);
	if (status == -1)
	{
		printf("errno = %d\n", errno);
		perror("execve : ");
		printf("Syntax error\n");
	}
	return (status);
}

int	prompt(t_node node, t_env **envir)
{
	int		st;
	int		exec_status;
	int		pid;
	char	**ch_env;

	st = 0;
	ch_env = list_to_char(*envir);
	if (is_builtin(node.cmd[0]))
		st = builtin(node, envir);
	else
	{
		pid = fork();
		if (!pid)
			exec_status = child_proc(node, envir, ch_env);
		wait(NULL);
	}
	return (st);
}
