/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:50:37 by gvarys            #+#    #+#             */
/*   Updated: 2022/03/05 11:41:28 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_exit(t_minishell *m_shell, char *str_exe)
{
	int	i;

	if (!str_exe[0])
		exit(m_shell->error_code);
	else
	{
		i = 1;
		while (str_exe[i])
		{
			if (!(ft_isdigit(str_exe[i])))
			{
				printf("minishell $ : %s: numeric argument required\n", str_exe);
				exit(255);
			}
			i++;
		}
		exit(ft_atoi(str_exe) % 256);
	}
}
