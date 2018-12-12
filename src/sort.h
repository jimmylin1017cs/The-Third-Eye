#ifndef SORT_H
#define SORT_H

#include <Python.h>

#include "box.h"
#include "utils.h"
#include "blas.h"
#include "cuda.h"
#include "image.h"
#include <stdio.h>
#include <math.h>


PyObject *pName, *pModule, *pDict, *pClass, *pInstance;
void sortInitialization(int num, int class_num, int sort_freq);
int sortUpdate(image im, box* detections, float** probs, int num, int classes, float thresh, int *sort_ids, int sort_freq, int filter_small_scale);
void sort_cleanUp(int sort_freq);

#endif