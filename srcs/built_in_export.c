/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 19:08:16 by asaadi            #+#    #+#             */
/*   Updated: 2021/02/18 16:36:19 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int len_to_char(char *str, int c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char *seach_env(char **envp, char *str)
{
	int i;
	char **equ0;
	char **equ1;

	i = 0;
	while (envp[i])
	{
		equ0 = ft_split(envp[i], '=');
		equ1 = ft_split(str, '=');
		if (!ft_strcmp(equ0[0], equ1[0]))
		{
			ft_free_2dem_arr((void***)&equ0);
			ft_free_2dem_arr((void***)&equ1);
			return (str);
		}
		i++;
		ft_free_2dem_arr((void***)&equ0);
		ft_free_2dem_arr((void***)&equ1);
	}
	return (NULL);
}

void edit_in_envp(char **envp, char *var_to_edit)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var_to_edit, len_to_char(var_to_edit, '=')))
		{
			envp[i] = ft_strdup(var_to_edit);
			break;
		}
		i++;
	}
}

int check_args_to_export(char *arg)
{
	int i;
	char **equ;

	i = 1;
	equ = ft_split(arg, '=');
	while (equ[0][i])
	{
		if (!ft_isalnum(equ[0][i]) || equ[0][i] != '_')
		{
			ft_free_2dem_arr((void***)&equ);
			return (0);
		}
	}
	ft_free_2dem_arr((void***)&equ);
	return (1);
}

void export_function(t_exec *exec)
{
	int len;
	int i;
	char **env__p;
	int j;

	j = 1;
	while (exec->args[j])
	{
		if ((ft_isalpha(exec->args[j][0]) || exec->args[j][0] == '_') && check_args_to_export(exec->args[j]))
		{
			if (ft_strchr(exec->args[j], '=') && seach_env(exec->envp, exec->args[j]))
			{
				ft_putendl_fd("here0", 1);
				edit_in_envp(exec->envp, exec->args[j]);
			}
			else if (exec->args[j] && !seach_env(exec->envp, exec->args[j]))
			{
				len = count_vars_env(exec->envp);
				if (!(env__p = (char **)malloc(sizeof(char *) * (len + 2))))
				{
					ft_putendl_fd("Error: Allocation Failed!", 2);
					exit(EXIT_FAILURE);
				}
				i = 0;
				while (exec->envp[i])
				{
					env__p[i] = ft_strdup(exec->envp[i]);
					i++;
				}
				env__p[i] = exec->args[j];
				env__p[i + 1] = NULL;
				ft_free_2dem_arr((void***)&(exec->envp));
				exec->envp = env__p;
			}
		}
		else
		{
			// printf("bash: export: `%s': not a valid identifier\n", exec->args[j]);
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(exec->args[j], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			exec->status = 1;
		}
		j++;
	}
}

void print_envp(char **envp)
{
	char **equ;
	char *s_chr;
	int i;

	i = 0;
	while (envp[i])
	{
		equ = ft_split(envp[i], '=');
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(equ[0], 1);
		if ((s_chr = ft_strchr(envp[i], '=')) != NULL)
		{
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(s_chr + 1, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		ft_free_2dem_arr((void***)&equ);
		i++;
	}
}

void sort_print_envp_alpha(char **envp)
{
	char *tmp;
	int i;
	int j;
	char **str;

	str = envp_cpy(envp);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[j])
		{
			if (ft_strcmp(str[i], str[j]) < 0)
			{
				tmp = str[j];
				str[j] = str[i];
				str[i] = tmp;
			}
			j++;
		}
		i++;
	}
	print_envp(str);
	ft_free_2dem_arr((void***)&str);
}