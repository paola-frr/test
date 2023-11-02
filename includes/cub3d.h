/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:36:40 by pferreir          #+#    #+#             */
/*   Updated: 2023/11/02 08:12:04 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include <X11/X.h>
# include <stdbool.h>
# include <stdio.h>
# include <float.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <X11/keysym.h>
# include <sys/stat.h>
# include <unistd.h>

# define tile 60
# define ROW 11
# define COL 15
# define WIDTH 660
# define HEIGHT 480
# define fov 1.047
# define N 0
# define S 1
# define E 2
# define W 3
# define moveS 0.0125
# define rotS 0.015
# define DPP ((WIDTH / 2) / tan(fov / 2))
# define deg fov / degToRad(WIDTH)

typedef struct s_texture
{
	char			*path;
	void			*ptr;
	int				*wall;
	int				height;
	int				width;
}	t_texture;

typedef struct s_player
{
	double	px;
	double	py;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		has_moved;
	int		move_x;
	int		move_y;
	int		rot;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	double	sdx;
	double	sdy;
	double	ddx;
	double	ddy;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		start;
	int		end;
}	t_ray;

typedef struct t_data
{
	int						nbline;
	int						nbcol;
	void					*mlx;
	void					*win;
	void					*img;
	void					*img1;
	char					*add;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
	int						counter;
	t_ray					ray;
	t_player				p;
	unsigned int			texture[4];
	int						player_pos_x;
	int						player_pos_y;
	char					player_dir;
	int						pos;
	int						f_r;
	int						f_g;
	int						f_b;
	int						c_r;
	int						c_g;
	int						c_b;
	int						row;
	int						h_map;
	int						cnt_1;
	int						pheight;
	int						len_map;
	int						len_path;
	int						no_here;
	int						so_here;
	int						we_here;
	int						ea_here;
	int						c_here;
	int						f_here;
	unsigned long			floor_color;
	unsigned long			ceiling_color;
	char					*path;
	char					*no_path;
	char					*so_path;
	char					*we_path;
	char					*ea_path;
	char					**map;
	char					**data;
	char					**work_map;
}			t_data;

/*		BORDER UTILS		*/
int	zero_or_letter(char c);
int	nospc(char c);
int	check_first_column(t_data *data);
int	check_last_column(t_data *data);
int	check_last_row(t_data *data);
/*		CHECKING BORDERS	*/
void	player_info(t_data *data, int x, int y);
int	longest_line_case(t_data *data, int x, int y, int len);
int	process_checking(t_data *data, int x, int y, int len);
int	check_borders(t_data *data);
/*		INIT N FREE			*/
int	init_map(t_data *data, int fd);
void	init_whos_here(t_data *data);
void	free_good_map(t_data *data);
void free_dstr(char **dstr);
/*		IS WHAT				*/
int	is_floor(t_data *data, char *s);
int	is_ceiling(t_data *data, char *s);
int	valid_for_path(char *s);
int	check_double_path(t_data *data, char *s, int i);
int	is_path(t_data *data, char *s);
/*		MAP					*/
int	height_of_map(int fd);
char	**check_map(t_data *data, int cur_row);
int	is_empty(t_data *data);
int	empty_row(char *s);
int	all_stuff_map(t_data *data);
int	check_all_inside(t_data *data);
int	parsing(t_data *data, char *file);
/*		UTILS				*/
int	invalid_start(t_data *data, char *s);
int	invalid_row(char *s);
int	check_valid_chars(t_data *data, char *s);
int	check_valid_char(char *s);
/*		WHAT THE PATH		*/
int	is_no(t_data *data);
int	is_so(t_data *data);
int	is_we(t_data *data);
int	is_ea(t_data *data);
int	set_path(t_data *data);

/*		TEXTURE		*/
int		choice_of_texture(t_ray *ray);
void	init_texture(t_data *d);
void	free_texture(t_data *d);

/*		INIT_GAME		*/
void	img_pix_put(t_img *img, int x, int y, int color);
int		can_we_see_the_window(t_data *d);
void	init_game(t_data *d);
int		close_window(t_data *d);

/*		DRAW_BACKGROUND		*/
void	draw_background(t_data *d);

/*		RAYCASTING		*/
void	lenght(t_data *d, t_ray *ray, t_player *player, int i);
void	vertical(t_data *d, t_ray *ray, t_player *player, int i);
void	horizontal(t_data *d, t_ray *ray, t_player *player, int i);
int		castAllRAys(t_player *player, t_data *data);
void	draw_wall(t_data *d, t_ray *r,  int column_id);
void	render_strip(t_data *d, t_ray *r, int i, t_player *p);

/*		PLAYER		*/
void	player_position(t_data *d, t_player *p);
void	init_player(t_data *data);
int		move_player(t_data *data);

/*		KEY_HANDLER		*/
int		key_press_handler(int key, t_data *d);
int		key_release_handler(int key, t_data *d);
void	key_handler(t_data *d);

/*		RENDER		*/
int		render2(t_data *d);
int		render(t_data *data);
void	init_ray(t_ray *ray);
void	render_map(t_data *d);
#endif
