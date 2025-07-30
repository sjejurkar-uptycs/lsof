
#if	defined(HAS_JFS2)
#define	_H_JFS_INO				/* prevent <jfs_ino.h> */
#define	_H_JFS_INODE				/* prevent <jfs_inode.h> */
#define	PROTO_H					/* prevent "proto.h" and
						 * "dproto.h" until struct
						 * inode is available from
						 * <j2/j2_inode.h> */
#define	DPROTO_H
#include "lsof.h"
#define	_KERNEL
#include <j2/j2_inode.h>
#undef	PROTO_H					/* enable "proto.h" */
#undef	DPROTO_H				/* enable "dproto.h" */
#include "proto.h"
#include "dproto.h"

int
readj2lino(ga, li)
	struct gnode *ga;			/* gnode address */
	struct l_ino *li;			/* local inode receiver */
{
	struct inode i;				/* jfs2 inode */
/*
 * Read the jfs2 inode and fill in the local inode receiver.
 *
 * Note: the caller is responsible for initializing *li to zeroes.
 */
	if (!ga
	||  !ga->gn_data
	||  kread((KA_T)ga->gn_data, (char *)&i, sizeof(i)))
	    return(1);
	li->dev = ga->gn_rdev;
	li->nlink = i.i_nlink;
	li->number = (INODETYPE)i.i_number;
	li->size = i.i_size;
	li->dev_def = li->nlink_def = li->number_def = li->size_def = 1;
	return(0);
}
#endif	/* defined(HAS_JFS2) */
