#include "simple_ss.hpp"
#include "extcom.h"
#include <iostream>
#include "task_slot.hpp"

int main(int argc, char **argv)
{

    init();
    simple_ss::core::task_manager::get_instance().emit(1, extcom_customer_data);
    simple_ss::core::task_manager::get_instance().run(1);
    simple_ss::core::task_manager::get_instance().run(1);
    std::cout << "ends " << std::endl;
}
