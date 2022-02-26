/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:40:07 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/24 17:28:19 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*broke_free(void *ptr, void *ret)
{
	free (ptr);
	return (ret);
}

int	broke_free2(void *ptr, int ret)
{
	free(ptr);
	return (ret);
}

int	cmd_free_broke(t_command *cmd_head)
{
	free_cmd(cmd_head);
	return (ERROR);
}
