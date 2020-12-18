#include "extcom.h"
#include "simple_ss.hpp"
#include "extcom_def.h"
#include <iostream>

static customer_data data;

void init()
{
    simple_ss::core::task_manager::get_instance().bind_tag_to_data(
        extcom_customer_data, &data);
    simple_ss::core::task_manager::get_instance().connect(extcom_customer_data,
                                                          process_data_changed);
}

void process_data_changed(const customer_data *data)
{
    std::cout << "I was called\n";
}
