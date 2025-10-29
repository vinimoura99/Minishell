/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:17:08 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/23 21:46:46 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_var(char *exp_var, char **env)
{
	int	i;
	int	var_len;

	var_len = ft_strlen(exp_var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(exp_var, env[i], ft_strlen(exp_var)) == 0)
			return (ft_strdup(env[i] + var_len));
		i++;
	}
	return (NULL);
}

int	env_index(char *str)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (str[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else if (str[i] == '$' && !single_quote && str[i + 1] != '\0'
			&& (is_envvar_char(str[i + 1]) || str[i + 1] == '?')
			&& !(str[i + 1] >= '0' && str[i + 1] <= '9'))
			return (i);
		i++;
	}
	return (-1);
}

char	*add_quotes_var(char *exp_var, int quotes)
{
	int		new_len;
	char	*new_exp_var;

	if (quotes != 1 && quotes != 2)
		return (NULL);
	new_len = ft_strlen(exp_var) + 2 + 1;
	new_exp_var = malloc(sizeof(char) * (new_len));
	if (!new_exp_var)
		return (NULL);
	if (quotes == 1)
	{
		ft_strlcpy(new_exp_var, "\"", new_len);
		ft_strlcat(new_exp_var, exp_var, new_len);
		ft_strlcat(new_exp_var, "\"", new_len);
	}
	else
	{
		ft_strlcpy(new_exp_var, "'", new_len);
		ft_strlcat(new_exp_var, exp_var, new_len);
		ft_strlcat(new_exp_var, "'", new_len);
	}
	free(exp_var);
	return (new_exp_var);
}

static char	*ret_shlvl_str(int shlvl)
{
	int		len1;
	int		len2;
	char	*shlvl_number_str;
	char	*shlvl_str;

	if (shlvl >= 999)
	{
		ft_putstr_fd(
			"bash: warning: shell level (1000) too high, resetting to 1\n", 2);
		return (ft_strdup("SHLVL=1"));
	}
	++shlvl;
	shlvl_number_str = ft_itoa(shlvl);
	len1 = ft_strlen("SHLVL=");
	len2 = ft_strlen(shlvl_number_str);
	shlvl_str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!shlvl_str)
		return (NULL);
	ft_strlcpy(shlvl_str, "SHLVL=", len1 + 1);
	ft_strlcat(shlvl_str, shlvl_number_str, len1 + len2 + 1);
	free(shlvl_number_str);
	return (shlvl_str);
}

char	*update_shlvl(char *envp)
{
	int		i;
	int		n;
	char	*str_shlvl;

	i = 0;
	char_search(envp, "=", &i);
	if (i < 0 || envp[0] == '-')
		return (ft_strdup("SHLVL=1"));
	++i;
	n = i;
	while (envp[n])
	{
		if (envp[n] && (envp[n] < '0' || envp[n] > '9'))
			return (ft_strdup("SHLVL=1"));
		++n;
	}
	str_shlvl = ret_shlvl_str(ft_atoi(&envp[i]));
	return (str_shlvl);
}
