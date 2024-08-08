#include "../pipex.h"

int	ft_error(char *str)
{
	ft_putstr_fd("pipex: ", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd(": ", STDOUT_FILENO);
	ft_putstr_fd(strerror(errno), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

static void	ft_wrong_cmd(t_data *data, char *cmd)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_free_data(data);
	exit(127);
}

static int	ft_child(t_data *data)
{
	data->pid1 = fork();
	if (data->pid1 == -1)
		return (-1);
	if (data->pid1 == 0)
	{
		if (data->fd_in_error)
			return (-1);
		if (close(data->fd_pipe[0]) == -1)
			return (-1);
		if (dup2(data->fd_in, 0) == -1)
			return (-1);
		if (dup2(data->fd_pipe[1], 1) == -1)
			return (-1);
		if (close(data->fd_pipe[1]) == -1)
			return (-1);
		if (data->cmd1->error)
			ft_wrong_cmd(data, data->argv[CMD1_INDEX]);
		if (execve(data->cmd1->cmd, data->cmd1->args, data->envp) == -1)
			return (-1);
	}
	return (0);
}

static int	ft_parent(t_data *data)
{
	data->pid2 = fork();
	if (data->pid2 == -1)
		return (-1);
	if (data->pid2 == 0)
	{
		if (data->fd_out_error)
			return (-1);
		if (close(data->fd_pipe[1]) == -1)
			return (-1);
		if (dup2(data->fd_pipe[0], 0) == -1)
			return (-1);
		if ((dup2(data->fd_out, 1) == -1))
			return (-1);
		if (close(data->fd_pipe[0]) == -1)
			return (-1);
		if (data->cmd2->error)
			ft_wrong_cmd(data, data->argv[CMD2_INDEX]);
		if (execve(data->cmd2->cmd, data->cmd2->args, data->envp) == -1)
			return (-1);
	}
	return (0);
}

int	ft_exec(t_data *data)
{
	if (pipe(data->fd_pipe) == -1)
		return (0);
	if (ft_child(data) == -1)
		return (0);
	if (ft_parent(data) == -1)
		return (0);
	close(data->fd_pipe[0]);
	close(data->fd_pipe[1]);
	waitpid(data->pid1, NULL, 0);
	waitpid(data->pid2, NULL, 0);
	return (1);
}
