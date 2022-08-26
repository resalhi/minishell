/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullfill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:07:43 by mmanouze          #+#    #+#             */
/*   Updated: 2022/08/21 19:00:12 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_parse *parse, int i)
{
	int	j;
	int	c;

	j = 0;
	c = 0;
	if (parse->data[i].cmd)
	{
		c++;
		while (parse->data[i].args[j])
		{
			j++;
			c++;
		}
	}
	return (c);
}

char	**join_args(t_parse *parse, int i)
{
	char	**split;
	int		j;
	int		c;
	int		len;

	j = 0;
	c = 0;
	len = count_args(parse, i);
	split = malloc(sizeof(char *) * (len + 1));
	if (parse->data[i].cmd)
	{
		split[j] = ft_strdup(parse->data[i].cmd);
		j++;
		if (parse->data[i].args[c])
		{
			while (parse->data[i].args[c])
			{
				split[j++] = ft_strdup(parse->data[i].args[c]);
				c++;
			}
		}
		split[j] = 0;
	}
	return (split);
}
