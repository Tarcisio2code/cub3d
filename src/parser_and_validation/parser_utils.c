/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilva <tsilva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:14:17 by tsilva            #+#    #+#             */
/*   Updated: 2025/09/29 17:28:17 by tsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../inc/parse_and_validation.h"

char	*trim_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len -1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

bool	is_empty_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!is_whitespace(line[i]) && line[i] != '\n')
			return (false);
	}
	return (true);
}

bool	is_map_line(char *line)
{
	int		i;

	if (!line)
		return (false);
	i = 0;
	while (line[i])
	{
		if (is_whitespace(line[i]) || line[i] == '\n')
			i++;
		else if (line[i] == '0' || line[i] == '1' || line[i] == 'D')
			return (true);
		else
			break ;
	}
	return (false);
}

bool	is_whitespace(char c)
{
	char	*whitespace;

	whitespace = " \t\v\f\r";
	return (ft_strchr(whitespace, c));
}

int	get_color(const char *str)
{
	int	n;

	n = -1;
	while (str[++n])
		if (str[n] < 48 || str[n] > 57)
			return (-1);
	return (ft_atoi(str));
}
