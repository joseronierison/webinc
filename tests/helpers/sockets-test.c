/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "sockets-test.check" instead.
 */

#include <check.h>

#line 1 "sockets-test.check"
#include "../../src/helpers/sockets.h"

START_TEST(sum2test)
{
#line 4
    fail_unless(sum_ab(3, 2) == 5, "sum_ab function borked");
}
END_TEST

