/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 19:04:06 by asaadi            #+#    #+#             */
/*   Updated: 2021/01/20 19:25:36 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_function(char **envp)
{
	int i;

	i = 0;
	while (envp[i] && ft_strchr(envp[i], '='))
	{
		ft_putstr_fd("======", 1);
		ft_putendl_fd(envp[i], 1);
		i++;
		// puts("++++++");
	}
}