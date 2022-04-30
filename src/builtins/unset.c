/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:27:46 by gvarys            #+#    #+#             */
/*   Updated: 2022/03/07 14:25:26 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_minishell *m_shell, char *str_exe)
{
	if (!(*str_exe))
		m_shell->error_code = 0;
	else
	{
		if (!valid_chars_in_env(str_exe))
		{
			printf("minishell $ unset: not a valid identifier\n");
			m_shell->error_code = 1;
		}
		else
			remove_envs(&m_shell->envs, str_exe);
		m_shell->error_code = 0;
	}
}
