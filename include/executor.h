/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:00:00 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/24 15:52:44 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "types.h"

/* ---------------EXECUTOR--------------- */

int		parse(char **input, t_token **head, t_node **root, int env_og_size);
char	*receive_input(char **env, t_exit *exit_code, int color);
int		exit_shell(t_token **head, t_node **root, char ***env,
			t_exit exit_code);
int		execute_builtin(t_node *root, char ***env, t_exit *exit_code,
			int redir);
int		execute_cmd(t_node *root, char ***env, t_exit *exit_code);
char	*get_path(char *cmd, char **env);
void	execve_error(t_node *root, char *path, t_exit *exit_code);
void	execute_external(char *path, t_node *root, t_exit *exit_code,
			char **env);
int		execute_tree(t_node *root, char ***env, t_exit *exit_code);
int		execute_node(t_node *root, char ***env, t_exit *exit_code, int redir);
int		execute_all(t_node *root, char ***env, t_exit *exit_code);
int		execute_pipe(t_node *node, char ***env, t_exit *exit_code);
int		send_left_node(t_node *node, int *pipe_fd, char ***env,
			t_exit *exit_code);
int		send_right_node(t_node *node, int *pipe_fd, char ***env,
			t_exit *exit_code);

/* ---------------BUILTINS--------------- */

int		builtin_echo(char **args, t_exit *shell_state);
int		builtin_cd(char **args, t_exit *shell_state, char ***env);
int		builtin_pwd(t_exit *shell_state);
int		builtin_export(char **args, char ***envp, t_exit *shell_state);
int		print_export(char **envp, t_exit *shell_state);
void	print_single_var(char *var);
int		find_var_index(char **envp, char *name, int len);
int		update_declared_var(char ***envp, int idx, char *arg);
int		declare_export(char *arg, char ***envp, char **new_env, char *new_var);
int		handle_concat_existing(char ***envp, int idx, char *name,
			char *new_val);
int		handle_concat_new(char ***envp, char *name, char *new_val);
int		process_concat(char *arg, char ***envp);
int		update_existing(char ***envp, int idx, char *new_var);
int		add_new_var(char ***envp, char *new_var);
int		process_assign(char *arg, char ***envp);
int		process_arg(char *arg, char ***envp, int type);
int		builtin_unset(char **args, char ***envp, t_exit *shell_state);
int		builtin_env(char **envp, t_exit *shell_state);
int		builtin_exit(t_node *root, char **env, t_exit exit_code);
void	exit_cleanup(char **env, t_node *root, int status);
char	*join_key_val(const char *key_eq, const char *val);
int		append_kv_to_env(char ***env, char *kv);
int		update_env_var(char ***env, const char *key_eq, const char *val);
int		do_cd_dash(char ***env, char **oldpwd_val);
int		do_cd_home(char ***env);
char	*get_prev_pwd(char **env);
int		change_dir(char **args, char ***env, char **oldpwd_val);
char	**expand_env(char ***envp);
char	*build_full_var(char *name, char *value);
char	*get_old_value(char *env_str);
char	*concat_str(char *s1, char *s2);
char	*extract_var_name(char *arg);
int		initialize_command(t_cmd **cmd, int args_count, int redir_count);
void	process_token(t_token **current, t_cmd *cmd, int *i, int *n);
int		allocate_cmd_arrays(int cmd_count, int ***args_count, int ***types);

/* -------------REDIRECTIONS------------- */

int		redir_out(char *arg);
int		redir_append(char *arg);
int		redir_in(char *arg);
int		redir_heredoc(int fd);
int		process_redirections(t_redir *redir, t_exit *exit_code);

/* ---------------HEREDOC--------------- */

int		heredoc(const char *del, int quoted, char **env, t_exit *exit_code);
void	process_heredoc(t_redir **redir, char **env, t_exit *exit_code);
void	process_all_heredocs(t_node *root, char **env, t_exit *exit_code);

#endif