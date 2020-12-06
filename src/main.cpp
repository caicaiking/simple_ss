#include "abama_ss.hpp"
#include "extcom.h"
#include <iostream>
int main(int argc, char **argv) {

  init();
  abama_ss::core::abama_core::get_instance().emit(extcom_customer_data);
}
