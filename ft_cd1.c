/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanouze <mmanouze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:30:35 by mmanouze          #+#    #+#             */
/*   Updated: 2022/08/22 14:31:33 by mmanouze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cher_home_err(void)
{
	g_status.g_status = 1;
	printf("bash: cd: HOME not set\n");
	if (g_status.g_id)
		exit(1);
}
