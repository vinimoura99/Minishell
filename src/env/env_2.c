/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:21:02 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/23 21:35:44 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_var_value(char *var_value, int heredoc_flag)
{
	char	*processed_value;

	if (!var_value)
		return (ft_strdup(""));
	processed_value = var_value;
	if (is_quoted(processed_value) && !heredoc_flag)
		processed_value = add_quotes_var(processed_value,
				is_quoted(processed_value));
	return (processed_value);
}

static char	*get_var_name(char *str, int i, int *n)
{
	char	*exp_var;

	if (str[i + 1] == '?')
	{
		*n = i + 2;
		return (ft_strdup("?"));
	}
	*n = i + 1;
	if (!is_envvar_char(str[*n]))
		return (NULL);
	while (is_envvar_char(str[*n]))
		++(*n);
	exp_var = malloc(sizeof(char) * (*n - i + 1));
	if (!exp_var)
		return (NULL);
	ft_strlcpy(exp_var, &str[i + 1], *n - i);
	return (exp_var);
}

static char	*handle_exit_code(char *str, int i, t_exit exit_code)
{
	char	*itoa_temp;
	char	*result;

	itoa_temp = ft_itoa(exit_code.exit_code);
	result = str_substitute(str, i, 2, itoa_temp);
	free(itoa_temp);
	return (result);
}

static char	*process_variable(char *str, int i, int *n, t_var_data *data)
{
	char	*exp_var;
	char	*var_value;

	exp_var = get_var_name(str, i, n);
	if (!exp_var)
		return (NULL);
	if (ft_strcmp(exp_var, "?") == 0)
	{
		free(exp_var);
		return (handle_exit_code(str, i, data->exit_code));
	}
	if (ft_strlen(exp_var) == 0)
	{
		free(exp_var);
		return (str_substitute(str, i, *n - i, ""));
	}
	ft_strlcat(exp_var, "=", ft_strlen(exp_var) + 2);
	var_value = process_var_value(search_var(exp_var, data->env),
			data->heredoc_flag);
	free(exp_var);
	str = str_substitute(str, i, *n - i, var_value);
	free(var_value);
	return (str);
}

char	*expand_var(char *str, char **env, t_exit exit_code, int heredoc_flag)
{
	int			i;
	int			n;
	t_var_data	data;

	data.env = env;
	data.exit_code = exit_code;
	data.heredoc_flag = heredoc_flag;
	i = env_index(str);
	while (i != -1)
	{
		str = process_variable(str, i, &n, &data);
		if (!str)
			return (NULL);
		i = env_index(str);
	}
	return (str);
}
