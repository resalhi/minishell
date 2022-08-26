/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:36:35 by ressalhi          #+#    #+#             */
/*   Updated: 2022/08/21 18:43:59 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skiping_qoute(char **str, int i, int *j, char c)
{
	(*j)++;
	while (str[i][(*j)] != c && str[i][(*j)])
		(*j)++;
}

void	counting_red(char **str, int i, int *j, int *count)
{
	if ((str[i][(*j)] == '>' && str[i][(*j) + 1] == '>')
		|| (str[i][(*j)] == '<' && str[i][(*j) + 1] == '<'))
	{
		(*j)++;
		(*count)++;
	}
	else if (str[i][(*j)] == '>' || str[i][(*j)] == '<')
		(*count)++;
}

int	count_red(char **str)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '"')
				skiping_qoute(str, i, &j, '"');
			else if (str[i][j] == 39)
				skiping_qoute(str, i, &j, 39);
			counting_red(str, i, &j, &count);
			j++;
		}
		i++;
	}
	return (count);
}

char	**redirections(char **tab, t_data *data)
{
	int		i;
	char	**t;

	i = 0;
	while (tab[i])
		i++;
	t = malloc(sizeof(char *) * (i + 1));
	if (!t)
		return (0);
	data->num_red = count_red(tab);
	data->red = malloc(sizeof(t_red) * data->num_red);
	if (!data->red)
		return (0);
	return (redirections2(tab, t, data));
}

int	parsing2(char **t, t_parse *parse, int i)
{
	int	j;
	int	k;

	k = 0;
	while (t[k])
		k++;
	parse->data[i].cmd = ft_strdup(t[0]);
	free(t[0]);
	parse->data[i].args = malloc(sizeof(char *) * k);
	k = 0;
	j = 1;
	while (t[j])
	{
		parse->data[i].args[k++] = ft_strdup(t[j]);
		free(t[j]);
		j++;
	}
	parse->data[i].args[k] = 0;
	return (1);
}
