//
// Created by ryousuke kaga on 2023/10/03.
//

#ifndef MYALGORITHMS_LIST_H
#define MYALGORITHMS_LIST_H

#include <stdlib.h>
#include <string.h>

typedef struct ListElm_ {
    void* data;
    struct ListElm_* next;
} ListElm;

typedef struct List_ {
    int size;
    int (*match)(const void* key1, const void* key2);
    void (*destroy)(void* data);
    ListElm* head;
    ListElm* tail;
} List;

void list_init(List*, void (*)(void* data));
void list_destroy(List*);
int list_ins_next(List* list, ListElm *element, const void* data);
int list_rem_next(List* list, ListElm* element, void** data);

#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)
#define list_is_tail(list, element) ((element) == (list)->tail ? 1 : 0)
#define list_data(element) ((element)->data)
#define list_next(element) ((element)->next)

#endif //MYALGORITHMS_LIST_H
