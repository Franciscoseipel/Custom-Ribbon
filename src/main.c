#include <pebble.h>

#define KEY_BACKGROUND_COLOR 0
#define KEY_h1nocolorband 1
#define KEY_h1_dir 2
#define KEY_h1numberColor 3
#define KEY_h1bandColor 4
#define KEY_h1x 5
#define KEY_h1y 6
#define KEY_h1duration 7
#define KEY_h1delay 8
#define KEY_h1outline 9
#define KEY_h1line 10
#define KEY_h1linesColor 11


#define KEY_h2trans 12
#define KEY_h2_dir 13
#define KEY_h2numberColor 14
#define KEY_h2bandColor 15
#define KEY_h2x 16
#define KEY_h2y 17
#define KEY_h2duration 18
#define KEY_h2delay 19
#define KEY_h2outline 20
#define KEY_h2line 21
#define KEY_h2linesColor 22



#define KEY_m1trans 23
#define KEY_m1_dir 24
#define KEY_m1numberColor 25
#define KEY_m1bandColor 26
#define KEY_m1x 27
#define KEY_m1y 28
#define KEY_m1duration 29
#define KEY_m1delay 30
#define KEY_m1outline 31
#define KEY_m1line 32
#define KEY_m1linesColor 33


#define KEY_m2trans 34
#define KEY_m2_dir 35
#define KEY_m2numberColor 36
#define KEY_m2bandColor 37
#define KEY_m2x 38
#define KEY_m2y 39
#define KEY_m2duration 40
#define KEY_m2delay 41
#define KEY_m2outline 42
#define KEY_m2line 43
#define KEY_m2linesColor 44

#define KEY_layer1 45
#define KEY_layer2 46
#define KEY_layer3 47
#define KEY_layer4 48

#define KEY_invertanimationdelay 49
#define KEY_changeallnumbers 50

#define KEY_TEMPERATURE 51
#define KEY_CONDITIONS 52

#define KEY_numberontop 53
#define KEY_h1posone 54
#define KEY_h2posone 55 
#define KEY_m1posone 56 
#define KEY_m2posone 57 

#define KEY_enegy 58
#define KEY_l1func 59 
#define KEY_l2func 60 
#define KEY_l3func 61 
#define KEY_extensionfontColor 62
#define KEY_extensionbackColor 63


typedef struct lines lines;

static Window *s_main_window;

static TextLayer *s_time_layer;

static TextLayer  *s_date_layer;
static TextLayer *s_weather_layer;
static TextLayer *s_health_layer;
static Layer *s_battery_layer;
static int s_battery_level;

//1 date 11 20.05.2015, 2 weather, 3 steps, 4 sleep , 99=none
//layer 1 none&1
//layer 2 none&2
//layer 3 none&3&4
int layer[3]={1,2,3};
bool healthon=1;
bool weateron=1;

AppTimer *outgoing;

static GPath *s_path[8];
static Layer *s_path_layer[8];

static GPath *s_path_band[8];
static Layer *s_path_layer_band[8];

static Layer *s_path_layer_extension;
static const GPathInfo extension_path = {
  .num_points = 4,
  .points = (GPoint []) {{0, 0}, {0, 85}, {181, 85}, {181, 0}}
};
static GPath *s_path_extension;

int delay[4]={500,0,600,100};
int duration[4]={1000,1000,1000,1000};

//int x[4]={26,90,26,90};
//int y[4]={32,32,97,97};

int x[4]={40,90,40,90};
int y[4]={32,32,97,97};

//int x[4]={45,100,35,90};
//int y[4]={32,32,97,97};

int change_all_numbers= 1;
int invert_animation_delay = 1;
int max_delay=10000;

int color_extension = 0xFFFFFF;
int color_extension_font = 0x000000;

int color_background = 0x000000;
int color[4] = {0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF};
//int color_band[8] = {0x00FF00,0xFFFF00,0x00FF00,0xFFFF00};
int color_band[4] = {0x00AAFF,0x0055FF,0x00ff00,0x009600};
bool no_color_band[4] = {false,false,false,false};
//int color_lines[4] = {0x00AAFF,0x0055FF,0x00ff00,0x009600};
int color_lines[4] = {0x000000,0x000000,0x000000,0x000000};
//int color_lines[4] = {0x0055FF,0x00AAFF,0x009600,0x00ff00};

//0=up 1=up-right 2=right 3=d_r 4=d 5=d_l 6=l 7=u_l
//int dir[4] = {3,3,3,7};
//int dir[4] = {1,1,5,5};
//int dir[4] = {7,7,7,7};//5,5,5};
int dir[4] = {7,6,5,6};
//int dir[4] = {2,4,0,6};

//übergang
int n=0;
int order[4]={2,0,1,3};
//int order[4]={1,0,3,2};

//
int an=0;
int initan=1;
bool outlines[4] = {false,false,false,false};
bool line[4] = {false,false,false,false};

int changenumber=0;

int energy;

//energy saving
//bool minutetick = 0;
bool noanimation = 0;
bool noextension = 0;
bool slidein=0; //unimplemented
bool taplimiter=0;

//
int taps = 0;
int minute_taps;



bool numberontop = 1;

//2=left 1=mid 0=right
int onepos[4] = {0,0,0,0};

int extension_animation = 0;

bool isone[4] = {0,0,0,0};
//180
//40
//
struct lines {
  GPoint p0[8]; //= {GPoint(0, 180)};
  GPoint p1[8]; //= {GPoint(180, 0)};
  int points;
}s_path_lines[4];
//lines *;

static GPathInfo PATH_1 = {
  .num_points = 4,
  .points = (GPoint[]) { {17, 0},{17, 50},{25, 50}, {25, 0}}
};
static GPathInfo PATH_2 = {
  .num_points = 12,
  .points = (GPoint[]) { {0, 0}, {0, 8},{17, 8},{17, 21},{0, 21},{0, 50},{25, 50},{25, 42},{8, 42},{8, 29},{25, 29},{25, 0}}
};
static GPathInfo PATH_3 = {
  .num_points = 12,
  .points = (GPoint[]) { {0, 0},{0, 8},{17, 8},{17, 21}, {3, 21},{3, 29},{17, 29},{17, 42},{0, 42},{0, 50},{25, 50},{25, 0}}
};
static GPathInfo PATH_4 = {
  .num_points = 10,
  .points = (GPoint[]) { {0, 0}, {0, 29}, {17, 29},{17, 50}, {25, 50}, {25, 0} , {17, 0}, {17, 21}, {8, 21}, {8, 0}}
};
static GPathInfo PATH_5 = {
  .num_points = 12,
  .points = (GPoint[]) { {0, 0},{0, 29},{17, 29},{17, 42},{0, 42},{0, 50},{25, 50},{25, 21},{8, 21},{8, 8},{25, 8},{25, 0}}
};
static GPathInfo PATH_6 = {
  .num_points = 10,
  .points = (GPoint[]) { {0, 0},{0, 50},{25, 50},{25, 21},{7, 21},{7, 29},{17, 29},{17, 42},{8, 42},{8, 0}}
};
static GPathInfo PATH_7 = {
  .num_points = 6,
  .points = (GPoint[]) { {0, 0}, {25, 0}, {25, 50}, {17, 50}, {17, 8} , {0, 8}}
};
static GPathInfo PATH_8 = {
  .num_points = 16,
  .points = (GPoint[]) { {0, 0}, {0, 50},{8, 50},{8, 29},{17, 29},{17, 42},{7, 42},{7, 50},{25, 50},{25, 0},{7, 0},{7, 8},
                       {17, 8},{17, 21},{8, 21},{8, 0}}
};
static GPathInfo PATH_9 = {
  .num_points = 10,
  .points = (GPoint[]) { {0, 0}, {0, 29},{18, 29},{18, 21},{8, 21},{8, 8},{17, 8},{17, 50},{25, 50},{25, 0}}
};
static GPathInfo PATH_0 = {
  .num_points = 10,
  .points = (GPoint[]) { {0, 0}, {0, 50},{18, 50},{18, 42},{8, 42},{8, 8},{17, 8},{17, 50},{25, 50},{25, 0}}
};

static GPathInfo PATH_band_up_right_1 = {
  .num_points = 4,
  .points = (GPoint[]) {{57+140+1, 0},{17+1, 40+140},{24-1, 90+140}, {90+140+24-1, 0}}
};
static GPathInfo PATH_band_up_right_2 = {
  .num_points = 7,
  .points = (GPoint[]) { {180+1, 0},{1, 180},{21+1, 40+140+1},{1, 65+140-4+1},{1, 90+140},{24-1, 90+140}, {90+140+24-1, 0}}
};
static GPathInfo PATH_band_up_right_3 = {
  .num_points = 8,
  .points = (GPoint[]) { {180+1, 0},{1, 180},{24, 90+140-21-8+1-20},{4, 90+140-21-8+1},{17+1, 90+140-25+1}, {1, 90+140-8+1},{24-1, 90+140}, {90+140+24-1, 0}}
};
static GPathInfo PATH_band_up_right_4 = {
  .num_points = 6,
  .points = (GPoint[]) { {180+1, 0},{1, 180},{1, 65+140},{24, 65+140},{24-1, 90+140}, {90+140+24-1, 0}}
};
static GPathInfo PATH_band_up_right_5 = {
  .num_points = 7,
  .points = (GPoint[]) { {180+1, 0},{1, 180},{1, 65+140},{21, 90+140-8-20+1},{1, 90+140-8+1},{24-1, 90+140}, {90+140+24-1, 0}}
};
static GPathInfo PATH_band_up_right_6 = {
  .num_points = 5,
  .points = (GPoint[]) { {180+1, 0},{1, 180},{1, 90+140},{24-1, 90+140}, {90+140+24-1, 0}}
};
static GPathInfo PATH_band_up_right_7 = {
  .num_points = 5,
  .points = (GPoint[]) { {180+1, 0},{1, 180},{24, 40+140},{24-1, 90+140}, {90+140+24-1, 0}}
};
static GPathInfo PATH_band_up_right_8 = {
  .num_points = 5,
  .points = (GPoint[]) {{180+1, 0},{1, 180},{1, 90+140},{24-1, 90+140}, {90+140+24-1, 0}}
};
static GPathInfo PATH_band_up_right_9 = {
  .num_points = 6,
  .points = (GPoint[]) {{180+1, 0},{1, 180},{1, 65+140},{24, 65+140},{24-1, 90+140}, {90+140+24-1, 0}}
};
static GPathInfo PATH_band_up_right_0 = {
  .num_points = 5,
  .points = (GPoint[]) {{180+1, 0},{1, 180} ,{1, 90+140}, {24-1, 90+140}, {90+140+24-1, 0}}
};

static GPathInfo PATH_band_down_right_1 = {
  .num_points = 5,
  .points = (GPoint[]) {{25-1, 0}, {23, 0},{25-8+2, 50},{180+25-8+2, 180+50}, {25+180-1, 180}}
};
static GPathInfo PATH_band_down_right_2 = {
  .num_points = 7,
  .points = (GPoint[]) {{25-1, 0}, {1, 8},{25-8+1, 25},{1, 25},{1, 49},{180+1, 180+49}, {25+180-1, 180}}
};
static GPathInfo PATH_band_down_right_3 = {
  .num_points = 9,
  .points = (GPoint[]) {{25-1, 0}, {23, 0},{0+1, 8},{25-8+1, 25},{4, 25+5-1},{25-2, 49-1},{1, 49},{180+1, 180+49}, {25+180-1, 180}}
};
static GPathInfo PATH_band_down_right_4 = {
  .num_points = 10,
  .points = (GPoint[]) {{25-1, 0},{22-1, 0},{18-1+2, 10+2}, {8-1, 0} ,{4-1, 0},{1, 25+4},{25-8+1, 46},{25-8+1, 50-1},{180+25-8+1, 180+50-1}, {25+180-1, 180}}
};
static GPathInfo PATH_band_down_right_5 = {
  .num_points = 7,
  .points = (GPoint[]) {{24, 0}, {1, 0},{1, 25+4}  ,{20+1, 49} ,{1, 49},{180+1, 180+50-1}, {25+180-1, 180}}
};
static GPathInfo PATH_band_down_right_6 = {
  .num_points = 5,
  .points = (GPoint[]) {{7, 0}, {1, 0} ,{1, 50-1},{180+1, 180+50-1}, {8+180-1, 180}}
};
static GPathInfo PATH_band_down_right_7 = {
  .num_points = 7,
  .points = (GPoint[]) {{24, 0}, {23, 0} ,{1, 8-1},{25-8+1, 25-1},{25-8+1, 50-1},{180+25-8+1, 180+50-1}, {25+180-1, 180}}
};
static GPathInfo PATH_band_down_right_8 = {
  .num_points = 5,
  .points = (GPoint[]) {{25-1, 0}, {1, 0} ,{2, 50},{180+2, 180+50}, {25+180-1, 180}}
};
static GPathInfo PATH_band_down_right_9 = {
  .num_points = 7,
  .points = (GPoint[]) {{25-1, 0}, {1, 0} ,{1, 25+4},{25-8+1, 46},{25-8+1, 50-1},{180+25-8+1, 180+50-1}, {25+180-1, 180}}
};
static GPathInfo PATH_band_down_right_0 = {
  .num_points = 5,
  .points = (GPoint[]) {{25-1, 0}, {1, 0} ,{2, 50},{180+2, 180+50}, {25+180-1, 180}}
};

static GPathInfo PATH_band_down_left_1 = {
  .num_points = 5,
  .points = (GPoint[]) {{107+140+1, 0},{17+1, 90+140},{75, 90+140-2}, {115+140, 50-2},  {115+140, 0}}
};
static GPathInfo PATH_band_down_left_2 = {
  .num_points = 8,
  .points = (GPoint[]) {{90+140+1, 0},{1, 90+140},{75, 90+140-2}, {115+140, 50-2}, {92+140+2, 50+1-2}, {92+140+25, 25+1}, {115+140, 25}, {115+140, 0}}
};
static GPathInfo PATH_band_down_left_3 = {
  .num_points = 5,
  .points = (GPoint[]) {{90+140+1, 0},{1, 90+140},{75, 90+140-2}, {115+140, 50-2},  {115+140, 0}}
};
static GPathInfo PATH_band_down_left_4 = {
  .num_points = 8,
  .points = (GPoint[]) {{90+140+4, 0},{90+140+1, 0},{1, 90+140},{75, 90+140-2}, {115+140, 50-2}, {115+140, 0},{115+140-8, 1}, {91+140, 16+1}}
};
static GPathInfo PATH_band_down_left_5 = {
  .num_points = 7,
  .points = (GPoint[]) {{91+140+25, 8-2},{91+140, 0},{1, 90+140},{75, 90+140-2}, {115+140, 50-2}, {115+140, 25}, {91+140+8, 25-2}}
};
static GPathInfo PATH_band_down_left_6 = {
  .num_points = 6,
  .points = (GPoint[]) {{91+140, 0},{0, 91+140},{75, 90+140-2}, {115+140, 50-2}, {115+140, 25}, {91+140, 25}}
};
static GPathInfo PATH_band_down_left_7 = {
  .num_points = 5,
  .points = (GPoint[]) {{90+140+1, 0},{1, 90+140},{75, 90+140-2}, {115+140, 50-2},  {115+140, 0}}
};
static GPathInfo PATH_band_down_left_8 = {
  .num_points = 5,
  .points = (GPoint[]) {{90+140+1, 0},{1, 90+140},{75, 90+140-2}, {115+140, 50-2},  {115+140, 0}}
};
static GPathInfo PATH_band_down_left_9 = {
  .num_points = 5,
  .points = (GPoint[]) {{90+140+1, 0},{1, 90+140},{75, 90+140-2}, {115+140, 50-2},  {115+140, 0}}
};
static GPathInfo PATH_band_down_left_0 = {
  .num_points = 5,
  .points = (GPoint[]) {{90+140+1, 0},{1, 90+140},{75, 90+140-2}, {115+140, 50-2},  {115+140, 0}}
};

static GPathInfo PATH_band_up_left_1 = {
  .num_points = 5,
  .points = (GPoint[]) {{0+25-8+2, 0},{180+50+25-8+2, 180+50} ,{25+180+50, 180+50},{25+180+50, 180+1},{50+25, 0+1}}
};
static GPathInfo PATH_band_up_left_2 = {
  .num_points = 9,
  .points = (GPoint[]) {{0+2, 0},{180+50+2, 180+50},{180+50+25, 180+50-8+1} ,{180+50+25-18, 180+24+1} ,{180+50+25, 180+25+1} ,{25+180+50, 180+1},{50+25, 0+1}}
};
static GPathInfo PATH_band_up_left_3 = {
  .num_points = 5,
  .points = (GPoint[]) { {0+2, 0},{180+50+2, 180+50} ,{25+180+50, 180+50},{25+180+50, 180+1},{50+25, 0+1}}
};
static GPathInfo PATH_band_up_left_4 = {
  .num_points = 6,
  .points = (GPoint[]) { {25-8+2, 0},{180+50+25-8+2, 180+50} ,{25+180+50, 180+50},{25+180+50, 180+1},{50+25, 0+1}}
};
static GPathInfo PATH_band_up_left_5 = {
  .num_points = 8,
  .points = (GPoint[]) { {0+2, 0},{180+50+2, 180+50} ,{25+180+50, 180+50},{180+50+25, 180+25-4+1},{180+50+1+3, 180+25-4-24+3+1},{180+50+1+3, 180+3},{25+180+50, 180+1},{50+25, 0+1}}
};
static GPathInfo PATH_band_up_left_6 = {
  .num_points = 7,
  .points = (GPoint[]) { {0+2, 0},{180+50+2, 180+50} ,{25+180+50, 180+50},{25+180+50-1, 180+25-5+1},{8+180+50-1, 183+1},{8+180+50-1, 180},{50+8-1, 0}}
};
static GPathInfo PATH_band_up_left_7 = {
  .num_points = 5,
  .points = (GPoint[]) { {25-8+2, 0},{180+50+25-8+2, 180+50} ,{25+180+50, 180+50},{25+180+50, 180+1},{50+25, 0+1}}
};
static GPathInfo PATH_band_up_left_8 = {
  .num_points = 5,
  .points = (GPoint[]) {{2, 0},{180+50+2, 180+50} ,{25+180+50, 180+50},{25+180+50, 180+1},{50+25, 0+1}}
};
static GPathInfo PATH_band_up_left_9 = {
  .num_points = 5,
  .points = (GPoint[]) {{25-8+2, 0},{180+50+25-8+2, 180+50} ,{25+180+50, 180+50},{25+180+50, 180+1},{50+25, 0+1}}
};
static GPathInfo PATH_band_up_left_0 = {
  .num_points = 5,
  .points = (GPoint[]) {{2, 0},{180+50+2, 180+50} ,{25+180+50, 180+50},{25+180+50, 180+1},{50+25, 0+1}}
};

static void PATH_line_up_right_1(int l) {
  s_path_lines[l].points = 1;
  s_path_lines[l].p0[0]=GPoint(24, 180);
  s_path_lines[l].p1[0]=GPoint(180+24, 0);
}
static void PATH_line_up_right_2(int l) {
  s_path_lines[l].points = 4;
  s_path_lines[l].p0[0]=GPoint(24, 180);
  s_path_lines[l].p1[0]=GPoint(180+24, 0);
  s_path_lines[l].p0[1]=GPoint(24, 180+28);
  s_path_lines[l].p1[1]=GPoint(180+24, 0+28);
  s_path_lines[l].p0[2]=GPoint(7, 180+42);
  s_path_lines[l].p1[2]=GPoint(7+15, 180+42-15);
  s_path_lines[l].p0[3]=GPoint(24, 180+42);
  s_path_lines[l].p1[3]=GPoint(24+180, 180+42-180);
}
static void PATH_line_up_right_3(int l) {
  s_path_lines[l].points = 1;
  s_path_lines[l].p0[0]=GPoint(24, 180);
  s_path_lines[l].p1[0]=GPoint(180+24, 0);
}
static void PATH_line_up_right_4(int l) {
  s_path_lines[l].points = 4;
  s_path_lines[l].p0[0]=GPoint(24, 180);
  s_path_lines[l].p1[0]=GPoint(180+24, 0);
  s_path_lines[l].p0[1]=GPoint(24-6, 180);
  s_path_lines[l].p1[1]=GPoint(180+24-6, 0);
  s_path_lines[l].p0[2]=GPoint(7, 180);
  s_path_lines[l].p1[2]=GPoint(180+7, 0);
  s_path_lines[l].p0[3]=GPoint(7, 180+22);
  s_path_lines[l].p1[3]=GPoint(7+15, 180+22-15);
}
static void PATH_line_up_right_5(int l) {
  s_path_lines[l].points = 4;
  s_path_lines[l].p0[0]=GPoint(24, 180);
  s_path_lines[l].p1[0]=GPoint(180+24, 0);
  s_path_lines[l].p0[1]=GPoint(25, 180+6);
  s_path_lines[l].p1[1]=GPoint(180+25, 6);
  s_path_lines[l].p0[2]=GPoint(24, 180+21);
  s_path_lines[l].p1[2]=GPoint(180+24, 21);
  s_path_lines[l].p0[3]=GPoint(6, 180+22);
  s_path_lines[l].p1[3]=GPoint(6+15, 180+22-15);
}
static void PATH_line_up_right_6(int l) {
  s_path_lines[l].points = 4;
  s_path_lines[l].p0[0]=GPoint(7, 180);
  s_path_lines[l].p1[0]=GPoint(180+7, 0);
  s_path_lines[l].p0[1]=GPoint(25, 180+20);
  s_path_lines[l].p1[1]=GPoint(180+25, 20);
  s_path_lines[l].p0[2]=GPoint(7, 180+21);
  s_path_lines[l].p1[2]=GPoint(180+7, 21);
  s_path_lines[l].p0[3]=GPoint(8, 180+42);
  s_path_lines[l].p1[3]=GPoint(8+15, 180+42-15);
}
static void PATH_line_up_right_7(int l) {
  s_path_lines[l].points = 1;
  s_path_lines[l].p0[0]=GPoint(24, 180);
  s_path_lines[l].p1[0]=GPoint(180+24, 0);
}
static void PATH_line_up_right_8(int l) {
  s_path_lines[l].points = 3;
  s_path_lines[l].p0[0]=GPoint(24, 180);
  s_path_lines[l].p1[0]=GPoint(180+24, 0);
  s_path_lines[l].p0[1]=GPoint(7, 180+42-20);//
  s_path_lines[l].p1[1]=GPoint(7+15, 180+42-15-20);
  s_path_lines[l].p0[2]=GPoint(7, 180+43);
  s_path_lines[l].p1[2]=GPoint(7+15, 180+43-15);
}
static void PATH_line_up_right_9(int l) {
  s_path_lines[l].points = 2;
  s_path_lines[l].p0[0]=GPoint(24, 180);
  s_path_lines[l].p1[0]=GPoint(180+24, 0);
  s_path_lines[l].p0[1]=GPoint(6, 180+42-20);//
  s_path_lines[l].p1[1]=GPoint(6+15, 180+42-15-20);
}
static void PATH_line_up_right_0(int l) {
  s_path_lines[l].points = 2;
  s_path_lines[l].p0[0]=GPoint(24, 180);
  s_path_lines[l].p1[0]=GPoint(180+24, 0);
  s_path_lines[l].p0[1]=GPoint(6, 180+43);
  s_path_lines[l].p1[1]=GPoint(6+15, 180+43-15);
}

static void PATH_line_down_left_1(int l) {
  s_path_lines[l].points = 1;
  s_path_lines[l].p0[0]=GPoint(50+17, 180+50);
  s_path_lines[l].p1[0]=GPoint(180+50+17, 50);

}
static void PATH_line_down_left_2(int l) {
  s_path_lines[l].points = 4;
  s_path_lines[l].p0[0]=GPoint(50, 180+50);
  s_path_lines[l].p1[0]=GPoint(180+50, 50);
  s_path_lines[l].p0[1]=GPoint(180+50+25-8, 8+1);
  s_path_lines[l].p1[1]=GPoint(180+50+25-8-15, 8+15+1);
  s_path_lines[l].p0[2]=GPoint(50, 180+50-41);
  s_path_lines[l].p1[2]=GPoint(180+50, 50-41);
  s_path_lines[l].p0[3]=GPoint(50+1, 180+50-41+13);
  s_path_lines[l].p1[3]=GPoint(180+50+1, 50-41+13);
}
static void PATH_line_down_left_3(int l) {
  s_path_lines[l].points = 6;
  s_path_lines[l].p0[0]=GPoint(50, 180+50);
  s_path_lines[l].p1[0]=GPoint(180+50, 50);
  s_path_lines[l].p0[1]=GPoint(180+50+25-8, 8+1);
  s_path_lines[l].p1[1]=GPoint(180+50+25-8-180, 8+180+1);
  s_path_lines[l].p0[2]=GPoint(180+50+25-8, 8+1+20+1);
  s_path_lines[l].p1[2]=GPoint(180+50+25-8-15, 8+15+1+20+1);
  s_path_lines[l].p0[3]=GPoint(50, 180+50-41);
  s_path_lines[l].p1[3]=GPoint(180+50, 50-41);
  s_path_lines[l].p0[4]=GPoint(50, 180+50-6);
  s_path_lines[l].p1[4]=GPoint(180+50, 50-6);
  s_path_lines[l].p0[5]=GPoint(50+3, 180+50-20);
  s_path_lines[l].p1[5]=GPoint(180+50+3, 50-20);
}
static void PATH_line_down_left_4(int l) {
  s_path_lines[l].points = 3;
  s_path_lines[l].p0[0]=GPoint(50+17, 180+50);
  s_path_lines[l].p1[0]=GPoint(180+50+17, 50);
  s_path_lines[l].p0[1]=GPoint(50, 180+50-20);
  s_path_lines[l].p1[1]=GPoint(180+50, 50-20);
  s_path_lines[l].p0[2]=GPoint(180+50+25-8+1, 8+1+20);
  s_path_lines[l].p1[2]=GPoint(180+50+25-8-180+1, 8+180+1+20);
}
static void PATH_line_down_left_5(int l) {
  s_path_lines[l].points = 4;
  s_path_lines[l].p0[0]=GPoint(50, 180+50);
  s_path_lines[l].p1[0]=GPoint(180+50, 50);
  s_path_lines[l].p0[1]=GPoint(180+50+25-8+1, 8+1+20);
  s_path_lines[l].p1[1]=GPoint(180+50+25-8-15+1, 8+15+1+20);
  s_path_lines[l].p0[2]=GPoint(50, 180+50-20);
  s_path_lines[l].p1[2]=GPoint(180+50, 50-20);
  s_path_lines[l].p0[3]=GPoint(50+1, 180+50-7);
  s_path_lines[l].p1[3]=GPoint(180+50+1, 50-7);
}
static void PATH_line_down_left_6(int l) {
  s_path_lines[l].points = 2;
  s_path_lines[l].p0[0]=GPoint(50, 180+50);
  s_path_lines[l].p1[0]=GPoint(180+50, 50);
  s_path_lines[l].p0[1]=GPoint(180+50+25-8+1, 8+1+20);
  s_path_lines[l].p1[1]=GPoint(180+50+25-8-15+1, 8+15+1+20);
}
static void PATH_line_down_left_7(int l) {
  s_path_lines[l].points = 3;
  s_path_lines[l].p0[0]=GPoint(50+17, 180+50);
  s_path_lines[l].p1[0]=GPoint(180+50+17, 50);
  s_path_lines[l].p0[1]=GPoint(180+50+25-8, 8);
  s_path_lines[l].p1[1]=GPoint(180+50+25-8-180, 8+180);
  s_path_lines[l].p0[2]=GPoint(50, 180+50-50+8);
  s_path_lines[l].p1[2]=GPoint(180+50, 50-50+8);
}
static void PATH_line_down_left_8(int l) {
  s_path_lines[l].points = 3;
  s_path_lines[l].p0[0]=GPoint(50, 180+50);
  s_path_lines[l].p1[0]=GPoint(180+50, 50);
  s_path_lines[l].p0[1]=GPoint(180+50+25-8, 8+1);
  s_path_lines[l].p1[1]=GPoint(180+50+25-8-15, 8+15+1);
  s_path_lines[l].p0[2]=GPoint(180+50+25-8, 8+1+20);
  s_path_lines[l].p1[2]=GPoint(180+50+25-8-15, 8+15+1+20);
}
static void PATH_line_down_left_9(int l) {
  s_path_lines[l].points = 3;
  s_path_lines[l].p0[0]=GPoint(50, 180+50-20);
  s_path_lines[l].p1[0]=GPoint(180+50, 50-20);
  s_path_lines[l].p0[1]=GPoint(180+50+25-8, 8);
  s_path_lines[l].p1[1]=GPoint(180+50+25-8-15, 8+15);
  s_path_lines[l].p0[2]=GPoint(50+17, 180+50);
  s_path_lines[l].p1[2]=GPoint(180+50+17, 50);
}
static void PATH_line_down_left_0(int l) {
  s_path_lines[l].points = 2;
  s_path_lines[l].p0[0]=GPoint(50, 180+50);
  s_path_lines[l].p1[0]=GPoint(180+50, 50);
  s_path_lines[l].p0[1]=GPoint(180+50+25-8, 8);
  s_path_lines[l].p1[1]=GPoint(180+50+25-8-15, 8+15);
}

static void PATH_line_down_right_1(int l) {
  s_path_lines[l].points = 1;
  s_path_lines[l].p0[0]=GPoint(25, 50);
  s_path_lines[l].p1[0]=GPoint(25+180, 50+180);

}
static void PATH_line_down_right_2(int l) {
  s_path_lines[l].points = 4;
  s_path_lines[l].p0[0]=GPoint(24, 28);
  s_path_lines[l].p1[0]=GPoint(24+180, 28+180);
  s_path_lines[l].p0[1]=GPoint(25, 50);
  s_path_lines[l].p1[1]=GPoint(25+180, 50+180);
  s_path_lines[l].p0[2]=GPoint(7, 8+20);
  s_path_lines[l].p1[2]=GPoint(7+15, 8+15+20);
  s_path_lines[l].p0[3]=GPoint(24, 50-8);
  s_path_lines[l].p1[3]=GPoint(24+180, 50-8+180);
}
static void PATH_line_down_right_3(int l) {
  s_path_lines[l].points = 1;
  s_path_lines[l].p0[0]=GPoint(25, 50);
  s_path_lines[l].p1[0]=GPoint(25+180, 50+180);
}
static void PATH_line_down_right_4(int l) {
  s_path_lines[l].points = 1;
  s_path_lines[l].p0[0]=GPoint(25, 50);
  s_path_lines[l].p1[0]=GPoint(25+180, 50+180);
}
static void PATH_line_down_right_5(int l) {
  s_path_lines[l].points = 4;
  s_path_lines[l].p0[0]=GPoint(7, 7);
  s_path_lines[l].p1[0]=GPoint(7+15, 7+15);
  s_path_lines[l].p0[1]=GPoint(25, 50);
  s_path_lines[l].p1[1]=GPoint(25+180, 50+180);
  s_path_lines[l].p0[2]=GPoint(24, 21);
  s_path_lines[l].p1[2]=GPoint(24+180, 21+180);
  s_path_lines[l].p0[3]=GPoint(24, 7);
  s_path_lines[l].p1[3]=GPoint(24+180, 7+180);
}
static void PATH_line_down_right_6(int l) {
  s_path_lines[l].points = 3;
  s_path_lines[l].p0[0]=GPoint(24, 21);
  s_path_lines[l].p1[0]=GPoint(24+180, 21+180);
  s_path_lines[l].p0[1]=GPoint(25, 50);
  s_path_lines[l].p1[1]=GPoint(25+180, 50+180);
  s_path_lines[l].p0[2]=GPoint(6, 8+20);
  s_path_lines[l].p1[2]=GPoint(6+15, 8+15+20);
}
static void PATH_line_down_right_7(int l) {
  s_path_lines[l].points = 1;
  s_path_lines[l].p0[0]=GPoint(25, 50);
  s_path_lines[l].p1[0]=GPoint(25+180, 50+180);
}
static void PATH_line_down_right_8(int l) {
  s_path_lines[l].points = 3;
  s_path_lines[l].p0[0]=GPoint(7, 8);
  s_path_lines[l].p1[0]=GPoint(7+15, 8+15);
  s_path_lines[l].p0[1]=GPoint(25, 50);
  s_path_lines[l].p1[1]=GPoint(25+180, 50+180);
  s_path_lines[l].p0[2]=GPoint(7, 8+20);
  s_path_lines[l].p1[2]=GPoint(7+15, 8+15+20);
}
static void PATH_line_down_right_9(int l) {
  s_path_lines[l].points = 2;
  s_path_lines[l].p0[0]=GPoint(25, 50);
  s_path_lines[l].p1[0]=GPoint(25+180, 50+180);
    s_path_lines[l].p0[1]=GPoint(7, 7);
  s_path_lines[l].p1[1]=GPoint(7+15, 7+15);
}
static void PATH_line_down_right_0(int l) {
  s_path_lines[l].points = 2;
  s_path_lines[l].p0[0]=GPoint(8, 8);
  s_path_lines[l].p1[0]=GPoint(8+15, 8+15);
  s_path_lines[l].p0[1]=GPoint(25, 50);
  s_path_lines[l].p1[1]=GPoint(25+180, 50+180);
}

static void PATH_line_up_left_1(int l) {
  s_path_lines[l].points = 1;
  s_path_lines[l].p0[0]=GPoint(50+17, 0-1);
  s_path_lines[l].p1[0]=GPoint(180+50+17, 180-1);

}
static void PATH_line_up_left_2(int l) {
  s_path_lines[l].points = 4;
  s_path_lines[l].p0[0]=GPoint(50, 0-1);
  s_path_lines[l].p1[0]=GPoint(180+50, 180-1);
  s_path_lines[l].p0[1]=GPoint(180+50+25-8+1, 201+1);
  s_path_lines[l].p1[1]=GPoint(180+50+25-8-15+1, 186+1);
  s_path_lines[l].p0[2]=GPoint(50, 20+1);
  s_path_lines[l].p1[2]=GPoint(180+50, 200+1);
  s_path_lines[l].p0[3]=GPoint(50+1, 7+1);
  s_path_lines[l].p1[3]=GPoint(180+50+1, 187+1);
}
static void PATH_line_up_left_3(int l) {
  s_path_lines[l].points = 6;
  s_path_lines[l].p0[0]=GPoint(50, 0-1);
  s_path_lines[l].p1[0]=GPoint(180+50, 180-1);
  s_path_lines[l].p0[1]=GPoint(180+50+25-8, 221+1);
  s_path_lines[l].p1[1]=GPoint(180+50+25-8-180, 41+1);
  s_path_lines[l].p0[2]=GPoint(180+50+25-8, 200+1);
  s_path_lines[l].p1[2]=GPoint(180+50+25-8-15, 185+1);
  s_path_lines[l].p0[3]=GPoint(50, 42);
  s_path_lines[l].p1[3]=GPoint(180+50, 221+1);
  s_path_lines[l].p0[4]=GPoint(50, 6+1);
  s_path_lines[l].p1[4]=GPoint(180+50, 186+1);
  s_path_lines[l].p0[5]=GPoint(50+3, 20+1);
  s_path_lines[l].p1[5]=GPoint(180+50+3, 200+1);
}
static void PATH_line_up_left_4(int l) {
  s_path_lines[l].points = 5;
  s_path_lines[l].p0[0]=GPoint(50+17, 0-1);
  s_path_lines[l].p1[0]=GPoint(180+50+17, 180-1);
  s_path_lines[l].p0[1]=GPoint(50, 20+8);
  s_path_lines[l].p1[1]=GPoint(180+50, 200+8);
  s_path_lines[l].p0[2]=GPoint(180+50+25-8+1, 201+1);
  s_path_lines[l].p1[2]=GPoint(180+50+25-8+1-15, 201+1-15);
  s_path_lines[l].p0[3]=GPoint(50, 0-1);
  s_path_lines[l].p1[3]=GPoint(180+50, 180-1);
  s_path_lines[l].p0[4]=GPoint(50+6, 0-1);
  s_path_lines[l].p1[4]=GPoint(180+50+6, 180-1);
}
static void PATH_line_up_left_5(int l) {
  s_path_lines[l].points = 4;
  s_path_lines[l].p0[0]=GPoint(50, 0-1);
  s_path_lines[l].p1[0]=GPoint(180+50, 180-1);
  s_path_lines[l].p0[1]=GPoint(180+50+25-8, 221+1);
  s_path_lines[l].p1[1]=GPoint(180+50+25-8-15, 206+1);
  s_path_lines[l].p0[2]=GPoint(50, 41+1);
  s_path_lines[l].p1[2]=GPoint(180+50, 221+1);
  s_path_lines[l].p0[3]=GPoint(50+1, 28+1);
  s_path_lines[l].p1[3]=GPoint(180+50+1, 208+1);
}
static void PATH_line_up_left_6(int l) {
  s_path_lines[l].points = 2;
  s_path_lines[l].p0[0]=GPoint(50, 0-1);
  s_path_lines[l].p1[0]=GPoint(180+50, 180-1);
  s_path_lines[l].p0[1]=GPoint(180+50+25-8+1, 201+22);
  s_path_lines[l].p1[1]=GPoint(180+50+25-8-15+1, 186+22);
}
static void PATH_line_up_left_7(int l) {
  s_path_lines[l].points = 2;
  s_path_lines[l].p0[0]=GPoint(50, 0-1);
  s_path_lines[l].p1[0]=GPoint(180+50, 180-1);
  s_path_lines[l].p0[1]=GPoint(50+1, 0-1+8);
  s_path_lines[l].p1[1]=GPoint(180+50+1, 180-1+8);
}
static void PATH_line_up_left_8(int l) {
  s_path_lines[l].points = 3;
  s_path_lines[l].p0[0]=GPoint(50, 0-1);
  s_path_lines[l].p1[0]=GPoint(180+50, 180-1);
  s_path_lines[l].p0[1]=GPoint(180+50+25-8, 221+1);
  s_path_lines[l].p1[1]=GPoint(180+50+25-8-15, 206+1);
  s_path_lines[l].p0[2]=GPoint(180+50+25-8, 201);
  s_path_lines[l].p1[2]=GPoint(180+50+25-8-15, 186);
}
static void PATH_line_up_left_9(int l) {
  s_path_lines[l].points = 3;
  s_path_lines[l].p0[0]=GPoint(50, 20+8);
  s_path_lines[l].p1[0]=GPoint(180+50, 200+8);
  s_path_lines[l].p0[1]=GPoint(180+50+25-8, 222-22);
  s_path_lines[l].p1[1]=GPoint(180+50+25-8-15, 207-22);
  s_path_lines[l].p0[2]=GPoint(50+17-25+9, 0);
  s_path_lines[l].p1[2]=GPoint(180+50+17-25+9, 180);
}
static void PATH_line_up_left_0(int l) {
  s_path_lines[l].points = 2;
  s_path_lines[l].p0[0]=GPoint(50+1, 0);
  s_path_lines[l].p1[0]=GPoint(180+50+1, 180);
  s_path_lines[l].p0[1]=GPoint(180+50+25-8+1, 222);
  s_path_lines[l].p1[1]=GPoint(180+50+25-8-15+1, 207);
}

//horizontal
static GPathInfo PATH_band_left_1 = {
  .num_points = 4,
  .points = (GPoint[]) {{0, 0},{25+180+50, 0},{25+180+50, 49}, {0, 49}}
};
static GPathInfo PATH_band_left_2 = {
  .num_points = 7,
  .points = (GPoint[]) {{0, 0},{25+180+50, 0}, {25+180+50, 25},{1+180+50, 25},{1+180+50, 49}, {25+180+50, 49}, {0, 49}}
};
static GPathInfo PATH_band_left_3 = {
  .num_points = 4,
  .points = (GPoint[]) {{0, 0},{25+180+50, 0},{25+180+50, 49}, {0, 49}}
};
static GPathInfo PATH_band_left_4 = {
  .num_points = 4,
  .points = (GPoint[]) {{0, 0},{25+180+50, 0},{25+180+50, 49}, {0, 49}}
};
static GPathInfo PATH_band_left_5 = {
  .num_points = 6,
  .points = (GPoint[]) {{0, 0},{1+180+50, 0}, {1+180+50, 25},{25+180+50, 25}, {25+180+50, 49}, {0, 49}}
};
static GPathInfo PATH_band_left_6 = {
  .num_points = 6,
  .points = (GPoint[]) {{0, 0},{1+180+50, 0}, {1+180+50, 25},{25+180+50, 25}, {25+180+50, 49}, {0, 49}}
};
static GPathInfo PATH_band_left_7 = {
  .num_points = 4,
  .points = (GPoint[]) {{0, 0},{25+180+50, 0},{25+180+50, 49}, {0, 49}}
};
static GPathInfo PATH_band_left_8 = {
  .num_points = 4,
  .points = (GPoint[]) {{0, 0},{25+180+50, 0},{25+180+50, 49}, {0, 49}}
};
static GPathInfo PATH_band_left_9 = {
  .num_points = 4,
  .points = (GPoint[]) {{0, 0},{25+180+50, 0},{25+180+50, 49}, {0, 49}}
};
static GPathInfo PATH_band_left_0 = {
  .num_points = 4,
  .points = (GPoint[]) {{0, 0},{25+180+50, 0},{25+180+50, 49}, {0, 49}}
};

static GPathInfo PATH_band_right_1 = {
  .num_points = 4,
  .points = (GPoint[]) {{24, 0},{25+180+50, 0},{25+180+50, 49}, {24, 49}}
};
static GPathInfo PATH_band_right_2 = {
  .num_points = 6,
  .points = (GPoint[]) {{1, 25},{24, 25},{24, 0},{25+180+50, 0},{25+180+50, 49}, {1, 49}}
};
static GPathInfo PATH_band_right_3 = {
  .num_points = 4,
  .points = (GPoint[]) {{24, 0},{25+180+50, 0},{25+180+50, 49}, {24, 49}}
};
static GPathInfo PATH_band_right_4 = {
  .num_points = 6,
  .points = (GPoint[]) {{24, 24},{1, 24},{1, 0},{25+180+50, 0},{25+180+50, 49}, {24, 49}}
};
static GPathInfo PATH_band_right_5 = {
  .num_points = 6,
  .points = (GPoint[]) {{24, 24},{1, 24},{1, 0},{25+180+50, 0},{25+180+50, 49}, {24, 49}}
};
static GPathInfo PATH_band_right_6 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 0},{25+180+50, 0},{25+180+50, 49}, {1, 49}}
};
static GPathInfo PATH_band_right_7 = {
  .num_points = 4,
  .points = (GPoint[]) {{24, 0},{25+180+50, 0},{25+180+50, 49}, {24, 49}}
};
static GPathInfo PATH_band_right_8 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 0},{25+180+50, 0},{25+180+50, 49}, {1, 49}}
};
static GPathInfo PATH_band_right_9 = {
  .num_points = 6,
  .points = (GPoint[]) {{24, 24},{1, 24},{1, 0},{25+180+50, 0},{25+180+50, 49}, {24, 49}}
};
static GPathInfo PATH_band_right_0 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 0},{25+180+50, 0},{25+180+50, 49}, {1, 49}}
};

static GPathInfo PATH_band_up_1 = {
  .num_points = 4,
  .points = (GPoint[]) {{18, 0},{18, 180+50},{24, 180+50}, {24, 0}}
};
static GPathInfo PATH_band_up_2 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 0},{1, 180+50},{24, 180+50}, {24, 0}}
};
static GPathInfo PATH_band_up_3 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 0},{1, 180+50},{24, 180+50}, {24, 0}}
};
static GPathInfo PATH_band_up_4 = {
  .num_points = 5,
  .points = (GPoint[]) {{1, 0},{1, 180+50-25},{1+23, 180+50-25},{24, 180+50}, {24, 0}}
};
static GPathInfo PATH_band_up_5 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 0},{1, 180+50},{24, 180+50}, {24, 0}}
};
static GPathInfo PATH_band_up_6 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 0},{1, 180+50},{24, 180+50}, {24, 0}}
};
static GPathInfo PATH_band_up_7 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 0},{1, 180+2},{24, 180+2}, {24, 0}}
};
static GPathInfo PATH_band_up_8 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 0},{1, 180+50},{24, 180+50}, {24, 0}}
};
static GPathInfo PATH_band_up_9 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 0},{1, 180+25},{24, 180+25}, {24, 0}}
};
static GPathInfo PATH_band_up_0 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 0},{1, 180+50},{24, 180+50}, {24, 0}}
};

static GPathInfo PATH_band_down_1 = {
  .num_points = 4,
  .points = (GPoint[]) {{18, 0},{18, 180+50},{24, 180+50}, {24, 0}}
};
static GPathInfo PATH_band_down_2 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 0},{1, 180+50},{24, 180+50}, {24, 0}}
};
static GPathInfo PATH_band_down_3 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 0},{1, 180+50},{24, 180+50}, {24, 0}}
};
static GPathInfo PATH_band_down_4 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 25},{1, 180+50},{24, 180+50}, {24, 25}}
};
static GPathInfo PATH_band_down_5 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 0},{1, 180+50},{24, 180+50}, {24, 0}}
};
static GPathInfo PATH_band_down_6 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 25},{1, 180+50},{24, 180+50}, {24, 25}}
};
static GPathInfo PATH_band_down_7 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 0},{1, 180+50},{24, 180+50}, {24, 0}}
};
static GPathInfo PATH_band_down_8 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 0},{1, 180+50},{24, 180+50}, {24, 0}}
};
static GPathInfo PATH_band_down_9 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 0},{1, 180+50},{24, 180+50}, {24, 0}}
};
static GPathInfo PATH_band_down_0 = {
  .num_points = 4,
  .points = (GPoint[]) {{1, 0},{1, 180+50},{24, 180+50}, {24, 0}}
};

static void PATH_line_left_1(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_left_2(int l) {
  s_path_lines[l].points = 2;

  s_path_lines[l].p0[0]=GPoint(0-25, 0+8);
  s_path_lines[l].p1[0]=GPoint(25+180+50-25, 0+8);
  s_path_lines[l].p0[1]=GPoint(0-25, 0+22);
  s_path_lines[l].p1[1]=GPoint(25+180+50-25, 0+22);
}
static void PATH_line_left_3(int l) {
  s_path_lines[l].points = 4;

  s_path_lines[l].p0[0]=GPoint(0-25, 0+8);
  s_path_lines[l].p1[0]=GPoint(25+180+50-25, 0+8);
  s_path_lines[l].p0[1]=GPoint(0-21, 0+22);
  s_path_lines[l].p1[1]=GPoint(25+180+50-21, 0+22);
  s_path_lines[l].p0[2]=GPoint(0-21, 0+29);
  s_path_lines[l].p1[2]=GPoint(25+180+50-21, 0+29);
  s_path_lines[l].p0[3]=GPoint(0-25, 0+50-7);
  s_path_lines[l].p1[3]=GPoint(25+180+50-25, 0+50-7);
}
static void PATH_line_left_4(int l) {
  s_path_lines[l].points = 1;
  s_path_lines[l].p0[0]=GPoint(0-21, 0+29);
  s_path_lines[l].p1[0]=GPoint(25+180+50-21, 0+29);
}
static void PATH_line_left_5(int l) {
  s_path_lines[l].points = 2;
  s_path_lines[l].p0[0]=GPoint(0-21, 0+29);
  s_path_lines[l].p1[0]=GPoint(25+180+50-21, 0+29);
  s_path_lines[l].p0[1]=GPoint(0-25, 0+50-7);
  s_path_lines[l].p1[1]=GPoint(25+180+50-25, 0+50-7);
}
static void PATH_line_left_6(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_left_7(int l) {
  s_path_lines[l].points = 1;
    s_path_lines[l].p0[0]=GPoint(0-25, 0+7);
  s_path_lines[l].p1[0]=GPoint(25+180+50-25, 0+7);
}
static void PATH_line_left_8(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_left_9(int l) {
  s_path_lines[l].points = 1;
    s_path_lines[l].p0[0]=GPoint(0-21, 0+29);
  s_path_lines[l].p1[0]=GPoint(25+180+50-21, 0+29);
}
static void PATH_line_left_0(int l) {
  s_path_lines[l].points = 0;
}

static void PATH_line_right_1(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_right_2(int l) {
  s_path_lines[l].points = 2;
  s_path_lines[l].p0[0]=GPoint(0+24, 0+29-1);
  s_path_lines[l].p1[0]=GPoint(25+180+50-21, 0+29-1);
  s_path_lines[l].p0[1]=GPoint(0+24, 0+50-7-1);
  s_path_lines[l].p1[1]=GPoint(25+180+50-25, 0+50-7-1);
}
static void PATH_line_right_3(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_right_4(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_right_5(int l) {
  s_path_lines[l].points = 2;
  s_path_lines[l].p0[0]=GPoint(24, 0+8-1);
  s_path_lines[l].p1[0]=GPoint(25+180+50-25, 0+8);
  s_path_lines[l].p0[1]=GPoint(24, 0+22-1);
  s_path_lines[l].p1[1]=GPoint(25+180+50-25, 0+22);
}
static void PATH_line_right_6(int l) {
  s_path_lines[l].points = 1;
  s_path_lines[l].p0[0]=GPoint(24, 0+22-1);
  s_path_lines[l].p1[0]=GPoint(25+180+50-25, 0+22);
}
static void PATH_line_right_7(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_right_8(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_right_9(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_right_0(int l) {
  s_path_lines[l].points = 0;
}

static void PATH_line_up_1(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_up_2(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_up_3(int l) {
  s_path_lines[l].points = 1;
  s_path_lines[l].p0[0]=GPoint(4, 180+5);
  s_path_lines[l].p1[0]=GPoint(4, 180+21);
}
static void PATH_line_up_4(int l) {
  s_path_lines[l].points = 2;
  s_path_lines[l].p0[0]=GPoint(7, 180+1);
  s_path_lines[l].p1[0]=GPoint(7, 0);
  s_path_lines[l].p0[1]=GPoint(18, 180+1);
  s_path_lines[l].p1[1]=GPoint(18, 0);
}
static void PATH_line_up_5(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_up_6(int l) {
  s_path_lines[l].points = 1;
  s_path_lines[l].p0[0]=GPoint(7, 180+1);
  s_path_lines[l].p1[0]=GPoint(7, 0);
}
static void PATH_line_up_7(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_up_8(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_up_9(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_up_0(int l) {
  s_path_lines[l].points = 0;
}

static void PATH_line_down_1(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_down_2(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_down_3(int l) {
  s_path_lines[l].points = 1;
  s_path_lines[l].p0[0]=GPoint(4, 29);
  s_path_lines[l].p1[0]=GPoint(4, 29+15);
}
static void PATH_line_down_4(int l) {
  s_path_lines[l].points = 1;
  s_path_lines[l].p0[0]=GPoint(18, 0);
  s_path_lines[l].p1[0]=GPoint(18, 180+50);
}
static void PATH_line_down_5(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_down_6(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_down_7(int l) {
  s_path_lines[l].points = 1;
  s_path_lines[l].p0[0]=GPoint(18, 0);
  s_path_lines[l].p1[0]=GPoint(18, 180+50);
}
static void PATH_line_down_8(int l) {
  s_path_lines[l].points = 0;
}
static void PATH_line_down_9(int l) {
  s_path_lines[l].points = 1;
  s_path_lines[l].p0[0]=GPoint(18, 0);
  s_path_lines[l].p1[0]=GPoint(18, 180+50);
}
static void PATH_line_down_0(int l) {
  s_path_lines[l].points = 0;
}

static void update_time();
static void update_time_minute();
static void main_window_unload(Window *window);
static void main_window_load(Window *window);

static void heath_update(){
    HealthMetric metric = HealthMetricStepCount;
  time_t start = time_start_of_today();
  time_t end = time(NULL);
  
  static char s_buffer[32];

// Check the metric has data available for today
  HealthServiceAccessibilityMask mask = health_service_metric_accessible(metric, 
  start, end);

  if(mask & HealthServiceAccessibilityMaskAvailable) {
  // Data is available!
    snprintf(s_buffer, sizeof(s_buffer), "%d Steps", (int)health_service_sum_today(metric)); 
    APP_LOG(APP_LOG_LEVEL_INFO, "Steps today: %d", 
          (int)health_service_sum_today(metric));
  } else {
  // No data recorded yet today
    APP_LOG(APP_LOG_LEVEL_ERROR, "Data unavailable!");
    snprintf(s_buffer, sizeof(s_buffer), "No data"); 
  }
  text_layer_set_text(s_health_layer, s_buffer);
}

static void health_handler(HealthEventType event, void *context) {
  // Which type of event occured?
  switch(event) {
    case HealthEventSignificantUpdate:
   if(healthon==1) heath_update();
      APP_LOG(APP_LOG_LEVEL_INFO, 
              "New HealthService HealthEventSignificantUpdate event");
      break;
    case HealthEventMovementUpdate:
      APP_LOG(APP_LOG_LEVEL_INFO, 
              "New HealthService HealthEventMovementUpdate event");
      break;
    case HealthEventSleepUpdate:
      APP_LOG(APP_LOG_LEVEL_INFO, 
              "New HealthService HealthEventSleepUpdate event");
      break;
  }
}
static void battery_callback(BatteryChargeState state) {
  // Record the new battery level
  s_battery_level = state.charge_percent;
  layer_mark_dirty(s_battery_layer);
}

static void inbox_received_handler(DictionaryIterator *iter, void *context) {
  Tuple *background_color_t = dict_find(iter, KEY_BACKGROUND_COLOR);
  Tuple *h1_no_color_band_t = dict_find(iter, KEY_h1nocolorband);
  Tuple *h1_dir_t = dict_find(iter, KEY_h1_dir);
  Tuple *h1_number_color_t = dict_find(iter, KEY_h1numberColor);
  Tuple *h1_band_color_t = dict_find(iter, KEY_h1bandColor);
  Tuple *h1_x_t = dict_find(iter, KEY_h1x);
  Tuple *h1_y_t = dict_find(iter, KEY_h1y);
  Tuple *h1_duration_t = dict_find(iter, KEY_h1duration);
  Tuple *h1_delay_t = dict_find(iter, KEY_h1delay);
  Tuple *h1_outline_t = dict_find(iter, KEY_h1outline );
  Tuple *h1_line_t = dict_find(iter, KEY_h1line );
  Tuple *h1_lines_Color_t = dict_find(iter, KEY_h1linesColor );
  
  if (background_color_t) {
    color_background = background_color_t->value->int32;
    persist_write_int(KEY_BACKGROUND_COLOR, color_background);
    window_set_background_color(s_main_window, GColorFromHEX(color_background));
  }
    if (h1_dir_t) {
     dir[0] = (h1_dir_t->value->int32)-1;
    persist_write_int(KEY_h1_dir, dir[0]+1);
  }

  if (h1_no_color_band_t) {
    no_color_band[0] = h1_no_color_band_t->value->int8;
    persist_write_int(KEY_h1nocolorband, no_color_band[0]);
  }
    if (h1_number_color_t) {
    color[0] = h1_number_color_t->value->int32;
    persist_write_int( KEY_h1numberColor, color[0]+1);
  }
  if (h1_band_color_t) {
    color_band[0] = h1_band_color_t->value->int32;
    persist_write_int( KEY_h1bandColor, color_band[0]+1);
  }
  if (h1_x_t) {
    x[0]  = h1_x_t->value->int32;
    APP_LOG(APP_LOG_LEVEL_DEBUG, "xload:%d",x[0] );
    persist_write_int( KEY_h1x, x[0]-500);
  }
  if (h1_y_t) {
    y[0] = h1_y_t->value->int32;
    persist_write_int( KEY_h1y, y[0]-500);
  }
  if (h1_duration_t) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "duration d" );
    duration[0] = h1_duration_t->value->int32;
    persist_write_int(  KEY_h1duration, duration[0]+50);
  }
  if (h1_delay_t) {
    delay[0] = h1_delay_t->value->int32;
    persist_write_int(  KEY_h1delay, delay[0]+50);
  }
    if (h1_outline_t) {
    outlines[0] = h1_outline_t->value->int8;
    persist_write_int(KEY_h1outline, outlines[0]);
  }
  if (h1_line_t) {
    line[0] = h1_line_t->value->int8;
    persist_write_int(KEY_h1line, line[0]);
  }
  if (h1_lines_Color_t) {
    color_lines[0] = h1_lines_Color_t->value->int32;
    persist_write_int(KEY_h1linesColor, color_lines[0]);
  }
    //h2
  Tuple *h2_trans_t = dict_find(iter, KEY_h2trans);
  Tuple *h2_dir_t = dict_find(iter, KEY_h2_dir);
  Tuple *h2_number_color_t = dict_find(iter, KEY_h2numberColor);
  Tuple *h2_band_color_t = dict_find(iter, KEY_h2bandColor);
  Tuple *h2_x_t = dict_find(iter, KEY_h2x);
  Tuple *h2_y_t = dict_find(iter, KEY_h2y);
  Tuple *h2_duration_t = dict_find(iter, KEY_h2duration);
  Tuple *h2_delay_t = dict_find(iter, KEY_h2delay);
  Tuple *h2_outline_t = dict_find(iter, KEY_h2outline );
  Tuple *h2_line_t = dict_find(iter, KEY_h2line );
  Tuple *h2_lines_Color_t = dict_find(iter, KEY_h2linesColor );
  
    if (h2_dir_t) {
     dir[1] = (h2_dir_t->value->int32)-1;
    persist_write_int(KEY_h2_dir, dir[1]+1);
  }

  if (h2_trans_t) {
    no_color_band[1] = h2_trans_t->value->int8;
    persist_write_int(KEY_h2trans, no_color_band[1]);
  }
    if (h2_number_color_t) {
    color[1] = h2_number_color_t->value->int32;
    persist_write_int( KEY_h2numberColor, color[1]+1);
  }
  if (h2_band_color_t) {
    color_band[1] = h2_band_color_t->value->int32;
    persist_write_int( KEY_h2bandColor, color_band[1]+1);
  }
  if (h2_x_t) {
    x[1]  = h2_x_t->value->int32;
    APP_LOG(APP_LOG_LEVEL_DEBUG, "xload:%d",x[1] );
    persist_write_int( KEY_h2x, x[1]-500);
  }
  if (h2_y_t) {
    y[1] = h2_y_t->value->int32;
    persist_write_int( KEY_h2y, y[1]-500);
  }
  if (h2_duration_t) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "duration d" );
    duration[1] = h2_duration_t->value->int32;
    persist_write_int(  KEY_h2duration, duration[1]+50);
  }
  if (h2_delay_t) {
    delay[1] = h2_delay_t->value->int32;
    persist_write_int(  KEY_h2delay, delay[1]+50);
  }
    if (h2_outline_t) {
    outlines[1] = h2_outline_t->value->int8;
    persist_write_int(KEY_h2outline, outlines[1]);
  }
  if (h2_line_t) {
    line[1] = h2_line_t->value->int8;
    persist_write_int(KEY_h2line, line[1]);
  }
  if (h2_lines_Color_t) {
    color_lines[1] = h2_lines_Color_t->value->int32;
    persist_write_int(KEY_h2linesColor, color_lines[1]);
  } 
  
  
  //m1
  Tuple *m1_trans_t = dict_find(iter, KEY_m1trans);
  Tuple *m1_dir_t = dict_find(iter, KEY_m1_dir);
  Tuple *m1_number_color_t = dict_find(iter, KEY_m1numberColor);
  Tuple *m1_band_color_t = dict_find(iter, KEY_m1bandColor);
  Tuple *m1_x_t = dict_find(iter, KEY_m1x);
  Tuple *m1_y_t = dict_find(iter, KEY_m1y);
  Tuple *m1_duration_t = dict_find(iter, KEY_m1duration);
  Tuple *m1_delay_t = dict_find(iter, KEY_m1delay);
  Tuple *m1_outline_t = dict_find(iter, KEY_m1outline );
  Tuple *m1_line_t = dict_find(iter, KEY_m1line );
  Tuple *m1_lines_Color_t = dict_find(iter, KEY_m1linesColor );
  
    if (m1_dir_t) {
     dir[2] = (m1_dir_t->value->int32)-1;
    persist_write_int(KEY_m1_dir, dir[2]+1);
  }

  if (m1_trans_t) {
    no_color_band[2] = m1_trans_t->value->int8;
    persist_write_int(KEY_m1trans, no_color_band[2]);
  }
    if (m1_number_color_t) {
    color[2] = m1_number_color_t->value->int32;
    persist_write_int( KEY_m1numberColor, color[2]+1);
  }
  if (m1_band_color_t) {
    color_band[2] = m1_band_color_t->value->int32;
    persist_write_int( KEY_m1bandColor, color_band[2]+1);
  }
  if (m1_x_t) {
    x[2]  = m1_x_t->value->int32;
    APP_LOG(APP_LOG_LEVEL_DEBUG, "xload:%d",x[2] );
    persist_write_int( KEY_m1x, x[2]-500);
  }
  if (m1_y_t) {
    y[2] = m1_y_t->value->int32;
    persist_write_int( KEY_m1y, y[2]-500);
  }
  if (m1_duration_t) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "duration d" );
    duration[2] = m1_duration_t->value->int32;
    persist_write_int(  KEY_m1duration, duration[2]+50);
  }
  if (m1_delay_t) {
    delay[2] = m1_delay_t->value->int32;
    persist_write_int(  KEY_m1delay, delay[2]+50);
  }
    if (m1_outline_t) {
    outlines[2] = m1_outline_t->value->int8;
    persist_write_int(KEY_m1outline, outlines[2]);
  }
  if (m1_line_t) {
    line[2] = m1_line_t->value->int8;
    persist_write_int(KEY_m1line, line[2]);
  }
  if (m1_lines_Color_t) {
    color_lines[2] = m1_lines_Color_t->value->int32;
    persist_write_int(KEY_m1linesColor, color_lines[2]);
  } 
  
  
  //m2
  Tuple *m2_trans_t = dict_find(iter, KEY_m2trans);
  Tuple *m2_dir_t = dict_find(iter, KEY_m2_dir);
  Tuple *m2_number_color_t = dict_find(iter, KEY_m2numberColor);
  Tuple *m2_band_color_t = dict_find(iter, KEY_m2bandColor);
  Tuple *m2_x_t = dict_find(iter, KEY_m2x);
  Tuple *m2_y_t = dict_find(iter, KEY_m2y);
  Tuple *m2_duration_t = dict_find(iter, KEY_m2duration);
  Tuple *m2_delay_t = dict_find(iter, KEY_m2delay);
  Tuple *m2_outline_t = dict_find(iter, KEY_m2outline );
  Tuple *m2_line_t = dict_find(iter, KEY_m2line );
  Tuple *m2_lines_Color_t = dict_find(iter, KEY_m2linesColor );
  
    if (m2_dir_t) {
     dir[3] = (m2_dir_t->value->int32)-1;
    persist_write_int(KEY_m2_dir, dir[3]+1);
  }

  if (m2_trans_t) {
    no_color_band[3] = m2_trans_t->value->int8;
    persist_write_int(KEY_m2trans, no_color_band[3]);
  }
    if (m2_number_color_t) {
    color[3] = m2_number_color_t->value->int32;
    persist_write_int( KEY_m2numberColor, color[3]+1);
  }
  if (m2_band_color_t) {
    color_band[3] = m2_band_color_t->value->int32;
    persist_write_int( KEY_m2bandColor, color_band[3]+1);
  }
  if (m2_x_t) {
    x[3]  = m2_x_t->value->int32;
    APP_LOG(APP_LOG_LEVEL_DEBUG, "xload:%d",x[3] );
    persist_write_int( KEY_m2x, x[3]-500);
  }
  if (m2_y_t) {
    y[3] = m2_y_t->value->int32;
    persist_write_int( KEY_m2y, y[3]-500);
  }
  if (m2_duration_t) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "duration d" );
    duration[3] = m2_duration_t->value->int32;
    persist_write_int(  KEY_m2duration, duration[3]+50);
  }
  if (m2_delay_t) {
    delay[3] = m2_delay_t->value->int32;
    persist_write_int(  KEY_m2delay, delay[3]+50);
  }
    if (m2_outline_t) {
    outlines[3] = m2_outline_t->value->int8;
    persist_write_int(KEY_m2outline, outlines[3]);
  }
  if (m2_line_t) {
    line[3] = m2_line_t->value->int8;
    persist_write_int(KEY_m2line, line[3]);
  }
  if (m2_lines_Color_t) {
    color_lines[3] = m2_lines_Color_t->value->int32;
    persist_write_int(KEY_m2linesColor, color_lines[3]);
  } 
  //+++++++++++++++++++++++++++++++++++++
  Tuple *number_on_top_t = dict_find(iter, KEY_numberontop);
  
  if (number_on_top_t) {
    numberontop = number_on_top_t->value->int8;
    persist_write_int(KEY_numberontop, numberontop +1);
  }
  
  Tuple *h1posone_t = dict_find(iter, KEY_h1posone);
  
  if (h1posone_t) {
     onepos[0] = (h1posone_t->value->int32);
    persist_write_int(KEY_h1posone, onepos[0]);
  }
  
    Tuple *h2posone_t = dict_find(iter, KEY_h2posone);
  
  if (h2posone_t) {
     onepos[1] = (h2posone_t->value->int32);
    persist_write_int(KEY_h2posone, onepos[1]);
  }
  
  Tuple *m1posone_t = dict_find(iter, KEY_m1posone);
  
  if (m1posone_t) {
     onepos[2] = (m1posone_t->value->int32);
    persist_write_int(KEY_m1posone, onepos[2]);
  }
  
  Tuple *m2posone_t = dict_find(iter, KEY_m2posone);
  
  if (m2posone_t) {
     onepos[3] = (m2posone_t->value->int32);
    persist_write_int(KEY_m2posone, onepos[3]);
  }
  
  
    Tuple *enegy_t = dict_find(iter, KEY_enegy);
  
  if (enegy_t) {
     energy = (enegy_t->value->int32);
    persist_write_int(KEY_enegy, energy);
  if(energy>3){
    taplimiter = 1;
    energy=energy-4;
  }
  if(energy>1){
    noextension = 1;
    energy=energy-2;
  }
  if(energy>0){
    noanimation = 1;
  }
    

  }
  
      Tuple *l1func_t = dict_find(iter, KEY_l1func);
  
  if (l1func_t) {
     layer[0] = (l1func_t->value->int32);
    persist_write_int(KEY_l1func, layer[0]);
  }
  
      Tuple *l2func_t = dict_find(iter, KEY_l2func);
  
  if (l2func_t) {
     layer[1] = (l2func_t->value->int32);
    persist_write_int(KEY_l2func, layer[1]);
  }
  
      Tuple *l3func_t = dict_find(iter, KEY_l3func);
  
  if (l3func_t) {
     layer[2] = (l3func_t->value->int32);
    persist_write_int(KEY_l3func, layer[2]);
  }
  
  Tuple *extension_font_Color_t = dict_find(iter, KEY_extensionfontColor);
  
  if (extension_font_Color_t) {
     color_extension_font = (extension_font_Color_t->value->int32);
    persist_write_int(KEY_extensionfontColor, color_extension_font);
  }
  
  Tuple *extension_back_Color_t = dict_find(iter, KEY_extensionbackColor);
  
  if (extension_back_Color_t) {
     color_extension = (extension_back_Color_t->value->int32);
    persist_write_int(KEY_extensionbackColor, color_extension);
  }
  
  
  
  
  
  
  
  
  
  
  //rest
 
  Tuple *layer1_t = dict_find(iter, KEY_layer1);
  Tuple *layer2_t = dict_find(iter, KEY_layer2);
  Tuple *layer3_t = dict_find(iter, KEY_layer3);
  Tuple *layer4_t = dict_find(iter, KEY_layer4);
  
  Tuple *invertanimationdelay_t = dict_find(iter, KEY_invertanimationdelay);
  Tuple *changeallnumbers_t = dict_find(iter, KEY_changeallnumbers);
  
  if (invertanimationdelay_t) {
    invert_animation_delay = invertanimationdelay_t->value->int8;
    persist_write_int(KEY_invertanimationdelay, invert_animation_delay+1);
  }
  
   if (changeallnumbers_t) {
    change_all_numbers = changeallnumbers_t->value->int8;
    persist_write_int(KEY_invertanimationdelay, change_all_numbers+1);
  }
  
  if (layer1_t) {
    order[0] = layer1_t->value->int32;
    persist_write_int( KEY_layer1, order[0]);
    order[0] = order[0] -1;
    APP_LOG(APP_LOG_LEVEL_DEBUG, "layer1:%d",order[0] );
  }
    if (layer2_t) {
    order[1] = layer2_t->value->int32;
    persist_write_int( KEY_layer2, order[1]);
    order[1] = order[1] -1;
      APP_LOG(APP_LOG_LEVEL_DEBUG, "layer1:%d",order[0] );
  }
    if (layer3_t) {
    order[2] = layer3_t->value->int32;
    persist_write_int( KEY_layer3, order[2]);
    order[2] = order[2] -1;
      APP_LOG(APP_LOG_LEVEL_DEBUG, "layer1:%d",order[0] );
  }
    if (layer4_t) {
    order[3] = layer4_t->value->int32;
    persist_write_int( KEY_layer4, order[3]);
    order[3] = order[3] -1;
      APP_LOG(APP_LOG_LEVEL_DEBUG, "layer1:%d",order[0] );
  }

  layer_mark_dirty(s_path_layer[0]);
  layer_mark_dirty(s_path_layer_band[0]);
  layer_mark_dirty(s_path_layer[1]);
  layer_mark_dirty(s_path_layer_band[1]);
  layer_mark_dirty(s_path_layer[2]);
  layer_mark_dirty(s_path_layer_band[2]);
  layer_mark_dirty(s_path_layer[3]);
  layer_mark_dirty(s_path_layer_band[3]);

  
  
  // Store incoming information
  static char temperature_buffer[8];
  static char conditions_buffer[32];
  static char weather_layer_buffer[32];
  // Read tuples for data
Tuple *temp_tuple = dict_find(iter, KEY_TEMPERATURE);
Tuple *conditions_tuple = dict_find(iter, KEY_CONDITIONS);

// If all data is available, use it
if(temp_tuple && conditions_tuple) {
  snprintf(temperature_buffer, sizeof(temperature_buffer), "%dC", (int)temp_tuple->value->int32);
  snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", conditions_tuple->value->cstring);
  // Assemble full string and display
snprintf(weather_layer_buffer, sizeof(weather_layer_buffer), "%s, %s", temperature_buffer, conditions_buffer);
  if(noextension==0&&weateron==1)text_layer_set_text(s_weather_layer, weather_layer_buffer);
}else{
  
 



  main_window_unload(s_main_window);
  initan=1;
  main_window_load(s_main_window);
  //update_time();
  update_time_minute();
}
  //end
  
  //update_time();
}
void on_animation_stopped(Animation *anim, bool finished, void *context){
  property_animation_destroy((PropertyAnimation*) anim);
}
void on_animation_stopped_extension(Animation *anim, bool finished, void *context){
   APP_LOG(APP_LOG_LEVEL_DEBUG, "stoped");
  property_animation_destroy((PropertyAnimation*) anim);
  if(finished== false){
    animation_schedule(anim);
     APP_LOG(APP_LOG_LEVEL_DEBUG, "restart");
  }
  extension_animation=0;
}
static void animate_extension(Layer *layer){
    
    extension_animation=1;
     GRect start = layer_get_frame(layer);
     GRect finish = layer_get_frame(layer);
     finish.origin.y=-84;
     finish.size.h=PBL_IF_ROUND_ELSE(181, 168)+84;
    //Declare animation
    PropertyAnimation *anim = property_animation_create_layer_frame(layer, &start, &finish);
         AnimationHandlers handlers = {
        //The reference to the stopped handler is the only one in the array
        .stopped = (AnimationStoppedHandler) on_animation_stopped
    };
    animation_set_handlers((Animation*) anim, handlers, NULL);
    //Set characteristics
    animation_set_duration((Animation*) anim, 800);
    //animation_set_delay((Animation*) anim, delay);
    Animation *a =property_animation_get_animation(anim);
    animation_schedule(a);
      
      
    //second animation
     start=finish;
     finish.origin.y=0;
     finish.size.h=PBL_IF_ROUND_ELSE(181, 168)+84;
    PropertyAnimation *anim2 = property_animation_create_layer_frame(layer, &start, &finish);
    AnimationHandlers handlers2 = {
        //The reference to the stopped handler is the only one in the array
        .stopped = (AnimationStoppedHandler) on_animation_stopped_extension
    };
    animation_set_handlers((Animation*) anim2, handlers2, NULL);
    //Set characteristics
    animation_set_duration((Animation*) anim2, 650);
    animation_set_delay((Animation*) anim2, 5000);
    Animation *b =property_animation_get_animation(anim2);
    animation_schedule(b);
  
    
}

static void accel_tap_handler(AccelAxisType axis, int32_t direction){
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "TAP");
  if(taplimiter==1){
    taps++; 
  }
  if(extension_animation==0&&taps<6){
    
    //
    layer_mark_dirty(s_battery_layer);
    
    
  if(healthon==1)heath_update();
    
      time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Write the current hours and minutes into a buffer
  static char s_buffer[16];
    
   switch(layer[0]) {
      case 11: strftime(s_buffer, sizeof(s_buffer), "%d:%m:%Y", tick_time);break;
      default: strftime(s_buffer, sizeof(s_buffer), "%a %d %b", tick_time);break;
    }

  // Show the date
  text_layer_set_text(s_date_layer, s_buffer);
    
    //animate
  Layer *root_layer = window_get_root_layer(s_main_window);
  animate_extension(root_layer);
    
    //layer_mark_dirty(s_battery_layer);
  }
}


static void time_switch(int l,int h){
  gpath_destroy(s_path[l]);
  gpath_destroy(s_path_band[l]);
  isone[l]=0;
  
     switch(h) {
    case 1: s_path[l] = gpath_create(&PATH_1);
       isone[l]=1;
       switch(dir[l]) {
         case 0:   //up
            PATH_line_up_1(l);
            s_path_band[l] = gpath_create(&PATH_band_up_1);break;
         case 1:   //up-right
            PATH_line_up_right_1(l);
            s_path_band[l] = gpath_create(&PATH_band_up_right_1);break;
          case 2:   //right
            PATH_line_right_1(l);
            s_path_band[l] = gpath_create(&PATH_band_right_1);break;
         case 3:   //down-right
            PATH_line_down_right_1(l);
            s_path_band[l] = gpath_create(&PATH_band_down_right_1);break;
         case 4:   //down
            PATH_line_down_1(l);
            s_path_band[l] = gpath_create(&PATH_band_down_1);break;
         case 5:   //down-left
            PATH_line_down_left_1(l);
            s_path_band[l] = gpath_create(&PATH_band_down_left_1);break;
         case 6:   //left
            PATH_line_left_1(l);
            s_path_band[l] = gpath_create(&PATH_band_left_1);break;
         case 7:   //up-left
            PATH_line_up_left_1(l);
            s_path_band[l] = gpath_create(&PATH_band_up_left_1);break;
       }
     break;
    case 2: s_path[l] = gpath_create(&PATH_2);
       switch(dir[l]) {
         case 0:   //up
            PATH_line_up_2(l);
            s_path_band[l] = gpath_create(&PATH_band_up_2);break;
         case 1:   //up-right
            PATH_line_up_right_2(l);
            s_path_band[l] = gpath_create(&PATH_band_up_right_2);break;
         case 2:   //right
            PATH_line_right_2(l);
            s_path_band[l] = gpath_create(&PATH_band_right_2);break;
         case 3:   //down-right
            PATH_line_down_right_2(l);
            s_path_band[l] = gpath_create(&PATH_band_down_right_2);break;
         case 4:   //down
            PATH_line_down_2(l);
            s_path_band[l] = gpath_create(&PATH_band_down_2);break;
         case 5:   //down-left
            PATH_line_down_left_2(l);
            s_path_band[l] = gpath_create(&PATH_band_down_left_2);break;
         case 6:   //left
            PATH_line_left_2(l);
            s_path_band[l] = gpath_create(&PATH_band_left_2);break;
         case 7:   //up-left
            PATH_line_up_left_2(l);
            s_path_band[l] = gpath_create(&PATH_band_up_left_2);break;
       }
     break;
    case 3: s_path[l] = gpath_create(&PATH_3);
       switch(dir[l]) {
         case 0:   //up
            PATH_line_up_3(l);
            s_path_band[l] = gpath_create(&PATH_band_up_3);break;
         case 1:   //up-right
            PATH_line_up_right_3(l);
            s_path_band[l] = gpath_create(&PATH_band_up_right_3);break;
         case 2:   //right
            PATH_line_right_3(l);
            s_path_band[l] = gpath_create(&PATH_band_right_3);break;
         case 3:   //down-right
            PATH_line_down_right_3(l);
            s_path_band[l] = gpath_create(&PATH_band_down_right_3);break;
         case 4:   //down
            PATH_line_down_3(l);
            s_path_band[l] = gpath_create(&PATH_band_down_3);break;
         case 5:   //down-left
            PATH_line_down_left_3(l);
            s_path_band[l] = gpath_create(&PATH_band_down_left_3);break;
         case 6:   //left
            PATH_line_left_3(l);
            s_path_band[l] = gpath_create(&PATH_band_left_3);break;
         case 7:   //up-left
            PATH_line_up_left_3(l);
            s_path_band[l] = gpath_create(&PATH_band_up_left_3);break;
         
       }
     break;
    case 4: s_path[l] = gpath_create(&PATH_4);
       switch(dir[l]) {
         case 0:   //up
            PATH_line_up_4(l);
            s_path_band[l] = gpath_create(&PATH_band_up_4);break;
         case 1:   //up-right
            PATH_line_up_right_4(l);
            s_path_band[l] = gpath_create(&PATH_band_up_right_4);break;
         case 2:   //right
            PATH_line_right_4(l);
            s_path_band[l] = gpath_create(&PATH_band_right_4);break;
         case 3:   //down-right
            PATH_line_down_right_4(l);
            s_path_band[l] = gpath_create(&PATH_band_down_right_4);break;
         case 4:   //down
            PATH_line_down_4(l);
            s_path_band[l] = gpath_create(&PATH_band_down_4);break;
         case 5:   //down-left
            PATH_line_down_left_4(l);
            s_path_band[l] = gpath_create(&PATH_band_down_left_4);break;
         case 6:   //left
            PATH_line_left_4(l);
            s_path_band[l] = gpath_create(&PATH_band_left_4);break;
         case 7:   //up-left
            PATH_line_up_left_4(l);
            s_path_band[l] = gpath_create(&PATH_band_up_left_4);break;
       }
     break;
    case 5: s_path[l] = gpath_create(&PATH_5);
       switch(dir[l]) {
         case 0:   //up
            PATH_line_up_5(l);
            s_path_band[l] = gpath_create(&PATH_band_up_5);break;
         case 1:   //up-right
            PATH_line_up_right_5(l);
            s_path_band[l] = gpath_create(&PATH_band_up_right_5);break;
         case 2:   //right
            PATH_line_right_5(l);
            s_path_band[l] = gpath_create(&PATH_band_right_5);break;
         case 3:   //down-right
            PATH_line_down_right_5(l);
            s_path_band[l] = gpath_create(&PATH_band_down_right_5);break;
         case 4:   //down
            PATH_line_down_5(l);
            s_path_band[l] = gpath_create(&PATH_band_down_5);break;
         case 5:   //down-left
            PATH_line_down_left_5(l);
            s_path_band[l] = gpath_create(&PATH_band_down_left_5);break;
         case 6:   //left
            PATH_line_left_5(l);
            s_path_band[l] = gpath_create(&PATH_band_left_5);break;
         case 7:   //up-left
            PATH_line_up_left_5(l);
            s_path_band[l] = gpath_create(&PATH_band_up_left_5);break;
       }
     break;
    case 6: s_path[l] = gpath_create(&PATH_6);
       switch(dir[l]) {
         case 0:   //up
            PATH_line_up_6(l);
            s_path_band[l] = gpath_create(&PATH_band_up_6);break;
         case 1:   //up-right
            PATH_line_up_right_6(l);
            s_path_band[l] = gpath_create(&PATH_band_up_right_6);break;
         case 2:   //right
            PATH_line_right_6(l);
            s_path_band[l] = gpath_create(&PATH_band_right_6);break;
         case 3:   //down-right
            PATH_line_down_right_6(l);
            s_path_band[l] = gpath_create(&PATH_band_down_right_6);break;
         case 4:   //down
            PATH_line_down_6(l);
            s_path_band[l] = gpath_create(&PATH_band_down_6);break;
         case 5:   //down-left
            PATH_line_down_left_6(l);
            s_path_band[l] = gpath_create(&PATH_band_down_left_6);break;
         case 6:   //left
            PATH_line_left_6(l);
            s_path_band[l] = gpath_create(&PATH_band_left_6);break;
         case 7:   //up-left
            PATH_line_up_left_6(l);
            s_path_band[l] = gpath_create(&PATH_band_up_left_6);break;
       }
     break;
    case 7: s_path[l] = gpath_create(&PATH_7);
       switch(dir[l]) {
         case 0:   //up
            PATH_line_up_7(l);
            s_path_band[l] = gpath_create(&PATH_band_up_7);break;
         case 1:   //up-right
            PATH_line_up_right_7(l);
            s_path_band[l] = gpath_create(&PATH_band_up_right_7);break;
         case 2:   //right
            PATH_line_right_7(l);
            s_path_band[l] = gpath_create(&PATH_band_right_7);break;
         case 3:   //down-right
            PATH_line_down_right_7(l);
            s_path_band[l] = gpath_create(&PATH_band_down_right_7);break;
         case 4:   //down
            PATH_line_down_7(l);
            s_path_band[l] = gpath_create(&PATH_band_down_7);break;
         case 5:   //down-left
            PATH_line_down_left_7(l);
            s_path_band[l] = gpath_create(&PATH_band_down_left_7);break;
         case 6:   //left
            PATH_line_left_7(l);
            s_path_band[l] = gpath_create(&PATH_band_left_7);break;
         case 7:   //up-left
            PATH_line_up_left_7(l);
            s_path_band[l] = gpath_create(&PATH_band_up_left_7);break;
       }
     break;
    case 8: s_path[l] = gpath_create(&PATH_8);
       switch(dir[l]) {
         case 0:   //up
            PATH_line_up_8(l);
            s_path_band[l] = gpath_create(&PATH_band_up_8);break;
         case 1:   //up-right
            PATH_line_up_right_8(l);
            s_path_band[l] = gpath_create(&PATH_band_up_right_8);break;
         case 2:   //right
            PATH_line_right_8(l);
            s_path_band[l] = gpath_create(&PATH_band_right_8);break;
         case 3:   //down-right
            PATH_line_down_right_8(l);
            s_path_band[l] = gpath_create(&PATH_band_down_right_8);break;
         case 4:   //down
            PATH_line_down_8(l);
            s_path_band[l] = gpath_create(&PATH_band_down_8);break;
         case 5:   //down-left
            PATH_line_down_left_8(l);
            s_path_band[l] = gpath_create(&PATH_band_down_left_8);break;
         case 6:   //left
            PATH_line_left_8(l);
            s_path_band[l] = gpath_create(&PATH_band_left_8);break;
         case 7:   //up-left
            PATH_line_up_left_8(l);
            s_path_band[l] = gpath_create(&PATH_band_up_left_8);break;
       }
     break;
    case 9: s_path[l] = gpath_create(&PATH_9);
       switch(dir[l]) {
         case 0:   //up
            PATH_line_up_9(l);
            s_path_band[l] = gpath_create(&PATH_band_up_9);break;
         case 1:   //up-right
            PATH_line_up_right_9(l);
            s_path_band[l] = gpath_create(&PATH_band_up_right_9);break;
         case 2:   //right
            PATH_line_right_9(l);
            s_path_band[l] = gpath_create(&PATH_band_right_9);break;
         case 3:   //down-right
            PATH_line_down_right_9(l);
            s_path_band[l] = gpath_create(&PATH_band_down_right_9);break;
         case 4:   //down
            PATH_line_down_9(l);
            s_path_band[l] = gpath_create(&PATH_band_down_9);break;
         case 5:   //down-left
            PATH_line_down_left_9(l);
            s_path_band[l] = gpath_create(&PATH_band_down_left_9);break;
         case 6:   //left
            PATH_line_left_9(l);
            s_path_band[l] = gpath_create(&PATH_band_left_9);break;
         case 7:   //up-left
            PATH_line_up_left_9(l);
            s_path_band[l] = gpath_create(&PATH_band_up_left_9);break;
       }
     break;
    case 0: s_path[l] = gpath_create(&PATH_0);
       switch(dir[l]) {
         case 0:   //up
            PATH_line_up_0(l);
            s_path_band[l] = gpath_create(&PATH_band_up_0);break;
         case 1:   //up-right
            PATH_line_up_right_0(l);
            s_path_band[l] = gpath_create(&PATH_band_up_right_0);break;
         case 2:   //right
            PATH_line_right_0(l);
            s_path_band[l] = gpath_create(&PATH_band_right_0);break;
         case 3:   //down-right
            PATH_line_down_right_0(l);
            s_path_band[l] = gpath_create(&PATH_band_down_right_0);break;
         case 4:   //down
            PATH_line_down_0(l);
            s_path_band[l] = gpath_create(&PATH_band_down_0);break;
         case 5:   //down-left
            PATH_line_down_left_0(l);
            s_path_band[l] = gpath_create(&PATH_band_down_left_0);break;
         case 6:   //left
            PATH_line_left_0(l);
            s_path_band[l] = gpath_create(&PATH_band_left_0);break;
         case 7:   //up-left
            PATH_line_up_left_0(l);
            s_path_band[l] = gpath_create(&PATH_band_up_left_0);break;
       }
     break;
  }
}
static void layer_update_proc(Layer *layer, GContext *ctx) {
  int l=0;
  if(layer==s_path_layer_band[0]||layer==s_path_layer[0]) l=0;
  if(layer==s_path_layer_band[1]||layer==s_path_layer[1]) l=1;
  if(layer==s_path_layer_band[2]||layer==s_path_layer[2]) l=2;
  if(layer==s_path_layer_band[3]||layer==s_path_layer[3]) l=3;
  
  
  if(layer==s_path_layer_band[l]){
    graphics_context_set_fill_color(ctx, GColorFromHEX(color_band[l]));
    if(outlines[l]==true){
      graphics_context_set_stroke_color(ctx, GColorFromHEX(color_lines[l]));}else{
      graphics_context_set_stroke_color(ctx, GColorFromHEX(color_band[l]));}
    if(no_color_band[l]==false)gpath_draw_filled(ctx, s_path_band[l]);
    if((no_color_band[l]==true&&outlines[l]==true)||no_color_band[l]==false)gpath_draw_outline(ctx, s_path_band[l]);
    //
    if(line[l]==true){
    switch( s_path_lines[l].points-1) {
        case 7:   
    graphics_context_set_stroke_color(ctx, GColorFromHEX(color_lines[l]));
    graphics_draw_line(ctx, s_path_lines[l].p0[7], s_path_lines[l].p1[7]);
        case 6:   
    graphics_context_set_stroke_color(ctx, GColorFromHEX(color_lines[l]));
    graphics_draw_line(ctx, s_path_lines[l].p0[6], s_path_lines[l].p1[6]);
        case 5:  
    graphics_context_set_stroke_color(ctx, GColorFromHEX(color_lines[l]));
    graphics_draw_line(ctx, s_path_lines[l].p0[5], s_path_lines[l].p1[5]);
        case 4:  
    graphics_context_set_stroke_color(ctx, GColorFromHEX(color_lines[l]));
    graphics_draw_line(ctx, s_path_lines[l].p0[4], s_path_lines[l].p1[4]);
        case 3:   
    graphics_context_set_stroke_color(ctx, GColorFromHEX(color_lines[l]));
    graphics_draw_line(ctx, s_path_lines[l].p0[3], s_path_lines[l].p1[3]);
        case 2:   
    graphics_context_set_stroke_color(ctx, GColorFromHEX(color_lines[l]));
    graphics_draw_line(ctx, s_path_lines[l].p0[2], s_path_lines[l].p1[2]);
        case 1:  
    graphics_context_set_stroke_color(ctx, GColorFromHEX(color_lines[l]));
    graphics_draw_line(ctx, s_path_lines[l].p0[1], s_path_lines[l].p1[1]);
        case 0:  
    graphics_context_set_stroke_color(ctx, GColorFromHEX(color_lines[l]));
    graphics_draw_line(ctx, s_path_lines[l].p0[0], s_path_lines[l].p1[0]);
        case -1:
      break;
    }
    }
    //
  }
  else{
    graphics_context_set_fill_color(ctx, GColorFromHEX(color[l]));
    gpath_draw_filled(ctx, s_path[l]);
  }
}
static void layer_update_proc_extension(Layer *layer, GContext *ctx){
  graphics_context_set_fill_color(ctx, GColorFromHEX(color_extension));
  gpath_draw_filled(ctx, s_path_extension);
}
static void battery_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);

  // Find the width of the bar

  //int width = (int)(float)(((float)s_battery_level / 100.0F) * 114.0F);
  //int width = (int)(float)(((float)s_battery_level / 100.0F) * 144.0F);
  int width = (int)(float)(((float)s_battery_level / 100.0F) * PBL_IF_ROUND_ELSE(181.0F, 144.0F));
  
  
  // Draw the background
  graphics_context_set_fill_color(ctx, GColorFromHEX(color_extension));
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);

  // Draw the bar
  graphics_context_set_fill_color(ctx, GColorFromHEX(color_extension_font));
  graphics_fill_rect(ctx, GRect(0, 0, width, bounds.size.h), 0, GCornerNone);
}

static void animate_layer(Layer *layerband, GRect *startband, GRect *finishband,Layer *layer, GRect *start, GRect *finish, int duration, int delay){
    //Declare animation
    PropertyAnimation *anim = property_animation_create_layer_frame(layer, start, finish);
         AnimationHandlers handlers = {
        //The reference to the stopped handler is the only one in the array
        .stopped = (AnimationStoppedHandler) on_animation_stopped
    };
    animation_set_handlers((Animation*) anim, handlers, NULL);
    //Set characteristics
    animation_set_duration((Animation*) anim, duration);
    animation_set_delay((Animation*) anim, delay);
    Animation *a =property_animation_get_animation(anim);
 
    PropertyAnimation *animband = property_animation_create_layer_frame(layerband, startband, finishband);
    animation_set_handlers((Animation*) animband, handlers, NULL);
    //Set characteristics
    animation_set_duration((Animation*) animband, duration);
    animation_set_delay((Animation*) animband, delay);
    Animation *b = property_animation_get_animation(animband);
    // Create the spawn animation
    Animation *spawn = animation_spawn_create(a, b, NULL);

    // Play the animation
    animation_schedule(spawn);
  
  
  
    //Set stopped handler to free memory
   /* AnimationHandlers handlers = {
        //The reference to the stopped handler is the only one in the array
        .stopped = (AnimationStoppedHandler) on_animation_stopped
    };
    animation_set_handlers((Animation*) anim, handlers, NULL);*/
 
    //Start animation!
    //animation_schedule((Animation*) anim);
}
static void annimation(int l,int rev){
  GRect from_frame ;
  GRect to_frame ;
  GRect from_frame_band ;
  GRect to_frame_band ;
  int outside = 0;
  int xi=x[l];
  //one pos
  if(isone[l]==1){
    if(onepos[l]==2)xi = xi - 17;
    if(onepos[l]==1)xi = xi - 8;
  }
  //
  switch(dir[l]) {
    case 0:   //up
      if(rev==0)outside = y[l] + 80;
      from_frame = layer_get_frame(s_path_layer[l]);
      to_frame = GRect( xi, y[l]-outside, 25 , 50);
      from_frame_band = layer_get_frame(s_path_layer_band[l]);
      to_frame_band = GRect( xi, y[l]-outside-180, 25 , 180+50);
      //vorübergenend
    if(invert_animation_delay==0||rev==1){
      animate_layer(s_path_layer_band[l] ,&from_frame_band,&to_frame_band , s_path_layer[l],&from_frame,&to_frame ,duration[l] , delay[l]);
    }else{animate_layer(s_path_layer_band[l] ,&from_frame_band,&to_frame_band , s_path_layer[l],&from_frame,&to_frame ,duration[l] ,max_delay-delay[l]);}
      break;
    case 1:   //up-right
      if(rev==0)outside = y[l] + 80;
      from_frame = layer_get_frame(s_path_layer[l]);
      to_frame = GRect( xi+outside, y[l]-outside, 25 , 50);
      from_frame_band = layer_get_frame(s_path_layer_band[l]);
      to_frame_band = GRect( xi+outside, y[l]-outside-180, 25+180+50 , 50+180);
      //vorübergenend
    if(invert_animation_delay==0||rev==1){
      animate_layer(s_path_layer_band[l] ,&from_frame_band,&to_frame_band , s_path_layer[l],&from_frame,&to_frame ,duration[l] , delay[l]);
    }else{animate_layer(s_path_layer_band[l] ,&from_frame_band,&to_frame_band , s_path_layer[l],&from_frame,&to_frame ,duration[l] ,max_delay-delay[l]);}
          break;
    case 2:   //right
      if(rev==0)outside = 180 - xi + 80;
      from_frame = layer_get_frame(s_path_layer[l]);
      to_frame = GRect( xi+outside, y[l], 25 , 50);
      from_frame_band = layer_get_frame(s_path_layer_band[l]);
      to_frame_band = GRect( xi+outside, y[l], 25+180+50 , 50);
      //vorübergenend
    if(invert_animation_delay==0||rev==1){
      animate_layer(s_path_layer_band[l] ,&from_frame_band,&to_frame_band , s_path_layer[l],&from_frame,&to_frame ,duration[l] , delay[l]);
    }else{animate_layer(s_path_layer_band[l] ,&from_frame_band,&to_frame_band , s_path_layer[l],&from_frame,&to_frame ,duration[l] ,max_delay-delay[l]);}
      break;
    case 3:   //down-right
      if(rev==0)outside = 180 - y[l] + 80;
      from_frame = layer_get_frame(s_path_layer[l]);
      to_frame = GRect( xi+outside, y[l]+outside, 25 , 50);
      from_frame_band = layer_get_frame(s_path_layer_band[l]);
      to_frame_band = GRect( xi+outside, y[l]+outside, 25+180+50 , 50+180);
      //vorübergenend
    if(invert_animation_delay==0||rev==1){
      animate_layer(s_path_layer_band[l] ,&from_frame_band,&to_frame_band , s_path_layer[l],&from_frame,&to_frame ,duration[l] , delay[l]);
      }else{animate_layer(s_path_layer_band[l] ,&from_frame_band,&to_frame_band , s_path_layer[l],&from_frame,&to_frame ,duration[l] ,max_delay-delay[l]);}  
      break;
    case 4:   //down
      if(rev==0)outside = 180 - y[l] + 80;
      from_frame = layer_get_frame(s_path_layer[l]);
      to_frame = GRect( xi, y[l]+outside, 25 , 50);
      from_frame_band = layer_get_frame(s_path_layer_band[l]);
      to_frame_band = GRect( xi, y[l]+outside, 25 , 180+50);
      //vorübergenend
    if(invert_animation_delay==0||rev==1){
      animate_layer(s_path_layer_band[l] ,&from_frame_band,&to_frame_band , s_path_layer[l],&from_frame,&to_frame ,duration[l] , delay[l]);
    }else{animate_layer(s_path_layer_band[l] ,&from_frame_band,&to_frame_band , s_path_layer[l],&from_frame,&to_frame ,duration[l] ,max_delay-delay[l]);}
      break;
    case 5:   //down-left
      if(rev==0)outside = 180 - y[l] + 80;
      from_frame = layer_get_frame(s_path_layer[l]);
      to_frame = GRect( xi-outside, y[l]+outside, 25 , 50);
      from_frame_band = layer_get_frame(s_path_layer_band[l]);
      to_frame_band = GRect( xi-outside-180-50, y[l]+outside, 25+180+50 , 50+180);
      //vorübergenend
    if(invert_animation_delay==0||rev==1){
      animate_layer(s_path_layer_band[l] ,&from_frame_band,&to_frame_band , s_path_layer[l],&from_frame,&to_frame ,duration[l] , delay[l]);
    }else{animate_layer(s_path_layer_band[l] ,&from_frame_band,&to_frame_band , s_path_layer[l],&from_frame,&to_frame ,duration[l] ,max_delay-delay[l]);}

      break;
    case 6:   //left
      if(rev==0)outside = xi + 80;
      from_frame = layer_get_frame(s_path_layer[l]);
      to_frame = GRect( xi-outside, y[l], 25 , 50);
      from_frame_band = layer_get_frame(s_path_layer_band[l]);
      to_frame_band = GRect( xi-outside-180-50, y[l], 25+180+50 , 50);
      //vorübergenend
    if(invert_animation_delay==0||rev==1){
      animate_layer(s_path_layer_band[l] ,&from_frame_band,&to_frame_band , s_path_layer[l],&from_frame,&to_frame ,duration[l] , delay[l]);
    }else{animate_layer(s_path_layer_band[l] ,&from_frame_band,&to_frame_band , s_path_layer[l],&from_frame,&to_frame ,duration[l] ,max_delay-delay[l]);}
      break;
    case 7:   //up-left
      if(rev==0)outside = y[l] + 80;
      from_frame = layer_get_frame(s_path_layer[l]);
      to_frame = GRect( xi-outside, y[l]-outside, 25 , 50);
      from_frame_band = layer_get_frame(s_path_layer_band[l]);
      to_frame_band = GRect( xi-outside-180-50, y[l]-outside-180, 25+180+50 , 50+180);
      //vorübergenend
    if(invert_animation_delay==0||rev==1){
      animate_layer(s_path_layer_band[l] ,&from_frame_band,&to_frame_band , s_path_layer[l],&from_frame,&to_frame ,duration[l] , delay[l]);
    }else{animate_layer(s_path_layer_band[l] ,&from_frame_band,&to_frame_band , s_path_layer[l],&from_frame,&to_frame ,duration[l] ,max_delay-delay[l]);}
      break;
  }
}

static void outgoing_callback(){
  if(extension_animation==0) animation_unschedule_all();
  /*if(change_all_numbers==1||(s_buffer[4]-'0'==9&&s_buffer[3]-'0'==5&&(s_buffer[1]-'0'==9||s_buffer[1]-'0'==1||s_buffer[1]-'0'==3)))annimation(0,0);
  if(change_all_numbers==1||(s_buffer[4]-'0'==9&&s_buffer[3]-'0'==5)) annimation(1,0);
  if(change_all_numbers==1||(s_buffer[4]-'0'==9))annimation(2,0);*/
  //int *g = l;
  if(changenumber>2)annimation(0,0);
  if(changenumber>1)annimation(1,0);
  if(changenumber>0)annimation(2,0);
  annimation(3,0);
}

static void demo(){
  Layer *root_layer = window_get_root_layer(s_main_window);
    animate_extension(root_layer);
  
}

static void update_time_minute() {
  taps=0;
  
  
     /* Layer *root_layer = window_get_root_layer(s_main_window);
    animate_extension(root_layer);*/
 // AppTimer *demo2 = app_timer_register(3000, demo, (void*)1);
   //demo2 
  
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Write the current hours and minutes into a buffer
  static char s_buffer[16];
  strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
                                          "%H:%M" : "%I:%M", tick_time);
  
  int seconds = tick_time->tm_sec;
  
  //if(seconds == 0 || initan == 1){
  //int l = 0;
  //int h= s_buffer[0]-'0';
  time_switch(0,s_buffer[0]-'0');
  time_switch(1,s_buffer[1]-'0');
  time_switch(2,s_buffer[3]-'0');
  time_switch(3,s_buffer[4]-'0');
  
  
  
  /*      time_switch(0,1);
  time_switch(1,3);
  time_switch(2,3);
  time_switch(3,7);*/
  
  
  
  text_layer_set_text(s_time_layer, s_buffer);
  //}
  //second berechnung
  int sec=1000;
  if(sec < delay[0]+duration[0])sec=delay[0]+duration[0];
  if(sec < delay[1]+duration[1])sec=delay[1]+duration[1];
  if(sec < delay[2]+duration[2])sec=delay[2]+duration[2];
  if(sec < delay[3]+duration[3])sec=delay[3]+duration[3];
  max_delay=sec;
  //sec = (sec / 1000)+2;
  //
  //TODO: 24 or 12 hour
  /*if(seconds == (60-sec)){
   if(extension_animation==0) animation_unschedule_all();
  if(change_all_numbers==1||(s_buffer[4]-'0'==9&&s_buffer[3]-'0'==5&&(s_buffer[1]-'0'==9||s_buffer[1]-'0'==1||s_buffer[1]-'0'==3)))annimation(0,0);
  if(change_all_numbers==1||(s_buffer[4]-'0'==9&&s_buffer[3]-'0'==5)) annimation(1,0);
  if(change_all_numbers==1||(s_buffer[4]-'0'==9))annimation(2,0);
  annimation(3,0);
  */ //}
  
  //int vorubergehen = initan; //kann später gelöscht werden
  
  
  if(noanimation == 0 || initan == 1){
  if(extension_animation==0)  animation_unschedule_all();
  annimation(0,1);
  annimation(1,1);
  annimation(2,1);
  annimation(3,1);
  
  }
  
  
  
  if(noanimation==0){
  
  if(change_all_numbers==1){
    changenumber = 3;
  
  }else{
      tick_time->tm_sec += 60;
  mktime(tick_time);
  strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
                                         "%H:%M" : "%I:%M", tick_time);
    
    
   changenumber = 0;
  if(s_buffer[4]-'0'==0){
    changenumber = 1;
    if(s_buffer[3]-'0'==0){
      changenumber = 2;
      if(s_buffer[1]-'0'==0){
        changenumber = 3;
      }
    }
  } 
  }
  
  
  int timert = 59000-max_delay-(seconds*1000);
    //if(initan==1)timert=timert-2000;
    if(seconds!=0)timert=timert-1000;
  
  if(timert>0)outgoing = app_timer_register(timert, outgoing_callback, (void*)1);
  }
  initan=0;
}
static void update_time() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Write the current hours and minutes into a buffer
  static char s_buffer[16];
  strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
                                          "%H:%M" : "%I:%M", tick_time);
  
  int seconds = tick_time->tm_sec;
  
  if(seconds == 0 || initan == 1){
    //demo
   /*   time_switch(0,1);
  time_switch(1,3);
  time_switch(2,3);
  time_switch(3,7);*/
  
    //d
    
  //int l = 0;
  //int h= s_buffer[0]-'0';
    
  time_switch(0,s_buffer[0]-'0');
  time_switch(1,s_buffer[1]-'0');
  time_switch(2,s_buffer[3]-'0');
  time_switch(3,s_buffer[4]-'0');
  
  text_layer_set_text(s_time_layer, s_buffer);
  }
  //second berechnung
  int sec=1000;
  if(sec < delay[0]+duration[0])sec=delay[0]+duration[0];
  if(sec < delay[1]+duration[1])sec=delay[1]+duration[1];
  if(sec < delay[2]+duration[2])sec=delay[2]+duration[2];
  if(sec < delay[3]+duration[3])sec=delay[3]+duration[3];
  max_delay=sec;
  sec = (sec / 1000)+2;
  //
  //TODO: 24 or 12 hour
  if(seconds == (60-sec)){
   if(extension_animation==0) animation_unschedule_all();
  if(change_all_numbers==1||(s_buffer[4]-'0'==9&&s_buffer[3]-'0'==5&&(s_buffer[1]-'0'==9||s_buffer[1]-'0'==1||s_buffer[1]-'0'==3)))annimation(0,0);
  if(change_all_numbers==1||(s_buffer[4]-'0'==9&&s_buffer[3]-'0'==5)) annimation(1,0);
  if(change_all_numbers==1||(s_buffer[4]-'0'==9))annimation(2,0);
  annimation(3,0);
  }
  
  //int vorubergehen = initan; //kann später gelöscht werden
  
  
  if(seconds == 0 || initan == 1){
  if(extension_animation==0)  animation_unschedule_all();
  annimation(0,1);
  annimation(1,1);
  annimation(2,1);
  annimation(3,1);
  initan=0;
  }
  
    //test
  /*
  if(seconds == 10||seconds == 30||seconds == 50){
    Layer *root_layer = window_get_root_layer(s_main_window);
    animate_extension(root_layer);
  }
  //
  */
  /*
  if(vorubergehen==1){
  Layer *root_layer = window_get_root_layer(s_main_window);
     GRect from_frame = layer_get_frame(root_layer);
     GRect to_frame = layer_get_frame(root_layer);
     to_frame.origin.y=-84;
     to_frame.size.h=168+84;
     
     int l = 0;
  
      animate_extension(root_layer,&from_frame,&to_frame ,duration[l] , delay[l]);
  }
  // 
  */
  /*
  //date
  // Copy date into buffer from tm structure
  strftime(s_buffer, sizeof(s_buffer), "%a %d %b", tick_time);
  // Show the date
  //TODO: actualisirungsrate
  text_layer_set_text(s_date_layer, s_buffer);
  */
  
  
}
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
//update_time();
  update_time_minute();
  
  
  // Get weather update every 30 minutes
if(noextension==0&&weateron==1)if(tick_time->tm_min % 30 == 0) {
  // Begin dictionary
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  // Add a key-value pair
  dict_write_uint8(iter, 0, 0);

  // Send the message!
  app_message_outbox_send();
}
}
static void load_band(Layer *window_layer){
  int outside=0;
  switch(dir[n]) {
    case 0:   //up
      outside = y[n] + 80;
      s_path_band[n] = gpath_create(&PATH_band_up_0);
      PATH_line_up_0(n); 
      s_path_layer_band[n] = layer_create( GRect( x[n], y[n]-outside-180, 25 , 50+180) ); break;
    case 1:   //up-right
      outside = y[n] + 80;
      s_path_band[n] = gpath_create(&PATH_band_up_right_0);
      PATH_line_up_right_0(n); 
      s_path_layer_band[n] = layer_create( GRect(x[n]+outside, y[n]-180-outside, 25+180+50 , 50+180)   ); 
      break;
    case 2:   //right
      outside = 180 - x[n] + 80;
      s_path_band[n] = gpath_create(&PATH_band_right_0); 
      PATH_line_right_0(n); 
      s_path_layer_band[n] = layer_create( GRect( x[n]+outside, y[n], 25+180+50 , 50) ); break;
    case 3:   //down-right
      outside = 180 - y[n] + 80;
      s_path_band[n] = gpath_create(&PATH_band_down_right_0);
      PATH_line_down_right_0(n);
      s_path_layer_band[n] = layer_create( GRect( x[n]+outside, y[n]+outside, 25+180+50 , 50+180) ); break;
    case 4:   //down
      outside = 180 - y[n] + 80;
      s_path_band[n] = gpath_create(&PATH_band_down_0); // ****************************
      PATH_line_down_0(n); //+++++++++++++++
      s_path_layer_band[n] = layer_create( GRect( x[n], y[n]+outside, 25 , 50+180) ); break;
    case 5:   //down-left
      outside = 180 - y[n] + 80;
      s_path_band[n] = gpath_create(&PATH_band_down_left_0); 
      PATH_line_down_left_0(n); 
      s_path_layer_band[n] = layer_create( GRect( x[n]-180-50-outside, y[n]+outside, 25+180+50 , 50+180) ); break;
    case 6:   //left
      outside = x[n] + 80;
      s_path_band[n] = gpath_create(&PATH_band_left_0);
      PATH_line_left_0(n);
      s_path_layer_band[n] = layer_create( GRect( x[n]-180-50-outside, y[n], 25+180+50 , 50) ); break;
    
    case 7:   //up-left
      outside = y[n] + 80;
      s_path_band[n] = gpath_create(&PATH_band_up_left_0);  
      PATH_line_up_left_0(n); 
      s_path_layer_band[n] = layer_create( GRect(x[n]-outside-180-50, y[n]-180-outside, 25+180+50 , 50+180)   ); break;
  }  
  layer_set_update_proc(s_path_layer_band[n], layer_update_proc);
  layer_add_child(window_layer, s_path_layer_band[n]);  
}
static void load_number(Layer *window_layer){
  int outside=0;
  switch(dir[n]) {
    case 0:   //up
      outside = y[n] + 80;
      s_path_layer[n]  = layer_create( GRect( x[n], y[n]-outside, 25 , 50) );break;
    case 1:   //up-right
      outside = y[n] + 80;
      s_path_layer[n]  = layer_create( GRect( x[n]+outside, y[n]-outside, 25 , 50) );break;
    case 2:   //right
      outside = 180 - x[n] + 80;
      s_path_layer[n]  = layer_create( GRect( x[n]+outside, y[n], 25 , 50) );break;
    case 3:   //down-left
      outside = 180 - y[n] + 80;
      s_path_layer[n]  = layer_create( GRect( x[n]+outside, y[n]+outside, 25 , 50) );break;
    case 4:   //up
      outside = 180 - y[n] + 80;
      s_path_layer[n]  = layer_create( GRect( x[n], y[n]+outside, 25 , 50) );break;
    case 5:   //down-left
      outside = 180 - y[n] + 80;
      s_path_layer[n]  = layer_create( GRect( x[n]-outside, y[n]+outside, 25 , 50) );break;
    case 6:   //left
      outside = x[n] + 80;
      s_path_layer[n]  = layer_create( GRect( x[n]-outside, y[n], 25 , 50) );break;
    case 7:   //up-left
      outside = y[n] + 80;
      s_path_layer[n]  = layer_create( GRect( x[n]-outside, y[n]-outside, 25 , 50) );break;
  }
  //Number
  s_path[n] = gpath_create(&PATH_0); // ************
  //s_path_layer[n]  = layer_create( GRect( x[n], y[n], 25 , 50) );//GRect( x[n]+100, y[n]-100, 25 , 50) );
  layer_set_update_proc(s_path_layer[n], layer_update_proc);
  layer_add_child(window_layer, s_path_layer[n]);
}
static void load_extension(Layer *window_layer){
  if(layer[1]==99)weateron=0;
  s_path_layer_extension  = layer_create( GRect( -1 , PBL_IF_ROUND_ELSE(180, 168) , PBL_IF_ROUND_ELSE(181, 145) , 85) );
  layer_set_update_proc(s_path_layer_extension, layer_update_proc_extension);
  s_path_extension = gpath_create(&extension_path);
  layer_add_child(window_layer, s_path_layer_extension);  
  int layerstart=0;
  //if(layer[0]==1){
  //date
  s_date_layer = text_layer_create(GRect(1, layerstart, PBL_IF_ROUND_ELSE(181, 144), 30));
  text_layer_set_text_color(s_date_layer, GColorFromHEX(color_extension_font));
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);
  text_layer_set_text(s_date_layer, "Wed 10 Jan");
  text_layer_set_font(s_date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  layer_add_child(s_path_layer_extension,text_layer_get_layer(s_date_layer));
    layerstart=layerstart + 24;
  //}
  
  if(weateron==1){
  //wheater
  // Create temperature Layer
  s_weather_layer = text_layer_create(
  GRect(0, layerstart, PBL_IF_ROUND_ELSE(181, 144), 30));

  // Style the text
  text_layer_set_background_color(s_weather_layer, GColorClear);
  text_layer_set_text_color(s_weather_layer, GColorFromHEX(color_extension_font));
  text_layer_set_font(s_weather_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  //text_layer_set_font(s_weather_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SILKSCREEN_24)));
  text_layer_set_text_alignment(s_weather_layer, GTextAlignmentCenter);
  text_layer_set_text(s_weather_layer, "Loading...");
  layer_add_child(s_path_layer_extension,text_layer_get_layer(s_weather_layer));
  layerstart=layerstart+21;
  
  }
    
  if(healthon==1){
  
   s_health_layer = text_layer_create(
  GRect(0, layerstart, PBL_IF_ROUND_ELSE(181, 144), 30));

  // Style the text
  text_layer_set_background_color(s_health_layer, GColorClear);
  text_layer_set_text_color(s_health_layer, GColorFromHEX(color_extension_font));
  text_layer_set_font(s_health_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  //text_layer_set_font(s_health_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SILKSCREEN_24)));
  text_layer_set_text_alignment(s_health_layer, GTextAlignmentCenter);
    
    //text_layer_set_text(s_health_layer, "744 Steps");
  //text_layer_set_text(s_health_layer, s_buffer);
  layer_add_child(s_path_layer_extension,text_layer_get_layer(s_health_layer));            
     
  }
  
  // Create battery meter Layer
s_battery_layer = layer_create(GRect(0, 3, PBL_IF_ROUND_ELSE(181, 144), 2));
layer_set_update_proc(s_battery_layer, battery_update_proc);

// Add to Window
layer_add_child(s_path_layer_extension, s_battery_layer);
             
  
}
static void main_window_load(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  
    
  ///APP_LOG(APP_LOG_LEVEL_DEBUG, "start" );

  if (persist_read_int(KEY_BACKGROUND_COLOR)) {
    color_background = persist_read_int(KEY_BACKGROUND_COLOR);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "color_background:%d",color_background );
  }
  //h1
  if (persist_read_bool(KEY_h1nocolorband)) {
    no_color_band[0] = persist_read_bool(KEY_h1nocolorband);
  }
  if (persist_read_int(KEY_h1_dir)) {
    dir[0]  = persist_read_int(KEY_h1_dir)-1;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Dir:%d",dir[0] );
  }
  if (persist_read_int(KEY_h1numberColor)) {
    color[0]  = persist_read_int(KEY_h1numberColor)-1;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Numbercolor:%d",color[0] );
  }
  if (persist_read_int(KEY_h1bandColor)) {
    color_band[0] = persist_read_int(KEY_h1bandColor)-1;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "bandcolor:%d",color_band[0] );
  }
  if (persist_read_int(KEY_h1x)) {
    x[0] = persist_read_int(KEY_h1x)+500;
    x[0]=PBL_IF_ROUND_ELSE(x[0]+18, x[0]);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "x:%d",x[0] );
  }
  if (persist_read_int(KEY_h1y)) {
    y[0] = persist_read_int(KEY_h1y)+500;
    y[0]=PBL_IF_ROUND_ELSE(y[0]+6, y[0]);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "y:%d",y[0] );
  }
  if (persist_read_int(KEY_h1duration)) {
    duration[0] = persist_read_int(KEY_h1duration)-50;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Duration:%d",duration[0] );
  }
  if (persist_read_int(KEY_h1delay)) {
    delay[0] = persist_read_int(KEY_h1delay)-50;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Delay:%d",delay[0] );
  }
  if (persist_read_bool(KEY_h1outline)) {
    outlines[0] = persist_read_bool(KEY_h1outline);
  }
  if (persist_read_bool(KEY_h1line)) {
    line[0] = persist_read_bool(KEY_h1line);
  }
  if (persist_read_bool(KEY_h1linesColor)) {
    color_lines[0] = persist_read_int(KEY_h1linesColor);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "savelineColor:%d",color_lines[1] );
  }
  
  
  
  //h2
  if (persist_read_bool(KEY_h2trans)) {
    no_color_band[1] = persist_read_bool(KEY_h2trans);
  }
  if (persist_read_int(KEY_h2_dir)) {
    dir[1]  = persist_read_int(KEY_h2_dir)-1;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Dir:%d",dir[1] );
  }
  if (persist_read_int(KEY_h2numberColor)) {
    color[1]  = persist_read_int(KEY_h2numberColor)-1;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Numbercolor:%d",color[1] );
  }
  if (persist_read_int(KEY_h2bandColor)) {
    color_band[1] = persist_read_int(KEY_h2bandColor)-1;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "bandcolor:%d",color_band[1] );
  }
  if (persist_read_int(KEY_h2x)) {
    x[1] = persist_read_int(KEY_h2x)+500;
     x[1]=PBL_IF_ROUND_ELSE(x[1]+18, x[1]);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "x:%d",x[1] );
  }
  if (persist_read_int(KEY_h2y)) {
    y[1] = persist_read_int(KEY_h2y)+500;
    y[1]=PBL_IF_ROUND_ELSE(y[1]+6, y[1]);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "y:%d",y[1] );
  }
  if (persist_read_int(KEY_h2duration)) {
    duration[1] = persist_read_int(KEY_h2duration)-50;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Duration:%d",duration[1] );
  }
  if (persist_read_int(KEY_h2delay)) {
    delay[1] = persist_read_int(KEY_h2delay)-50;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Delay:%d",delay[1] );
  }
  if (persist_read_bool(KEY_h2outline)) {
    outlines[1] = persist_read_bool(KEY_h2outline);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "outline:%d",outlines[1] );
  }
  if (persist_read_bool(KEY_h2line)) {
    line[1] = persist_read_bool(KEY_h2line);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "line:%d",line[1] );
  }
  if (persist_read_bool(KEY_h2linesColor)) {
    color_lines[1] = persist_read_int(KEY_h2linesColor);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "lineColor:%d",color_lines[1] );
  }
  
  
  //m1
  if (persist_read_bool(KEY_m1trans)) {
    no_color_band[2] = persist_read_bool(KEY_m1trans);
  }
  if (persist_read_int(KEY_m1_dir)) {
    dir[2]  = persist_read_int(KEY_m1_dir)-1;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Dir:%d",dir[2] );
  }
  if (persist_read_int(KEY_m1numberColor)) {
    color[2]  = persist_read_int(KEY_m1numberColor)-1;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Numbercolor:%d",color[2] );
  }
  if (persist_read_int(KEY_m1bandColor)) {
    color_band[2] = persist_read_int(KEY_m1bandColor)-1;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "bandcolor:%d",color_band[2] );
  }
  if (persist_read_int(KEY_m1x)) {
    x[2] = persist_read_int(KEY_m1x)+500;
     x[2]=PBL_IF_ROUND_ELSE(x[2]+18, x[2]);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "x:%d",x[2] );
  }
  if (persist_read_int(KEY_m1y)) {
    y[2] = persist_read_int(KEY_m1y)+500;
    y[2]=PBL_IF_ROUND_ELSE(y[2]+6, y[2]);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "y:%d",y[2] );
  }
  if (persist_read_int(KEY_m1duration)) {
    duration[2] = persist_read_int(KEY_m1duration)-50;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Duration:%d",duration[2] );
  }
  if (persist_read_int(KEY_m1delay)) {
    delay[2] = persist_read_int(KEY_m1delay)-50;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Delay:%d",delay[2] );
  }
  if (persist_read_bool(KEY_m1outline)) {
    outlines[2] = persist_read_bool(KEY_m1outline);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "outline:%d",outlines[2] );
  }
  if (persist_read_bool(KEY_m1line)) {
    line[2] = persist_read_bool(KEY_m1line);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "line:%d",line[2] );
  }
  if (persist_read_bool(KEY_m1linesColor)) {
    color_lines[2] = persist_read_int(KEY_m1linesColor);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "lineColor:%d",color_lines[2] );
  }
  
  //m2
  if (persist_read_bool(KEY_m2trans)) {
    no_color_band[3] = persist_read_bool(KEY_m2trans);
  }
  if (persist_read_int(KEY_m2_dir)) {
    dir[3]  = persist_read_int(KEY_m2_dir)-1;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Dir:%d",dir[3] );
  }
  if (persist_read_int(KEY_m2numberColor)) {
    color[3]  = persist_read_int(KEY_m2numberColor)-1;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Numbercolor:%d",color[3] );
  }
  if (persist_read_int(KEY_m2bandColor)) {
    color_band[3] = persist_read_int(KEY_m2bandColor)-1;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "bandcolor:%d",color_band[3] );
  }
  if (persist_read_int(KEY_m2x)) {
    x[3] = persist_read_int(KEY_m2x)+500;
     x[3]=PBL_IF_ROUND_ELSE(x[3]+18, x[3]);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "x:%d",x[3] );
  }
  if (persist_read_int(KEY_m2y)) {
    y[3] = persist_read_int(KEY_m2y)+500;
    y[3]=PBL_IF_ROUND_ELSE(y[3]+6, y[3]);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "y:%d",y[3] );
  }
  if (persist_read_int(KEY_m2duration)) {
    duration[3] = persist_read_int(KEY_m2duration)-50;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Duration:%d",duration[3] );
  }
  if (persist_read_int(KEY_m2delay)) {
    delay[3] = persist_read_int(KEY_m2delay)-50;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Delay:%d",delay[3] );
  }
  if (persist_read_bool(KEY_m2outline)) {
    outlines[3] = persist_read_bool(KEY_m2outline);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "outline:%d",outlines[3] );
  }
  if (persist_read_bool(KEY_m2line)) {
    line[3] = persist_read_bool(KEY_m2line);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "line:%d",line[3] );
  }
  if (persist_read_bool(KEY_m2linesColor)) {
    color_lines[3] = persist_read_int(KEY_m2linesColor);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "lineColor:%d",color_lines[3] );
  }
  //etc
  if (persist_read_bool(KEY_invertanimationdelay)) {
    invert_animation_delay = persist_read_bool(KEY_invertanimationdelay)-1;
  }
  
    if (persist_read_bool(KEY_changeallnumbers)) {
    change_all_numbers = persist_read_bool(KEY_changeallnumbers)-1;
  }
  
  
  
  
  if (persist_read_int(KEY_layer1)) {
    order[0] = persist_read_int(KEY_layer1)-1;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "layer1:%d",order[0] );
  }
    if (persist_read_int(KEY_layer2)) {
    order[1] = persist_read_int(KEY_layer2)-1;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "layer2:%d",order[1] );
  }
    if (persist_read_int(KEY_layer3)) {
    order[2] = persist_read_int(KEY_layer3)-1;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "layer3:%d",order[2] );
  }
    if (persist_read_int(KEY_layer4)) {
    order[3] = persist_read_int(KEY_layer4)-1;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "layer3:%d",order[3] );
  }
  
  //++
  
  if (persist_read_bool(KEY_numberontop)) {
    numberontop = persist_read_bool(KEY_numberontop)-1;
  }
  if (persist_read_int(KEY_h1posone)) {
    onepos[0] = persist_read_int(KEY_h1posone);
  }
  if (persist_read_int(KEY_h2posone)) {
    onepos[1] = persist_read_int(KEY_h2posone);
  }
  if (persist_read_int(KEY_m1posone)) {
    onepos[2] = persist_read_int(KEY_m1posone);
  }
  if (persist_read_int(KEY_m2posone)) {
    onepos[3] = persist_read_int(KEY_m2posone);
  }
  
  if (persist_read_int(KEY_enegy)) {
    energy = persist_read_int(KEY_enegy);
    if(energy>3){
    taplimiter = 1;
    energy=energy-4;
  }
  if(energy>1){
    noextension = 1;
    energy=energy-2;
  }
  if(energy>0){
    noanimation = 1;
  }
  }
  if (persist_read_int(KEY_l1func)) {
    layer[0] = persist_read_int(KEY_l1func);
  }
  if (persist_read_int(KEY_l2func)) {
    layer[1] = persist_read_int(KEY_l2func);
  }
  if (persist_read_int(KEY_l3func)) {
    layer[2] = persist_read_int(KEY_l3func);
  }
  if (persist_read_int(KEY_extensionfontColor)) {
    color_extension_font = persist_read_int(KEY_extensionfontColor);
  }
  if (persist_read_int(KEY_extensionbackColor)) {
    color_extension = persist_read_int(KEY_extensionbackColor);
  }
  
  
  
  //-- 
  
  
  GRect bounds = layer_get_bounds(window_layer);
  //band
  n=order[3];
  load_band(window_layer);
  if(numberontop==0){load_number(window_layer);}
  n=order[2];
  load_band(window_layer);
  if(numberontop==0){load_number(window_layer);}
  n=order[1];
  load_band(window_layer);
  if(numberontop==0){load_number(window_layer);}
  n=order[0];
  load_band(window_layer);
  if(numberontop==0){load_number(window_layer);}
  
  
  
  
  
  
  //(())
  
  //(())
  
  
  //number
  if(numberontop==1){
    n=0;
    load_number(window_layer);
    n=1;
    load_number(window_layer);
    n=2;
    load_number(window_layer);
    n=3;
    load_number(window_layer);
  }
  
  
  if(noextension==0)load_extension(window_layer);
  
  
  
  s_time_layer = text_layer_create(
  GRect(300, PBL_IF_ROUND_ELSE(58, 52), bounds.size.w, 50));

  // Improve the layout to be more like a watchface
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlue);
  text_layer_set_text(s_time_layer, "00:00");
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  window_set_background_color(s_main_window, GColorFromHEX(color_background));
  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
  
  //test
/*
  
  HealthMetric metric = HealthMetricStepCount;
  time_t start = time_start_of_today();
  time_t end = time(NULL);
// Check the metric has data available for today
  HealthServiceAccessibilityMask mask = health_service_metric_accessible(metric, 
  start, end);
  if(mask & HealthServiceAccessibilityMaskAvailable) {
  // Data is available!
  APP_LOG(APP_LOG_LEVEL_INFO, "Steps today: %d", 
          (int)health_service_sum_today(metric));
} else {
  // No data recorded yet today
    APP_LOG(APP_LOG_LEVEL_ERROR, "Data unavailable!");
  }
  */
  //
  

}
static void main_window_unload(Window *window) {
  text_layer_destroy(s_time_layer);
  layer_destroy(s_path_layer[0]);
  layer_destroy(s_path_layer[1]);
  layer_destroy(s_path_layer[2]);
  layer_destroy(s_path_layer[3]);
  layer_destroy(s_path_layer_band[0]);
  layer_destroy(s_path_layer_band[1]);
  layer_destroy(s_path_layer_band[2]);
  layer_destroy(s_path_layer_band[3]);
  
  gpath_destroy(s_path[0]);
  gpath_destroy(s_path[1]);
  gpath_destroy(s_path[2]);
  gpath_destroy(s_path[3]);
  gpath_destroy(s_path_band[0]);
  gpath_destroy(s_path_band[1]);
  gpath_destroy(s_path_band[2]);
  gpath_destroy(s_path_band[3]);
  
  text_layer_destroy(s_date_layer);
  text_layer_destroy(s_weather_layer);
  text_layer_destroy(s_health_layer);
  layer_destroy(s_battery_layer);
  layer_destroy(s_path_layer_extension);
  gpath_destroy(s_path_extension);
}
static void init() {
  // pebble round?
  x[0]=PBL_IF_ROUND_ELSE(x[0]+18, x[0]);
  y[0]=PBL_IF_ROUND_ELSE(y[0]+6, y[0]);
  x[1]=PBL_IF_ROUND_ELSE(x[1]+18, x[1]);
  y[1]=PBL_IF_ROUND_ELSE(y[1]+6, y[1]);
  x[2]=PBL_IF_ROUND_ELSE(x[2]+18, x[2]);
  y[2]=PBL_IF_ROUND_ELSE(y[2]+6, y[2]);
  x[3]=PBL_IF_ROUND_ELSE(x[3]+18, x[3]);
  y[3]=PBL_IF_ROUND_ELSE(y[3]+6, y[3]);
  //
  
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Register with TickTimerService
tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  //tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
  
  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  
  /*   if (persist_read_int(KEY_BACKGROUND_COLOR)) {
    color_background = persist_read_int(KEY_BACKGROUND_COLOR);
    //set_background_and_text_color(background_color);
  }*/
  

  // Show the Window on the watch, with animated=true
  window_set_background_color(s_main_window, GColorFromHEX(color_background));
  window_stack_push(s_main_window, true);
  
  //Subscribe to AccelerometerService
  if(noextension==0){accel_tap_service_subscribe(accel_tap_handler);}
  
  app_message_register_inbox_received(inbox_received_handler);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  
  if(noextension==0)battery_state_service_subscribe(battery_callback);
  
  if(noextension==0)battery_callback(battery_state_service_peek());
  //test
  healthon=PBL_IF_HEALTH_ELSE(1,0);
  
  if (persist_read_int(KEY_l3func)) {
    layer[2] = persist_read_int(KEY_l3func);
    if(layer[2]==99)healthon=0;
  }
   if (persist_read_int(KEY_l2func)) {
    layer[1] = persist_read_int(KEY_l2func);
    if(layer[1]==99)weateron=0;
  }
  //healthon=1;
  //weateron=0;
  
/*  #if defined(PBL_HEALTH)
// Attempt to subscribe 
if(!health_service_events_subscribe(health_handler, NULL)) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Health not available!");
  healthon=0;
}
#else
APP_LOG(APP_LOG_LEVEL_ERROR, "Health not available!");
  healthon=0;
#endif
  //
  */
  
  
  
  update_time_minute();
}
static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}
int main(void) {
  init();
  app_event_loop();
  deinit();
}