/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:47:45 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/23 17:36:19 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_direct_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	return (NULL);
}

static char	*find_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (envp[i] + 5);
}

static char	*try_path(char *dir, char *cmd)
{
	size_t		len;
	char		*access_dir;
	struct stat	stat_buffer;

	len = ft_strlen(dir) + 1 + ft_strlen(cmd) + 1;
	access_dir = malloc(len);
	if (!access_dir)
		return (NULL);
	ft_strlcpy(access_dir, dir, len);
	ft_strlcat(access_dir, "/", len);
	ft_strlcat(access_dir, cmd, len);
	if (access(access_dir, F_OK | X_OK) == 0)
	{
		if (stat(access_dir, &stat_buffer) == 0 && S_ISDIR(stat_buffer.st_mode))
		{
			free(access_dir);
			return (NULL);
		}
		return (access_dir);
	}
	free(access_dir);
	return (NULL);
}

static void	try_all_dirs(char *cmd, char **dirs, char **path)
{
	int	i;

	i = 0;
	while (dirs[i])
	{
		*path = try_path(dirs[i++], cmd);
		if (*path)
			break ;
	}
}

char	*get_path(char *cmd, char **envp)
{
	char	**dirs;
	char	*path;
	char	*path_env;

	if (!envp || !cmd)
		return (NULL);
	path = check_direct_path(cmd);
	if (path)
		return (path);
	path_env = find_path_env(envp);
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	path = NULL;
	try_all_dirs(cmd, dirs, &path);
	ft_free_array(&dirs);
	return (path);
}
