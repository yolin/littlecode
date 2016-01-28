#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/sysinfo.h>
//#include "knlintf.h"
#include <string.h>
#include "admin_list.h"

void admin_list_init_node(struct admin_cfg_list *arg, int id, char* command)
{
    memset(arg, 0, sizeof(struct admin_cfg_list));
    arg->id = id;
    if(command)
        strcpy(arg->command, command);
    else
        strcpy(arg->command, "test");
}

struct admin_cfg_list * admin_list_find(int id, struct list_head *head)
{
    struct list_head *iter;
    static struct admin_cfg_list *objPtr;

    __list_for_each(iter, head) {
        objPtr = list_entry(iter, struct admin_cfg_list, list_member);
        if(objPtr->id == id) {
            return objPtr;
        }
    }
    return 0;
}

void admin_list_add_node(struct admin_cfg_list *arg, struct list_head *head)
{

    struct admin_cfg_list *fooPtr = (struct admin_cfg_list *)malloc(sizeof(struct admin_cfg_list));
    assert(fooPtr != NULL);
    memcpy(fooPtr, arg, sizeof(struct admin_cfg_list));
    INIT_LIST_HEAD(&fooPtr->list_member);
    list_add(&fooPtr->list_member, head);
}

int admin_list_delete(char *command, struct list_head *head)
{
    struct list_head *iter;
    struct admin_cfg_list *objPtr;

    __list_for_each(iter, head) {
        objPtr = list_entry(iter, struct admin_cfg_list, list_member);
        if(strncmp(objPtr->command, command, strlen(command))) {
            list_del(&objPtr->list_member);
            free(objPtr);
            return 1;
        }
    }

    return 0;
}

void admin_list_delete_all(struct list_head *head)
{
    struct list_head *iter;
    struct admin_cfg_list *objPtr;

redo:
    __list_for_each(iter, head) {
        objPtr = list_entry(iter, struct admin_cfg_list, list_member);
        list_del(&objPtr->list_member);
        free(objPtr);
        goto redo;
    }
}

void admin_list_display(struct list_head *head)
{
    struct list_head *iter;
    struct admin_cfg_list *objPtr;

    __list_for_each(iter, head) {
        objPtr = list_entry(iter, struct admin_cfg_list, list_member);
        printf("\nid:%d\t", objPtr->id);
        printf("command:%s\n", objPtr->command);
    }
}


