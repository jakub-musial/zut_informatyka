#include <utmpx.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <grp.h>
#include <string.h>
#include <dlfcn.h>


int main(int argc, char **argv) 
{	
	int h_flag = 0, g_flag = 0, ret, index; 

	while ((ret = getopt(argc, argv, "hg")) != -1)
	{
		switch (ret)
		{
			case 'h': h_flag = 1; break;
			case 'g': g_flag = 1; break;
			default: abort();
		}
	}


	struct utmpx *utxent;
	struct passwd *pw;
	
	while ((utxent = getutxent()) != NULL)
	{
		if (utxent->ut_type == USER_PROCESS) 
		{
			pw = getpwnam(utxent->ut_user);
			if (pw == NULL) return 0;
			
			printf("%s", utxent->ut_user);

			if (h_flag) printf(" (%s)", utxent->ut_host);
			if (g_flag)
			{
				void *handle = dlopen("./lib.so", RTLD_LAZY);
				if (!handle)
				{
					printf("%s\n", dlerror());
					exit(EXIT_FAILURE);
				}
				dlerror();

				char** (*fp_get_user_group_list)(char*, gid_t);
				fp_get_user_group_list = dlsym(handle, "get_user_group_list");
				char *error;
				if ((error = dlerror()) != NULL)  
				{
					fprintf(stderr, "%s\n", error);
        			exit(EXIT_FAILURE);
				}

				char **group_list = (*fp_get_user_group_list)(utxent->ut_user, pw->pw_gid);
				dlclose(handle);
				
				printf(" [");
				for (int i = 0; group_list[i] != NULL; i++)  {
					printf("%s%s", (i > 0) ? ", " : "", group_list[i]);
					free(group_list[i]);\
					}
				printf("]");
				
			}
			printf("\n");
		}
	}
	return 0;
}
