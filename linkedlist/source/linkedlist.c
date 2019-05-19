/**
 * @file linkedlist.c
 * @author Oguzhan Mutlu (oguzhan-mutlu@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "linkedlist.h"
#include "stdlib.h"
#include "string.h"

/*OS Abstraction Layer*/
#define malloc_interface(size) malloc(size)
#define calloc_interface(count,size) calloc(count,size)
#define free_interface(point32_ter) free(point32_ter)

/*TODO : Refactor*/

struct linked_list_item
{
    int32_t queue_number;
    linked_list_data_t data;
    linked_list_item_t *next;
    linked_list_item_t *before;
};

/*Private Function Prototypes*/
static void linked_list_delete_item(linked_list_t *list, int32_t item_id);
static int32_t linked_list_add_item(linked_list_t *list, int32_t before_item_id);
static linked_list_data_t* linked_list_get_data(linked_list_t *list, int32_t item_id);
static void linked_list_set_data(linked_list_t *list, int32_t item_id, 
                                linked_list_data_t *data);

/*Public Functions*/
/**
 * @brief linked_list_create
 * 
 * @param item_count 
 * @return linked_list_t* 
 */
linked_list_t *linked_list_create(int32_t item_count)
{
    linked_list_t *list;
    linked_list_item_t *head, *temp, *first;
    list = calloc_interface(1, sizeof(linked_list_t));

    /*Giriş koruması*/
    if(0 > item_count)
    {
        return NULL;
    }

    for(int32_t i = 0; i < item_count; i++)
    {
        if(0 == i)
        {
            temp = malloc_interface(sizeof(linked_list_item_t));
            temp->queue_number = i;
            temp->data.data = NULL;
            first = head = temp;
        }
        else
        {
            temp = head;
            temp->next = malloc_interface(sizeof(linked_list_item_t));
            head = temp->next;
            head->queue_number = i;
            head->data.data = NULL;
            head->before = temp;
        } 
    }

    head->next = NULL;
    list->item_count = item_count;
    list->list_last = head;
    list->list_first = first;

    list->add_item = linked_list_add_item;
    list->delete_item = linked_list_delete_item;
    list->set_data = linked_list_set_data;
    list->get_data = linked_list_get_data;

    return list;
}

/**
 * @brief linked_list_destroy
 * 
 * @param list 
 */
void linked_list_destroy(linked_list_t *list)
{
    linked_list_item_t *temp;
    for(int32_t i = 0; i < list->item_count; i++)
    {     
        temp = list->list_first->next;   
        free_interface(list->list_first);      
        list->list_first = temp;    
    }
    free_interface(list);
    list = NULL;
}

/*Private Functions*/
/**
 * @brief 
 * 
 * @param list 
 * @param item_id 
 * @return linked_list_item_t* 
 */
static linked_list_item_t* find_item_by_id(linked_list_t *list, int32_t item_id)
{
    linked_list_item_t *ret;
    linked_list_item_t *temp = list->list_first;
    for(int32_t i = 0; i < list->item_count ; i++)
    {
        if(item_id == temp->queue_number)
        {
            ret = temp;
            break;
        }
        else
        {
            temp = temp->next;
            if(NULL == temp->next)
            {
                ret = NULL;
            }
        }
    }
    return ret;
}

/**
 * @brief 
 * 
 * @param list 
 * @param list_item 
 * @param direction 
 */
static void shift_ids(linked_list_t *list, linked_list_item_t *list_item, 
                                                        int32_t direction)
{
    linked_list_item_t *temp = list_item;
    for(uint32_t i = list_item->queue_number; i < list->item_count; i++)
    {
        if(1 == direction)
        {//İleri kaydır
            temp = list_item->next;
            temp->queue_number++;
            list_item = temp;
        }
        if(0 == direction)
        {//Geri kaydır
            temp->queue_number--;
            list_item = temp;
        }
    }
}

/**
 * @brief 
 * 
 * @param value 
 * @param boundary_1 
 * @param boundary_2 
 * @return int32_t 
 */
static inline int32_t input_protection(int value, int boundary_1, int boundary_2)
{
    /*Giriş Koruması*/
    if((boundary_1 > value) || (boundary_2 < value))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 
 * 
 * @param list 
 * @param item_id 
 */
static void linked_list_delete_item(linked_list_t *list, int32_t item_id)
{
    linked_list_item_t *before_item, *next_item, *temp;

    /*Giriş Koruması*/
    if(input_protection(item_id, 0, list->item_count))
    {
        return;
    }

    temp = find_item_by_id(list, item_id);
    before_item = temp->before;
    next_item = temp->next;
    free_interface(temp);

    if(temp == list->list_first)
    {//Baştan silme
        list->list_first = next_item;
        list->list_first->before = NULL;
    }
    else if(temp == list->list_last)
    {//Sondan silme
        list->list_last = before_item;
        list->list_last->next = NULL;
    }
    else
    {//Aradan silme
        before_item->next = next_item;
        next_item->before = before_item;
    }
    shift_ids(list, next_item, 0);
    list->item_count--;
}

/*before_item NULL ise en başa eklenecek, before_item list->list_last ise 
en sona eklenecek*/
/**
 * @brief 
 * 
 * @param list 
 * @param before_item_id 
 * @return int32_t 
 */
static int32_t linked_list_add_item(linked_list_t *list, int32_t before_item_id)
{
    linked_list_item_t *new_item;
    linked_list_item_t *before_item;
    
    /*Giriş Koruması*/
    if(input_protection(before_item_id, 0, list->item_count))
    {
        return -1;
    }

    new_item = malloc_interface(sizeof(linked_list_item_t));
    new_item->queue_number = before_item_id + 1;
    before_item = find_item_by_id(list, before_item_id);

    if(NULL == before_item)
    {//Başa ekleme
        /*NOT: Setfirst fonksiyonu olacak*/
        list->list_first->before = new_item;
        new_item->next = list->list_first;
        new_item->before = NULL;
        list->list_first = new_item; 
    }
    else if (list->list_last == before_item)
    {//Sona ekleme
        /*NOT: Setlast fonksiyonu olacak*/
        new_item->before = list->list_last;
        list->list_last->next = new_item;
        list->list_last = new_item;
        new_item->next = NULL;
    }
    else
    {//Ortaya ekleme
        /*Set N. fonksiyonu olacak*/
        before_item->next->before = new_item;
        new_item->next = before_item->next;
        before_item->next = new_item;
        new_item->before = before_item;
    }
    shift_ids(list, new_item, 1);
    list->item_count++;

    return new_item->queue_number;
}

/**
 * @brief 
 * 
 * @param list 
 * @param item_id 
 * @return linked_list_data_t* 
 */
static linked_list_data_t* linked_list_get_data(linked_list_t *list, 
                                                int32_t item_id)
{
    linked_list_item_t *item;

    /*Giriş Koruması*/
    if(input_protection(item_id, 0, list->item_count))
    {
        return NULL;
    }

    item = find_item_by_id(list, item_id);
    return &item->data;
}

/**
 * @brief 
 * 
 * @param list 
 * @param item_id 
 * @param data 
 */
static void linked_list_set_data(linked_list_t *list, int32_t item_id, 
                                linked_list_data_t *data)
{
    linked_list_item_t *item;

    /*Giriş Koruması*/
    if(input_protection(item_id, 0, list->item_count))
    {
        return;
    }

    item = find_item_by_id(list, item_id);
    item->data.data = data->data;
    item->data.data_size = data->data_size;
}

