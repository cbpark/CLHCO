#ifndef SRC_MOMENTUM_H_
#define SRC_MOMENTUM_H_

namespace lhco {
struct Pt {
    double value;
    explicit Pt(double v) : value(v) { }
};

struct Eta {
    double value;
    explicit Eta(double v) : value(v) { }
};

struct Phi {
    double value;
    explicit Phi(double v) : value(v) { }
};

struct Mass {
    double value;
    explicit Mass(double v) : value(v) { }
};
}

#endif  // SRC_MOMENTUM_H_
