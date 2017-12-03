//
// Created by lucian on 03.12.2017.
//

#include "BallFall.h"


void Ball_Fall::View_Point::print_matrix(char (*screen)[8], const Ball_Fall::Ball &ball, const Ball_Fall::Pad* pads) const {
    for (char i = 0; i < DISPLAY_HEIGHT; i++) {
        for (char j = 0; j < DISPLAY_WIDTH; j++) {
            screen[i][j] = 0;
        }
    }

    for (char i = 0; i < PADS_NUM; i++) {
        height_type pad_y = pads[i].y - this->y;
        if (pad_y < 0 || pad_y >= DISPLAY_HEIGHT) continue;
        for (char j = 0; j < pads[i].length && j <DISPLAY_WIDTH; j++) {
            screen[pad_y][j + pads[i].x] = 1;
        }
    }
    screen[ball.y - this->y][ball.x - this->x] = 1;
}

void Ball_Fall::View_Point::print(char *screen, const Ball_Fall::Ball &ball, Ball_Fall::Pad pads[]) {
    char helper_screen[DISPLAY_HEIGHT][DISPLAY_WIDTH];
    print_matrix(helper_screen, ball, pads);

    for(char i = 0; i < DISPLAY_HEIGHT; i++) {
        screen[i] = 0;
        for (char j = 0; j < DISPLAY_WIDTH; j++) {
            if (helper_screen[i][j] == 1) {
                screen[i] = (char)(screen[i] | (1 << j));
            }
        }
    }
}

void Ball_Fall::attach_ball() {
    ball.current_pad = nullptr;
    for (auto &pad : pads) {
        if (pad.y == ball.y + 1 && pad.left() <= ball.x && ball.x <= pad.right()) {
            ball.current_pad = &pad;
            return;
        }
    }
}

Ball_Fall::Pad Ball_Fall::generate_pad(height_type &lph) {
    lph = lph + PAD_SPACING + 1;

    return {(char) get_random(0, DISPLAY_WIDTH - PAD_WIDTH), lph, PAD_WIDTH};
}

void Ball_Fall::init_pads() {
    height_type pad_1_h = BALL_INIT_POS_Y + 1;
    pads[0] = Pad(0, pad_1_h, DISPLAY_WIDTH);
    last_pad_height = pad_1_h;

    for (int i = 1; i < PADS_NUM; i++) {
        pads[i] = generate_pad(last_pad_height);
    }
}

void Ball_Fall::move_ball(char direction) {
    direction = (char) (direction < 0 ? -1 : direction == 0 ? 0 : 1);
    char new_x = ball.x + direction;
    if (new_x >= 0 && new_x < DISPLAY_WIDTH) ball.x = new_x;
    attach_ball();
}

void Ball_Fall::drop_ball() {
    if (ball.current_pad == nullptr) {
        ball.y += 1;
        attach_ball();
        if (ball.y - view_point.y == DISPLAY_HEIGHT - 1) view_point.y += 1;
    }
}

bool Ball_Fall::pads_up() {
    if (ball.current_pad != nullptr && ball.current_pad->y <= view_point.y + 1) {
        return false;
    }

    for (char i = 0; i < PADS_NUM; i++) {
        if (pads[i].y <= view_point.y) {
            pads[i] = generate_pad(last_pad_height);
            continue;
        }
        pads[i].y -= 1;
    }

    if (ball.current_pad != nullptr) {
        ball.y = ball.current_pad->y - 1;
    }

    last_pad_height--;
    return true;
}

void Ball_Fall::start_game() {
    pads[0] = generate_pad(last_pad_height);
    attach_ball();
}

void Ball_Fall::print_matrix(char (*screen)[8]) const {
    view_point.print_matrix(screen, ball, pads);
}

void Ball_Fall::print(char *screen) {
    view_point.print(screen, ball, pads);
}

Ball_Fall::Ball_Fall() : last_pad_height(0),
                         ball(BALL_INIT_POS_X, BALL_INIT_POS_Y),
                         view_point(OFFSET_SCREEN_X, -OFFSET_SCREEN_Y) {
    reset();
}

void Ball_Fall::reset() {
    view_point.x = OFFSET_SCREEN_X;
    view_point.y = -OFFSET_SCREEN_Y;

    ball.x = BALL_INIT_POS_X;
    ball.y = BALL_INIT_POS_Y;

    init_pads();
    attach_ball();
}
