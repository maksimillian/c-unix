enum {
    F_1x4,
    F_2x2,
    F_PLUS,
};

struct figure_definition;

typedef struct cup cup_t;
typedef struct figure_definition fig_def_t;
typedef struct figure_state fig_state_t;

struct figure_definition {
    int (*const fall_1_row)(fig_state_t, const cup_t);
    void (*const print)(const fig_state_t, cup_t);
    int (*const rotate_cw)(fig_state_t, const cup_t);
    int (*const rotate_ccw)(fig_state_t, cup_t);
    int (*const shift_left)(fig_state_t, cup_t);
    int (*const shift_right)(fig_state_t, cup_t);
};

struct figure_state {
    const fig_def_t *m;
    //...
};

int f_1x4_fall_1_row(fig_state_t, cup_t);
void f_1x4_print(fig_state_t, cup_t);
int f_1x4_rotate_cw(fig_state_t, cup_t);
int f_1x4_rotate_ccw(fig_state_t, cup_t);
int f_1x4_shift_left(fig_state_t, cup_t);
int f_1x4_shift_right(fig_state_t, cup_t);

// clang-format off
const struct figure_definition
Figures[] = {
    [F_1x4] = {
        f_1x4_fall_1_row,
        f_1x4_print,
        f_1x4_rotate_cw,
        f_1x4_rotate_ccw,
        f_1x4_shift_left,
        f_1x4_shift_right,
    }
};
// clang-format on

int main() {
    cup_t c;
    fig_state_t s = {.m = &Figures[F_1x4]};
    s.m->print(s, c);
}
