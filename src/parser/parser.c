/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:00:48 by gvarys            #+#    #+#             */
/*   Updated: 2022/03/07 15:14:52 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	type_searcher(char *str)
{
	if (!str)
		return (0);
	if (!(ft_strncmp(str, "|", 2)))
		return (PIPE);
	if (!(ft_strncmp(str, ";", 2)))
		return (BIN);
	if (!(ft_strncmp(str, "<", 2)))
		return (REDIRECT_IN);
	else if (!(ft_strncmp(str, "<<", 3)))
		return (HEREDOC);
	if (!(ft_strncmp(str, ">", 2)))
		return (REDIRECT_OUT);
	else if (!(ft_strncmp(str, ">>", 3)))
		return (REDIRECT_AP);
	if (str[0] == '|' || str[0] == ';' || str[0] == '<' || str[0] == '>')
		return (SYNTAX_ERROR);
	return (0);
}

t_str_exe	*create_str_exe(char *content)
{
	t_str_exe	*new;

	new = (t_str_exe *)ft_calloc(1, sizeof(t_str_exe));
	if (!new)
		return (new);
	if (content)
		new->str_exe = ft_strdup(content);
	else
		new->str_exe = NULL;
	return (new);
}

void	str_exe_addback(t_str_exe **str_exe, t_str_exe *new)
{
	t_str_exe	*temp;
	t_str_exe	*save;

	save = *str_exe;
	if (!save)
		save = new;
	else
	{
		while (save->next)
			save = save->next;
		temp = save;
		save->next = new;
		temp = save->next;
		temp->prev = save;
	}
}

void	parse_str(t_minishell *m_shell, char *str)
{
	char	**str_split;
	char	*str_temp;

	if (ft_strlen(str) == 0)
		return ;
	str_temp = ft_strtrim(str, " \t");
	if (!str_temp)
		exit(1);
	if (ft_strlen(str_temp) == 0)
		return ;
	str_split = ft_split_delux(str_temp);
	if (!str_split || check_syntax(str_split))
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		m_shell->error_code = 258;
		return ;
	}
	split_inseption(m_shell, str_split);
	free(str_temp);
	parse_handler(m_shell, str_split);
	free_split(str_split);
}

void	free_str_exe(t_str_exe *str_exe)
{
	t_str_exe	*temp;

	while (str_exe)
	{
		temp = str_exe;
		str_exe = str_exe->next;
		if (temp->str_exe)
			free(temp->str_exe);
		if (temp)
			free(temp);
	}
}
