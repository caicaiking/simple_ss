#ifndef extcom_def
#define extcom_def

enum
{
    extcom_base = 0x3000,
    extcom_customer_data
};

struct customer_data
{
    int speed;
    bool is_on;
    int energe_budget;
};

#endif