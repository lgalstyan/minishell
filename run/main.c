/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyenokya <tyenokya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:10:37 by lgalstya          #+#    #+#             */
/*   Updated: 2023/01/30 11:49:18 by tyenokya         ###   ########.fr       */
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

static void	take_pars_val(t_node *node, t_env **envir)
{
	t_node	*curr;

	curr = node;
	while (curr)
	{
		prompt(*curr, envir);
		curr = curr->next;
	}
}

void	shlvl(t_env **en)
{
	t_env	*curr;
	char	*value;

	curr = *en;
	value = NULL;
	while (curr)
	{
		if (!ft_strcmp(curr->key, "SHLVL"))
		{
			value = run_ft_strdup(curr->value);
			free(curr->value);
			curr->value = ft_itoa(ft_atoi(value) + 1);
			free(value);
		}
		curr = curr->next;
	}
}
// TODO
// heredoc_eri mej " ' ery ogtagorcel function vory ignora anum squtery

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char	*line;
	t_node	*node;
	t_env	**envir;
	// int		fd;

	exit_code = 0;
	envir = malloc(sizeof(t_env *));
	*envir = NULL;
	environments(env, envir);
	shlvl(envir);
	while (1)
	{
		printf(ESC_GREEN);
		line = readline("minishell :"ESC_WHITE);
		if (line[0])
			add_history(line);
		else
			continue ;
		node = lexer(line);
		node = parser(node);
		// node.cmd = ft_split(line, ' ');
		take_pars_val(node, envir);
		//write(fd, line, ft_strlen(line)); 
	}
	return (0);
}
