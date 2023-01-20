/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalstya <lgalstya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:10:37 by lgalstya          #+#    #+#             */
/*   Updated: 2023/01/20 16:18:56 by lgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ignore_signals(void)
{
	// "Ctrl-C"
   	signal(SIGINT, SIG_IGN);
	// "Ctrl-Z"
    signal(SIGTSTP, SIG_IGN);
	// "Ctrl-\"
    signal(SIGQUIT, SIG_IGN);
}

static void	take_pars_val(t_node *node, t_env **envir, char **env)
{
	int status;
	int i;

	i = 0;
	status = 0;
	while (node[i].cmd)
	{
		status = prompt(node[i], envir, env);
		printf("xelooooooooo\n");
		if(!status)
		{
			printf("unknown command\n");
			return ;
		}
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char	*line;
	t_node	*node;
	t_env	**envir;
	int		fd;

	envir = malloc(sizeof(t_env*));
	*envir = NULL;
	environments(env, envir);
	fd = open("./../dup.txt", O_CREAT | O_WRONLY);
	// if(fd < 0)
    // 	printf("Error: File not found\n");
	// dup(fd);
	// ignore_signals();
	// dup2(fd, 1);
	// printf(BOLD_GREEN);
	while (1)
	{
		printf(ESC_GREEN);
		line = readline("minishell :"ESC_WHITE);
		if (line[0])
			add_history(line);
		else
			continue ;
		node = parser(line);
		take_pars_val(node, envir, env);
		write(fd, line, ft_strlen(line));
	}
	return (0);
}
