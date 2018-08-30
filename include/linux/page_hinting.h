#include <linux/smpboot.h>

#define MAX_FGPT_ENTRIES	1000
/*
 * hypervisor_pages - It is a dummy structure passed with the hypercall.
 * @pfn - page frame number for the page which is to be freed.
 * @pages - number of pages which are supposed to be freed.
 * A global array object is used to to hold the list of pfn and pages and is
 * passed as part of the hypercall.
 */
struct hypervisor_pages {
	unsigned long pfn;
	unsigned int pages;
};

extern struct smp_hotplug_thread hinting_threads;
extern struct hypervisor_pages hypervisor_pagelist[MAX_FGPT_ENTRIES];

extern int guest_page_hinting_flag;
extern struct static_key_false guest_page_hinting_key;
extern unsigned int isolated_page_counter, failed_isolation_counter;
extern bool want_page_poisoning;
extern void (*request_hypercall)(void *, u64, int);
extern void *balloon_ptr;

int guest_page_hinting_sysctl(struct ctl_table *table, int write,
			      void __user *buffer, size_t *lenp, loff_t *ppos);
void guest_free_page(struct page *page, int order);
int count_isolated_pages(struct ctl_table *table, int write,
			 void __user *buffer, size_t *lenp, loff_t *ppos);
int count_failed_isolations(struct ctl_table *table, int write,
			    void __user *buffer, size_t *lenp, loff_t *ppos);
extern int __isolate_free_page(struct page *page, unsigned int order);

static inline void disable_page_poisoning(void)
{
#ifdef CONFIG_PAGE_POISONING
	want_page_poisoning = 0;
#endif
}
