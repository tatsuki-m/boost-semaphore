#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <iostream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shem_shared_data.hpp"

using namespace boost::interprocess;

int main() {
    struct shm_remove

    srand(time(NULL));

    //use old shared memory if exists else create a new one
    shared_memory_object shm(open_or_create, "shared_memory", read_write);

    //set the size of the memory object
    shm.truncate(sizeof(shared_memory_buffer));

    //map the whole shared memory in this process
     mapped_region region(shm,read_write);

    //get the region address
    void *addr = region.get_address();

    //create a shrad memory buffer in memory
    shared_memory_buffer *data = new (addr) shared_memory_buffer;

    while (true) {
        //wait until the written number gets exucutes
        data->writer.wait();
          std::cout << data->value << std::endl;
          ++data->value;
          std::cout << data->value << std::endl;
        sleep(1);

        if (data->value >= 5) {
          break;
        };

        data->reader.post();
    }
    std::cout << "delete hoge" << std::endl;
    delete data->hoge;
    shared_memory_object::remove("shared_memory");
    std::cout << "hoge deleted" << std::endl;
    return 0;
}

