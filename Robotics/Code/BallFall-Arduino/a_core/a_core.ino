#define DISPLAY_WIDTH 8
#define DISPLAY_HEIGHT 8
#define PADS_NUM 3

#define BALL_INIT_POZ_X 3
#define BALL_INIT_POZ_Y 0

#define OFFSET_SCREEN_X 0
#define OFFSET_SCREEN_Y 0

#define PAD_WIDTH 3
#define PAD_SPACING 2

int getRandom(int min, int max);

class BallFal {
    struct Pad {
        char x;
        int y;
        char length;

        Pad() : x(0), y(0), length(0) {}

        Pad(char x, int y, char length) : x(x), y(y), length(length) {}

        char left() {
            return x;
        }

        char right() {
            return (char)(x + length - 1);
        }
    };

    struct Ball {
        char x;
        int y;
        Pad* currentPad;
        Ball(char x, int y) : x(x), y(y), currentPad(nullptr) {}
    } ball;

    struct ViewPoint {
        char x;
        int y;
        char width;
        char height;
        ViewPoint(char x, int y) : x(x), y(y), width(DISPLAY_WIDTH), height(DISPLAY_HEIGHT) {}

        void print(char screen[DISPLAY_HEIGHT][DISPLAY_WIDTH], const Ball &ball, Pad pads[]) {
            for (char i = 0; i < DISPLAY_HEIGHT; i++) {
                for (char j = 0; j < DISPLAY_WIDTH; j++) {
                    screen[i][j] = 0;
                }
            }

            for (int i = 0; i < PADS_NUM; i++) {
                int padY = pads[i].y - this->y;
                if (padY < 0 || padY >= DISPLAY_HEIGHT) continue;
                for (char j = 0; j < pads[i].length && j < DISPLAY_WIDTH; j++) {
                    screen[padY][j + pads[i].x] = 1;
                }
            }

            screen[ball.y - this->y][ball.x - this->x] = 1;
        }

        void print(char screen[DISPLAY_HEIGHT], const Ball &ball, Pad pads[]) {
            char helperScreen[DISPLAY_HEIGHT][DISPLAY_WIDTH];
            print(helperScreen, ball, pads);

            for (char i = 0; i < DISPLAY_HEIGHT; i++) {
                screen[i] = 0;
                for (char j = 0; j < DISPLAY_WIDTH; j++) {
                    if (helperScreen[i][j] == 1) {
                        screen[i] = (char)(screen[i] | (1 << j));
                    }
                }
            }
        }
    } viewPoint;

    Pad pads[PADS_NUM];

    int lastPad;

    void attachBall() {
        ball.currentPad = nullptr;
        for (auto &pad : pads) {
            if (pad.y == ball.y + 1 && pad.left() <= ball.x && ball.x <= pad.right()) {
                ball.currentPad = &pad;
                return;
            }
        }
    }

    Pad generatePad() {
        lastPad = lastPad + PAD_SPACING + 1;

        return {(char)getRandom(0, DISPLAY_WIDTH - PAD_WIDTH), lastPad, PAD_WIDTH};
    }

    void initPads() {
        pads[0] = Pad(0, BALL_INIT_POZ_Y + 1, DISPLAY_WIDTH);
        lastPad = BALL_INIT_POZ_Y + 1;
        for (int i = 1; i < PADS_NUM; i++) {
            pads[i] = generatePad();
        }
    }

public:
    BallFal() : lastPad(0), ball(BALL_INIT_POZ_X, BALL_INIT_POZ_Y), viewPoint(OFFSET_SCREEN_X, -OFFSET_SCREEN_Y) {
        initPads();
        attachBall();
    }

    // move ball on the x axis; -1 for left, 0 for stay, 1 for right
    void moveBall(char direction) {
        direction = (char)(direction < 0 ? -1 : direction == 0 ? 0 : 1);
        char newX = ball.x + direction;
        if (newX >= 0 && newX < DISPLAY_WIDTH) ball.x = newX;
        attachBall();
    }

    int dropBall() {
        if (ball.currentPad == nullptr) {
            ball.y += 1;
            attachBall();
            if (ball.y - viewPoint.y == DISPLAY_HEIGHT - 1) viewPoint.y += 1;
        }
        return ball.y;
    }

    bool padsUp() {
        if (ball.currentPad != nullptr && ball.currentPad->y <= viewPoint.y + 1) {
            return false;
        }
        for (int i = 0; i < PADS_NUM; i++) {
            if (pads[i].y <= viewPoint.y) {
                pads[i].y = viewPoint.y + viewPoint.height;
                continue;
            }
            pads[i].y -= 1;
        }
        if (ball.currentPad != nullptr) {
            ball.y = ball.currentPad->y - 1;
        }
        return true;
    }

    void startGame() {
        pads[0] = Pad(5, 10, 3);
        attachBall();
    }

    void print(char screen[DISPLAY_HEIGHT][DISPLAY_WIDTH]) {
        viewPoint.print(screen, ball, pads);
    };

    void print(char screen[DISPLAY_HEIGHT]) {
        viewPoint.print(screen, ball, pads);
    }
};
