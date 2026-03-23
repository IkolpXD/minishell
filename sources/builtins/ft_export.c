/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danuno-g <danuno-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 11:33:07 by danuno-g          #+#    #+#             */
/*   Updated: 2026/03/20 23:25:30 by danuno-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_export_arg(t_shell *shell, char *arg)
{
	int		has_equal;
	t_env	*node;
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (!parse_export_arg(arg, &key, &value, &has_equal))
		return (1);
	if (key[0] == '\0')
		return (free(key), free(value), 0);
	if (!has_equal)
	{
		node = get_node_env(shell->env, key);
		if (!node)
			add_env(&shell->env, key, NULL);
	}
	else
		add_or_update(&shell->env, key, value);
	return (free(key), free(value), 0);
}

int	ft_export(t_shell *shell, char **args)
{
	int	i;

	if (!args[1])
	{
		print_export_sorted(shell->env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (handle_export_arg(shell, args[i]))
			return (1);
		i++;
	}
	return (0);
}
