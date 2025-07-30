

/*
 * The caller must define CVFS_DEVSAVE to have the device number moved
 * from the mounts entry to the local vfs structure.
 *
 * The caller must define CVFS_NLKSAVE to have the link count moved from
 * the mounts entry to the local vfs structure.
 *
 * The caller must define CVFS_SZSAVE to have the size moved from the
 * mounts entry to the local vfs structure.
 */


#include "../machine.h"

#if	defined(USE_LIB_COMPLETEVFS)

#include	"../lsof.h"


/*
 * completevfs() - complete local vfs structure
 */

void
completevfs(vfs, dev)
	struct l_vfs *vfs;		/* local vfs structure pointer */
	dev_t *dev;			/* device */
{
	struct mounts *mp;
/*
 * If only Internet socket files are selected, don't bother completing the
 * local vfs structure.
 */
	if (Selinet)
	    return;
/*
 * Search for a match on device number.
 */
	for (mp = readmnt(); mp; mp = mp->next) {
	    if (mp->dev == *dev) {

# if	defined(CVFS_DEVSAVE)
		vfs->dev = mp->dev;
# endif	/* defined(CVFS_DEVSAVE) */

# if	defined(CVFS_NLKSAVE)
		vfs->nlink = mp->nlink;
# endif	/* defined(CVFS_NLKSAVE) */

# if	defined(CVFS_SZSAVE)
		vfs->size = mp->size;
# endif	/* defined(CVFS_SZSAVE) */

		vfs->dir = mp->dir;
		vfs->fsname = mp->fsname;

# if	defined(HASFSINO)
		vfs->fs_ino = mp->inode;
# endif	/* defined(HASFSINO) */

# if	defined(HASMNTSTAT)
		vfs->mnt_stat = mp->stat;
# endif	/* defined(HASMNTSTAT) */


		return;
	    }
	}
}
#else	/* !defined(USE_LIB_COMPLETEVFS) */
char cvfs_d1[] = "d"; char *cvfs_d2 = cvfs_d1;
#endif	/* defined(USE_LIB_COMPLETEVFS) */
