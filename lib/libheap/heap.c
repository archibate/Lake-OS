#include <lxL4/page.h>
#include <lxL4/sysmm.h>
#include <lxL4/umemlay.h>
#include <ad_t.h>
#include <assert.h>
#include "malloc.h"
#include "heap.h"

#define HEAP_START USR_STACK_BEG

static ad_t heap_top = HEAP_START;
static struct heap_hdr *first = 0;

static void grow_heap_to(ad_t end);
static void shrink_heap_to(struct heap_hdr *chunk);
static void split_chunk(struct heap_hdr *chunk, unsigned int len);
static void merge_around(struct heap_hdr *chunk);

#if 0
void show_heap_info(void)
{
	struct heap_hdr *curr = first;
	while (curr) {
		ASSERT(curr->next != curr, "(heap) heap_hdr list self-loop");
		printstr("    0x");
		printint((ad_t) curr);
		printstr("    0x");
		printint(curr->len);
		printstr("   ");
		if (curr->allocated)
			printstr("  used\n");
		else
			printstr("  free\n");
		curr = curr->next;
	}
	printstr("\n");
}
#endif

void *malloc(size_t size)
{
	unsigned len = size + HEAP_HDR_SIZE;

	struct heap_hdr *curr = first, *prev = 0;

	while (curr) {
		assert(curr->next != curr);
		if (!curr->allocated && curr->len >= len) {
			split_chunk(curr, len);
			curr->allocated = 1;
			return (void *) (curr + 1);
		}
		prev = curr;
		curr = curr->next;
	}

	ad_t start;
	if (prev) {
		start = (ad_t) prev + prev->len;
	} else {
		start = HEAP_START;
		first = (struct heap_hdr *) start;
	}

	grow_heap_to(start + len);
	curr = (struct heap_hdr *) start;
	if (prev != curr)
		curr->prev = prev;
	else
		curr->prev = 0;
	curr->next = 0;
	curr->allocated = 1;
	curr->len = len;

	if (prev && prev != curr)
		prev->next = curr;

	return (void *)(curr + 1);
}

static void split_chunk(struct heap_hdr *chunk, unsigned int len)
{
	if (chunk->len - len > HEAP_HDR_SIZE) {
		struct heap_hdr *new_chk = (struct heap_hdr *)
			((ad_t) chunk + len);
		new_chk->prev = chunk;
		new_chk->next = chunk->next;
		new_chk->allocated = 0;
		new_chk->len = chunk->len - len;

		chunk->next = new_chk;
		chunk->len = len;
	}
}

static void sbrk_heap_top(void)
{
	ad_t res = L4m_Setbrk(heap_top);
	assert(!res);
}

static void grow_heap_to(ad_t end)
{
	while (heap_top < end) {
		heap_top += PGSIZE;
	}
	sbrk_heap_top();
}

void free(void *p)
{
	struct heap_hdr *curr = (struct heap_hdr *) p;
	curr -= 1;
	curr->allocated = 0;
	merge_around(curr);
}

static void shrink_heap_to(struct heap_hdr *chunk)
{
	if (chunk->prev == 0)
		first = 0;
	else
		chunk->prev->next = 0;

	while (heap_top - PGSIZE >= (ad_t) chunk) {
		heap_top -= PGSIZE;
	}
	sbrk_heap_top();
}

static void merge_around(struct heap_hdr *chunk)
{
	if (chunk->next && !chunk->next->allocated) {
		chunk->len += chunk->next->len;
		if (chunk->next->next) {
			chunk->next->next->prev = chunk;
		}
		chunk->next = chunk->next->next;
	}

	if (chunk->prev && !chunk->prev->allocated) {
		chunk->prev->len += chunk->len;
		chunk->prev->next = chunk->next;
		if (chunk->next) {
			chunk->next->prev = chunk->prev;
		}
		chunk = chunk->prev;
	}

	if (!chunk->next)
		shrink_heap_to(chunk);
}
