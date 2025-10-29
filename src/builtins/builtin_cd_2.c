/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:26:28 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/22 13:24:09 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prev_pwd(char **env)
{
	char	buf[PATH_MAX];
	char	*pwd;

	pwd = search_var("PWD=", env);
	if (pwd)
		return (pwd);
	if (getcwd(buf, sizeof(buf)))
		return (ft_strdup(buf));
	return (NULL);
}

int	change_dir(char **args, char ***env, char **oldpwd_val)
{
	if (args[1] && args[1][0] == '-' && args[1][1] == '\0')
		return (do_cd_dash(env, oldpwd_val));
	if (!args[1])
		return (do_cd_home(env));
	if (chdir(args[1]) == -1)
	{
		perror("cd");
		return (-1);
	}
	return (0);
}

int	finish_cd(char **args, t_exit *shell_state, char ***env, t_cd_paths paths)
{
	char	cwd_buf[PATH_MAX];
	char	*newcwd;

	newcwd = NULL;
	if (getcwd(cwd_buf, sizeof(cwd_buf)))
		newcwd = ft_strdup(cwd_buf);
	if (paths.prev_pwd)
		update_env_var(env, "OLDPWD=", paths.prev_pwd);
	if (newcwd)
		update_env_var(env, "PWD=", newcwd);
	if (args[1] && args[1][0] == '-' && args[1][1] == '\0' && newcwd)
		printf("%s\n", newcwd);
	if (paths.prev_pwd)
		free(paths.prev_pwd);
	if (paths.oldpwd_val)
		free(paths.oldpwd_val);
	if (newcwd)
		free(newcwd);
	shell_state->exit_code = 0;
	return (0);
}

static int	handle_cd_error(char *prev_pwd, char *oldpwd_val,
		t_exit *shell_state)
{
	if (prev_pwd)
		free(prev_pwd);
	if (oldpwd_val)
		free(oldpwd_val);
	shell_state->exit_code = 1;
	return (1);
}

int	builtin_cd(char **args, t_exit *shell_state, char ***env)
{
	t_cd_paths	paths;
	int			r;

	if (args[1] && args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		shell_state->exit_code = 1;
		return (1);
	}
	paths.oldpwd_val = NULL;
	paths.prev_pwd = get_prev_pwd(*env);
	r = change_dir(args, env, &paths.oldpwd_val);
	if (r == 2)
		return (handle_cd_error(paths.prev_pwd, NULL, shell_state));
	if (r == -1)
		return (handle_cd_error(paths.prev_pwd, paths.oldpwd_val, shell_state));
	return (finish_cd(args, shell_state, env, paths));
}
