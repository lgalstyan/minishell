/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyenokya <tyenokya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:10:37 by lgalstya          #+#    #+#             */
/*   Updated: 2023/03/21 16:28:30 by tyenokya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

static void	take_pars_val(t_node *node, t_env **envir, int in_cpy, int out_cpy)
{
	int	n;

	n = node_len(node);
	if (node->counts.s_pipe > 0)
		ft_pipe(node, envir, n);
	else
		commands(*node, envir);
	dup2(in_cpy, 0);
	dup2(out_cpy, 1);
}

static void	not_line(char *line)
{
	if (!line)
		ft_print_exit();
}

void	readline_main(t_node *node, t_env *envir, int in_cpy, int out_cpy)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline(ESC_GREEN"💚 minishell :"ESC_WHITE);
		not_line(line);
		if (!line || !ft_noly_space(line))
		{
			free(line);
			continue ;
		}
		else
			add_history(line);
		lexer(&node, line, &envir);
		if (line)
			free(line);
		if (!node)
			continue ;
		node = parser(node, &envir);
		if (!node)
			continue ;
		take_pars_val(node, &envir, in_cpy, out_cpy);
		free_node(node);
	}
}

int	second_hook(void)
{
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_node	*node;
	t_env	*envir;
	int		in_cpy;
	int		out_cpy;

	(void)argv;
	(void)argc;
	rl_catch_signals = 0;
	rl_event_hook = second_hook;
	rl_done = 1;
	signal(SIGINT, &handler);
	signal(SIGQUIT, SIG_IGN);
	envir = NULL;
	node = NULL;
	in_cpy = dup(0);
	out_cpy = dup(1);
	environments(env, &envir);
	shlvl(&envir);
	readline_main(node, envir, in_cpy, out_cpy);
	close(out_cpy);
	close(in_cpy);
	return (0);
}
