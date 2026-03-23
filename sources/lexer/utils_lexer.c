/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 21:43:48 by made-jes          #+#    #+#             */
/*   Updated: 2026/03/20 21:43:48 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_quotes(const char *line, int *i)
{
	int		start;
	char	quote;

	start = *i;
	quote = line[(*i)];
	(*i)++;
	while (line[*i])
	{
		if (line[*i] == '\\' && quote == '"' && line[*i + 1])
		{
			*i += 2;
			continue ;
		}
		if (line[*i] == quote)
		{
			(*i)++;
			return (ft_substr(line, start, *i - start));
		}
		(*i)++;
	}
	syntax_error("unclosed quotes");
	return (NULL);
}

char	*handle_double_operator(const char *line, int *i)
{
	char	*op;

	op = ft_substr(line, *i, 2);
	*i += 2;
	return (op);
}

char	*handle_single_operator(const char *line, int *i)
{
	char	*op;

	op = ft_substr(line, (*i)++, 1);
	return (op);
}

char	*handle_word(const char *line, int *i)
{
	int	start;

	start = *i;
	while (line[*i] && !ft_is_space(line[*i]) && line[*i] != '>'
		&& line[*i] != '<' && line[*i] != '|' && line[*i] != '\''
		&& line[*i] != '\"')
		(*i)++;
	return (ft_substr(line, start, *i - start));
}
