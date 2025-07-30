#if	defined(HAS_STRFTIME)
#include <time.h>
#endif	/* defined(HAS_STRFTIME) */


/*
 * util_strftime() -- utility function to call strftime(3) without header
 *		      file distractions
 */

int
util_strftime(fmtr, fmtl, fmt)
	char *fmtr;			/* format output receiver */
	int fmtl;			/* sizeof(*fmtr) */
	char *fmt;			/* format */
{

#if	defined(HAS_STRFTIME)
	struct tm *lt;
	time_t tm;

	tm = time((time_t *)NULL);
	lt = localtime(&tm);
	return(strftime(fmtr, fmtl, fmt, lt));
#else	/* !defined(HAS_STRFTIME) */
	return(0);
#endif	/* defined(HAS_STRFTIME) */

}
