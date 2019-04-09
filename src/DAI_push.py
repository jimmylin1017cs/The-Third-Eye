import time, DAN, requests, random
import json
import numpy as np
import cv2
import base64
from ast import literal_eval

#from requests.utils import requote_uri


#ServerURL = 'http://IP:9999' #with no secure connection
#ServerURL = 'https://DomainName' #with SSL connection
ServerURL = 'http://140.113.86.143:9999'
Reg_addr = None #if None, Reg_addr = MAC address

DAN.profile['dm_name']='MODEL_BOX'
DAN.profile['df_list']=['IDF_BOX']
DAN.profile['d_name']= None # None for autoNaming
DAN.device_registration_with_retry(ServerURL, Reg_addr)

#cv2.setUseOptimized(True)

#cap = cv2.VideoCapture('time_counter.flv')

def send_boxes_to_iottalk(boxes):

    #print(type(buf))
    #array = buf.tolist()
    #print(len(buf))
    boxes_information = json.dumps(boxes)
    print(boxes_information)
    #print(data)
    #print(len(data))

    try:
        # @0: json
        DAN.push('IDF_BOX', boxes_information)
        print('push')
    except Exception as e:
        print(e)
        if str(e).find('mac_addr not found:') != -1:
            print('Reg_addr is not found. Try to re-register...')
            DAN.device_registration_with_retry(ServerURL, Reg_addr)
        else:
            print('Connection failed due to unknow reasons.')
            #time.sleep(1)
    #time.sleep(0.2)
