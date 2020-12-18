#include "extcom.h"
#include "abama_ss.hpp"
#include "extcom_def.h"
#include <iostream>

static customer_data data;

void init()
{
    abama_ss::core::abama_core::get_instance().bind_tag_to_data(
        extcom_customer_data, &data);
    abama_ss::core::abama_core::get_instance().connect(extcom_customer_data,
                                                       process_data_changed);
}

void process_data_changed(const customer_data *data)
{
    std::cout << "I was called\n";
}
