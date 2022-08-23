#include "hook.h"

typedef void	(*key_hook_func)(t_mlx_data *mlx_data);

/*
static const key_hook_func	g_key_hook_func_tab[348] = {
	NULL,	// 1
	NULL,	// 2
	NULL,	// 3
	NULL,	// 4
	NULL,	// 5
	NULL,	// 6
	NULL,	// 7
	NULL,	// 8
	NULL,	// 9
	NULL,	// 10
	NULL,	// 11
	NULL,	// 12
	NULL,	// 13
	NULL,	// 14
	NULL,	// 15
	NULL,	// 16
	NULL,	// 17
	NULL,	// 18
	NULL,	// 19
	NULL,	// 20
	NULL,	// 21
	NULL,	// 22
	NULL,	// 23
	NULL,	// 24
	NULL,	// 25
	NULL,	// 26
	NULL,	// 27
	NULL,	// 28
	NULL,	// 29
	NULL,	// 30
	NULL,	// 31
	NULL,	// MLX_KEY_SPACE			= 32,
	NULL,	// 33
	NULL,	// 34
	NULL,	// 35
	NULL,	// 36
	NULL,	// 37
	NULL,	// 38
	NULL,	// MLX_KEY_APOSTROPHE		= 39,
	NULL,	// 40
	NULL,	// 41
	NULL,	// 42
	NULL,	// 43
	NULL,	// MLX_KEY_COMMA			= 44,
	NULL,	// MLX_KEY_MINUS			= 45,
	NULL,	// MLX_KEY_PERIOD			= 46,
	NULL,	// MLX_KEY_SLASH			= 47,
	NULL,	// MLX_KEY_0				= 48,
	NULL,	// MLX_KEY_1				= 49,
	NULL,	// MLX_KEY_2				= 50,
	NULL,	// MLX_KEY_3				= 51,
	NULL,	// MLX_KEY_4				= 52,
	NULL,	// MLX_KEY_5				= 53,
	NULL,	// MLX_KEY_6				= 54,
	NULL,	// MLX_KEY_7				= 55,
	NULL,	// MLX_KEY_8				= 56,
	NULL,	// MLX_KEY_9				= 57,
	NULL,	// MLX_KEY_SEMICOLON		= 59,
	NULL,	// 60
	NULL,	// MLX_KEY_EQUAL			= 61,
	NULL,	// 62
	NULL,	// 63
	NULL,	// 64
	move_left,	// MLX_KEY_A				= 65,
	NULL,	// MLX_KEY_B				= 66,
	NULL,	// MLX_KEY_C				= 67,
	move_right,	// MLX_KEY_D				= 68,
	NULL,	// MLX_KEY_E				= 69,
	NULL,	// MLX_KEY_F				= 70,
	NULL,	// MLX_KEY_G				= 71,
	NULL,	// MLX_KEY_H				= 72,
	NULL,	// MLX_KEY_I				= 73,
	NULL,	// MLX_KEY_J				= 74,
	NULL,	// MLX_KEY_K				= 75,
	NULL,	// MLX_KEY_L				= 76,
	NULL,	// MLX_KEY_M				= 77,
	NULL,	// MLX_KEY_N				= 78,
	NULL,	// MLX_KEY_O				= 79,
	NULL,	// MLX_KEY_P				= 80,
	NULL,	// MLX_KEY_Q				= 81,
	NULL,	// MLX_KEY_R				= 82,
	move_backward,	// MLX_KEY_S				= 83,
	NULL,	// MLX_KEY_T				= 84,
	NULL,	// MLX_KEY_U				= 85,
	NULL,	// MLX_KEY_V				= 86,
	move_forward,	// MLX_KEY_W				= 87,
	NULL,	// MLX_KEY_X				= 88,
	NULL,	// MLX_KEY_Y				= 89,
	NULL,	// MLX_KEY_Z				= 90,
	NULL,	// MLX_KEY_LEFT_BRACKET	= 91,
	NULL,	// MLX_KEY_BACKSLASH		= 92,
	NULL,	// MLX_KEY_RIGHT_BRACKET	= 93,
	NULL,	// 94
	NULL,	// 95
	NULL,	// MLX_KEY_GRAVE_ACCENT	= 96,
	NULL,	// 96
	NULL,	// 97
	NULL,	// 98
	NULL,	// 99
	NULL,	// 100
	NULL,	// 101
	NULL,	// 102
	NULL,	// 103
	NULL,	// 104
	NULL,	// 105
	NULL,	// 106
	NULL,	// 107
	NULL,	// 108
	NULL,	// 109
	NULL,	// 110
	NULL,	// 111
	NULL,	// 112
	NULL,	// 113
	NULL,	// 114
	NULL,	// 115
	NULL,	// 116
	NULL,	// 117
	NULL,	// 118
	NULL,	// 119
	NULL,	// 120
	NULL,	// 121
	NULL,	// 122
	NULL,	// 123
	NULL,	// 124
	NULL,	// 125
	NULL,	// 126
	NULL,	// 127
	NULL,	// 128
	NULL,	// 129
	NULL,	// 130
	NULL,	// 131
	NULL,	// 132
	NULL,	// 133
	NULL,	// 134
	NULL,	// 135
	NULL,	// 136
	NULL,	// 137
	NULL,	// 138
	NULL,	// 139
	NULL,	// 140
	NULL,	// 141
	NULL,	// 142
	NULL,	// 143
	NULL,	// 144
	NULL,	// 145
	NULL,	// 146
	NULL,	// 147
	NULL,	// 148
	NULL,	// 149
	NULL,	// 150
	NULL,	// 151
	NULL,	// 152
	NULL,	// 153
	NULL,	// 154
	NULL,	// 155
	NULL,	// 156
	NULL,	// 157
	NULL,	// 158
	NULL,	// 159
	NULL,	// 160
	NULL,	// 161
	NULL,	// 162
	NULL,	// 163
	NULL,	// 164
	NULL,	// 165
	NULL,	// 166
	NULL,	// 167
	NULL,	// 168
	NULL,	// 169
	NULL,	// 170
	NULL,	// 171
	NULL,	// 172
	NULL,	// 173
	NULL,	// 174
	NULL,	// 175
	NULL,	// 176
	NULL,	// 177
	NULL,	// 178
	NULL,	// 179
	NULL,	// 180
	NULL,	// 181
	NULL,	// 182
	NULL,	// 183
	NULL,	// 184
	NULL,	// 185
	NULL,	// 186
	NULL,	// 187
	NULL,	// 188
	NULL,	// 189
	NULL,	// 190
	NULL,	// 191
	NULL,	// 192
	NULL,	// 193
	NULL,	// 194
	NULL,	// 195
	NULL,	// 196
	NULL,	// 197
	NULL,	// 198
	NULL,	// 199
	NULL,	// 200
	NULL,	// 201
	NULL,	// 202
	NULL,	// 203
	NULL,	// 204
	NULL,	// 205
	NULL,	// 206
	NULL,	// 207
	NULL,	// 208
	NULL,	// 209
	NULL,	// 210
	NULL,	// 211
	NULL,	// 212
	NULL,	// 213
	NULL,	// 214
	NULL,	// 215
	NULL,	// 216
	NULL,	// 217
	NULL,	// 218
	NULL,	// 219
	NULL,	// 220
	NULL,	// 221
	NULL,	// 222
	NULL,	// 223
	NULL,	// 224
	NULL,	// 225
	NULL,	// 226
	NULL,	// 227
	NULL,	// 228
	NULL,	// 229
	NULL,	// 230
	NULL,	// 231
	NULL,	// 232
	NULL,	// 233
	NULL,	// 234
	NULL,	// 235
	NULL,	// 236
	NULL,	// 237
	NULL,	// 238
	NULL,	// 239
	NULL,	// 240
	NULL,	// 241
	NULL,	// 242
	NULL,	// 243
	NULL,	// 244
	NULL,	// 245
	NULL,	// 246
	NULL,	// 247
	NULL,	// 248
	NULL,	// 249
	NULL,	// 250
	NULL,	// 251
	NULL,	// 252
	NULL,	// 253
	NULL,	// 254
	NULL,	// 255
	NULL,	// MLX_KEY_ESCAPE			= 256,
	NULL,	// MLX_KEY_ENTER			= 257,
	NULL,	// MLX_KEY_TAB				= 258,
	NULL,	// MLX_KEY_BACKSPACE		= 259,
	NULL,	// MLX_KEY_INSERT			= 260,
	NULL,	// MLX_KEY_DELETE			= 261,
	NULL,	// MLX_KEY_RIGHT			= 262,
	NULL,	// MLX_KEY_LEFT			= 263,
	NULL,	// MLX_KEY_DOWN			= 264,
	NULL,	// MLX_KEY_UP				= 265,
	NULL,	// MLX_KEY_PAGE_UP			= 266,
	NULL,	// MLX_KEY_PAGE_DOWN		= 267,
	NULL,	// MLX_KEY_HOME			= 268,
	NULL,	// MLX_KEY_END				= 269,
	NULL,	// 270
	NULL,	// 271
	NULL,	// 272
	NULL,	// 273
	NULL,	// 274
	NULL,	// 275
	NULL,	// 276
	NULL,	// 277
	NULL,	// 278
	NULL,	// 279
	NULL,	// MLX_KEY_CAPS_LOCK		= 280,
	NULL,	// MLX_KEY_SCROLL_LOCK		= 281,
	NULL,	// MLX_KEY_NUM_LOCK		= 282,
	NULL,	// MLX_KEY_PRINT_SCREEN	= 283,
	NULL,	// MLX_KEY_PAUSE			= 284,
	NULL,	// 285
	NULL,	// 286
	NULL,	// 287
	NULL,	// 288
	NULL,	// 289
	NULL,	// MLX_KEY_F1				= 290,
	NULL,	// MLX_KEY_F2				= 291,
	NULL,	// MLX_KEY_F3				= 292,
	NULL,	// MLX_KEY_F4				= 293,
	NULL,	// MLX_KEY_F5				= 294,
	NULL,	// MLX_KEY_F6				= 295,
	NULL,	// MLX_KEY_F7				= 296,
	NULL,	// MLX_KEY_F8				= 297,
	NULL,	// MLX_KEY_F9				= 298,
	NULL,	// MLX_KEY_F10				= 299,
	NULL,	// MLX_KEY_F11				= 300,
	NULL,	// MLX_KEY_F12				= 301,
	NULL,	// MLX_KEY_F13				= 302,
	NULL,	// MLX_KEY_F14				= 303,
	NULL,	// MLX_KEY_F15				= 304,
	NULL,	// MLX_KEY_F16				= 305,
	NULL,	// MLX_KEY_F17				= 306,
	NULL,	// MLX_KEY_F18				= 307,
	NULL,	// MLX_KEY_F19				= 308,
	NULL,	// MLX_KEY_F20				= 309,
	NULL,	// MLX_KEY_F21				= 310,
	NULL,	// MLX_KEY_F22				= 311,
	NULL,	// MLX_KEY_F23				= 312,
	NULL,	// MLX_KEY_F24				= 313,
	NULL,	// MLX_KEY_F25				= 314,
	NULL,	// 315
	NULL,	// 316
	NULL,	// 317
	NULL,	// 318
	NULL,	// 319
	NULL,	// MLX_KEY_KP_0			= 320,
	NULL,	// MLX_KEY_KP_1			= 321,
	NULL,	// MLX_KEY_KP_2			= 322,
	NULL,	// MLX_KEY_KP_3			= 323,
	NULL,	// MLX_KEY_KP_4			= 324,
	NULL,	// MLX_KEY_KP_5			= 325,
	NULL,	// MLX_KEY_KP_6			= 326,
	NULL,	// MLX_KEY_KP_7			= 327,
	NULL,	// MLX_KEY_KP_8			= 328,
	NULL,	// MLX_KEY_KP_9			= 329,
	NULL,	// MLX_KEY_KP_DECIMAL		= 330,
	NULL,	// MLX_KEY_KP_DIVIDE		= 331,
	NULL,	// MLX_KEY_KP_MULTIPLY		= 332,
	NULL,	// MLX_KEY_KP_SUBTRACT		= 333,
	NULL,	// MLX_KEY_KP_ADD			= 334,
	NULL,	// MLX_KEY_KP_ENTER		= 335,
	NULL,	// MLX_KEY_KP_EQUAL		= 336,
	NULL,	// 337
	NULL,	// 338
	NULL,	// 339
	NULL,	// MLX_KEY_LEFT_SHIFT		= 340,
	NULL,	// MLX_KEY_LEFT_CONTROL	= 341,
	NULL,	// MLX_KEY_LEFT_ALT		= 342,
	NULL,	// MLX_KEY_LEFT_SUPER		= 343,
	NULL,	// MLX_KEY_RIGHT_SHIFT		= 344,
	NULL,	// MLX_KEY_RIGHT_CONTROL	= 345,
	NULL,	// MLX_KEY_RIGHT_ALT		= 346,
	NULL,	// MLX_KEY_RIGHT_SUPER		= 347,
	NULL,	// MLX_KEY_MENU			= 348,
};
*/

void	key_hook(mlx_key_data_t keydata, void* param)
{
	t_mlx_data	*mlx_data;

	mlx_data = param;
	if (mlx_is_key_down(mlx_data->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(mlx_data->mlx_ptr);
	if (mlx_is_key_down(mlx_data->mlx_ptr, MLX_KEY_UP))
		mlx_data->player.y -= 5;
	if (mlx_is_key_down(mlx_data->mlx_ptr, MLX_KEY_DOWN))
		mlx_data->player.y += 5;
	if (mlx_is_key_down(mlx_data->mlx_ptr, MLX_KEY_LEFT))
		mlx_data->player.x -= 5;
	if (mlx_is_key_down(mlx_data->mlx_ptr, MLX_KEY_RIGHT))
		mlx_data->player.x += 5;
	//g_key_hook_func_tab[keydata.key]((t_mlx_data *)param);
	(void)keydata;
	(void)param;
}

void	cursor_hook(double xpos, double ypos, void* param)
{
	(void)xpos;
	(void)ypos;
	(void)param;
}
