#ifndef MP3_TOOLS_H
#define MP3_TOOLS_H

//Sample & Bit rates
extern const int brs[];
extern const int srs[];

//Granule-Channel block
//Repeated for following blocks
// Granule / Channel
//0/0, 0/1, 1/0, 1/1
struct BlockInfo {
    //35 bits baseline
    unsigned short part2_3_length;      //12 bits, Exact # of bits taken up by scale factors(2) & huffman data(3)
    unsigned short big_values;          //9 bits, # of fc pairs using large value huffman tables
    unsigned char global_gain;          //8 bits, global quantization size
    unsigned char scalefac_compress;    //4 bits, Controls how scale factors are packed
    unsigned char window_sw_flg;        //1 bit, Determines if short (1) or long (0) windows are used

    //Long window
    unsigned short table_sel_long;      //15 bits, (3 * 5) 3 5-bit values determining huffman codebooks for regions 0, 1, 2
    unsigned char reg0_count;           //4 bits, boundry size of region 0
    unsigned char reg1_count;           //3 bits, boundry size of region 1

    //short window
    unsigned char block_type;           //2 bits, window transition
    unsigned char mixed_bflag;          //1 bit, says if long windows used for higher frequency
    unsigned short table_sel_short;     //10 bits, (2 * 5) Same as table sel long
    unsigned short subblock_gain;       //9 bits,  (3 * 3)

    //End field
    unsigned char end_field;            //3 bits
    //Preflag
    //scalefac_scale
    //count1table_select
};

//Side Information struct
struct SideInformation {
    unsigned short main_data;       //9 bits, start of main data
    unsigned char private;          //3 bits, not useful
    unsigned char scfsi;            //8 bits (4 ch0 / 4 ch1), Scale factor bands

    //2 granules x 2 channels = 4 granule-channel blocks
    struct BlockInfo block_00;
    struct BlockInfo block_01;
    struct BlockInfo block_10;
    struct BlockInfo block_11;
} ;

//Frame Linked List 
//Needs CRC, MODE, & Emphasis check
struct Frame{
    unsigned header_data;                   //Actual information of the Header
    unsigned frame_size;                    //Size of the frame calculated from header info
    struct SideInformation side_info;       //Side information          
    unsigned char *main_data;               //Pointer to start of the main_data of frame
    struct frame* next;                     //Points to next frame
};

//Calculates the Frame Length of the frame
//Returns 0 if the frame is invalid
unsigned find_frameLen(unsigned char *data, int index);

//Testing for side information
void side_test(unsigned char *data);

//Frame Instantiation
struct Frame create_frame();




#endif