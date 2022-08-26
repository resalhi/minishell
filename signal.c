/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:18:18 by mmanouze          #+#    #+#             */
/*   Updated: 2022/08/23 11:39:24 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int sign)
{
	if (sign == SIGINT && !g_status.g_herd)
	{
		g_status.g_status = 1;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	check_space(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (str[j] == ' ')
		j++;
	if (j == i)
		return (1);
	else
		return (0);
}

int	check(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
	{
		free(str);
		return (1);
	}
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	free(str);
	return (1);
}
