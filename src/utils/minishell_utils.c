/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:38:24 by ereginia          #+#    #+#             */
/*   Updated: 2022/03/06 20:14:22 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check binary
//if exist -> return path
//else -> null
char	*ft_exist(char *env, char *cmd)
{
	char	**path;
	char	*buf;
	char	*buf2;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	path = ft_split(env, ':');
	while (path[i] != NULL)
	{
		buf = ft_strjoin(path[i], "/");
		buf2 = ft_strjoin(buf, cmd);
		free(buf);
		if (!access(buf2, 0))
		{
			free_split(path);
			return (buf2);
		}
		free(buf2);
		i++;
	}
	free_split(path);
	return (NULL);
}

//dup2 with error check
int	ft_dup(int old, int newfd)
{
	int	buf;

	buf = dup2(old, newfd);
	if (buf == -1)
	{
		ft_putstr_fd("dup2 error\n", 2);
		exit(EXIT_FAILURE);
	}
	return (buf);
}

//fork with error check
int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("fork failed\n", 2);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

//pipe with error check
void	ft_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("pipe creation failed\n", 2);
		exit(EXIT_FAILURE);
	}
}
