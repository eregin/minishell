/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:57:58 by gvarys            #+#    #+#             */
/*   Updated: 2022/03/05 13:33:48 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_builtins(t_minishell *m_shell, char *str, int id)
{
	if (id == 1)
		my_cd(m_shell, str);
	if (id == 5)
	{
		m_shell->error_code = 0;
		my_echo(str + 5, m_shell);
	}
	if (id == 6)
	{
		m_shell->error_code = 0;
		env(m_shell->envs);
	}
	if (id == 2)
		my_exit(m_shell, str + 4);
	if (id == 3)
		my_export(m_shell, str + 6);
	if (id == 7)
	{
		m_shell->error_code = 0;
		my_pwd();
	}
	if (id == 4)
		unset(m_shell, str + 6);
	return (1);
}

int	builtints_handler(t_minishell *m_shell, char *str, bool flag)
{
	int	exit_status;

	exit_status = 0;
	if (!str)
		return (exit_status);
	if (!(ft_strncmp(str, "cd", 2)) && (str[2] == ' ' || str[2] == 0))
		exit_status = 1;
	if (!(ft_strncmp(str, "echo", 4)) && (str[4] == ' ' || str[4] == 0))
		exit_status = 5;
	if (!(ft_strncmp(str, "env", 3)) && (str[3] == ' ' || str[3] == 0))
		exit_status = 6;
	if (!(ft_strncmp(str, "exit", 4)) && (str[4] == ' ' || str[4] == 0))
		exit_status = 2;
	if (!(ft_strncmp(str, "export", 6)) && (str[6] == ' ' || str[6] == 0))
		exit_status = 3;
	if (!(ft_strncmp(str, "pwd", 3)) && (str[3] == ' ' || str[3] == 0))
		exit_status = 7;
	if (!(ft_strncmp(str, "unset", 5)) && (str[5] == ' ' || str[5] == 0))
		exit_status = 4;
	if ((exit_status < 5 && exit_status > 0) || (flag && exit_status > 4))
		return (execute_builtins(m_shell, str, exit_status));
	return (0);
}
