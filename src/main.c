/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:38:16 by gvarys            #+#    #+#             */
/*   Updated: 2022/03/07 12:50:26 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	norm_helper(t_minishell	*m_shell, char *str, t_pipes *pipex)
{
	int			i;
	t_str_exe	*buf;

	parse_str(m_shell, str);
	ft_memset(pipex, 0, sizeof(pipex));
	pipex->pid_count = pids_counter(m_shell);
	pipex->pipe_count = pipes_counter(m_shell);
	pipex->pipes = ft_piping(pipex->pipe_count);
	pipex->pids = ft_piding(pipex->pid_count);
	buf = m_shell->str_exe;
	i = 0;
	while (i < pipex->pid_count && buf)
	{
		executable(m_shell, buf, pipex, i);
		buf = get_next_pipe(buf);
		i++;
	}
}

void	exe_handler(t_minishell	*m_shell, char *str)
{
	t_pipes		pipex;
	int			i;

	norm_helper(m_shell, str, &pipex);
	i = -1;
	close_unusedpipes(pipex.pipes, -1, -1, pipex.pipe_count);
	while (++i < pipex.pipe_count + 1 && pipex.pipe_count)
	{
		free(pipex.pipes[i]);
		pipex.pipes[i] = NULL;
	}
	if (pipex.pipe_count)
	{
		free(pipex.pipes);
		pipex.pipes = NULL;
	}
	free(pipex.pids);
	pipex.pids = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_minishell	m_shell;

	(void) argc;
	(void) argv;
	ft_memset(&m_shell, 0, sizeof(m_shell));
	envp_to_dict(&m_shell.envs, envp);
	while (true)
	{
		start_signals();
		str = readline("minishell $ ");
		if (!str)
		{
			printf("\033[Aminishell $ exit\n");
			exit(0);
		}
		add_history(str);
		exe_handler(&m_shell, str);
		free(str);
		free_str_exe(m_shell.str_exe);
		m_shell.str_exe = NULL;
	}
	return (0);
}
