#ifndef DAI_PUSH
#define DAI_PUSH

#include <Python.h>
#include <iostream>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

#include "image.h"

static PyObject *pModule, *pDict, *pFunc, *pInstance;

void iot_talk(image im, person_box *person_boxes, int person_amount);
void iot_init();
void iot_send(std::vector<unsigned char> &outbuf, std::vector<person_box> &boxes);

#ifdef __cplusplus
}
#endif

#endif

