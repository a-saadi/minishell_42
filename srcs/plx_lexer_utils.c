/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plx_lexer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:23:37 by abel-mak          #+#    #+#             */
/*   Updated: 2021/03/06 12:39:09 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parser.h"

void	remove_first_token(t_list **tokens_list, enum e_state type)
{
	t_list *tmp;

	tmp = (*tokens_list);
	if (tmp != NULL && ((t_token*)tmp->content)->type == e_state_escape
			&& tmp->next == NULL)
		return ;
	else if (tmp != NULL && ((t_token *)tmp->content)->type == type)
	{
		(*tokens_list) = tmp->next;
		free_token(tmp);
		remove_first_token(tokens_list, type);
	}
}

t_list	*remove_token_by_type(t_list **tokens_list, enum e_state type,
		enum e_state d)
{
	t_list *tmp;
	t_list *escape;

	remove_first_token(tokens_list, type);
	tmp = *tokens_list;
	while (tmp != NULL && (d == 0 || d != ((t_token*)tmp->content)->type))
	{
		if (tmp->next != NULL && ((t_token*)tmp->next->content)->type == type)
		{
			if (((t_token*)tmp->next->content)->type == e_state_escape
					&& tmp->next->next == NULL)
				tmp = tmp->next;
			else
			{
				escape = tmp->next;
				tmp->next = tmp->next->next;
				free_token(escape);
				tmp = *tokens_list;
			}
		}
		else
			tmp = tmp->next;
	}
	return (*tokens_list);
}

/*
** d for delimiter + 0 for no delimiter (do not confond with e_state_delim)
*/

void	join_same_type(t_list *tokens_list, enum e_state type, enum e_state d)
{
	t_list	*tmp;
	t_list	*next_nsc;
	char	*tmp_str;

	tmp = tokens_list;
	while (tmp != NULL && (d == 0 || d != ((t_token *)tmp->content)->type))
	{
		if (((t_token *)tmp->content)->type == type && tmp->next != NULL
				&& ((t_token *)tmp->next->content)->type == type)
		{
			next_nsc = tmp->next;
			tmp_str = ((t_token *)tmp->content)->value;
			((t_token *)tmp->content)->value = ft_strjoin(
				tmp_str,
				((t_token *)next_nsc->content)->value);
			tmp->next = next_nsc->next;
			free_token(next_nsc);
			free(tmp_str);
			tmp = tokens_list;
		}
		else
			tmp = tmp->next;
	}
}

int		is_valid_after_dollar(t_list *tl)
{
	enum e_state type;

	if (tl->next != NULL)
	{
		type = ((t_token*)tl->next->content)->type;
		if (type == e_state_nsc || type == e_state_wildcard
			|| type == e_state_qsm)
			return (1);
	}
	return (0);
}
