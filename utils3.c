/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:39:30 by ressalhi          #+#    #+#             */
/*   Updated: 2022/08/21 18:52:31 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_qoutes3(char *str, int i, t_parse *parse, char c)
{
	parse->dqoute++;
	i++;
	while (str[i])
	{
		if (str[i] == c)
		{
			parse->dqoute++;
			break ;
		}
		i++;
	}
	return (i);
}

int	check_qoutes4(char *str, int i, t_parse *parse, char c)
{
	parse->sqoute++;
	i++;
	while (str[i])
	{
		if (str[i] == c)
		{
			parse->sqoute++;
			break ;
		}
		i++;
	}
	return (i);
}

int	ft_check_qoutes3(t_parse *parse)
{
	if (parse->dqoute % 2 != 0 || parse->sqoute % 2 != 0)
	{
		g_status.g_status = 258;
		printf("Unclosed Qoute\n");
		return (0);
	}
	return (1);
}

int	check_qoutes2(char *str, t_parse *parse)
{
	int	i;

	parse->dqoute = 0;
	parse->sqoute = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i = check_qoutes3(str, i, parse, '"');
			if (!str[i])
				break ;
		}
		else if (str[i] == 39)
		{
			i = check_qoutes4(str, i, parse, 39);
			if (!str[i])
				break ;
		}
		i++;
	}
	if (!ft_check_qoutes3(parse))
		return (0);
	return (1);
}

int	check_qoutes(char **tab, t_parse *parse)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!check_qoutes2(tab[i], parse))
			return (0);
		i++;
	}
	return (1);
}
