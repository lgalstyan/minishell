#include "minishell.h"

// stanum e char **, stugum e te inch hramar e u kanchum e hamapatasxany

int	builtin(t_node node, t_env **en)
{
	int status;

	status = -1;
	if (!ft_strcmp(node.cmd[0], "echo"))
	{
		printf(BOLD_BLUE);
		cmd_echo(node, en);
	}	
	else if (!ft_strcmp(node.cmd[0], "cd"))
	{
		cmd_cd(node, en);
		// printf("%s\n",getcwd(node.cmd[1], ft_strlen(node.cmd[1])));
	}
	else if (!ft_strcmp(node.cmd[0], "pwd"))
		cmd_pwd(&status);
	else if (!ft_strcmp(node.cmd[0], "export"))
		cmd_export(node, en);
	else if (!ft_strcmp(node.cmd[0], "unset"))
		cmd_unset(node.cmd[1], en);
	else if (!ft_strcmp(node.cmd[0], "env"))
		print_list(en);
	else if (!ft_strcmp(node.cmd[0], "exit"))
	{
		status = 0;
		cmd_exit();
	}
	else 
	{
		char *const args[] = {"/bin/bash", "-c", "echo"};
		execve("/bin/bash", args, args);
	}
		// printf("%s: command not found\n", node.cmd[0]);
		return (status);
}