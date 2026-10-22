#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "mp3_tools.h"
#include "utils.h"

const int brs[] = {0, 320, 400, 480, 560, 640, 800, 960, 1120, 1280, 1600, 1920, 2240, 2560, 3200, 0};
const int srs[] = {441, 480, 320, 0};

const unsigned char slen1[] = {0,0,0,0,3,1,1,1,2,2,2,3,3,3,4,4};
const unsigned char slen2[] = {0,1,2,3,0,1,2,3,1,2,3,1,2,3,2,3};

//Use unsigned
unsigned find_frameLen(unsigned char *data) { // maybe refactor to use usigned int
    if(!data) return 0;

    //Bitrate, samplerate, & padding ready to use
    int br = brs[get_bits(&data[0], 16, 4)];
    int sr = srs[get_bits(&data[0], 20, 2)]; 
    int p = get_bits(&data[0], 22, 1);

    //Null Check
    if((br == 0) || (sr == 0)) return 0;

    //Final calculation
    return (144*br)/sr+p;
}

/*
struct SideInfo *parse_sideInfo(unsigned char *data) {
    if(!data) return NULL;

    //Instantiate Side Info
    struct SideInfo *info = malloc(sizeof(struct SideInfo));

    //Shortcut for get_bits
    unsigned char *d = &data[0];
    
    //Extracting info
    info->main_data = get_bits(d, 0, 9);
    info->scfsi = get_bits(d, 12, 8);
    //unsigned char sf0 = get_bits(d, 12, 4);
    //unsigned char sf1 = get_bits(d, 16, 4);
    //unsigned short p23 = get_bits(d, 20, 12);
    //unsigned short bv = get_bits(d, 32, 9);
    //unsigned char gg = get_bits(d, 41, 8);
    //unsigned char sfc = get_bits(d, 49, 4);
    //unsigned char ws = get_bits(d, 53, 1);

    return info;
}

*/

//Need to add joint 
struct Frame *create_frame(unsigned char *data, int index) {
    if(!data) return NULL;

    //Instantiate frame
    struct Frame *frame = malloc(sizeof(struct Frame));

    //Get header
    frame->header = get_bits(&data[index], 0, 32);
    if(frame->header >> 16 != 0xFFFB) return NULL;     //Checks to see if Frame Header starts with 0xFFFB

    //Find frame length & Validate
    frame->frame_size = find_frameLen(&data[index]);
    if(frame->frame_size <= 0) return NULL;

    //Gets the size of main data;
    

    //Get Main;
    unsigned short main_begins = index-get_bits(&data[index+4], 0, 9);


    //Parse Side information
    //
    //unsigned char scfsi = get_bits(&data[index+4], 12, 8);

    //Set frame next;
    frame->next = NULL;

    return frame;
}