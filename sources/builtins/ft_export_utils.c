/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 23:08:00 by jomanuel          #+#    #+#             */
/*   Updated: 2026/03/27 21:09:22 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*get_node_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	update_env(t_env *node, char *value)
{
	free(node->value);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
}

void	add_env(t_env **env, char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	if (!*env)
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	add_or_update(t_env **env, char *key, char *value)
{
	t_env	*node;

	node = get_node_env(*env, key);
	if (node && value)
		update_env(node, value);
	else if (!node)
		add_env(env, key, value);
}

int	parse_export_arg(char *arg, char **key, char **value, int *has_equal)
{
	char	*eq;

	if (!is_valid_identifier(arg))
		return (-1);
	eq = ft_strchr(arg, '=');
	*has_equal = (eq != NULL);
	if (!eq)
	{
		*key = ft_strdup(arg);
		*value = NULL;
		return (*key != NULL);
	}
	*key = ft_substr(arg, 0, eq - arg);
	if (!*key)
		return (0);
	*value = ft_strdup(eq + 1);
	if (!*value)
	{
		free(*key);
		*key = NULL;
		return (0);
	}
	return (1);
}
