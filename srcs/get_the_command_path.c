/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_the_command_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:06:58 by asaadi            #+#    #+#             */
/*   Updated: 2021/01/27 12:38:12 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_the_path_command(char *pathname)
{
	struct stat stat_buf;

	if (stat(pathname, &stat_buf) != 0)
		return (0);
	return (1);
}

int get_cmd_path(char **args, char **envp)
{
	char	*path;
	char	**path_split;
	char	*bin;
	int		i;

	/* find the command path */
	i = 0;
	if (ft_strchr(args[0], '/') == NULL)
	{
		if ((path = get_var_env(envp, "PATH")) != NULL)
		{
			path_split = ft_split(path, ':');
			ft_free_arr(path);
			while (path_split[i])
			{
				if (!(bin = (char *)malloc(sizeof(char) * (ft_strlen(path_split[i]) + ft_strlen(args[0]) + 1))))
				{
					ft_putendl_fd("Error: Allocation failed!", 2);
					//check leak
				}
				ft_strlcat(bin, path_split[i], ft_strlen(bin) + ft_strlen(path_split[i]) + 1);
				ft_strlcat(bin, "/", ft_strlen(bin) + 2);
				ft_strlcat(bin, args[0], ft_strlen(bin) + ft_strlen(args[0]) + 1);
				if (check_the_path_command(bin) == 1)
					break;
				i++;
			}
			ft_free_2dem_arr(path_split);
			if (!check_the_path_command(bin))
			{
				ft_putstr_fd("bash: ", 2);
				ft_putstr_fd(args[0], 2);
				ft_putendl_fd(": command not found", 2);
				// exit_function(EXIT_FAILURE);
				return (0);
			}
			args[0] = ft_strdup(bin);
			ft_free_arr(bin);
		}
	}
	return (1);
}