#ifndef DAI_PUSH
#define DAI_PUSH

#include <Python.h>
#include <iostream>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

#include "sort.h"
#include "image.h"

void iot_init();
void iot_talk_send(std::vector<person_sort_det> &person_sort_dets, int &frame_stamp);

#ifdef __cplusplus
}
#endif

#endif

