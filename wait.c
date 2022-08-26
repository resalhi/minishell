/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanouze <mmanouze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 19:31:17 by mmanouze          #+#    #+#             */
/*   Updated: 2022/08/22 11:37:40 by mmanouze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_cmd(t_pipex *t_pipe, t_parse *parse)
{
	int	i;
	int	j;
	int	c;
	int	k;

	i = 0;
	j = 0;
	if (parse->num_data >= 1)
	{
		while (i < parse->num_data)
		{
			c = 0;
			if (parse->data[i].cmd)
			{
				if (parse->num_data == 1 && not_builtins(parse, 0))
					k = 1;
				else
					j++;
			}
			i++;
		}
	}
	t_pipe->cmd_number = j;
	if (t_pipe->cmd_number)
		t_pipe->wait_id = malloc(sizeof(int) * (j));
}

int	not_builtins(t_parse *parse, int i)
{
	if (!ft_strcmp(parse->data[i].cmd, "pwd")
		|| !ft_strcmp(parse->data[i].cmd, "export")
		|| !ft_strcmp(parse->data[i].cmd, "env")
		|| !ft_strcmp(parse->data[i].cmd, "unset")
		|| !ft_strcmp(parse->data[i].cmd, "cd")
		|| !ft_strcmp(parse->data[i].cmd, "exit")
		|| !ft_strcmp(parse->data[i].cmd, "echo"))
		return (1);
	return (0);
}
