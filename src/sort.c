#include "utils.h"
#include "sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define PERSON_ONLY 1
#define MAX_SORT_NUM 500

static float **last_probs;
static box *last_boxes;
static int *last_sort_ids;
static int last_sort_ct = 0;

void sortInitialization(int num, int class_num, int sort_freq){
    int j;
    //Py_SetPythonHome("/usr/bin/python");
	Py_Initialize();
    // return String Object with "sort", use for import module named "sort.py"
    pName = PyString_FromString("sort"); //.py name
    // import Python Module
    pModule = PyImport_Import(pName);
    if (!pModule) {
        PyErr_Print();
        exit(1);
    }

    // get the Dictionary Object which have { function name : function object }
	pDict = PyModule_GetDict(pModule);
    // get the Class Sort(object) from Dictionary Object
	pClass = PyDict_GetItemString(pDict, "Sort"); // class name

	// Create an instance of the class
    // check whether the Class Sort can be called
    if (PyCallable_Check(pClass)){
        // create the Class Sort and call the "__init__" function
        // we can use Class Sort function by using pInstance
        // like PyObject_CallMethod(pInstance, "update", "O", dets);
		pInstance = PyObject_CallObject(pClass, NULL);     
    }
}

int sortUpdate(image im, box* detections, float** probs, int num, int classes, float thresh, int *sort_ids, int sort_freq, int filter_small_scale){

	// return the List Object with length 0
    PyObject *dets = PyList_New(0);
    float has_prob[num];
	int dets_ct = 0;
	int i, j;
	for(i = 0; i < num; ++i){
		int klass = max_index(probs[i], classes);
        if (PERSON_ONLY && klass!=0) continue;
        float prob = probs[i][klass];
        if (prob<=thresh) continue;
        probs[i][klass] = 0.0;
        has_prob[dets_ct] = prob;
        dets_ct++;
        box b = detections[i];
        float left  = (b.x-b.w/2.)*im.w;
        float right = (b.x+b.w/2.)*im.w;
        float top   = (b.y-b.h/2.)*im.h;
        float bot   = (b.y+b.h/2.)*im.h;
        if(left < 0) left = 0;
        if(right > im.w-1) right = im.w-1;
        if(top < 0) top = 0;
        if(bot > im.h-1) bot = im.h-1;
        if(filter_small_scale!=0 && ((right-left)<im.h/filter_small_scale || (bot-top)<im.h/filter_small_scale))
            continue;

        // store left, top, right, bot, prob
        PyObject *det = PyList_New(5);
        
        PyList_SetItem(det, 0, PyFloat_FromDouble(left));
        PyList_SetItem(det, 1, PyFloat_FromDouble(top));
        PyList_SetItem(det, 2, PyFloat_FromDouble(right));
        PyList_SetItem(det, 3, PyFloat_FromDouble(bot));
        PyList_SetItem(det, 4, PyFloat_FromDouble(prob));
        
        // append det to dets end
        // return 0 if successful, -1 if unsuccessful
        int iRetn = PyList_Append(dets, det);
      	if (iRetn == -1) {
      		printf("ERROR: failed to append into dets.\n");
      		Py_RETURN_FALSE;
      	}
        
        // use "tp_dealloc" free det
      	Py_DECREF(det);
	}

    // not find any person
    if (dets_ct==0)
    {
        Py_DECREF(dets);
        return 0;
    }

    // call the Class Sort function "update(self, dets)" with argument dets
    // return 
    PyObject *tracker = PyObject_CallMethod(pInstance, "update", "O", dets);
    int tracker_len = (int)PyList_Size(tracker);
    box sort_boxes[num];

    // recreate the boxes (detections) and probs, only contain person information
	for (i = 0; i < tracker_len; i++)
    {
        PyObject * sort_box;

        // return index i object
        sort_box = PyList_GetItem(tracker, i);
        const int x = (int)PyFloat_AsDouble(PyList_GetItem(sort_box, 0));
        const int y = (int)PyFloat_AsDouble(PyList_GetItem(sort_box, 1));
        const int w = (int)PyFloat_AsDouble(PyList_GetItem(sort_box, 2))-x;
        const int h = (int)PyFloat_AsDouble(PyList_GetItem(sort_box, 3))-y;
        detections[i].x = x;
        detections[i].y = y;
        detections[i].w = w;
        detections[i].h = h;
        
        // UNDO: deal with class and prob, now only person!!!!!!!!!!!!!!

        // get the track id
        sort_ids[i] = (int)(PyFloat_AsDouble(PyList_GetItem(sort_box, 4))) % MAX_SORT_NUM;

        // can use 0 directory, because 0 is person
        // restore prob from copy above "float prob = probs[i][klass]; has_prob[dets_ct] = prob;"
        if (i<dets_ct) probs[i][0] = has_prob[i];
        else probs[i][0] = 1.0;
   	}
    
    Py_DECREF(tracker);    
   	Py_DECREF(dets);
    return tracker_len;
    //return sort_boxes;
}

void sort_cleanUp(int sort_freq){
	Py_DECREF(pModule);
    Py_DECREF(pName);
    Py_Finalize();
    if (sort_freq!=1){
        free(last_boxes);
        free(last_probs);
        free(last_sort_ids);
    }
}
