#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>

#include "adf4351.h"

#include <whitebox_ioctl.h>
#include "whitebox_test.h"

#define WHITEBOX_DEV "/dev/whitebox"

int test_adf4351_pack_unpack(void *data) {
    adf4351_t adf4351;
    adf4351_load(&adf4351, 0x00180005);
    adf4351_load(&adf4351, 0x00CD01FC);
    adf4351_load(&adf4351, 0x000004B3);
    adf4351_load(&adf4351, 0x00004EC2);
    adf4351_load(&adf4351, 0x00000069);
    adf4351_load(&adf4351, 0x003C8058);

    assert(0x00180005 == adf4351_pack(&adf4351, 5));
    assert(0x00CD01FC == adf4351_pack(&adf4351, 4));
    assert(0x000004B3 == adf4351_pack(&adf4351, 3));
    assert(0x00004EC2 == adf4351_pack(&adf4351, 2));
    assert(0x00000069 == adf4351_pack(&adf4351, 1));
    assert(0x003C8058 == adf4351_pack(&adf4351, 0));

    assert(abs(198e6 - adf4351_actual_frequency(&adf4351, 26e6)) < 1e3);
    return 0;
}

int test_adf4351_compute_frequency(void *data) {
    adf4351_t adf4351;
    adf4351_load(&adf4351, 0x00180005);
    adf4351_load(&adf4351, 0x00CD01FC);
    adf4351_load(&adf4351, 0x000004B3);
    adf4351_load(&adf4351, 0x00004EC2);
    adf4351_load(&adf4351, 0x00000069);
    adf4351_load(&adf4351, 0x003C8058);
    assert(abs(198e6 - adf4351_actual_frequency(&adf4351, 26e6)) < 1e3);
    return 0;
}

int test_adf4351_tune(void *data) {
    adf4351_t adf4351;
    adf4351_pll_enable(&adf4351, 10e6, 4e3, 756e6);
    assert(fabs(756e6 - adf4351_actual_frequency(&adf4351, 10e6)) < 1e3);
    return 0;
}

int test_adf4351_responds(void *data) {
    int fd;
    whitebox_args_t w;
    adf4351_t adf4351;
    fd = open(WHITEBOX_DEV, O_WRONLY);
    assert(fd > 0);
    adf4351_ioctl_get(&adf4351, &w);
    adf4351.ld_pin_mode = LD_PIN_MODE_LOW;
    adf4351_ioctl_set(&adf4351, &w);
    ioctl(fd, WA_SET, &w);
    assert(!ioctl(fd, WA_LOCKED));

    adf4351.ld_pin_mode = LD_PIN_MODE_HIGH;
    adf4351_ioctl_set(&adf4351, &w);
    ioctl(fd, WA_SET, &w);
    assert(ioctl(fd, WA_LOCKED));

    adf4351.ld_pin_mode = LD_PIN_MODE_DLD;
    adf4351_ioctl_set(&adf4351, &w);
    ioctl(fd, WA_SET, &w);
    close(fd);
}

int main(int argc, char **argv) {
    whitebox_test_t tests[] = {
        WHITEBOX_TEST(test_adf4351_pack_unpack),
        WHITEBOX_TEST(test_adf4351_compute_frequency),
        WHITEBOX_TEST(test_adf4351_tune),
        WHITEBOX_TEST(test_adf4351_responds),
        WHITEBOX_TEST(0),
    };
    return whitebox_test_main(tests, NULL, argc, argv);
}
