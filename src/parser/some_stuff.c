/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 13:11:33 by ereginia          #+#    #+#             */
/*   Updated: 2022/03/07 11:38:08 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_flag(char *str, t_stuff *iter)
{
	if (str[iter->i] == '\'' && iter->flag == 0)
		iter->flag = 1;
	else if (str[iter->i] == '\'' && iter->flag == 1)
		iter->flag = 0;
	if (str[iter->i] == '\"' && iter->flag == 0)
		iter->flag = 2;
	else if (str[iter->i] == '\"' && iter->flag == 2)
		iter->flag = 0;
}

void	set_half_flag(char *str, t_stuff *iter)
{
	if (str[iter->i] == '\'')
		iter->flag = 1;
	if (str[iter->i] == '\"')
		iter->flag = 2;
}

void	iter_ik(t_stuff *iter)
{
	iter->i++;
	iter->k++;
}

int	char_is_separator(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ';')
		return (1);
	if (c == ' ')
		return (2);
	if (c == '\0')
		return (3);
	return (0);
}

int	count_words_helper(char *str, t_stuff *iter)
{
	int	words;

	words = 0;
	if (char_is_separator(str[iter->i + 1]) > 0
		&& char_is_separator(str[iter->i]) == 0)
		words++;
	if (char_is_separator(str[iter->i]) > 0
		&& char_is_separator(str[iter->i]) < 3 && !str[iter->i + 1])
		words++;
	if (char_is_separator(str[iter->i]) > 0
		&& char_is_separator(str[iter->i + 1]) == 0)
		words++;
	if (char_is_separator(str[iter->i]) == 2
		&& char_is_separator(str[iter->i + 1]) == 0)
		words--;
	if (char_is_separator(str[iter->i]) == 1
		&& char_is_separator(str[iter->i + 1]) == 2)
		words++;
	return (words);
}
