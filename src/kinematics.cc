/* Copyright (c) 2015, 2017, Chan Beom Park <cbpark@gmail.com> */

#include "kinematics.h"
#include <cmath>
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif  // HAVE_CONFIG_H
#ifdef HAVE_ROOT
#include "TLorentzVector.h"
#include "TVector3.h"
#endif  // HAVE_ROOT

namespace lhco {
#ifdef HAVE_ROOT
TLorentzVector mkLorentzVector(const Energy &e, const Px &px, const Py &py,
                               const Pz &pz) {
    return {px.value, py.value, pz.value, e.value};
}

TVector3 mkVector3(const Px &px, const Py &py, const Pz &pz) {
    return {px.value, py.value, pz.value};
}
#endif

#ifdef HAVE_ROOT
double pseudoRapidity(const Px &px, const Py &py, const Pz &pz) {
    const TVector3 v3 = mkVector3(px, py, pz);
    return v3.Eta();
}
#else
double pseudoRapidity(const Px &px, const Py &py, const Pz &pz) {
    ThreeMomentum p(px, py, pz);
    double costheta = p.cosTheta();
    if (costheta * costheta < 1.0) {
        return -0.5 * std::log((1.0 - costheta) / (1.0 + costheta));
    }

    if (pz.value == 0.0) {
        return 0.0;
    } else if (pz.value > 0.0) {
        return 10.0e+10;
    } else {
        return -10.0e+10;
    }
}
#endif  // HAVE_ROOT

#ifdef HAVE_ROOT
double invariantMass(const Energy &e, const Px &px, const Py &py,
                     const Pz &pz) {
    const TLorentzVector v4 = mkLorentzVector(e, px, py, pz);
    return v4.M();
}
#else
double invariantMass(const Energy &e, const Px &px, const Py &py,
                     const Pz &pz) {
    const double m2 = e.value * e.value - px.value * px.value -
                      py.value * py.value - pz.value * pz.value;
    return m2 < 0 ? -std::sqrt(-m2) : std::sqrt(m2);
}
#endif  // HAVE_ROOT
}  // namespace lhco
