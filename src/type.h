#ifndef SRC_TYPE_H_
#define SRC_TYPE_H_

#include <cmath>

namespace lhco {
class Particle {
private:
    double pt_  = 0.0;
    double phi_ = 0.0;
    double px_  = 0.0;
    double py_  = 0.0;

public:
    Particle() { }
    Particle(double _pt, double _phi)
        : pt_(_pt), phi_(_phi),
          px_(_pt * std::cos(_phi)), py_(_pt * std::sin(_phi)) { }
    virtual ~Particle() { }

    double pt() const {
        return pt_;
    }
    double phi() const {
        return phi_;
    }
    double px() const {
        return px_;
    }
    double py() const {
        return py_;
    }
};

class Met : public Particle {
public:
    Met() { }
    Met(double _pt, double _phi) : Particle(_pt, _phi) { }
    ~Met() { }
};

class Visible : public Particle {
public:
    enum class Charge {Positive, Negative, Neutral};

private:
    double eta_ = 0.0;
    double m_   = 0.0;
    double pz_  = 0.0;
    double e_   = 0.0;
    Charge q_   = Charge::Neutral;

    void set_energy(double _m) {
        if (_m >= 0) {
            e_ = std::sqrt(pt() * pt() + pz_ * pz_ + _m * _m);
        } else {
            e_ = std::sqrt(pt() * pt() + pz_ * pz_);
        }
    }

public:
    Visible() { }
    Visible(double _pt, double _phi, double _eta, double _m)
        : Particle(_pt, _phi), eta_(_eta), m_(_m), pz_(_pt * std::sinh(_eta)) {
        set_energy(_m);
    }
    Visible(double _pt, double _phi, double _eta, double _m, int _q)
        : Particle(_pt, _phi), eta_(_eta), m_(_m), pz_(_pt * std::sinh(_eta)) {
        set_energy(_m);
        set_charge(_q);
    }
    virtual ~Visible() { }

    double eta() const {
        return eta_;
    }
    double mass() const {
        return m_;
    }
    double pz() const {
        return pz_;
    }
    double energy() const {
        return e_;
    }
    void set_charge(int _q) {
        if (_q > 0) {
            q_ = Charge::Positive;
        } else if (_q < 0) {
            q_ = Charge::Negative;
        } else {
            q_ = Charge::Neutral;
        }
    }
};

class Photon : public Visible {
public:
    Photon() { }
    Photon(double _pt, double _phi, double _eta, double _m)
        : Visible(_pt, _phi, _eta, _m) { }
    ~Photon() { }
};

class Electron : public Visible {
public:
    Electron() { }
    Electron(double _pt, double _phi, double _eta, double _m, int _q)
        : Visible(_pt, _phi, _eta, _m, _q) { }
    ~Electron() { }
};

class Muon : public Visible {
private:
    double ptiso_;
    double etrat_;

    void set_ptiso_etrat(double hadem) {
        ptiso_ = std::trunc(hadem);
        etrat_ = hadem - ptiso_;
    }

public:
    Muon() { }
    Muon(double _pt, double _phi, double _eta, double _m, int _q, double hadem)
        : Visible(_pt, _phi, _eta, _m, _q) {
        set_ptiso_etrat(hadem);
    }
    ~Muon() { }

    double ptiso() const {
        return ptiso_;
    }
    double etrat() const {
        return etrat_;
    }
};

class Tau : public Visible {
public:
    enum class TauProng {OneProng, ThreeProng};

private:
    TauProng prong_;

    void set_prong(double ntrk) {
        int prong = static_cast<int>(ntrk);
        if (prong < 2) {
            prong_ = TauProng::OneProng;
        } else {
            prong_ = TauProng::ThreeProng;
        }
    }

public:
    Tau() { }
    Tau(double _pt, double _phi, double _eta, double _m, double ntrk)
        : Visible(_pt, _phi, _eta, _m) {
        ntrk > 0? set_charge(1) : set_charge(-1);
        set_prong(ntrk);
    }
};
}  // namespace lhco

#endif  // SRC_TYPE_H_
