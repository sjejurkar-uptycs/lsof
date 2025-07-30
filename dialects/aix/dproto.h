
#if	!defined(DPROTO_H)
#define	DPROTO_H

# if     defined(HAS_AFS)
_PROTOTYPE(extern struct vnode *alloc_vcache,(void));
_PROTOTYPE(extern int hasAFS,(struct vnode *vp));
_PROTOTYPE(extern int readafsnode,(KA_T va, struct vnode *v, struct afsnode *an));
# endif  /* defined(HAS_AFS) */

# if	defined(HAS_JFS2)
_PROTOTYPE(extern int readj2lino,(struct gnode *ga, struct l_ino *li));
# endif	/* defined(HAS_JFS2) */

_PROTOTYPE(extern int getchan,(char *p));
_PROTOTYPE(extern int is_file_named,(char *p, enum vtype ty, chan_t ch, int ic));
_PROTOTYPE(extern char isglocked,(struct gnode *ga));
_PROTOTYPE(extern int readlino,(struct gnode *ga, struct l_ino *li));
_PROTOTYPE(extern struct l_vfs *readvfs,(struct vnode *vn));

# if	AIXV>=4200
_PROTOTYPE(extern void process_shmt,(KA_T sa));
# endif	/* AIV>=4200 */

# if	defined(HASDCACHE) && AIXV>=4140
_PROTOTYPE(extern void clr_sect,(void));
_PROTOTYPE(extern int rw_clone_sect,(int m));
# endif	/* defined(HASDCACHE) && AIXV>=4140 */

#endif	/* !defined(DPROTO_H) */
