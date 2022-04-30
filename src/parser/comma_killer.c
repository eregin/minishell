/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comma_killer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:20:45 by ereginia          #+#    #+#             */
/*   Updated: 2022/03/05 15:34:23 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char *str)
{
	int	i;
	int	flag;
	int	word;

	i = 0;
	flag = 0;
	word = 1;
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
		if (str[i] == ' ' && str[i + 1] != ' ' && !flag)
			word++;
		i++;
	}
	return (word);
}

static int	char_count(char *str, int *i)
{
	t_stuff	iter;

	ft_memset(&iter, 0, sizeof(iter));
	iter.k = *i;
	while (str[*i])
	{
		if (str[*i] == '\'' && iter.flag == 0)
		{
			iter.j++;
			iter.flag = 1;
		}
		else if (str[*i] == '\'' && iter.flag == 1)
			iter.flag = 0;
		if (str[*i] == '\"' && iter.flag == 0)
		{
			iter.j++;
			iter.flag = 2;
		}
		else if (str[*i] == '\"' && iter.flag == 2)
			iter.flag = 0;
		if (str[*i] == ' ' && !iter.flag)
			break ;
		*i = *i + 1;
	}
	return (*i - 2 * iter.j - iter.k);
}

static void	write_word(char *dest, char *from, int size)
{
	t_stuff	iter;

	ft_memset(&iter, 0, sizeof(iter));
	while (from[iter.i] && iter.j < size)
	{
		if (from[iter.i] == '\'' && iter.flag == 0)
			iter.flag = 1;
		else if (from[iter.i] == '\'' && iter.flag == 1)
			iter.flag = 0;
		if (from[iter.i] == '\"' && iter.flag == 0)
			iter.flag = 2;
		else if (from[iter.i] == '\"' && iter.flag == 2)
			iter.flag = 0;
		if ((from[iter.i] == '\'' && iter.flag != 2)
			|| (from[iter.i] == '\"' && iter.flag != 1))
		{
			iter.i++;
			continue ;
		}
		dest[iter.j] = from[iter.i];
		iter.i++;
		iter.j++;
	}
	dest[iter.j] = '\0';
}

static void	write_split(char **split, char *str)
{
	int		i;
	int		j;
	int		k;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		k = i;
		j = char_count(str, &i);
		split[word] = (char *)malloc(sizeof(char) * (j + 1));
		write_word(split[word], str + k, j);
		if (str[i] == ' ')
			i++;
		word++;
	}
	split[word] = NULL;
}

char	**comma_killer(char *str)
{
	char	**res;
	int		words;
	int		i;

	i = 0;
	words = count_words(str);
	if (words < 0)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	write_split(res, str);
	return (res);
}
