/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanouze <mmanouze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:01:44 by mmanouze          #+#    #+#             */
/*   Updated: 2022/08/25 17:21:11 by mmanouze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_paths(char **env)
{
	int		i;
	char	*str;
	char	**ok;

	i = 0;
	str = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
		{
			str = ft_strchr(env[i], '/');
			break ;
		}
		i++;
	}
	if (str == NULL)
		return (NULL);
	ok = ft_split(str, ':');
	return (ok);
}

char	*command_path(char *cmd, char **paths)
{
	int		i;
	int		j;
	char	*join;

	i = 0;
	j = 1;
	while (paths[i])
	{
		join = ft_strjoin_p(paths[i], cmd);
		if (!access(join, X_OK))
			return (join);
		free(join);
		i++;
	}
	return (NULL);
}

void	do_command(t_parse *parse, int i, char **comd)
{
	char	**paths;
	char	*take;

	g_status.g_id = 1;
	check_child_built(parse, comd);
	if (access(parse->data[i].cmd, F_OK & X_OK) == 0)
		execve(parse->data[i].cmd, comd, parse->env);
	paths = ft_paths(parse->env);
	if (!paths)
		protection(comd[0]);
	take = command_path(comd[0], paths);
	if (execve(take, comd, parse->env) == -1)
	{
		write(2, "bash: ", 6);
		write(2, comd[0], ft_strlen(comd[0]));
		write(2, " :command not found\n", 21);
		exit(127);
	}
}

void	start(t_parse *parse, int i, t_pipex *t_pipe, char **comd)
{
	int	k;

	g_status.g_status = 0;
	pipe(t_pipe->fd);
	k = check_red(parse, t_pipe, i);
	t_pipe->wait_id[t_pipe->id] = fork();
	if (t_pipe->wait_id[t_pipe->id++] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (k == 1)
		{
			ft_pattern(parse, i);
			close(t_pipe->fd[0]);
			close(t_pipe->fd[1]);
			do_command(parse, i, comd);
		}
		else
		{
			ft_pattern(parse, i);
			child_else(parse, t_pipe, i, comd);
		}
	}
	else
		ft_parent(t_pipe, parse, i);
}

int	check_red(t_parse *parse, t_pipex *t_pipe, int i)
{
	int	c;

	c = 0;
	dup2(t_pipe->save[1], 1);
	t_pipe->in_err = 0;
	t_pipe->out_err = 0;
	t_pipe->out = 0;
	if (parse->data[i].num_red >= 1)
	{
		if (parse->num_data == 1 && not_builtins(parse, 0))
			g_status.g_status = 0;
		while (c < parse->data[i].num_red)
		{
			input_file(parse, t_pipe, i, c);
			output_file(parse, t_pipe, i, c);
			append_file(parse, t_pipe, i, c);
			if (parse->data[i].red[c].type == 3)
				dup2(parse->data[i].fd[0], 0);
			c++;
		}
		if (t_pipe->out != 1 && parse->num_data != 1)
			dup2(t_pipe->fd[1], 1);
		return (1);
	}
	return (0);
}
