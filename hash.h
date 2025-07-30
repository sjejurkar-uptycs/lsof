#if	!defined(LSOF_HASH_H)
#define	LSOF_HASH_H	1

/* Find element in hash table by key, return NULL if not found
 * 
 * table: hash table
 * hash: hash function/macro
 * type: struct type
 * member: member to match key
 * key: key
 * 
 * the struct type should have a member called next
 **/
#define HASH_FIND_ELEMENT(table, hash, type, member, key)		\
    ({type *__value = NULL;						\
	int __h = hash(key);						\
	if ((table)) {							\
	    for (__value = (table)[__h];__value;__value = __value->next) { \
		if ((key) == __value->member) break;			\
	    };								\
	};								\
	__value;})

/* Insert element into hash table
 * 
 * table: hash table
 * hash: hash function/macro
 * element: element
 * member: member name containing key
 * 
 * the type of element should have a member called next
 **/
#define HASH_INSERT_ELEMENT(table, hash, element, member)	\
    ({int __h = hash((element)->member);			\
	(element)->next = (table)[__h];				\
	(table)[__h] = (element);				\
    })

#endif
