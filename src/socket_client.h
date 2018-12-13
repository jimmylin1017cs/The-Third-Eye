#include "socket_header.h"

extern "C" {
#include "image.h"
}

#include <iostream>
#include <vector>

#define PERSON_MAX_NUM 3

void image_to_json(image im, int port);

void json_to_image(const char * json_str);

//image json_to_image(const char * json_str);

int send_message(std::string ip, int port, int quality);

int send_frame(std::string ip, int port, int quality, std::vector<unsigned char> frame);
int send_frame(std::string ip, int port, int quality, image im);
int send_frame(std::string ip, int port, int quality, image im, int frame_stamp);