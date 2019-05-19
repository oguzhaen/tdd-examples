/**
 * @file Test-LinkedList.cpp
 * @author Oguzhan Mutlu (oguzhan-mutlu@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <CppUTest/TestHarness.h>
#include "string.h"

#define LINKEDLIST_FAIL     (-1)
#define LINKEDLIST_SUCCESS  (0)

/*Bu satır çok önemli CPP dosyasına C entegre etmek isteğimiz zaman bunu koymazsak link error alıyoruz*/
extern "C" {
//    #include "strncmp.h"
    #include <linkedlist.h>
}

TEST_GROUP(LinkedTest) {
    linked_list_t *list = NULL;
    void setup() {
        // Setup ...
        
        list = linked_list_create(5);
        CHECK(NULL != list);
    }

    void teardown() {
        // Teardown ...
        linked_list_destroy(list);
    }

};

#define EXAMPLE2_LINKEDLIST

#ifdef EXAMPLE2_LINKEDLIST

/*  TEST LIST EXAMPLE2_LINKEDLIST
*   1- islistcreatedproperly +
*   2- insertlistitem 
*   3- deletelistitem
*   4- getlistitem +
*   5- insertbetween2items
*   6- islastitemconnectionsnull
*   7- destroylist
*   8- boundaryvalues
*/

TEST(LinkedTest, delete_item)
{
    list->delete_item(list, 20);
}

TEST(LinkedTest, insert_item)
{
    int current_count=4;
    current_count = list->add_item(list, current_count);
}

TEST(LinkedTest, boundary_values)
{
    int ret;
    ret = list->add_item(list, -1);
    CHECK(ret == LINKEDLIST_FAIL);
    list->delete_item(list, 20);
}

TEST(LinkedTest, set_get_data)
{
    int data_ff = 356666;
    int data_size_ff = sizeof(int);
    linked_list_data_t data;
    linked_list_data_t *cm_data;
    int *cmp; 

    data.data = &data_ff;
    data.data_size = data_size_ff;

    list->set_data(list, 3, &data);
    cm_data = list->get_data(list, 3);
    
    cmp = (int *) cm_data->data;
    CHECK_EQUAL(data_ff, (int) *cmp);
    CHECK_EQUAL(data_size_ff, cm_data->data_size);
}

#endif