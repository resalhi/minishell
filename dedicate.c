/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dedicate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:16:50 by mmanouze          #+#    #+#             */
/*   Updated: 2022/08/22 11:56:41 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initializing(t_pipex *t_pipe, t_parse *parse, char **env)
{
	t_pipe->id = 0;
	t_pipe->out = 0;
	t_pipe->in_err = 0;
	g_status.g_status = 0;
	t_pipe->cmd_number = 0;
	t_pipe->save[0] = dup(0);
	t_pipe->save[1] = dup(1);
	parse->env = ft_env(env);
}

void	ft_default(t_pipex *t_pipe)
{
	dup2(t_pipe->save[0], 0);
	dup2(t_pipe->save[1], 1);
}

void	ft_free2(char **cmd)
{
	int	j;

	j = 0;
	while (cmd[j])
	{
		free(cmd[j]);
		j++;
	}
	free(cmd);
}
