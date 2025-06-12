# cub3d <parse>
## Things that Nobu wants Lazy to do
- Complete <cub3d>
  - I think 
  - Let me know if you find some issue
## reference
#### design
https://github.com/noburestaurant/cub3d/blob/norminette/design/design_file_parsing.md
#### structure info
**\*** : infos obtained in the parse part
- t_config
```
typedef struct s_config
{
	char	*no_path; // *
	char	*so_path; // *
	char	*we_path; // *
	char	*ea_path; // *
	int		floor_color[3]; // *
	int		ceil_color[3]; // *
	int		has_no;
	int		has_so;
	int		has_we;
	int		has_ea;
	int		has_floor;
	int		has_ceil;
}	t_config;
```

- t_parse_data
```
typedef struct s_parse_data
{
	int		height; // *
	int		max_width; // *
	int		in_map_section;
	char	**raw_map; // *
	char	*error_msg;
}	t_parse_data;
```

- t_vars
```
typedef struct s_vars
{
	void			*mlx;
	void			*win;
	t_img_player	*img_player;
	void			*img_renga;
	void			*img_grass;
	t_texture_list	*textures;
	t_config		config; // *
	char			**map; // *
	t_player		player;
	t_ray			ray;
	t_render_wall	render_info;
	int				img_width;
	int				img_height;
	int				width;
	int				height;
}	t_vars;
```
