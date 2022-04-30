/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:28:18 by gvarys            #+#    #+#             */
/*   Updated: 2022/03/07 15:08:05 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/syslimits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <editline/readline.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include "../libft/libft.h"

# define NOTHIN 0
# define PIPE 1
# define BIN 2
# define REDIRECT_IN 3
# define REDIRECT_OUT 4
# define HEREDOC 5
# define REDIRECT_AP 6
# define SYNTAX_ERROR 7

typedef struct s_stuff
{
	int		i;
	int		j;
	int		k;
	int		flag;
	char	*buf;
}	t_stuff;

typedef struct s_pipes
{
	int	**pipes;
	int	*pids;
	int	pipe_count;
	int	pid_count;
}	t_pipes;

typedef struct s_str_exe
{
	char				*str_exe;
	int					type;
	struct s_str_exe	*prev;
	struct s_str_exe	*next;
}	t_str_exe;

typedef struct s_envs
{
	char			*key;
	char			*value;
	struct s_envs	*next;
}	t_envs;

typedef struct s_minishell
{
	int			error_code;
	t_envs		*envs;
	t_str_exe	*str_exe;
}	t_minishell;

//minishell_utils.c
char		*ft_exist(char *env, char *cmd);
int			ft_dup(int old, int newfd);
int			ft_fork(void);
void		ft_pipe(int *fd);
//pipes_and_pids.c
int			**ft_piping(int count);
int			*ft_piding(int count);
void		close_unusedpipes(int **pipes, int pipe_num1, \
	int pipe_num2, int count);
void		wait_all_pids(int pids_count);

//execute_and_redirects.c
void		execute_process(char *c_line, t_minishell *m_shell);
void		read_redirect(char *file_path);
void		write_redirect(char *file_path, int mode);
void		read_heredoc_process(char *stop, int fd);
//envp.c
void		envp_to_dict(t_envs **envs, char **envp);
char		*search_envs(t_envs **envs, char *key);
void		remove_envs(t_envs **envs, char *key);
bool		valid_chars_in_env(char *key);
void		parce_envp(t_envs **envs, char *envp);

//signals
void		start_signals(void);

//readline prototypes
void		rl_replace_line(const char *text, int clear_undo);

//errors
int			error(int err);

// parser/parser.c
int			type_searcher(char *str);
void		parse_str(t_minishell *m_shell, char *str);
void		str_exe_addback(t_str_exe **str_exe, t_str_exe *new);
void		free_str_exe(t_str_exe *str_exe);
t_str_exe	*create_str_exe(char *content);
// parser/parser_utils.c
void		parse_handler(t_minishell *m_shell, char **str);
int			check_syntax(char **str);
// parser/inseption_split.c
void		split_inseption(t_minishell *m_shell, char **spt);
int			dollar_len(t_minishell *m_shell, char *str, int *l);
// parser/comma_killer.c
char		**comma_killer(char *str);
// parser/some_staff.c
void		set_flag(char *str, t_stuff *iter);
void		iter_ik(t_stuff *iter);
void		set_half_flag(char *str, t_stuff *iter);
int			char_is_separator(char c);
int			count_words_helper(char *str, t_stuff *iter);
// parser/inseption_split_utils.c
void		dollar_write(t_minishell *m_shell, char *str, \
	t_stuff *iter, char *res);
int			flag_for_len(char c, t_stuff *iter);
void		word_len_in_quotes(t_minishell *m_shell, char *str, t_stuff *iter);

// utils/ft_split_delux.c
char		**ft_split_delux(char *str);

// utils/clean.c
void		free_split(char **tofree);

// executable/exe.c
void		executable(t_minishell	*m_shell, t_str_exe *str_exec, \
	t_pipes *pipex, int i);
t_str_exe	*get_next_pipe(t_str_exe *str_exec);
int			pipe_type(t_str_exe *str_exec);
int			pipes_counter(t_minishell	*m_shell);
int			pids_counter(t_minishell	*m_shell);
int			which_pipe(t_str_exe *str_exec);
// executable/exe_utils.c
char		**get_envp(t_envs *envs);

//builtins
int			builtints_handler(t_minishell *m_shell, char *str, bool flag);
void		unset(t_minishell *m_shell, char *str_exe);
void		env(t_envs *envs);
void		my_exit(t_minishell *m_shell, char *str_exe);
void		my_pwd(void);
void		my_export(t_minishell *m_shell, char *str_exe);
void		my_cd(t_minishell *m_shell, char *str_exe);
void		my_echo(char *str_exe, t_minishell *m_shell);

#endif