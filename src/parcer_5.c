/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:24:57 by nomargen          #+#    #+#             */
/*   Updated: 2022/10/10 20:46:08 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

char	*skip_empty_lines(int map_file_fd, int *line)
{
	char	*crnt_str;

	while (1)
	{
		crnt_str = get_next_line(map_file_fd);
		if (crnt_str == NULL)
		{
			print_err_with_header(*line, "Sudden end of file!\n");
			break ;
		}
		if (crnt_str[0] != '\n')
			break ;
		(*line)++;
		safe_free(crnt_str, 0);
	}
	return (crnt_str);
}

int	get_parce_index(char *str, int *index, int line)
{
	static char	prefix[6][3] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			i;
	char		**mass;

	i = 0;
	mass = ft_split(str, ' ');
	if (!check_alloc(mass))
		return (0);
	while (i < 6)
	{
		if (ft_strcmp(prefix[i], mass[0]) == 0)
		{
			*index = i;
			free_alloced_ptr_mas(&mass);
			return (1);
		}
		i++;
	}
	print_err_with_header(line, "Wrong type of line!\n");
	free_alloced_ptr_mas(&mass);
	return (0);
}

int	parce_color_type(t_game *game, char *str, int line)
{		
	static int	is_was[2] = {0, 0};
	int			index;
	int			*color_ptr;

	if (!get_parce_index(str, &index, line))
		return (0);
	if (index < 4)
		return (print_err_with_header(line,
				"One field type must go together!\n"));
	if (is_was[index - 4] == 1)
		return (print_err_with_header(line, "Duplication color type!\n"));
	if (index - 4 == 0)
		color_ptr = &(game->floor_color);
	else
		color_ptr = &(game->ceilling_color);
	if (!parse_rgb(color_ptr, &str[2], line))
		return (0);
	is_was[index - 4] = 1;
	return (1);
}

int	get_mas_len(char **mas)
{
	int	i;

	i = 0;
	while (mas[i])
		i++;
	return (i);
}

int	parce_texture_type(t_game *game, char *str, int line)
{
	int		index;
	char	**mas;

	if (!get_parce_index(str, &index, line))
		return (0);
	if (index > 3)
		return (print_err_with_header(line,
				"One field type must go together!\n"));
	if (game->textures_path[index] != NULL)
		return (print_err_with_header(line, "Duplication texture type!\n"));
	mas = ft_split(str, ' ');
	if (!check_alloc(mas))
		return (0);
	if (get_mas_len(mas) != 2)
		return (print_err_with_header(line, "Expected the end of line!\n"));
	if (!is_exist(mas[1], line))
	{
		free_alloced_ptr_mas(&mas);
		return (0);
	}
	game->textures_path[index] = ft_strdup(mas[1]);
	free_alloced_ptr_mas(&mas);
	return (1);
}
