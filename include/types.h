/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoura-d <vmoura-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:00:00 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/19 13:35:06 by vmoura-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_exit
{
	int				exit_code;
}					t_exit;

typedef struct s_redir
{
	int				*redir_type;
	int				*quotes;
	char			**args;
	int				redir_count;
	int				*heredoc_fd;
}					t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			type;
	int				input_fd;
	int				output_fd;
	t_redir			*redir;
}					t_cmd;

typedef struct s_node
{
	char			type;
	t_cmd			*cmd;
	int				env_og_size;
	struct s_node	*parent;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct s_token
{
	char			type;
	char			*str;
	char			quote;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd_info
{
	int				pipe_count;
	int				*args_count;
	int				*types;
}					t_cmd_info;

typedef struct s_cd_paths
{
	char			*prev_pwd;
	char			*oldpwd_val;
}					t_cd_paths;

typedef struct s_var_data
{
	char			**env;
	t_exit			exit_code;
	int				heredoc_flag;
}					t_var_data;

typedef struct s_heredoc_data
{
	char			**env;
	t_exit			exit_code;
	int				quoted;
}					t_heredoc_data;

typedef struct s_main_data
{
	char			**env;
	t_exit			exit_code;
	int				env_og_size;
}					t_main_data;

# define CMD_BUILT_IN 1
# define CMD_ASSIGNMENT 2
# define CMD_EXTERNAL 3

# define ARGUMENT 1
# define PIPE 2
# define REDIR_IN 3
# define REDIR_OUT 4
# define REDIR_APPEND 5
# define REDIR_HEREDOC 6
# define TOKEN_EOF 7

# define INVALID 0
# define DECLARATION 1
# define ASSIGNMENT 2
# define CONCATENATION 3

#endif