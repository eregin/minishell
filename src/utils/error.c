/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 12:45:45 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/22 15:52:56 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//err - exit status + message to STDERR
int	error(int err)
{
	if (err == 1)
		write(2, "Malloc error\n", 13);
	if (err == 2)
		write(2, "exit\n", 5);
	if (err == 3)
		write(2, "Path error\n", 11);
	return (err);
}
