/*
 * fino.c -- find block (optional) and character device file inode numbers
 *
 * The caller must define:
 *
 *	HASBLKDEV	to activate the block device inode lookup
 */


#include "machine.h"

#if	defined(HASBLKDEV) || defined(USE_LIB_FIND_CH_INO)

#include "../lsof.h"

#else	/* !defined(HASBLKDEV) && !defined(USE_LIB_FIND_CH_INO) */
char fino_d1[] = "d"; char *fino_d2 = fino_d1;
#endif	/* defined(HASBLKDEV) || defined(USE_LIB_FIND_CH_INO) */


#if	defined(HASBLKDEV)
/*
 * find_bl_ino() - find the inode number for a block device file
 */

void
find_bl_ino()
{
	dev_t ldev, tdev;
	int low, hi, mid;

	readdev(0);

# if	defined(HASDCACHE)
find_bl_ino_again:
# endif	/* defined(HASDCACHE) */

	low = mid = 0;
	hi = BNdev - 1;
	if (!Lf->dev_def || (Lf->dev != DevDev) || !Lf->rdev_def)
	    return;
	ldev = Lf->rdev;
	while (low <= hi) {
	    mid = (low + hi) / 2;
	    tdev = BSdev[mid]->rdev;
	    if (ldev < tdev)
		hi = mid - 1;
	    else if (ldev > tdev)
		low = mid + 1;
	    else {

# if	defined(HASDCACHE)
		if (DCunsafe && !BSdev[mid]->v && !vfy_dev(BSdev[mid]))
		    goto find_bl_ino_again;
# endif	/* defined(HASDCACHE) */

		Lf->inode = BSdev[mid]->inode;
		if (Lf->inp_ty == 0)
		    Lf->inp_ty = 1;
		return;
	    }
	}
}
#endif	/* defined(HASBLKDEV) */


#if	defined(USE_LIB_FIND_CH_INO)
/*
 * find_ch_ino() - find the inode number for a character device file
 */

void
find_ch_ino()
{
	dev_t ldev, tdev;
	int low, hi, mid;

	readdev(0);

# if	defined(HASDCACHE)
find_ch_ino_again:
# endif	/* defined(HASDCACHE) */

	low = mid = 0;
	hi = Ndev - 1;
	if (!Lf->dev_def || (Lf->dev != DevDev) || !Lf->rdev_def)
	    return;
	ldev = Lf->rdev;
	while (low <= hi) {
	    mid = (low + hi) / 2;
	    tdev = Sdev[mid]->rdev;
	    if (ldev < tdev)
		hi = mid - 1;
	    else if (ldev > tdev)
		low = mid + 1;
	    else {

# if	defined(HASDCACHE)
		if (DCunsafe && !Sdev[mid]->v && !vfy_dev(Sdev[mid]))
		    goto find_ch_ino_again;
# endif	/* defined(HASDCACHE) */

		Lf->inode = Sdev[mid]->inode;
		if (Lf->inp_ty == 0)
		    Lf->inp_ty = 1;
		return;
	    }
	}
}
#endif	/* defined(USE_LIB_FIND_CH_INO) */
