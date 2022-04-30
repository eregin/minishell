/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:09:59 by ereginia          #+#    #+#             */
/*   Updated: 2022/04/30 16:27:25 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	buildins_or_binary(t_minishell *m_shell, t_str_exe *buf)
{
	while (buf)
	{
		if (buf->type < 3 && builtints_handler(m_shell, buf->str_exe, true))
			exit(1);
		if (buf->type < 3)
			execute_process(buf->str_exe, m_shell);
		buf = buf->next;
	}
}

static void	redirect_handle(t_str_exe *buf)
{
	while (buf && buf->type != BIN && buf->type != PIPE)
	{
		if (buf->type == REDIRECT_IN)
			read_redirect(buf->str_exe);
		else if (buf->type == REDIRECT_OUT)
			write_redirect(buf->str_exe, REDIRECT_OUT);
		else if (buf->type == REDIRECT_AP)
			write_redirect(buf->str_exe, REDIRECT_AP);
		buf = buf->next;
	}
}

static void	pipe_laying(t_str_exe *str_exec, t_pipes *pipex, int pipe_id)
{
	if (pipe_type(str_exec) == 2)
	{
		ft_dup(pipex->pipes[pipe_id][1], 1);
		close_unusedpipes(pipex->pipes, -1, -1, pipex->pipe_count);
	}
	else if (pipe_type(str_exec) == 1)
	{
		ft_dup(pipex->pipes[pipe_id - 1][0], 0);
		close_unusedpipes(pipex->pipes, -1, -1, pipex->pipe_count);
	}
	else if (pipe_type(str_exec) == 3)
	{
		ft_dup(pipex->pipes[pipe_id][1], 1);
		ft_dup(pipex->pipes[pipe_id - 1][0], 0);
		close_unusedpipes(pipex->pipes, -1, -1, pipex->pipe_count);
	}
}

static void	norm_helper(t_str_exe *str_exec, t_pipes *pipex, \
	t_minishell *m_shell, int pipe_id)
{
	start_signals();
	signal(SIGQUIT, SIG_DFL);
	if (get_next_pipe(str_exec) && get_next_pipe(str_exec)->prev->type == 5)
		read_heredoc_process(get_next_pipe(str_exec)->prev->str_exe,
			pipex->pipes[pipe_id][1]);
	pipe_laying(str_exec, pipex, pipe_id);
	redirect_handle(str_exec);
	buildins_or_binary(m_shell, str_exec);
	exit(1);
}

void	executable(t_minishell *m_shell, t_str_exe *str_exec,
	t_pipes *pipex, int i)
{
	int			pipe_id;

	pipe_id = which_pipe(str_exec);
	if (builtints_handler(m_shell, str_exec->str_exe, false))
		return ;
	signal(SIGINT, SIG_IGN);
	pipex->pids[i] = ft_fork();
	if (pipex->pids[i] == 0)
		norm_helper(str_exec, pipex, m_shell, pipe_id);
	if (str_exec && (str_exec->type == 2 || str_exec->type == 0
			|| (get_next_pipe(str_exec)
				&& get_next_pipe(str_exec)->prev->type == 5)))
	{
		close_unusedpipes(pipex->pipes, -1, -1, pipe_id);
		waitpid(pipex->pids[i], &m_shell->error_code, 0);
		m_shell->error_code = WEXITSTATUS(m_shell->error_code);
	}
}
