/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoura-d <vmoura-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:00:00 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/19 11:39:14 by vmoura-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"

/* -----------INPUT VALIDATOR----------- */

int		input_validator(char *input);
int		handle_quotes_error(int quotes_error);
char	*separate_redirs(char *input);
char	*separate_pipe(char *input);
char	*format_input(char *input, char **env, t_exit exit_code);
int		check_quotes(char *input);
int		check_redirs(char *input);
int		check_pipes(char *input);

/* -----------------CMD----------------- */

t_cmd	*create_cmd(t_token **current, int args_count, int type,
			int redir_count);
void	define_cmd(t_token *start, int cmd_count, int **args_count,
			int **types);
void	define_cmd_type(int is_builtin_flag, int is_assignment_flag,
			int *types);
int		is_assignment(char *str);
int		is_builtin(char *arg);
int		count_cmds(t_token *start);
void	jump_next_cmd(t_token **current);
void	define_redir(t_token **current, t_redir **redir, int *n);
int		init_redir(t_redir **redir, int redir_count);
int		init_cmd(t_cmd **new_cmd, int args_count);

/* -------------BINARY TREE------------- */

int		count_pipes(t_token *start);
t_node	*create_cmd_node(t_token **current, int args_count, int type);
t_node	*create_pipe_node(void);
t_node	*build_tree(t_token *tokens, int env_og_size);
void	assign_root_parent(t_node *node, t_node *root);

#endif