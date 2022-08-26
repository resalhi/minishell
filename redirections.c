/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:32:40 by ressalhi          #+#    #+#             */
/*   Updated: 2022/07/20 19:23:43 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirections_append(t_data *data, char **tab, int i, int *j)
{
	data->red[*j].type = APPEND;
	i++;
	data->red[*j].file = ft_strdup(tab[i]);
	(*j)++;
	return (i);
}

int	redirections_herdoc(t_data *data, char **tab, int i, int *j)
{
	data->red[*j].type = HERDOC;
	i++;
	data->red[*j].file = ft_strdup(tab[i]);
	(*j)++;
	return (i);
}

int	redirections_output(t_data *data, char **tab, int i, int *j)
{
	data->red[*j].type = OUTPUT;
	i++;
	data->red[*j].file = ft_strdup(tab[i]);
	(*j)++;
	return (i);
}

int	redirections_input(t_data *data, char **tab, int i, int *j)
{
	data->red[*j].type = INPUT;
	i++;
	data->red[*j].file = ft_strdup(tab[i]);
	(*j)++;
	return (i);
}

char	**redirections2(char **tab, char **t, t_data *data)
{
	int	i;
	int	j;
	int	h;

	j = 0;
	h = 0;
	i = 0;
	while (tab[i])
	{
		if (!ft_strcmp(tab[i], ">>"))
			i = redirections_append(data, tab, i, &j);
		else if (!ft_strcmp(tab[i], "<<"))
			i = redirections_herdoc(data, tab, i, &j);
		else if (!ft_strcmp(tab[i], ">"))
			i = redirections_output(data, tab, i, &j);
		else if (!ft_strcmp(tab[i], "<"))
			i = redirections_input(data, tab, i, &j);
		else
			t[h++] = ft_strdup(tab[i]);
		i++;
	}
	t[h] = 0;
	ft_free_tab(tab);
	return (t);
}
