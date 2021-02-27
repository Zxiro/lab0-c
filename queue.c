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
    list_ele_t *pre = q->head;
    while (pre != NULL) { /*Check whether the quene become NULL*/
        list_ele_t *fr = pre;
        pre = pre->next; /*point to the next node to be freed*/
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
    char *news;
    newh = malloc(sizeof(newh));
    news = malloc(sizeof(news));
    if (!q || !newh || !news) {
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    memcpy(news, s, strlen(s) + 1);
    /*Copy the value of s from the addr of s to news*/
    newh->value = news;
    if (q->tail == NULL) {
        newh->next = q->head;
        q->tail = newh;
    }
    if (q->tail != NULL) {
        newh->next = q->head;
    }
    q->head = newh;
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
    list_ele_t *newt;
    char *news;
    newt = malloc(sizeof(newt));
    news = malloc(sizeof(news));
    if (!q || !newt || !news) {
        return false;
    }
    /* Remember: It should operate in O(1) time */
    memcpy(news, s, strlen(s) + 1);
    /*Copy the value of s from the addr of s to news*/
    newt->value = news;
    if (q->tail == NULL) {
        q->head = newt;
    }
    if (q->tail != NULL) {
        q->tail->next = newt;
    }
    q->tail = newt;
    newt->next = NULL;
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
    if (!q || !q->head) {
        return false;
    }
    list_ele_t *frptr = q->head; /*Assign an node to be removed*/
    if (sp) {                    /*If the value != NULL*/
        memcpy(sp, frptr->value, bufsize);
        sp[bufsize - 1] = '\0';
    }
    q->size -= 1;
    q->head = q->head->next;
    free(frptr);
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
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
