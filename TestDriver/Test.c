#include <ntddk.h>
#include "ght_hash_table.h"

#include "Test.h"

VOID
test_Simple(
	VOID
)
{
	ght_hash_table_t *p_table;
	int *p_data;
	int *p_he;

	p_table = ght_create(128);
	if (NULL == p_table)
	{
		// We can't allocate the hash-table, nothing to do here
		return;
	}

	p_data = (int*)ExAllocatePool(PagedPool, sizeof(int));
	if (NULL == p_data)
	{
		// We can't allocate the data, nothing to do here
		return;
	}

	/* Assign the data a value */
	*p_data = 15;

	/* Insert "blabla" into the hash table */
	NT_ASSERT(0 == ght_insert(
		p_table,
		p_data,
		(unsigned int)(sizeof(char)*strlen("blabla")),
		"blabla"));

	/* Search for "blabla" */
	p_he = ght_get(
		p_table,
		(unsigned int)(sizeof(char)*strlen("blabla")), 
		"blabla");
	NT_ASSERT(NULL != p_he);

	/* Remove the hash table */
	ght_finalize(p_table);
}

VOID
TEST_RunTests(
	VOID
)
{
	test_Simple();
}
