#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>
#include <string.h>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include "shem_shared_data.hpp"

using namespace boost::interprocess;

void Function1() {
    std::cout << "this is func1" << std::endl;
}

void Function2() {
    std::cout << "this is func2" << std::endl;
}

int main (){
    shared_memory_object shm(open_only, "shared_memory",read_write);
    mapped_region region(shm,read_write);
    void *addr = region.get_address();
    shared_memory_buffer *data = static_cast<shared_memory_buffer*>(addr);

    while(true) {
        // wait until a number gets available
        std::cout << "before wait" << std::endl;
        data->reader.wait();
        std::cout << "after wait" << std::endl;

        if (data->value == 1)
            Function1();
        else if (data->value == 2)
            Function2();
        //signal to writer
        data->writer.post();
    }
    return 0;
}

