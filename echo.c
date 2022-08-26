/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 19:29:35 by ressalhi          #+#    #+#             */
/*   Updated: 2022/08/17 16:54:31 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tab(char **tab, int n)
{
	int	i;

	i = n;
	while (tab[i])
	{
		printf("%s", tab[i]);
		i++;
		if (tab[i])
			printf(" ");
	}
	if (n == 0)
		printf("\n");
}

void	ft_echo2(char **tab, int i, int j)
{
	while (tab[i])
	{
		if (tab[i][0] != '-')
		{
			print_tab(tab, i);
			return ;
		}
		j = 1;
		while (tab[i][j])
		{
			if (tab[i][j] != 'n')
			{
				print_tab(tab, i);
				return ;
			}
			j++;
		}
		if (tab[i][j - 1] == '-')
		{
			print_tab(tab, i);
			return ;
		}
		i++;
	}
}

void	ft_echo(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!tab[0])
	{
		printf("\n");
		return ;
	}
	if (tab[0][0] == '-')
		ft_echo2(tab, i, j);
	else
		print_tab(tab, 0);
	g_status.g_status = 0;
}
