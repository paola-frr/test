/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:36:40 by pferreir          #+#    #+#             */
/*   Updated: 2023/10/31 03:25:09 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include <X11/X.h>
# include <float.h>
# include <stdbool.h>
# include <stdio.h>
# include <math.h>

# define height 448
# define width 640
# define tile 64
# define fov 60
# define N 0
# define S 1
# define E 2
# define W 3

typedef struct s_ray
{
	float	rang;
	float	LH;
	float	LV;
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	float	wall_hit_x;
	float	wall_hit_y;
	float	was_hit_vertical;
	float	wall_hit_vx;
	float	wall_hit_vy;
	float	wall_hit_hy;
	float	wall_hit_hx;
	int		vhit;
	int		hhit;
	int		facing_down;
	int		facing_up;
	int		facing_right;
	int		facing_left;
	float	distance;
	int		strip_height;
	int		top;
	int		bottom;
}			t_ray;

typedef struct s_player
{
	int		moved;
	float	x;
	float	y;
	float	rad;
	float	turnD;
	float	walkD;
	float	rotAng;
	float	moveS;
	float	rotS;
	float	translate;
}			t_player;

typedef struct t_data
{
	void					*mlx;
	void					*win;
	void					*img;
	char					*add;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
	int						counter;
	int						nbcol;
	int						nbline;
	int						px;
	int						py;
	t_player				player;
	int						**tex;
	t_ray					ray;
	int						pos;
	int						f_r;
	int						f_g;
	int						f_b;
	unsigned int			pixel_f;
	unsigned int			pixel_c;
	int						c_r;
	int						c_g;
	int						c_b;
	int						h_map;
	int						cnt_1;
	int						height;
	int						len_map;
	int						len_path;
	int						no_here;
	int						so_here;
	int						we_here;
	int						ea_here;
	int						c_here;
	int						f_here;
	char					*tmp_path;
	char					*no_path;
	char					*so_path;
	char					*we_path;
	char					*ea_path;
	char					**map;
	char					**data;
	char					**work_map;
}							t_data;

/*		IS_WHAT		*/
int			is_floor(t_data *data, char *s);
int			is_ceiling(t_data *data, char *s);
int			set_path(t_data *data);
int			is_path(t_data *data, char *s);

int			check_valid_char(char *s);
int			parsing(t_data *data, char *file);
void		free_dstr(char **dstr);
int			check_borders(t_data *data);
void		init_whos_here(t_data *data);

int	check_first_column(t_data *data);
int	check_last_column(t_data *data);
int	check_last_row(t_data *data);


/*			INIT			*/
void	init_game(t_data *d);

/*			RAYCASTING			*/
void	lenght(t_data *d, t_ray *ray);
void	vertical(t_data *d, t_ray *ray, int ang);
void	horizontal(t_data *d, t_ray *ray, int ang);
void	raycasting(t_data *d);

/*			RAYCASTING_UTILS			*/
void	render_strip(t_data *data, t_ray *ray, int i);
void	draw_background(t_data *data);

/*			PLAYER			*/
int	move_player(t_data *data);


#endif
