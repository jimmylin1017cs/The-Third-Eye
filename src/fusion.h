#ifndef FUSION_H
#define FUSION_H
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <math.h>
#include "box.h"
#include "utils.h"

#define PI_PATH_NUM 3
#define VI_PATH_NUM 500
#define MAX_DATA_PATH_NUM 3000


typedef struct  {
	double x;
	double y;
}Data;

typedef struct  {
	int num;
	char name[200];
}Fusion_result;

typedef struct  {
	int num; 
	double x;
	double y;
}Video_data;

int fusion(Video_data *all_vi_data, Fusion_result *match_result, int *match_result_size, int all_vi_data_size, char fusion_name_result[][30]);

#endif
