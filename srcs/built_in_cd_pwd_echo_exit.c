/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd_pwd_echo_exit.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:22:13 by asaadi            #+#    #+#             */
/*   Updated: 2021/01/18 17:05:02 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void pwd_function(void)
{
	char _cwd[PATH_MAX];

	if ((getcwd(_cwd, sizeof(_cwd)) == NULL))
		ft_putendl_fd(strerror(errno), 1);
	else
		ft_putendl_fd(_cwd, 1);
}

void exit_function(int _id)
{
	exit(_id);
}