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

#include "../../inc/bonus/parser_bonus.h"

int	parce_type2(char *str, t_game *game, int *line, int map_file_fd)
{
	int		parce_index;
	int		cnt;
	int		type;

	if (get_parce_index(str, &parce_index, *line))
	{
		type = parce_index < 4;
		cnt = type * 4 + !type * 2;
		while (cnt > 0)
		{
			if ((type && !parce_texture_type(game, str, *line))
				|| (!type && !parce_color_type(game, get_rgb_arr(str), *line)))
				return (safe_free(str, 0));
			safe_free(str, 0);
			if (cnt != 1)
				str = get_next_line(map_file_fd);
			(*line)++;
			if (str == NULL)
				return (print_err_with_header(*line, "Sudden end of file!\n"));
			cnt--;
		}
	}
	else
		return (print_err_with_header(*line, "Sudden end of file!\n"));
	return (1);
}

int	parce_type(t_game *game, int map_file_fd, int *line)
{
	char	*str;

	str = skip_empty_lines(map_file_fd, line);
	if (str == NULL)
		return (0);
	return (parce_type2(str, game, line, map_file_fd));
}

int	print_file_err(char const *map_file_path)
{
	ft_putstr_fd("Error\n", ERR_FD);
	perror(map_file_path);
	return (0);
}

int	parce_map_file(t_game *game, char const *map_file_path)
{
	int	map_file_fd;
	int	line;
	int	index;

	line = 1;
	if (game == NULL || map_file_path == NULL)
		return (0);
	map_file_fd = open(map_file_path, O_RDONLY);
	if (map_file_fd < 0)
		return (print_file_err(map_file_path));
	if (!parce_type(game, map_file_fd, &line))
		return (close_fd_ret(map_file_fd, 0));
	if (!check_empty_line(map_file_fd, &line))
		return (close_fd_ret(map_file_fd, 0));
	if (!parce_type(game, map_file_fd, &line))
		return (close_fd_ret(map_file_fd, 0));
	if (!check_empty_line(map_file_fd, &line))
		return (close_fd_ret(map_file_fd, 0));
	if (!check_map(game, map_file_fd, &line, &index))
		return (close_fd_ret(map_file_fd, 0));
	if (!generate_map(game, map_file_path, index))
		return (close_fd_ret(map_file_fd, 0));
	return (close_fd_ret(map_file_fd, 1));
}

int	check_params(int argc, char const *argv[])
{
	size_t		map_file_path_len;
	size_t		file_extension_len;
	char const	*map_name;

	if (argc != 2 || argv == NULL)
		return (0);
	map_name = argv[1];
	map_file_path_len = ft_strlen(map_name);
	file_extension_len = ft_strlen(FILE_EXT);
	if (map_file_path_len < 5)
		return (0);
	if (ft_strcmp(&map_name[map_file_path_len - file_extension_len], FILE_EXT))
		return (0);
	return (1);
}
