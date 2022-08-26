/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:04:17 by mmanouze          #+#    #+#             */
/*   Updated: 2022/08/26 14:09:53 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(t_parse *parse, char *limiter, int i)
{
	char	*read;

	g_status.g_herd = 1;
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		read = readline(">");
		if (!read)
		{
			free(read);
			exit(0);
		}
		else if (!ft_strcmp(limiter, read))
		{
			free(read);
			free(limiter);
			exit(1);
		}
		read = dollar_hundler(read, parse);
		write(parse->data[i].fd[1], read, ft_strlen(read));
		write(parse->data[i].fd[1], "\n", 1);
		free(read);
	}
}

int	find_here_d(t_parse *parse, int i)
{
	int	j;

	j = 0;
	if (parse->data[i].num_red >= 1)
	{
		while (j < parse->data[i].num_red)
		{
			if (parse->data[i].red[j].type == HERDOC)
			{
				if (parse->data[i].cmd)
					return (1);
			}
			j++;
		}
	}
	return (0);
}

void	h_d(t_parse *parse)
{
	int	i;
	int	c;

	i = 0;
	while (i < parse->num_data)
	{
		c = 0;
		if (parse->data[i].num_red >= 1)
		{
			if (g_status.g_conti == 1)
				break ;
			while (c < parse->data[i].num_red)
			{
				if (parse->data[i].red[c].type == HERDOC)
				{
					if (hd_duty(parse, i, c) == 2)
						break ;
				}
				c++;
			}
		}
		i++;
	}
}

int	hd_duty(t_parse *parse, int i, int c)
{
	int	sts;
	int	id;

	sts = 0;
	pipe(parse->data[i].fd);
	id = fork();
	if (id == 0)
		here_doc(parse, ft_strdup(parse->data[i].red[c].file), i);
	else
	{
		waitpid(id, &sts, 0);
		if (sts == 2)
		{
			parse->data[i].sign = 1;
			g_status.g_status = 1;
			g_status.g_conti = 1;
		}
		else
			g_status.g_status = 0;
		close(parse->data[i].fd[1]);
	}
	return (sts);
}
