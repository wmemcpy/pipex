#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>

/* ************************************************************************** */

# define IN_INDEX 1
# define CMD1_INDEX 2
# define CMD2_INDEX 3
# define OUT_INDEX 4

/* ************************************************************************** */

typedef struct s_cmd
{
	bool	error;
	char	*cmd;
	char	**args;
}			t_cmd;

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**envp;
	char	**path;
	t_cmd	*cmd1;
	t_cmd	*cmd2;
	int		fd_in;
	bool	fd_in_error;
	int		fd_out;
	bool	fd_out_error;
	int		fd_pipe[2];
	pid_t	pid1;
	pid_t	pid2;
}			t_data;

/* ************************************************************************** */
bool		ft_check_envp(t_data *data, t_cmd *cmd);
bool		ft_is_void(char *str);
int			ft_tablen(char **tab);
void		ft_free_data(t_data *data);
/* ************************************************************************** */
int			ft_error(char *str);
int			ft_exec(t_data *data);
/* ************************************************************************** */

#endif