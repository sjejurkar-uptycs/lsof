#include "machine.h"

#if	defined(USE_LIB_CKKV)

#include "../lsof.h"
#include <sys/utsname.h>


/*
 * ckkv() - check kernel version
 */

void
ckkv(d, er, ev, ea)
	char *d;			/* dialect */
	char *er;			/* expected revision; NULL, no test */
	char *ev;			/* expected version; NULL, no test */
	char *ea;			/* expected architecture; NULL, no
					 * test */
{

# if	defined(HASKERNIDCK)
	struct utsname u;

	if (Fwarn)
	    return;
/*
 * Read the system information via uname(2).
 */
	if (uname(&u) < 0) {
	    (void) fprintf(stderr, "%s: uname error: %s\n",
		Pn, strerror(errno));
	    Error();
	}
	if (er && strcmp(er, u.release)) {
	    (void) fprintf(stderr,
		"%s: WARNING: compiled for %s release %s; this is %s.\n",
		Pn, d, er, u.release);
	}
	if (ev && strcmp(ev, u.version)) {
	    (void) fprintf(stderr,
		"%s: WARNING: compiled for %s version %s; this is %s.\n",
		Pn, d, ev, u.version);
	}
	if (ea && strcmp(ea, u.machine)) {
	    (void) fprintf(stderr,
		"%s: WARNING: compiled for %s architecture %s; this is %s.\n",
		Pn, d, ea, u.machine);
	}
# endif	/* defined(HASKERNIDCK) */

}
#else	/* !defined(USE_LIB_CKKV) */
char ckkv_d1[] = "d"; char *ckkv_d2 = ckkv_d1;
#endif	/* defined(USE_LIB_CKKV) */
