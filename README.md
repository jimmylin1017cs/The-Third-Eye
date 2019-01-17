# the-third-eye

## File List

- SORT
  - sort.h
  - sort.cpp
      - call `sort.py` function `def update(self, dets):`
  - [sort.py](https://github.com/abewley/sort/blob/master/sort.py)
  - sort.pyc
- IoT Talk
  - DAI_push.h
  - DAI_push.cpp
      - edit from [DAI.py](https://github.com/IoTtalk/Dummy_Device_IoTtalk_v1_py/blob/master/DAI.py)
  - [csmapi.py](https://github.com/IoTtalk/Dummy_Device_IoTtalk_v1_py/blob/master/csmapi.py)
  - DAI_push.py
  - [DAN.py](https://github.com/IoTtalk/Dummy_Device_IoTtalk_v1_py/blob/master/DAN.py)
  - DAN.pyc
- Fusion
  - fusion.h
  - fusion.c

## Edit

### New

...

### Old

- Add `draw_detections_sort()` in `image.c` and `image.h`
- Add `intHandler()` in `demo.c`
- Call `signal()` and `sortInitialization()` in `demo()` in `demo.c`
- Call `sortUpdate()` and `draw_detections_sort()` in `detect_in_thread()` in `demo.c`

## Reference

### Darknet

use darknet_v2 (old version)

![Darknet Logo](http://pjreddie.com/media/files/darknet-black-small.png)

Darknet is an open source neural network framework written in C and CUDA. It is fast, easy to install, and supports CPU and GPU computation.

For more information see the [Darknet project website](http://pjreddie.com/darknet).

For questions or issues please use the [Google Group](https://groups.google.com/forum/#!forum/darknet).

### Simple Online and Realtime Tracking (SORT)

[abewley/sort](https://github.com/abewley/sort)

#### License

SORT is released under the GPL License (refer to the LICENSE file for details) to promote the open use of the tracker and future improvements. If you require a permissive license contact Alex ([alex@bewley.ai](alex@bewley.ai)).

### IoT Talk

[IoTtalk/Dummy_Device_IoTtalk_v1_py](https://github.com/IoTtalk/Dummy_Device_IoTtalk_v1_py)
