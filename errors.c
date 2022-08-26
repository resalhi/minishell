/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:30:31 by ressalhi          #+#    #+#             */
/*   Updated: 2022/08/25 14:04:35 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error2(char *str, int *i)
{
	while (str[(*i)] == ' ' || str[(*i)] == '\t')
		(*i)++;
	if (str[(*i)] == '|' || str[(*i)] == '<'
		|| str[(*i)] == '>' || str[(*i)] == '\0')
	{
		printf("Syntax error\n");
		g_status.g_status = 258;
		return (-1);
	}
	return ((*i));
}

int	check_errors3(char *str, int *i)
{
	if (str[(*i)] == '<')
	{
		(*i)++;
		(*i) = check_error2(str, i);
		if ((*i) == -1)
			return (0);
	}
	else if (str[(*i)] == '>')
	{
		(*i)++;
		(*i) = check_error2(str, i);
		if ((*i) == -1)
			return (0);
	}
	return (1);
}

int	skipping_qoutes(char *str, int *i)
{
	if (str[(*i)] == '"')
	{
		(*i)++;
		if (str[(*i)] == '\0')
			return (0);
		while (str[(*i)] != '"' && str[(*i)])
			(*i)++;
		if (str[(*i)] == '\0')
			return (0);
	}
	else if (str[(*i)] == 39)
	{
		(*i)++;
		if (str[(*i)] == '\0')
			return (0);
		while (str[(*i)] != 39 && str[(*i)])
			(*i)++;
		if (str[(*i)] == '\0')
			return (0);
	}
	return (1);
}

int	checking_red(char *str, int *i)
{
	if (str[(*i)] == '<' && str[(*i) + 1] == '<')
	{
		(*i) = (*i) + 2;
		(*i) = check_error2(str, i);
		if ((*i) == -1)
			return (0);
	}
	else if (str[(*i)] == '>' && str[(*i) + 1] == '>')
	{
		(*i) = (*i) + 2;
		(*i) = check_error2(str, i);
		if ((*i) == -1)
			return (0);
	}
	else if (!check_errors3(str, i))
		return (0);
	return (1);
}

int	check_errors(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!skipping_qoutes(str, &i))
			break ;
		if (!checking_red(str, &i))
			return (0);
		i++;
	}
	return (1);
}
