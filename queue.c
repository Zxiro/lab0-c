#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q) {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q) {
        return;
    }
    list_ele_t *fr;
    while (q->head) { /*Check whether the quene become NULL*/
        fr = q->head;
        q->head = fr->next; /*point to the next node to be freed*/
        free(fr->value);
        free(fr);
    }
    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!q || !newh) {
        free(newh);
        return false;
    }
    newh->value = malloc((strlen(s) + 1) * sizeof(char));
    if (!newh->value) {
        free(newh->value);
        free(newh);
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    memcpy(newh->value, s, strlen(s) + 1);
    /*Copy the value of s from the addr of s to news*/
    newh->next = q->head;
    q->head = newh;
    if (q->tail == NULL) {
        q->tail = newh;
    }
    q->size += 1;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q) {
        return false;
    }
    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if (!newt) {
        free(newt);
        return false;
    }
    newt->value = malloc((strlen(s) + 1) * sizeof(char *));
    if (!newt->value) {
        free(newt);
        return false;
    }
    /* Remember: It should operate in O(1) time */
    memcpy(newt->value, s, strlen(s) + 1);
    /*Copy the value of s from the addr of s to news*/
    newt->next = NULL;
    if (q->tail == NULL) {
        q->head = newt;
        q->tail = newt;
    } else {
        q->tail->next = newt;
        q->tail = newt;
    }
    q->size += 1;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !q->head || !sp) {
        return false; /*Need to notice about all NULL suitation!*/
    }
    list_ele_t *frptr = q->head;          /*Assign an node to be removed*/
    if (bufsize > strlen(frptr->value)) { /*If the value != NULL*/
        memcpy(sp, frptr->value, strlen(frptr->value));
        sp[strlen(frptr->value)] = '\0'; /*Terminator*/
    } else {
        memcpy(sp, frptr->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    q->head = frptr->next;
    free(frptr->value);
    free(frptr);
    q->size -= 1;
    if (q->size == 0) {
        q->tail = NULL;
    }
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* Remember: It should operate in O(1) time */
    if (!q) {
        return 0;
    }
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (!q || !q->head || q->size <= 1) {
        return;
    }
    list_ele_t *tmp = q->head->next;
    q->tail->next = q->head;
    while (tmp != q->tail) {
        q->head->next = tmp->next;
        tmp->next = q->tail->next;
        q->tail->next = tmp;
        tmp = q->head->next;
    }
    q->tail = q->head;
    q->tail->next = NULL;
    q->head = tmp;
    return;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */

/*Using Merge sort in order to achieve O(nlgn) complexity*/

list_ele_t *merge(list_ele_t *l, list_ele_t *r)
{
    /*Check whether need to merge*/
    if (!r) {
        return l;
    }
    if (!l) {
        return r;
    }
    list_ele_t *head = NULL;
    list_ele_t *tmp = NULL;
    /*Recursive, Check whether next node needed to be merged*/
    if (strcasecmp(l->value, r->value) < 0) {
        /*Based on qtest.c line 563 limitation*/
        head = l;
        l = l->next;
    } else {
        head = r;
        r = r->next;
    }
    tmp = head;
    while (l && r) {
        if (strcasecmp(l->value, r->value) < 0) {
            tmp->next = l;
            l = l->next;

        } else {
            tmp->next = r;
            r = r->next;
        }
        tmp = tmp->next;
    }
    if (l)
        tmp->next = l;
    if (r)
        tmp->next = r;
    return head;
}


list_ele_t *mergeSort(list_ele_t *head)
{
    /*Check the ptr*/
    if (!head || !head->next) {
        return head;
    }
    /*Assign two ptr to travesal the queue*/
    list_ele_t *fast = head->next;
    list_ele_t *slow = head;
    /*Use ptr-fast in order to go through the queue
     * and find the cut point of the queue*/
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    /*After the while iteration arrive the cutting point*/
    list_ele_t *mid = slow->next;
    slow->next = NULL;
    list_ele_t *l_merged = mergeSort(head);
    list_ele_t *r_merged = mergeSort(mid);
    return merge(l_merged, r_merged);
}

void q_sort(queue_t *q)
{
    if (!q || !q->head || !q->head->next) {
        return;
    }
    q->head = mergeSort(q->head);
    while (q->tail->next) {
        q->tail = q->tail->next;
    }
}
