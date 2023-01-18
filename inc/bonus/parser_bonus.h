/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:19:26 by nomargen          #+#    #+#             */
/*   Updated: 2022/10/10 20:47:39 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSER_BONUS_H
# define PARSER_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include "../../lib/libft/libft.h"
# include "get_next_line_bonus.h"
# include "game_bonus.h"

# define FILE_EXT (".cub")
# define RGB_ERR_FORMAT ("Wrong RGB format!\nMust be: \"<R>,<G>,<B>\"\n")
# define RGB_ERR_NL ("There should be a new line after the numbers!\n")

void	free_alloced_n_ptr_mas(char **mass[], size_t size);
int		safe_free(void *ptr, int ret_val);
int		check_params(int argc, char const *argv[]);
int		parce_map_file(t_game *game, char const *map_file_path);
int		print_err_with_header(int line, char *err_str);
int		check_field(char *crnt_str, char *parse_prefix, int line);
int		is_exist(char *file_name, int line);
int		is_map_char(char ch);
int		parce_textures(t_game *game, int map_file_fd, int *line);
int		check_empty_line(int map_file_fd, int *line);
int		check_map(t_game *game, int map_file_fd, int *line, int *index);
char	*get_map_line(int map_file_fd, int map_line_size);
int		close_fd_ret(int fd, int ret);
int		parce_ceilling_n_floor_colors(t_game *game, int map_file_fd, int *line);
void	search_player(t_game *game, int str_num);
void	print_field_err(char *crnt_str, char *parse_prefix,
			size_t parse_prefix_len, int line);
int		parse_rgb(int *rgb, char *crnt_str, int line);
char	*skip_empty_lines(int map_file_fd, int *line);
char	*get_rgb_arr(char *crnt_str);
int		check_map_walls2(t_game *game, int i, int j);
int		allocate_n_open_map(t_game *game, int *map_file_fd,
			char const *map_file_path);
int		skip_lines(int fd, int cnt);
int		get_parce_index(char *str, int *index, int line);
int		parce_texture_type(t_game *game, char *str, int line);
int		parce_color_type(t_game *game, char *str, int line);
int		generate_map(t_game *game, char const *map_file_path, int index);
int		check_alloc(void *ptr);
int		free_alloced_ptr_mas(char ***mass);

#endif
