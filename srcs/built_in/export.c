
#include "built_in.h"

int	export_cmd(t_cmd const *cmd, char **envp_ptr[])
{
	(void)cmd;
	(void)envp_ptr;
	printf("salut\n");
	fflush(stdout);
	return (1);
}
