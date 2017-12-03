//
// Created by lucian on 03.12.2017.
//

#ifndef BALLFALL_V2_BALLFALL_H
#define BALLFALL_V2_BALLFALL_H

#define DISPLAY_WIDTH 8
#define DISPLAY_HEIGHT 8
#define PADS_NUM 3

#define BALL_INIT_POS_X 3
#define BALL_INIT_POS_Y 0

#define OFFSET_SCREEN_X 0
#define OFFSET_SCREEN_Y 0

#define PAD_WIDTH 3
#define PAD_SPACING 2

int get_random(int min, int max);

typedef unsigned long int height_type;

class Ball_Fall {
    struct Pad {
        char x;
        height_type y;
        char length;

        Pad() : x(0), y(0), length(0) {}

        Pad(char x, height_type y, char length) : x(x), y(y), length(length) {}

        char left() {
            return x;
        }

        char right() {
            return (char) (x + length - 1);
        }
    };

    struct Ball {
        char x;
        height_type y;
        Pad* current_pad;
        Ball(char x, height_type y) : x(x), y(y), current_pad(nullptr) {}
    } ball;

    struct View_Point {
        char x;
        height_type y;
        char width;
        char height;
        View_Point(char x, height_type y) : x(x), y(y), width(DISPLAY_WIDTH), height(DISPLAY_HEIGHT) {}

        void print_matrix(char (*screen)[8], const Ball &ball, const Pad* pads) const;

        void print(char screen[DISPLAY_HEIGHT], const Ball &ball, Pad pads[]);
    } view_point;

    Pad pads[PADS_NUM];

    height_type last_pad_height;

    void attach_ball();

    Pad generate_pad(height_type &lph);

    void init_pads();

public:
    Ball_Fall();

    void move_ball(char direction);

    void drop_ball();

    bool pads_up();

    void start_game();

    void reset();

    void print_matrix(char (*screen)[8]) const;

    void print(char screen[DISPLAY_HEIGHT]);
};


#endif //BALLFALL_V2_BALLFALL_H
