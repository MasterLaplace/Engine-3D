#include "engine.h"
#include "../include/test.h"

engine_t engine;

SET_NB_TEST(1)

void test_swap(void) {
    int a = 4, b = 5;
    float x = 4.0f, y = 5.0f;

    SWAP(a, b); // swap two ints, a and b
    SWAP(x, y); // swap two floats, x and y

    ASSERT_TRUE((a==5) && (b==4) && (x==5.0f) && (y==4.0f))
}

int main(void)
{
    START_TEST

    TEST(pid, test_swap)

    END_TEST
}
