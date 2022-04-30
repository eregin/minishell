/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:53:49 by gvarys            #+#    #+#             */
/*   Updated: 2022/03/05 12:07:49 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_envs(t_envs **envs, char *key)
{
	t_envs	*temp;

	if (!envs || !(*envs) || !key)
		return (0);
	temp = *envs;
	while (temp)
	{
		if ((ft_strncmp(temp->key, key, ft_strlen(temp->key) + 1)) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (0);
}

static t_envs	*create_envs_dict(char *envp)
{
	int		i;
	int		j;
	t_envs	*new;

	new = (t_envs *) malloc(sizeof(t_envs));
	if (!new)
		exit(error(1));
	i = 0;
	while (envp[i] != '=')
		i++;
	new->key = ft_substr(envp, 0, i);
	if (!new->key)
		exit(error(1));
	j = i + 1;
	while (envp[j] != '\0' && envp[j] != '\n')
		j++;
	new->value = ft_substr(envp, i + 1, j - i);
	if (!new->value)
		exit(error(1));
	new->next = 0;
	return (new);
}

void	parce_envp(t_envs **envs, char *envp)
{
	t_envs	*temp;

	if (!(*envs))
	{
		*envs = create_envs_dict(envp);
	}
	else
	{
		temp = *envs;
		while (temp->next)
			temp = temp->next;
		temp->next = create_envs_dict(envp);
	}
}

void	envp_to_dict(t_envs **envs, char **envp)
{
	int		i;
	char	*number;
	char	*temp;
	char	*temp2;

	i = -1;
	while (envp[++i])
		parce_envp(envs, envp[i]);
	if (search_envs(envs, "SHLVL"))
	{
		number = ft_strdup(search_envs(envs, "SHLVL"));
		remove_envs(envs, "SHLVL");
		temp2 = ft_itoa(ft_atoi(number) + 1);
		temp = ft_strjoin("SHLVL=", temp2);
		parce_envp(envs, temp);
		free(temp2);
		free(temp);
		free(number);
	}
	else
	{
		parce_envp(envs, "SHLVL=1");
	}
	if (!search_envs(envs, "PATH"))
		parce_envp(envs, "PATH=/Users/ereginia\
			/.brew/bin:/usr/local/bin:/usr/bin:/bin:\
			/usr/sbin:/sbin:/usr/local/share/dotnet:\
			/usr/local/munki:/opt/X11/bin:~/.dotnet\
			/tools:/Users/ereginia/.brew/bin");
}
