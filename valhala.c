/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valhala.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanouze <mmanouze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:13:29 by mmanouze          #+#    #+#             */
/*   Updated: 2022/08/25 16:29:17 by mmanouze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_begin(t_parse *parse, t_pipex *t_pipe)
{
	g_status.g_status = 0;
	g_status.g_conti = 0;
	g_status.g_id = 0;
	h_d(parse);
	commands(parse, t_pipe);
}

void	commands(t_parse *parse, t_pipex *t_pipe)
{
	char	**cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < parse->num_data - 1)
	{	
		if (parse->data[i].cmd == NULL)
		{
			j = check_red(parse, t_pipe, i);
			i++;
			continue ;
		}
		cmd = join_args(parse, i);
		start(parse, i, t_pipe, cmd);
		ft_free2(cmd);
		i++;
	}
	first_last(parse, t_pipe, i);
	childs_room(t_pipe);
}

void	childs_room(t_pipex *t_pipe)
{
	int	status;

	while (t_pipe->id < t_pipe->cmd_number)
	{
		if (waitpid(t_pipe->wait_id[t_pipe->id], &status, 0) == -1)
		{
			write(2, "Error waitpid\n", 15);
			exit(1);
		}
		if (WIFEXITED(status))
			g_status.g_status = WEXITSTATUS(status);
		if (status == 2)
			g_status.g_status = 130;
		if (status == 3)
			g_status.g_status = 131;
		t_pipe->id++;
	}
	if (t_pipe->out_err == 1 || t_pipe->in_err == 9)
		g_status.g_status = 1;
	if (t_pipe->cmd_number)
		free(t_pipe->wait_id);
	t_pipe->wait_id = 0;
	t_pipe->id = 0;
}

void	first_last(t_parse *parse, t_pipex *t_pipe, int i)
{
	int		k;
	char	**cmd;

	cmd = NULL;
	if (g_status.g_conti != 1)
		g_status.g_status = 0;
	k = check_red(parse, t_pipe, i);
	if (find_here_d(parse, i) || parse->data[i].cmd)
	{
		t_pipe->wait_id[t_pipe->id] = fork();
		if (t_pipe->wait_id[t_pipe->id] == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			if (parse->data[i].cmd)
				cmd = join_args(parse, i);
			ft_pattern(parse, i);
			do_command(parse, i, cmd);
		}
	}
	t_pipe->id = 0;
	close(0);
}

int	check_for_builtins(t_parse *parse, t_pipex *t_pipe)
{
	char	**cmd;
	int		j;
	int		k;

	j = 0;
	if (parse->num_data == 1)
	{
		if (not_builtins(parse, 0))
		{
			h_d(parse);
			k = check_red(parse, t_pipe, 0);
			if (g_status.g_status == 1 && k == 1)
				return (1);
			cmd = join_args(parse, 0);
			excute_builtins(cmd, parse);
			ft_free2(cmd);
			return (1);
		}
	}
	return (0);
}
