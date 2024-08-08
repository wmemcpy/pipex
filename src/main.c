#include "../pipex.h"

static char	*ft_find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		++i;
	}
	return (NULL);
}

static void	ft_try_path(t_data *data, t_cmd *cmd)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = 0;
	if (ft_check_envp(data, cmd))
		return ;
	while (data->path[i])
	{
		tmp1 = ft_strjoin(data->path[i], "/");
		tmp2 = ft_strjoin(tmp1, cmd->cmd);
		free(tmp1);
		if (access(tmp2, X_OK) == 0)
		{
			free(cmd->cmd);
			cmd->cmd = tmp2;
			return ;
		}
		free(tmp2);
		++i;
	}
	cmd->error = true;
}

static t_cmd	*ft_init_cmd(t_data *data, char *cmd)
{
	t_cmd	*new_cmd;
	char	**split;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		ft_error("malloc");
	new_cmd->error = false;
	new_cmd->cmd = NULL;
	new_cmd->args = NULL;
	if (cmd[0] == '\0' || ft_is_void(cmd))
	{
		new_cmd->error = true;
		new_cmd->cmd = ft_strdup(cmd);
		return (new_cmd);
	}
	split = ft_split(cmd, ' ');
	if (!split)
		ft_error("malloc");
	new_cmd->cmd = ft_strdup(split[0]);
	ft_free_array((void **)split);
	new_cmd->args = ft_split(cmd, ' ');
	if (access(new_cmd->cmd, X_OK) == 0)
		return (new_cmd);
	ft_try_path(data, new_cmd);
	return (new_cmd);
}

int	ft_init_data(t_data *data)
{
	data->path = ft_split(ft_find_path(data->envp), ':');
	data->cmd1 = ft_init_cmd(data, data->argv[CMD1_INDEX]);
	data->cmd2 = ft_init_cmd(data, data->argv[CMD2_INDEX]);
	data->fd_in_error = false;
	data->fd_out_error = false;
	if (access(data->argv[IN_INDEX], R_OK) == -1)
		data->fd_in_error = true;
	data->fd_in = open(data->argv[IN_INDEX], O_RDONLY);
	if (data->fd_in == -1)
	{
		data->fd_in_error = true;
		ft_error(data->argv[IN_INDEX]);
	}
	if (access(data->argv[OUT_INDEX], W_OK) == -1)
		data->fd_out_error = true;
	data->fd_out = open(data->argv[OUT_INDEX], O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (data->fd_out == -1)
	{
		data->fd_out_error = true;
		ft_error(data->argv[OUT_INDEX]);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 5)
	{
		ft_error("Error: invalid number of arguments");
		return (EXIT_FAILURE);
	}
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	if (!ft_init_data(&data))
		ft_error("Error: init failed");
	ft_exec(&data);
	ft_free_data(&data);
	return (EXIT_SUCCESS);
}
