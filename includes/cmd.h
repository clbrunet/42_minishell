#ifndef CMD_H
# define CMD_H

typedef struct s_cmd	t_cmd;
struct					s_cmd
{
	char	*exe;
	char	**args;
	t_cmd	*pipe;
};

#endif
