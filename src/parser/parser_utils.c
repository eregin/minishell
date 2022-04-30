/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:09:23 by ereginia          #+#    #+#             */
/*   Updated: 2022/03/07 15:08:37 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_str_exe	*parse_redirects(t_minishell *m_shell, t_str_exe *temp, \
	char **str, int *i)
{
	int	m;

	m = *i;
	while (str[m] && type_searcher(str[m]) != 1 && type_searcher(str[m]) != 2)
	{
		if (type_searcher(str[m]) > 2)
		{
			if (!temp)
			{
				temp = create_str_exe(str[m + 1]);
				temp->type = type_searcher(str[m]);
				m_shell->str_exe = temp;
			}
			else
			{
				temp = create_str_exe(str[m + 1]);
				temp->type = type_searcher(str[m]);
				str_exe_addback(&m_shell->str_exe, temp);
			}
		}
		m++;
	}
	*i = m;
	return (temp);
}

static char	*parse_cmd(char **str, int i)
{
	char	*result;
	char	*temp;

	result = NULL;
	temp = NULL;
	while (type_searcher(str[i]) != 1 && type_searcher(str[i]) != 2 && str[i])
	{
		if ((i == 0 && type_searcher(str[i]) == 0)
			|| (type_searcher(str[i]) == 0 && type_searcher(str[i - 1]) < 3))
		{
			if (!result)
				result = ft_strdup(str[i]);
			else
			{
				temp = ft_strjoin(result, " ");
				free(result);
				result = ft_strjoin(temp, str[i]);
				free(temp);
			}
		}
		i++;
	}
	return (result);
}

int	check_syntax(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (type_searcher(str[i]) == SYNTAX_ERROR)
			return (1);
		i++;
	}
	return (0);
}

void	parse_handler(t_minishell *m_shell, char **str)
{
	t_str_exe	*temp;
	char		*buf;
	int			i;
	int			m;

	temp = NULL;
	buf = NULL;
	i = 0;
	while (str[i])
	{
		m = i;
		temp = parse_redirects(m_shell, temp, str, &i);
		buf = parse_cmd(str, m);
		temp = create_str_exe(buf);
		temp->type = type_searcher(str[i]);
		if (!m_shell->str_exe)
			m_shell->str_exe = temp;
		else
			str_exe_addback(&m_shell->str_exe, temp);
		free(buf);
		buf = NULL;
		if (str[i] && type_searcher(str[i]) >= 0 && type_searcher(str[i]) <= 2)
			i++;
	}
}
