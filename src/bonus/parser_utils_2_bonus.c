/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:20:50 by nomargen          #+#    #+#             */
/*   Updated: 2022/10/10 20:46:13 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/bonus/parser_bonus.h"

void	free_alloced_n_ptr_mas(char **mass[], size_t size)
{
	size_t	i;

	if (*mass == NULL)
		return ;
	i = 0;
	while (i < size)
	{
		free((*mass)[i]);
		i++;
	}
	free (*mass);
	*mass = NULL;
}

int	close_fd_ret(int fd, int ret)
{
	if (fd >= 0)
		close(fd);
	return (ret);
}

int	check_field(char *crnt_str, char *parse_prefix, int line)
{
	size_t	parse_prefix_len;

	parse_prefix_len = ft_strlen(parse_prefix);
	if (crnt_str == NULL)
	{
		print_field_err(crnt_str, parse_prefix, parse_prefix_len, line);
		return (0);
	}
	parse_prefix_len = ft_strlen(parse_prefix);
	if (crnt_str[ft_strlen(crnt_str) - 1] == '\n')
	{
		crnt_str[ft_strlen(crnt_str) - 1] = 0;
	}
	if (ft_strncmp(crnt_str, parse_prefix, parse_prefix_len))
	{
		print_field_err(crnt_str, parse_prefix, parse_prefix_len, line);
		return (0);
	}
	return (1);
}

int	check_map_walls(t_game *game, int line)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_size_y)
	{
		j = 0;
		while (j < game->map_size_x)
		{
			if (game->map[i][j] == '0')
			{
				if (!check_map_walls2(game, i, j))
				{
					print_err_with_header(i + line,
						"The walls on the map are placed incorrectly!\n");
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	generate_map(t_game *game, char const *map_file_path, int index)
{
	int	i;
	int	map_file_fd;

	i = 0;
	game->map = malloc(sizeof(char *) * game->map_size_y);
	if (!allocate_n_open_map(game, &map_file_fd, map_file_path))
		return (0);
	if (!skip_lines(map_file_fd, index - 1))
		return (close_fd_ret(map_file_fd, 0));
	while (i < game->map_size_y)
	{
		game->map[i] = get_map_line(map_file_fd,
				game->map_size_x);
		if (game->map[i] == NULL)
		{
			ft_putstr_fd("Allocation fail!\n", ERR_FD);
			free_alloced_n_ptr_mas(&game->map, i);
			return (close_fd_ret(map_file_fd, 0));
		}
		search_player(game, i);
		i++;
	}
	if (!check_map_walls(game, index))
		return (close_fd_ret(map_file_fd, 0));
	return (close_fd_ret(map_file_fd, 1));
}
