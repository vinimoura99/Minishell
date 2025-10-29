/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:00:00 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/23 17:10:29 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

/* -----------------AUX----------------- */

char	*str_remove_at(char *str, int index);
char	*str_add_at(char *str, char to_add, int index);
void	fill_add_at(char *new_str, char *str, char to_add, int index);
char	*str_substitute(char *str, int index, int chars_to_remove, char *str2);
char	char_search(char *input, char *characters, int *start);
int		get_str_index(char **str, char *str_to_search, int check_unset);
int		is_whitespace(char c);
int		is_quoted(char *str);
int		is_envvar_start(char c);
int		is_envvar_char(char c);
int		is_n_flag(const char *arg);
int		is_numeric(const char *str);
int		is_valid_identifier(const char *str);
void	skip_whitespaces(char *input, int *i);
int		ft_strcmp(const char *s1, const char *s2);
int		str_arr_len(char **arr);
void	swap(char **a, char **b);
void	bubble_sort(char **arr, int start, int end);
char	**sorted_copy(char **arr);
char	**copy_str_array(char **arr, int size);
int		define_color(char **envp);

/* -----------------FREE----------------- */

void	free_redir(t_redir **redir);
void	free_cmd(t_cmd **cmd);
void	free_binary_tree(t_node **root);
void	free_all(t_token **head, t_node **root);
void	*ft_free_array(char ***strs);
void	free_token(t_token **head);
void	free_env_vars(char *user_env, char *pwd_env, int pwd_alloc);
void	free_pipe(t_cmd **cmd);
void	free_node(t_node **node);

/* -----------------ENV----------------- */

char	**copy_env(char **env, int *og_size, int *color);
char	**build_basic_env(int *og_size, int *color);
char	*update_shlvl(char *envp);
char	*expand_var(char *str, char **env, t_exit exit_code, int heredoc_flag);
char	*search_var(char *exp_var, char **env);
int		env_index(char *str);
char	*get_user_env(char **env);
char	*get_pwd_env(char **env, char *home_env, int *allocated);
char	*create_pwd_prompt(char *pwd_env);
char	*assemble_user_prompt(char *user_env, char *temp_pwd, int color);
char	*get_user(char **env, int color);
char	*add_quotes_var(char *exp_var, int quotes);

/* ---------------SIGNALS--------------- */

void	sigint_handler(int signo);
void	setup_signals_shell(void);
void	setup_signals_heredoc(void);
void	sigint_heredoc_handler(int signo);
void	sigint_child_handler(int signo);

#endif