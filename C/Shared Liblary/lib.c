#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <grp.h>
#include <string.h>

char** get_user_group_list(char *user, gid_t gid)
{
	int ngroups = 0;
	getgrouplist(user, gid, NULL, &ngroups);

	gid_t groups[ngroups];
	getgrouplist(user, gid, groups, &ngroups);

	char **group_names = malloc((ngroups + 1) * sizeof(char*));
	for (int i = 0; i < ngroups; i++)
	{
    	struct group *gr = getgrgid(groups[i]);
    	if (gr != NULL) 
		{
			group_names[i] = malloc(strlen(gr->gr_name));
			strcpy(group_names[i], gr->gr_name);
		}
	}

	group_names[ngroups] = NULL;

	return group_names;
}
