/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:25:13 by ereginia          #+#    #+#             */
/*   Updated: 2022/03/06 20:14:27 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check how much forks we need
int	pids_counter(t_minishell *m_shell)
{
	t_str_exe	*buf;
	int			pids;

	pids = 1;
	buf = m_shell->str_exe;
	while (buf)
	{
		if (buf->type == 1 || buf->type == 2 || buf->type == 5)
			pids++;
		buf = buf->next;
	}
	if (buf == m_shell->str_exe)
		return (0);
	return (pids);
}

int	pipes_counter(t_minishell *m_shell)
{
	t_str_exe	*buf;
	int			pipes;

	pipes = 0;
	buf = m_shell->str_exe;
	while (buf)
	{
		if (buf->type == 1 || buf->type == 5)
			pipes++;
		buf = buf->next;
	}
	return (pipes);
}

t_str_exe	*get_next_pipe(t_str_exe *str_exec)
{
	while (str_exec && str_exec->type > 2 && str_exec->type != 5)
		str_exec = (str_exec)->next;
	return (str_exec->next);
}

int	pipe_type(t_str_exe *str_exec)
{
	int			i;
	int			j;
	t_str_exe	*buf;

	buf = str_exec;
	if (buf->prev)
		i = (buf->prev->type == 1 || buf->prev->type == 5);
	else
		i = 0;
	while (buf && buf->type > 2 && str_exec->type != 5)
		buf = buf->next;
	j = (buf->type == 1 || buf->type == 5);
	return (i + 2 * j);
}

//number of bottom pipe
int	which_pipe(t_str_exe *str_exec)
{
	t_str_exe	*buf;
	int			count;

	count = 0;
	buf = str_exec;
	while (buf)
	{
		if (buf->prev && (buf->prev->type == 1 || buf->prev->type == 5))
			count++;
		buf = buf->prev;
	}
	return (count);
}
