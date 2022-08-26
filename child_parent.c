/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 19:52:41 by mmanouze          #+#    #+#             */
/*   Updated: 2022/08/23 18:49:56 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_else(t_parse *parse, t_pipex *t_pipe, int i, char **comd)
{
	dup2(t_pipe->fd[1], 1);
	close(t_pipe->fd[0]);
	close(t_pipe->fd[1]);
	do_command(parse, i, comd);
}

void	ft_pattern(t_parse *parse, int i)
{
	if (g_status.g_conti == 1)
		exit(1);
	if (g_status.g_status == 1)
		exit(1);
	if (parse->data[i].sign == 1)
		exit(1);
}

void	ft_parent(t_pipex *t_pipe, t_parse *parse, int i)
{
	if (parse->data[i + 1].cmd)
		dup2(t_pipe->fd[0], 0);
	close(t_pipe->fd[0]);
	close(t_pipe->fd[1]);
}

void	protection(char *comd)
{
	write(2, "bash: ", 6);
	write(2, comd, ft_strlen(comd));
	write(2, " : No such file or directory\n", 30);
	exit(127);
}

void	check_child_built(t_parse *parse, char **comd)
{
	if (!ft_strcmp(comd[0], "pwd") || !ft_strcmp(comd[0], "export")
		|| !ft_strcmp(comd[0], "env") || !ft_strcmp(comd[0], "unset")
		|| !ft_strcmp(comd[0], "cd") || !ft_strcmp(comd[0], "exit")
		|| !ft_strcmp(comd[0], "echo"))
	{
		excute_builtins(comd, parse);
		exit(0);
	}
}
