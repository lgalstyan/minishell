/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyenokya <tyenokya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:59:37 by lgalstya          #+#    #+#             */
/*   Updated: 2023/02/24 15:16:22 by tyenokya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

t_node	*init_readline(char *str, t_node *node)
{
	node->readline = ft_strdup(str);
	node->next = NULL;
	return (node);
}

static int	pipe_count(char *line)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (line && line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			ignore_quotes(line, &i);
		if (!line[i])
			break ;
		//Lernona grel
		// if (line[i] == '\"')
		// {
		// 	while (line[++i] && line[i] != '\"')
		// 		;
		// 	++i;	
		// }
		// else if (line[i] == '\'')
		// {
		// 	while (line[++i] && line[i] != '\'')
		// 		;
		// 	++i;	
		// }
		// if (line && line[i] == '\0')
		// 	break ;
		//esqany
		if (line[i] == '|')
			count++;
		i++;
	}
	return (count);
}
int ft_check_pipe(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		while (str[i] && str[i] != '|')
			++i;
		if (str[i] == '|')
		{
			++i;
			while (str && str[i] && is_space(str[i]) == 1)
				++i;
			if (str[i] == '|')
				return (1);
		}
		else
			break ;
		++i;
	}
	return (0);
	
}

static int	checks(char *str, t_env **en)
{
	// int	i = 0;
	// while(str && str[i])
	// 	if (is_space(str[i]))
	// 		++i;
	// if (!str[i])
	// 	{
	// 		set_exit_code("258", en);//esi sirun implementacnenq tex chgravi, hetoel es kodov exity chi ashxatum
	// 		return (1);
	// 	}            //u mekel es printfy write petqa lini kareliya sirun funkya grel tox tal u exiti tivy inqy arandzin ani tex chgravi
	if (checkquotes(str))
	{
		printf("Syntax error: the number of quotes is incorrect\n");
		set_exit_code("258", en);
		return (1);
	}
	if (ft_check_pipe(str) || pipe_count(str) + 1 != ft_wcount(str, '|'))
	{
		printf("Syntax error: the number of pipe is incorrect\n");
		set_exit_code("258", en);
		return (1);
	}
	return (0);
}

t_node	*lexer(char *str, t_env **en)
{
	int		i;
	char	**sp;
	t_node	*node;
	t_node	*new;

	i = 0;
	node = NULL;
	if (checks(str, en))
		return (0);
	sp = pars_ft_split(str, '|');
	while (sp && sp[i])
	{
		new = malloc(sizeof(t_node));
		init_readline(sp[i], new);//stex petqa listnel nodenel maqrel ete new-n chi stexcvum, sp-n el
		ft_list_add_back(&node, new);
		++i;
	}
	node->counts.s_pipe = pipe_count(str);
	free_arr(sp);
	return (node);
}
