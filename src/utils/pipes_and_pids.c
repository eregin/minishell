/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_pids.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:00:45 by ereginia          #+#    #+#             */
/*   Updated: 2022/03/06 20:14:21 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//make pipe array
//each pipe is array[2]
int	**ft_piping(int count)
{
	int	i;
	int	**p_pipes;

	i = -1;
	if (count == 0)
		return (NULL);
	p_pipes = (int **)malloc(sizeof(int *) * (count + 1));
	if (p_pipes == NULL)
		return (NULL);
	while (i++ < count)
	{
		p_pipes[i] = malloc(sizeof(int) * 2);
		if (p_pipes[i] == NULL || pipe(p_pipes[i]) < 0)
		{
			ft_putstr_fd("pipe creation error\n", 2);
			while (i > -1)
			{
				free(p_pipes[i]);
				i--;
			}
			free(p_pipes);
			return (NULL);
		}
	}
	return (p_pipes);
}

//allocate PID array
int	*ft_piding(int count)
{
	int	i;
	int	*p_pids;

	i = 0;
	p_pids = (int *)malloc(sizeof(int) * count);
	return (p_pids);
}

//close unused fd
void	close_unusedpipes(int **pipes, int pipe_num1, int pipe_num2, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if ((i != pipe_num1) && (i != pipe_num2))
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}

//w8 for child
void	wait_all_pids(int pids_count)
{
	int	i;

	i = 0;
	while (i++ < pids_count)
		wait(NULL);
}
