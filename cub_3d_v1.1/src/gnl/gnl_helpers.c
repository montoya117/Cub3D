#include "cub_3d.h"

char	*gnl_init_stash(char *stash)
{
	if (!stash)
		return (ft_strdup(""));
	return (stash);
}

char	*gnl_join_and_free(char *stash, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(stash, buffer);
	free(stash);
	return (temp);
}
