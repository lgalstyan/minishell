#include "minishell.h"

void	ft_print_hered(char *line, int fd)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	line = NULL;
}

int	ft_stop(char *s, char *str)
{
	if (!s)
	{
		ft_free_str(s);
		return (1);
	}
	if (ft_strcmp(str, s) == 0)
	{
		ft_free_str(s);
		return (1);
	}
	return (0);
}

void	ft_dup_here(int fd, char **file, int flag)
{
	if (flag == 1)
	{
		close(fd);
		fd = open((*file), O_RDONLY);
		dup2(fd, 0);
		close(fd);
	}
	unlink(*file);
	free(*file);
}

void	heredoc(char *str)
{
	char	*s;
	int		fd;
	char	*file;

	file = ft_strjoin(".", str);
	str += 2;
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		s = readline("> ");
		if (ft_stop(s, str))
			break ;
		ft_print_hered(s, fd);
	}
	ft_dup_here(fd, &file, 1);
}

void	heredoc_not(char *str)
{
	char	*s;
	int		fd;
	char	*file;

	file = ft_strjoin(".", str);
	str += 2;
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		s = readline("> ");
		if (!s)
			return ;
		if (!ft_strcmp(str, s))
			break ;
		ft_print_hered(s, fd);
	}
	ft_dup_here(fd, &file, 0);
}