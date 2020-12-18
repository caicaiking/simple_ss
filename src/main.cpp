#include "abama_ss.hpp"
#include "extcom.h"
#include <iostream>
#include "task_slot.hpp"

int main(int argc, char **argv)
{

    init();
    abama_ss::core::abama_core::get_instance().emit(1, extcom_customer_data);
    abama_ss::core::abama_core::get_instance().run(1);
    abama_ss::core::abama_core::get_instance().run(1);
    std::cout << "ends " << std::endl;
}
