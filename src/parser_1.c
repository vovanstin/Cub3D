/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:23:34 by nomargen          #+#    #+#             */
/*   Updated: 2022/10/10 20:46:03 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	check_empty_line(int map_file_fd, int *line)
{
	char		*crnt_str;

	crnt_str = get_next_line(map_file_fd);
	(*line)++;
	if (crnt_str == NULL)
	{
		print_err_with_header(*line, "Sudden end of file!\n");
		return (0);
	}
	if (crnt_str[0] != '\n')
	{
		print_err_with_header(*line, "Line must be empty!\n");
		free(crnt_str);
		return (0);
	}
	free (crnt_str);
	return (1);
}

int	get_num_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (!ft_isdigit(str[i]))
			return (i);
		i++;
	}
	return (i);
}

void	set_space(size_t i, size_t *j, char *crnt_str)
{
	crnt_str[(*j)++] = crnt_str[i];
	crnt_str[(*j)++] = ' ';
}

char	*get_rgb_arr(char *crnt_str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(crnt_str))
	{
		if (i != ft_strlen(crnt_str) - 1 && (crnt_str[i] != ' '
				&& crnt_str[i] != ',') && (crnt_str[i + 1] != ' '
				&& crnt_str[i + 1] != ','))
			crnt_str[j++] = crnt_str[i];
		else if (crnt_str[i] != ' ' && crnt_str[i] != ','
			&& crnt_str[i] != '\n')
			set_space(i, &j, crnt_str);
		else if (crnt_str[i] != ' ' && crnt_str[i] != ','
			&& crnt_str[i] == '\n')
		{
			crnt_str[j++] = crnt_str[i];
			break ;
		}
		i++;
	}
	crnt_str[j] = '\0';
	return (crnt_str);
}

int	parse_rgb(int *rgb, char *crnt_str, int line)
{
	int	num_len;
	int	rgb_mas[3];
	int	i;

	i = 0;
	while (i < 3)
	{
		num_len = get_num_len(crnt_str);
		if (num_len == 0 || crnt_str[0] == 0)
			return (print_err_with_header(line,
					"Wrong RGB format!\nMust be: \"<R>,<G>,<B>\"\n"));
		else if (num_len > 3 || ft_atoi(crnt_str) > 255)
			return (print_err_with_header(line,
					"Wrong RGB number range!\nMust be in range of 0-255\n"));
		else
			rgb_mas[i] = ft_atoi(crnt_str);
		if (i != 2 && crnt_str[num_len] != ' ')
			return (print_err_with_header(line, RGB_ERR_FORMAT));
		crnt_str += num_len + (i != 2);
		i++;
	}
	*rgb = (rgb_mas[0] << 16 | rgb_mas[1] << 8 | rgb_mas[2]);
	return (1);
}
