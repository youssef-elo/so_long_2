/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:12:45 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/06/05 22:47:33 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

// check the command line args right extension right amount of args
int	check_input(int argc, char *file)
{
	int	l;
	int	line_count;
	int	fd;

	line_count = 0;
	if (argc != 2)
	{
		if (argc == 1)
			write(1, "Error\nNo map available.\n", 23);
		else
			write(1, "Error\nToo many arguments.\n", 25);
		exit(1);
	}
	l = ft_strlen(file);
	if (ft_strcmp(file + l - 4, ".ber") != 0 || l <= 4)
		ft_error(NULL, 0, 0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error(NULL, 0, 0);
	count_lines(&line_count, fd);
	if (line_count < 3 || line_count > 22)
		ft_error(NULL, 0, 0);
	return (line_count);
}

// count the size of the map and check if the map is rectangular
// and check if the number of P C E in the map is valid
void	count_lines(int *line_count, int fd)
{
	char	*line;
	int		first_line;
	int		pce[3];

	pce[0] = 0;
	pce[1] = 0;
	pce[2] = 0;
	line = get_next_line(fd);
	first_line = length(line, pce, 1);
	while (line)
	{
		(*line_count)++;
		if ((first_line < 3 || first_line > 42
				|| length(line, pce, 1) != first_line) && line)
		{
			free(line);
			ft_error(NULL, 0, 0);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (pce[0] != 1 || pce[1] == 0 || pce[2] != 1)
		ft_error(NULL, 0, 0);
	close(fd);
}

// reads the map from the given file and gets the player's starting
// position in the map and checks the map
void	get_map(char *file, int map_size, t_data *data)
{
	int		fd;
	char	*p;
	char	**map;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	map = (char **)malloc(map_size * sizeof(char *));
	if (map == NULL)
		return ;
	*map = get_next_line(fd);
	while (i < map_size - 1)
	{
		p = ft_strchr(*map, 'P');
		if (p)
			((1) && (data->p_x = (p - (*map)) * 60, data->p_y = i * 60));
		map++;
		*map = get_next_line(fd);
		i++;
	}
	close(fd);
	map -= map_size - 1;
	check_map(map, map_size);
	data->map = map;
	check_path(map, data);
}

// check if the map is surronded by walls
void	check_map(char **map, int line_count)
{
	int	i;
	int	j;

	i = 0;
	while (i < line_count)
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
			if (!(ft_strchr("01PCEG", map[i][j++])))
				ft_error(NULL, 0, 0);
		j = 0;
		if (i == 0 || i == (line_count - 1))
		{
			while (map[i][j] != '\n' && map[i][j])
			{
				if (map[i][j] != '1')
					ft_error(map, line_count, 1);
				j++;
			}
		}
		if (map[i][0] != '1' || map[i][length(map[i], NULL, 0) - 1] != '1')
			ft_error(map, line_count, 1);
		i++;
	}
}

// calculates the lenght of string up to newline or end
// of string the flag is to count the p c and e in the map
int	length(char *s, int *pce, int flag)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] && s[i] != '\n')
	{
		if (flag == 1)
		{
			if (s[i] == 'P')
				pce[0]++;
			if (s[i] == 'C')
				pce[1]++;
			if (s[i] == 'E')
				pce[2]++;
		}
		i++;
	}
	return (i);
}
