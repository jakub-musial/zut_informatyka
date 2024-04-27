#include <utmpx.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

int print_info() {
	struct utmpx *utxent;
	struct passwd *pwnam;
	
	do
	{
		utxent = getutxent();
		if (utxent == NULL) return 0;
		
		if (utxent->ut_type == USER_PROCESS) 
		{
			pwnam = getpwnam(utxent->ut_user);
			if (pwnam == NULL) return 0;
			
			printf("%d (%s) %s %s\n",
				pwnam->pw_uid, utxent->ut_user, utxent->ut_line, utxent->ut_host);
		}
	}
	while (utxent != NULL);
	
	return 1;
}
