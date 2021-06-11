

#include "test.h"

#define TEST_UNIT_MAX         100000

int main(int argc, char const *argv[])
{
    cout<<"test proccess is ready, start test>>>\n";

    for(int i = 0; i < TEST_UNIT_MAX; ++i) {
        const TEST_RUN_FUNC& test_func = test_func_unit_array[i];
        if (!test_func) {
            //遇到NULL结束标志
            break;
        }
        
        test_func();
    }

    cout<<"test is over, press [Enter] to finish.\n";
    getchar();
    return 0;
}
