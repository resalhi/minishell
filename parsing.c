/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:26:20 by ressalhi          #+#    #+#             */
/*   Updated: 2022/08/21 18:43:24 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_red(t_parse *p, int i)
{
	int	h;

	h = 0;
	while (h < p->data[i].num_red)
	{
		if (p->data[i].red[h].type != HERDOC)
			p->data[i].red[h].file = dollar_hundler(p->data[i].red[h].file,
					p);
		p->data[i].red[h].file = remove_qoutes(p->data[i].red[h].file);
		h++;
	}
}

void	nulling(t_parse *p, char **t, int *i)
{
	p->data[(*i)].cmd = NULL;
	p->data[(*i)].args = malloc(sizeof(char *));
	p->data[(*i)].args[0] = NULL;
	(*i)++;
	free(t);
}

int	parsing_2(char **t, t_parse *p, int i)
{
	parsing2(t, p, i);
	i++;
	free(t);
	return (i);
}

int	parsing(char **tab, t_parse *p)
{
	int		i;
	char	*str;
	char	**t;

	i = 0;
	while (tab[i])
	{
		str = str_to_split(tab[i], ' ');
		if (!str)
			return (0);
		t = ft_split(str, SPLIT_TOKEN);
		free(str);
		t = redirections(t, &p->data[i]);
		if (!t)
			return (0);
		clean_red(p, i);
		if (!t[0])
		{
			nulling(p, t, &i);
			continue ;
		}
		i = parsing_2(t, p, i);
	}
	return (1);
}

int	parser(char *str, t_parse *parse)
{
	char	**tab;
	int		i;

	tab = error_management(str, parse);
	if (!tab)
		return (0);
	tab = expanding(tab);
	i = 0;
	while (tab[i])
		i++;
	parse->data = malloc(sizeof(t_data) * i);
	if (!parse->data)
		return (0);
	parse->num_data = i;
	if (!parsing(tab, parse))
		return (0);
	if (!dollar(parse, i))
		return (0);
	if (!remove_trash(parse, i))
		return (0);
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (1);
}
