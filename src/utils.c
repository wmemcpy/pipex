#include "../pipex.h"

bool	ft_check_envp(t_data *data, t_cmd *cmd)
{
	if (data->path == NULL)
	{
		if (access(cmd->cmd, X_OK) == 0)
			return (true);
		cmd->error = true;
		return (true);
	}
	return (false);
}

bool	ft_is_void(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (false);
		++i;
	}
	return (true);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		++i;
	return (i);
}

static void	ft_close_fd(t_data *data)
{
	if (data->fd_in)
		close(data->fd_in);
	if (data->fd_out)
		close(data->fd_out);
	if (data->fd_pipe[0])
		close(data->fd_pipe[0]);
	if (data->fd_pipe[1])
		close(data->fd_pipe[1]);
}

void	ft_free_data(t_data *data)
{
	if (data->path)
		ft_free_array((void **)data->path);
	if (data->cmd1)
	{
		if (data->cmd1->cmd)
			free(data->cmd1->cmd);
		if (data->cmd1->args)
			ft_free_array((void **)data->cmd1->args);
		free(data->cmd1);
	}
	if (data->cmd2)
	{
		if (data->cmd2->cmd)
			free(data->cmd2->cmd);
		if (data->cmd2->args)
			ft_free_array((void **)data->cmd2->args);
		free(data->cmd2);
	}
	ft_close_fd(data);
}
