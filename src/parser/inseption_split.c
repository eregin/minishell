/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inseption_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 10:52:41 by ereginia          #+#    #+#             */
/*   Updated: 2022/03/07 11:23:22 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_dollar(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '\'' && flag == 0)
			flag = 1;
		else if (str[i] == '\'' && flag == 1)
			flag = 0;
		if (str[i] == '\"' && flag == 0)
			flag = 2;
		else if (str[i] == '\"' && flag == 2)
			flag = 0;
		if (str[i] == '$' && flag != 1)
			return (1);
		i++;
	}
	return (0);
}

int	dollar_len(t_minishell *m_shell, char *str, int *l)
{
	t_stuff	iter;

	ft_memset(&iter, 0, sizeof(iter));
	while (str[iter.i + 1] && (ft_isalnum(str[iter.i + 1])
			|| str[iter.i + 1] == '?'))
		iter.i++;
	*l = *l + iter.i + 1;
	iter.buf = ft_substr(str, 1, iter.i);
	if (!ft_strncmp(iter.buf, "?", 2))
	{
		iter.k++;
		while (iter.i / 10)
		{
			iter.i = iter.i / 10;
			iter.k++;
		}
	}
	else
		iter.k = ft_strlen(search_envs(&m_shell->envs, iter.buf));
	free(iter.buf);
	return (iter.k);
}

static int	word_len(t_minishell *m_shell, char *str)
{
	t_stuff	iter;

	ft_memset(&iter, 0, sizeof(iter));
	while (str[iter.i])
	{
		if (flag_for_len(str[iter.i], &iter))
			continue ;
		while (str[iter.i] && iter.flag)
			word_len_in_quotes(m_shell, str, &iter);
		if (iter.flag == 3)
		{
			iter.flag = 0;
			continue ;
		}
		if (str[iter.i] && !iter.flag)
		{
			if (str[iter.i] == '$')
				iter.k = iter.k + dollar_len(m_shell, &str[iter.i], &iter.i);
			else
				iter_ik(&iter);
		}
	}
	return (iter.k);
}

static char	*word_replace(t_minishell *m_shell, char *str)
{
	char	*res;
	t_stuff	iter;

	ft_memset(&iter, 0, sizeof(iter));
	res = (char *)malloc(sizeof(char) * word_len(m_shell, str) + 1);
	while (str[iter.i])
	{
		set_flag(str, &iter);
		if (str[iter.i] != '$' || iter.flag == 1)
			res[iter.k] = str[iter.i];
		else
		{
			dollar_write(m_shell, str, &iter, res);
			continue ;
		}
		iter_ik(&iter);
	}
	res[iter.k] = '\0';
	return (res);
}

void	split_inseption(t_minishell *m_shell, char **spt)
{
	int		i;
	char	*buf;

	i = 0;
	if (spt == NULL)
		return ;
	while (spt[i])
	{
		if (is_dollar(spt[i]))
		{
			buf = spt[i];
			spt[i] = word_replace(m_shell, buf);
			free(buf);
		}
		i++;
	}
}
