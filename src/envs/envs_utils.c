/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:31:08 by gvarys            #+#    #+#             */
/*   Updated: 2022/03/07 13:36:58 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	valid_chars_in_env(char *key)
{
	if (key && (ft_isalpha(*key) || *key == '_'))
		key++;
	else
		return (false);
	while (*key && *key != '=')
	{
		if (ft_isalnum(*key) || *key == '_')
			key++;
		else
			return (false);
	}
	return (true);
}

static void	free_one_env(t_envs *envs)
{
	free(envs->key);
	free(envs->value);
	free(envs);
}

void	remove_envs(t_envs **envs, char *key)
{
	t_envs	*save;
	t_envs	*temp;

	if (!envs || !(*envs) || !key)
		return ;
	temp = *envs;
	if (!(ft_strncmp(temp->key, key, ft_strlen(key) + 1)))
	{
		save = temp->next;
		free_one_env(temp);
		*envs = save;
	}
	while (temp && temp->next)
	{
		if (!(ft_strncmp(temp->next->key, key, ft_strlen(key) + 1)))
		{
			save = temp->next->next;
			free_one_env(temp->next);
			temp->next = save;
		}
		temp = temp->next;
	}
}

char	**get_envp(t_envs *envs)
{
	char	**result;
	char	*temp;
	t_envs	*buf;
	int		words;

	words = 0;
	buf = envs;
	while (buf)
	{
		buf = buf->next;
		words++;
	}
	result = (char **)malloc(sizeof(char *) * (words + 1));
	words = 0;
	buf = envs;
	while (buf)
	{
		temp = ft_strjoin(buf->key, "=");
		result[words] = ft_strjoin(temp, buf->value);
		free(temp);
		buf = buf->next;
		words++;
	}
	result[words] = NULL;
	return (result);
}
