#ifndef CMD_H
# define CMD_H

typedef struct s_cmd	t_cmd;
struct					s_cmd
{
	char	*exe;
	char	**args;
	t_cmd	*pipe;
};

typedef struct s_parse_cmd	t_parse_cmd;
struct					s_parse_cmd
{
	t_cmd	*cmd;
	t_cmd	*p_cmd;
	t_cmd	*first_cmd;
	const char *str_cmd;

};
#endif
