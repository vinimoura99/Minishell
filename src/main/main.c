/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:28:29 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/24 15:53:00 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exit		*g_exit_code;

static void	process_command(char *input, t_token **head, t_node **root,
		t_main_data *data)
{
	parse(&input, head, root, data->env_og_size);
	process_all_heredocs(*root, data->env, &data->exit_code);
	if (data->exit_code.exit_code != -5)
		execute_all(*root, &data->env, &data->exit_code);
	else
		data->exit_code.exit_code = 130;
	free_binary_tree(root);
}

int	main(int ac, char **av, char **envp)
{
	int			color;
	char		*input;
	t_token		*head;
	t_node		*root;
	t_main_data	data;

	(void)ac;
	(void)av;
	g_exit_code = &data.exit_code;
	data.exit_code.exit_code = 0;
	setup_signals_shell();
	data.env_og_size = 0;
	if (envp && *envp)
		data.env = copy_env(envp, &data.env_og_size, &color);
	else
		data.env = build_basic_env(&data.env_og_size, &color);
	while (1)
	{
		input = receive_input(data.env, &data.exit_code, color);
		if (data.exit_code.exit_code == -1)
			break ;
		if (input)
			process_command(input, &head, &root, &data);
	}
	return (exit_shell(&head, &root, &data.env, data.exit_code));
}

int	exit_shell(t_token **head, t_node **root, char ***env, t_exit exit_code)
{
	if (env)
		ft_free_array(env);
	if (exit_code.exit_code == -1)
	{
		printf("exit\n");
		exit_code.exit_code = 0;
		return (exit_code.exit_code);
	}
	free_all(head, root);
	return (exit_code.exit_code);
}

int	parse(char **input, t_token **head, t_node **root, int env_og_size)
{
	int	input_count;

	input_count = ft_strcount_q(*input) + 1;
	(*head) = NULL;
	if (!input_count)
		return (-1);
	if (!head)
	{
		printf("No tokens created\n");
		return (-1);
	}
	tokenizer(*input, head, input_count);
	(*root) = build_tree(*head, env_og_size);
	free_token(head);
	return (0);
}

char	*receive_input(char **env, t_exit *exit_code, int color)
{
	char	*input;
	char	*user;

	user = get_user(env, color);
	input = readline(user);
	free(user);
	if (!input)
	{
		exit_code->exit_code = -1;
		return (NULL);
	}
	if (input[0] == '\0')
	{
		free(input);
		return (NULL);
	}
	add_history(input);
	if (input_validator(input) == -1)
	{
		exit_code->exit_code = 2;
		free(input);
		return (NULL);
	}
	input = format_input(input, env, *exit_code);
	return (input);
}
