#include "minishell.h"

// stanum e char **, stugum e te inch hramar e u kanchum e hamapatasxany

int is_builtin(char *cmd)
{
	if(!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
	|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
	|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "unset")
	|| !ft_strcmp(cmd, "exit"))
		return (0);
	return (-1);
}

int	builtin(t_node node, t_env **en)
{
	int status;

	status = -1;
	if (!ft_strcmp(node.cmd[0], "echo"))
	{
		printf(BOLD_BLUE);
		cmd_echo(node, en);
		status = 1;
	}	
	else if (!ft_strcmp(node.cmd[0], "cd"))
	{
		cmd_cd(node, en);
		// printf("%s\n",getcwd(node.cmd[1], ft_strlen(node.cmd[1])));
	}
	else if (!ft_strcmp(node.cmd[0], "pwd"))
	{
		status = 1;
		cmd_pwd();
	}
	else if (!ft_strcmp(node.cmd[0], "export"))
	{
		status = 1;
		cmd_export(node, en);
	}
	else if (!ft_strcmp(node.cmd[0], "unset"))
	{
		status = 1;
		cmd_unset(node.cmd[1], en);
	}
	else if (!ft_strcmp(node.cmd[0], "env"))
	{
		status = 1;
		print_list(en);
	}
	else if (!ft_strcmp(node.cmd[0], "exit"))
	{
		status = 1;
		cmd_exit(node.cmd);
	}
	// printf("%s: command not found\n", node.cmd[0]);
	return (status);
}