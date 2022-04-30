/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:01:17 by gvarys            #+#    #+#             */
/*   Updated: 2022/03/07 14:23:38 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_key(t_envs **envs, char *str_exe)
{
	int		i;
	char	*key;

	i = 0;
	while (str_exe[i] != '=')
		i++;
	key = ft_substr(str_exe, 0, i);
	if (!key)
		exit(error(1));
	if (search_envs(envs, key))
		remove_envs(envs, key);
	free(key);
}

static void	empty_handler(t_envs *envs)
{
	while (envs)
	{
		printf("declare -x %s=%s\n", envs->key, envs->value);
		envs = envs->next;
	}
}

static int	equal_check(char *str_exe)
{
	size_t	i;

	i = 0;
	while (str_exe[i])
	{
		if (str_exe[i] == '=')
			break ;
		i++;
	}
	if (i == ft_strlen(str_exe))
		return (1);
	return (0);
}

void	my_export(t_minishell *m_shell, char *str_exe)
{
	if (!(*str_exe))
	{
		empty_handler(m_shell->envs);
		m_shell->error_code = 0;
		return ;
	}
	if (equal_check(str_exe))
		return ;
	if (!valid_chars_in_env(str_exe + 1))
	{
		printf("minishell $ export: not a valid identifier\n");
		m_shell->error_code = 1;
	}
	else
	{
		check_key(&m_shell->envs, str_exe + 1);
		parce_envp(&m_shell->envs, str_exe + 1);
	}
	m_shell->error_code = 0;
}
