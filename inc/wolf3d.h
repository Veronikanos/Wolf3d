/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 21:32:53 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/26 22:20:39 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <pthread.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include "get_next_line.h"
# include "libft.h"
# include "SDL_image.h"

# define WIDTH		1280u
# define HEIGHT		720u
# define HEIGHT_H	360u
# define NAME		"Wolf3d by vtlostiu"
# define TEXTURES	8
# define TEXWIDTH	64
# define TEXHEIGHT	64
# define DIST		8.0
# define RED		0xFC0000u
# define GREEN		0x6CC409u
# define BLUE		0x433AFFu
# define YELLOW		0xFEE84Au
# define PINK		0xEF45F7u
# define DEF_COL	0x0C00FFu
# define FLOOR_COL	0xBAB7B7u
# define CEIL_COL	0xB7F1FAu

typedef struct		s_point
{
	int				x;
	int				y;
}					t_xy;

typedef struct		s_flag
{
	bool			straight;
	bool			back;
	bool			right;
	bool			right_rot;
	bool			left;
	bool			left_rot;
	bool			tex_change;
	bool			tex_compass;
	bool			speed_up;
	bool			color_mode;
	bool			light_mode;
}					t_flag;

typedef struct		s_vector2
{
	double			x;
	double			y;
}					t_vec2;

typedef struct		s_player
{
	t_vec2			pos;
	t_vec2			dir;
	double			move_rate;
	double			rot_rate;
}					t_plr;

typedef struct		s_ray
{
	t_vec2			dir;
	t_vec2			side_dist;
	t_vec2			diff_dist;
}					t_ray;

typedef struct		s_pix
{
	SDL_Window		*win;
	SDL_Surface		*screen_surf;
	SDL_Surface		**tex_arr;
	size_t			width;
	size_t			height;
	t_flag			flag;
	double			time;
	double			old_time;
	double			new_time;
	double			wall_x;
	double			wall_dist;
	double			speed;
	int				tex_id;
	int				d;
	int				**map;
	int				edge;
	Uint32			*screen;
	Uint32			line_height;
	t_vec2			plane;
	t_vec2			wall_side;
	t_xy			ray_map_cord;
	t_xy			from_to;
	t_xy			step;
	t_xy			tex_cord;
	t_plr			player;
	t_ray			ray;
	bool			game_over;
}					t_pix;

typedef struct		s_lines
{
	char			*str;
	struct s_lines	*next;
}					t_lines;

int					ft_del_all(t_lines **head);
int					choose_tex(t_pix *pix, int y);
void				errors_handler(int err, t_pix *pix);
void				is_file_valid(t_pix *pix, t_lines **lst, char **argv);
void				ft_add_to_end(t_lines **head, char *str);
void				parsing(t_pix *pix, t_lines *lst, t_vec2 *pos);
void				event_handler(t_pix *pix);
void				game_process(t_pix *pix);
void				draw_line(t_pix *pix, size_t x, t_xy from_to, Uint32 color);
void				clear_screen(t_pix *pix);
void				time_and_rate(t_pix *pix);
void				del_all(t_pix *pix, size_t i);
void				show_menu(void);
Uint32				choose_color(t_pix *pix);
t_pix				*init(void);

#endif
