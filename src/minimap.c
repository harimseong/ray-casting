#include "minimap.h"

inline static t_ivec2	transfer_pos(const t_player player, int x, int y,
	const t_map map);

// transfer pixel position to map position to grid position
inline static uint32_t	get_color(const t_ivec2 pos, const t_map map);

static const uint32_t	g_color_table[128] = {
	0x000000ff,	//	0
	0x000000ff,	//	1
	0x000000ff,	//	2
	0x000000ff,	//	3
	0x000000ff,	//	4
	0x000000ff,	//	5
	0x000000ff,	//	6
	0x000000ff,	//	7
	0x000000ff,	//	8
	0x000000ff,	//	9
	0x000000ff,	//	10
	0x000000ff,	//	11
	0x000000ff,	//	12
	0x000000ff,	//	13
	0x000000ff,	//	14
	0x000000ff,	//	15
	0x000000ff,	//	16
	0x000000ff,	//	17
	0x000000ff,	//	18
	0x000000ff,	//	19
	0x000000ff,	//	20
	0x000000ff,	//	21
	0x000000ff,	//	22
	0x000000ff,	//	23
	0x000000ff,	//	24
	0x000000ff,	//	25
	0x000000ff,	//	26
	0x000000ff,	//	27
	0x000000ff,	//	28
	0x000000ff,	//	29
	0x000000ff,	//	30
	0x000000ff,	//	31
	0x000000ff,	//	32
	0x000000ff,	//	33
	0x000000ff,	//	34
	0x000000ff,	//	35
	0x000000ff,	//	36
	0x000000ff,	//	37
	0x000000ff,	//	38
	0x000000ff,	//	39
	0x000000ff,	//	40
	0x000000ff,	//	41
	0x000000ff,	//	42
	0x000000ff,	//	43
	0x000000ff,	//	44
	0x000000ff,	//	45
	0x000000ff,	//	46
	0x000000ff,	//	47
	0x000000ff,	//	48 = '0'
	0x7f7f7fff,	//	49 = '1'
	0x000000ff,	//	50
	0x3fbfbfff,	//	51
	0x000000ff,	//	52
	0x000000ff,	//	53
	0x000000ff,	//	54
	0x000000ff,	//	55
	0x000000ff,	//	56
	0x000000ff,	//	57
	0x000000ff,	//	58
	0x000000ff,	//	59
	0x000000ff,	//	60
	0x000000ff,	//	61
	0x000000ff,	//	62
	0x000000ff,	//	63
	0x000000ff,	//	64
	0x000000ff,	//	65
	0x000000ff,	//	66
	0x000000ff,	//	67
	0x000000ff,	//	68
	0xffffffff,	//	69 = 'E'
	0x000000ff,	//	70
	0x000000ff,	//	71
	0x000000ff,	//	72
	0x000000ff,	//	73
	0x000000ff,	//	74
	0x000000ff,	//	75
	0x000000ff,	//	76
	0x000000ff,	//	77
	0xffffffff,	//	78 = 'N'
	0x000000ff,	//	79
	0x000000ff,	//	80
	0x000000ff,	//	81
	0x000000ff,	//	82
	0xffffffff,	//	83 = 'S'
	0x000000ff,	//	84
	0x000000ff,	//	85
	0x000000ff,	//	86
	0xffffffff,	//	87 = 'W'
	0x000000ff,	//	88
	0x000000ff,	//	89
	0x000000ff,	//	90
	0x000000ff,	//	91
	0x000000ff,	//	92
	0x000000ff,	//	93
	0x000000ff,	//	94
	0x000000ff,	//	95
	0x000000ff,	//	96
	0x000000ff,	//	97
	0x000000ff,	//	98
	0x000000ff,	//	99
	0x000000ff,	//	100
	0x000000ff,	//	101
	0x000000ff,	//	102
	0x000000ff,	//	103
	0x000000ff,	//	104
	0x000000ff,	//	105
	0x000000ff,	//	106
	0x000000ff,	//	107
	0x000000ff,	//	108
	0x000000ff,	//	109
	0x000000ff,	//	110
	0x000000ff,	//	111
	0x000000ff,	//	112
	0x000000ff,	//	113
	0x000000ff,	//	114
	0x000000ff,	//	115
	0x000000ff,	//	116
	0x000000ff,	//	117
	0x000000ff,	//	118
	0x000000ff,	//	119
	0x000000ff,	//	120
	0x000000ff,	//	121
	0x000000ff,	//	122
	0x000000ff,	//	123
	0x000000ff,	//	124
	0x000000ff,	//	125
	0x000000ff,	//	126
	0x000000ff,	//	127
};

static const int		g_map_per_pixel = MINIMAP_GRID_NUM * GRID_LEN / MINIMAP_WIDTH;

void	render_minimap(t_mlx_data data)
{
	uint32_t	y;
	uint32_t	x;	
	uint32_t	color;

	y = 0;
	while (y < MINIMAP_HEIGHT)
	{
		x = 0;
		while (x < MINIMAP_WIDTH)
		{
			color = get_color(transfer_pos(data.player, x, y, data.map), data.map);
			mlx_put_pixel(data.minimap, x, y, color);
			++x;
		}
		++y;
	}
}

inline static t_ivec2	transfer_pos(const t_player player, int x, int y, const t_map map)
{
	double	map_pos_x;
	double	map_pos_y;

	map_pos_x = (player.x - 3 * GRID_LEN) + g_map_per_pixel * x;
	map_pos_y = (player.y - 3 * GRID_LEN) + g_map_per_pixel * y;
	if ((map_pos_x < 0.0 || map_pos_x >= map.width * GRID_LEN)
		|| (map_pos_y < 0.0 || map_pos_y >= map.height * GRID_LEN))
		return ((t_ivec2){-1, -1});
	return ((t_ivec2){map_pos_x / GRID_LEN, map_pos_y / GRID_LEN});
}

inline static uint32_t	get_color(const t_ivec2 pos, const t_map map)
{
	if (pos.x == -1)
		return (0x000000ff);
	return (g_color_table[(int)map.map[pos.y][pos.x]]);
}
