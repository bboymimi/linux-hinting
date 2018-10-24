#include <linux/smpboot.h>

#define MAX_FGPT_ENTRIES	250000
//#define MAX_FGPT_ENTRIES	5
//#define MAX_FGPT_ENTRIES	1000
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
	unsigned int order;
};

extern struct smp_hotplug_thread hinting_threads;
extern struct hypervisor_pages hypervisor_pagelist[MAX_FGPT_ENTRIES];

extern int guest_page_hinting_flag;
extern struct static_key_false guest_page_hinting_key;
extern unsigned long total_isolated_memory, failed_isolation_memory, tail_isolated_memory, scanned_memory, guest_returned_memory, buddy_skipped_memory;
extern unsigned long captured_freed_memory, reallocated_memory, free_non_buddy_memory, total_freed_memory, pcpbulklist_memory, zero_order_pages, lrulist_memory;
extern bool want_page_poisoning;
extern void (*request_hypercall)(void *, u64, int);
extern void *balloon_ptr;

int guest_page_hinting_sysctl(struct ctl_table *table, int write,
			      void __user *buffer, size_t *lenp, loff_t *ppos);
void guest_free_page(struct page *page, int order);
int count_pcpbulklist_memory(struct ctl_table *table, int write,
			 void __user *buffer, size_t *lenp, loff_t *ppos);
int count_lrulist_memory(struct ctl_table *table, int write,
			 void __user *buffer, size_t *lenp, loff_t *ppos);
int count_buddy_skipped_memory(struct ctl_table *table, int write,
			 void __user *buffer, size_t *lenp, loff_t *ppos);
int count_total_isolated_memory(struct ctl_table *table, int write,
			 void __user *buffer, size_t *lenp, loff_t *ppos);
int count_tail_isolated_memory(struct ctl_table *table, int write,
			 void __user *buffer, size_t *lenp, loff_t *ppos);
int count_failed_isolations_memory(struct ctl_table *table, int write,
			    void __user *buffer, size_t *lenp, loff_t *ppos);
int count_scanned_memory(struct ctl_table *table, int write,
			    void __user *buffer, size_t *lenp, loff_t *ppos);
int count_guest_returned_memory(struct ctl_table *table, int write,
			    void __user *buffer, size_t *lenp, loff_t *ppos);
int count_captured_freed_memory(struct ctl_table *table, int write,
                         void __user *buffer, size_t *lenp,
                         loff_t *ppos);
int count_total_freed_memory(struct ctl_table *table, int write,
                         void __user *buffer, size_t *lenp,
                         loff_t *ppos);
int count_reallocated_memory(struct ctl_table *table, int write,
                         void __user *buffer, size_t *lenp,
                         loff_t *ppos);
int count_free_non_buddy_memory(struct ctl_table *table, int write,
                         void __user *buffer, size_t *lenp,
                         loff_t *ppos);
int count_zero_order_pages(struct ctl_table *table, int write,
                         void __user *buffer, size_t *lenp,
                         loff_t *ppos);
extern int __isolate_free_page(struct page *page, unsigned int order);

extern void __free_one_page(struct page *page,
                unsigned long pfn,
                struct zone *zone, unsigned int order,
                int migratetype);

static inline void disable_page_poisoning(void)
{
#ifdef CONFIG_PAGE_POISONING
	want_page_poisoning = 0;
#endif
}
