/**
 * @file linkedlist.h
 * @author Oguzhan Mutlu (oguzhan-mutlu@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "stdint.h"

/*Private struct*/
typedef struct linked_list_item linked_list_item_t;

/*Public structures*/
typedef struct linked_list linked_list_t;
typedef struct linked_list_data linked_list_data_t;

struct linked_list_data
{
    void *data;
    int32_t data_size;
};
struct linked_list
{
    /*Public variables*/
    int32_t item_count;
    /*Public member functions*/
    int32_t (*add_item)(linked_list_t *list, int32_t before_item_id);
    void (*delete_item)(linked_list_t *list, int32_t item_id);
    linked_list_data_t* (*get_data)(linked_list_t *list, int32_t item_id);
    void (*set_data)(linked_list_t *list, int32_t item_id, 
                    linked_list_data_t *data);
    /*Private variables*/
    linked_list_item_t *list_first;
    linked_list_item_t *list_last;

};

/*Constructor and destructor*/
linked_list_t *linked_list_create(int32_t item_count);
void linked_list_destroy(linked_list_t *list);


#endif /*LINKEDLIST_H*/