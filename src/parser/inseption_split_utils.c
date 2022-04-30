/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inseption_split_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 14:20:57 by ereginia          #+#    #+#             */
/*   Updated: 2022/03/05 15:44:12 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_write(t_minishell *m_shell, char *str, t_stuff *iter, char *res)
{
	char	*temp;

	while (str[iter->i + iter->j + 1] && (ft_isalnum(str[iter->i + iter->j + 1])
			|| str[iter->i + iter->j + 1] == '?'))
		iter->j++;
	iter->buf = ft_substr(&str[iter->i], 1, iter->j);
	if (!ft_strncmp(iter->buf, "?", 2))
		temp = ft_itoa(m_shell->error_code);
	else
		temp = search_envs(&m_shell->envs, iter->buf);
	ft_strlcpy(&res[iter->k], temp, ft_strlen(temp) + 1);
	iter->k = iter->k + ft_strlen(temp);
	if (!ft_strncmp(iter->buf, "?", 2))
		free(temp);
	free(iter->buf);
	iter->i = iter->i + iter->j + 1;
	iter->j = 0;
}

int	flag_for_len(char c, t_stuff *iter)
{
	if (c == '\'' && iter->flag == 0)
	{
		iter->flag = 1;
		iter_ik(iter);
		return (1);
	}
	if (c == '\"' && iter->flag == 0)
	{
		iter->flag = 2;
		iter_ik(iter);
		return (1);
	}
	return (0);
}

void	word_len_in_quotes(t_minishell *m_shell, char *str, t_stuff *iter)
{
	if (str[iter->i] == '\'' && iter->flag == 1)
		iter->flag = 3;
	if (str[iter->i] == '\"' && iter->flag == 2)
		iter->flag = 3;
	if (str[iter->i] == '$' && iter->flag != 1)
		iter->k = iter->k + dollar_len(m_shell, &str[iter->i], &iter->i);
	else
		iter_ik(iter);
}
