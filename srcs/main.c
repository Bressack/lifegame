/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 12:08:51 by tharchen          #+#    #+#             */
/*   Updated: 2019/12/03 08:17:26 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lg.h>

# define WIN_X		g_mlx.win.x
# define WIN_Y		g_mlx.win.y

# define MLX_ID		g_mlx.id
# define WIN_ID		g_mlx.win.id
# define IMG_ID		g_mlx.win.img.id
# define IMG_X		g_mlx.win.img.x
# define IMG_Y		g_mlx.win.img.y
# define IMG_GRID	g_mlx.win.img.grid
# define IMG_DATA	g_mlx.win.img.data

# define MAP		g_map[curr].map
# define MAP_X		g_map[curr].x
# define MAP_Y		g_map[curr].y

# define DEAD		0
# define ALIVE		1

# define COLOR_ALIVE_NEW	255, 50, 50
# define COLOR_ALIVE		255, 255, 255
# define COLOR_DEAD			0, 0, 0

# define CELL_TOP_LEFT_		(i > 0 && i < MAP_Y - 1 && j > 0 && j < MAP_X - 1 ? MAP[i - 1][j - 1] : 0)
# define CELL_TOP_MID__		(i > 0 && i < MAP_Y - 1 && j > 0 && j < MAP_X - 1 ? MAP[i - 1][j]     : 0)
# define CELL_TOP_RIGHT		(i > 0 && i < MAP_Y - 1 && j > 0 && j < MAP_X - 1 ? MAP[i - 1][j + 1] : 0)
# define CELL_MID_LEFT_		(i > 0 && i < MAP_Y - 1 && j > 0 && j < MAP_X - 1 ? MAP[i    ][j - 1] : 0)
# define CELL_MID_RIGHT		(i > 0 && i < MAP_Y - 1 && j > 0 && j < MAP_X - 1 ? MAP[i    ][j + 1] : 0)
# define CELL_BOT_LEFT_		(i > 0 && i < MAP_Y - 1 && j > 0 && j < MAP_X - 1 ? MAP[i + 1][j - 1] : 0)
# define CELL_BOT_MID__		(i > 0 && i < MAP_Y - 1 && j > 0 && j < MAP_X - 1 ? MAP[i + 1][j]     : 0)
# define CELL_BOT_RIGHT		(i > 0 && i < MAP_Y - 1 && j > 0 && j < MAP_X - 1 ? MAP[i + 1][j + 1] : 0)

// usage: lifegame x y

int			ft_rand_bin(void)
{
	return (rand() % (2 - 0) + 0);
}

typedef struct		s_img
{
	void			*id;
	unsigned int	*data;
	unsigned int	**grid;
	int				bpp;
	int				sl;
	int				ed;
	int				x;
	int				y;
}					t_img;
typedef struct		s_win
{
	void			*id;
	int				x;
	int				y;
	t_img			img;
}					t_win;
typedef struct		s_mlx
{
	void			*id;
	t_win			win;
}					t_mlx;
typedef struct		s_map
{
	int				**map;
	int				x;
	int				y;
}					t_map;

t_mlx				g_mlx;
t_map				g_map[2];
int					curr = 0;

# define INIT 3

void	init_grid(void)
{
	IMG_GRID = malloc(sizeof(unsigned int *) * WIN_Y);
	for (int i = 0; i < WIN_Y; i++)
		IMG_GRID[i] = &IMG_DATA[i * WIN_X];
	for (int i = 0; i < MAP_Y; i++)
		for (int j = 0; j < MAP_X; j++)
			MAP[i][j] = 0;
}

void	init_map(int id, int x, int y)
{
	g_map[id].map = malloc(sizeof(int *) * y);
	for (int i = 0; i < y; i++)
		g_map[id].map[i] = malloc(sizeof(int) * x);
	g_map[id].x = x;
	g_map[id].y = y;
}

void	init_mlx(int x, int y)
{
	MLX_ID = mlx_init();
	WIN_ID = mlx_new_window(MLX_ID, WIN_X, WIN_Y, "Lifegame");
	g_mlx.win.x = x;
	g_mlx.win.y = y;
	IMG_X = WIN_X;
	IMG_Y = WIN_Y;
	IMG_ID = mlx_new_image(MLX_ID, IMG_X, IMG_Y);
	g_mlx.win.img.data = (unsigned int *)mlx_get_data_addr(IMG_ID, &g_mlx.win.img.bpp, &g_mlx.win.img.sl, &g_mlx.win.img.ed);
}

void	pixset(int x, int y, int r, int g, int b)
{
	unsigned int pixel;
	unsigned char *tmp = (unsigned char *)&pixel;

	if (g_mlx.win.img.ed == 0)
		{ tmp[3] = 0; tmp[2] = r; tmp[1] = g; tmp[0] = b; }
	else
		{ tmp[0] = 0; tmp[1] = r; tmp[2] = g; tmp[3] = b; }
	IMG_GRID[y][x] = mlx_get_color_value(MLX_ID, (int)pixel);
}

void	map_to_image(void)
{
	int spix_x = (double)(IMG_X / MAP_X) > 0.5 ? IMG_X / MAP_X + 1 : IMG_X / MAP_X;
	int spix_y = (double)(IMG_Y / MAP_Y) > 0.5 ? IMG_Y / MAP_Y + 1 : IMG_Y / MAP_Y;

	int i = 0;
	int j = 0;

	int i_map = 0;
	int j_map = 0;

	int i_cell = 0;
	int j_cell = 0;

	while (i < IMG_Y)
	{
		while (j < IMG_X)
		{
			
			j += spix_x;
		}
		i += spix_y;
	}

	for (int i = 0, ii = 0; i < IMG_Y && ii < MAP_Y; i += spix_y, ii++)
	{
		for (int j = 0, jj = 0; j < IMG_X && jj < MAP_X; j += spix_x, jj++)
		{
			for (int k = i; k < spix_y + i; k++)
			{
				for (int l = j; l < spix_x + j; l++)
				{
					if (MAP[ii][jj] == 1)
						pixset(l, k, COLOR_ALIVE_NEW);
					else if (MAP[ii][jj])
						pixset(l, k, COLOR_ALIVE);
					else
						pixset(l, k, COLOR_DEAD);
				}
			}
		}
	}
}

int		next_curr(void)
{
	return (curr ? 0 : 1);
}

int		process(void *arg)
{
	int	tot = 0;

	(void)arg;
	printf("WIN_X : %d\n", WIN_X);
	printf("WIN_Y : %d\n", WIN_Y);
	printf("IMG_X : %d\n", IMG_X);
	printf("IMG_Y : %d\n", IMG_Y);
	printf("MAP_X : %d\n", MAP_X);
	printf("MAP_Y : %d\n", MAP_Y);
	while (42)
	{
		for (int i = 0; i < MAP_Y; i++)
		{
			for (int j = 0; j < MAP_X; j++)
			{
				tot = 0;
				tot += CELL_TOP_LEFT_;
				tot += CELL_TOP_MID__;
				tot += CELL_TOP_RIGHT;

				tot += CELL_MID_LEFT_;
				tot += CELL_MID_RIGHT;

				tot += CELL_BOT_LEFT_;
				tot += CELL_BOT_MID__;
				tot += CELL_BOT_RIGHT;

				if (tot == 3)
					g_map[next_curr()].map[i][j] = 1;
				else if (tot == 2)
					g_map[next_curr()].map[i][j] = g_map[curr].map[i][j] * 2;
				else if (tot < 2 || tot > 3)
					g_map[next_curr()].map[i][j] = 0;

			}
		}
		map_to_image();
		mlx_put_image_to_window(MLX_ID, WIN_ID, IMG_ID, 0, 0);
		mlx_do_sync(MLX_ID);
		curr = next_curr();
		// usleep(100000);
	}
	return (0);
}

int		main(int ac, char **av)
{
	if (ac != 5)
		return (printf("usage: lifegame win_x, win_y map_x map_y\n") * 0 + -1);
	srand(time(NULL));
	init_mlx(atoi(av[1]), atoi(av[2]));
	init_map(0, atoi(av[3]), atoi(av[4]));
	init_map(1, atoi(av[3]), atoi(av[4]));
	init_grid();

	for (int i = 0; i < MAP_Y; i++)
		for (int j = 0; j < MAP_X; j++)
			MAP[i][j] = ft_rand_bin();
	map_to_image();
	mlx_put_image_to_window(MLX_ID, WIN_ID, IMG_ID, 0, 0);
	mlx_do_sync(MLX_ID);

	process(NULL);
	// mlx_loop_hook(WIN_ID, process, NULL);
	// mlx_loop(MLX_ID);
	return (0);
}
