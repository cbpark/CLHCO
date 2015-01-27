#ifndef SRC_TYPE_H_
#define SRC_TYPE_H_

#include <cmath>
#include <iostream>
#include <string>

namespace lhco {
class Particle {
private:
    double pt_  = 0.0;
    double phi_ = 0.0;
    double px_  = 0.0;
    double py_  = 0.0;

public:
    Particle() { }
    Particle(double pt, double phi)
        : pt_(pt), phi_(phi),
          px_(pt * std::cos(phi)), py_(pt * std::sin(phi)) { }
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

    virtual const std::string show() const = 0;
};

struct Met : public Particle {
    Met() { }
    Met(double pt, double phi) : Particle(pt, phi) { }
    ~Met() { }

    const std::string show() const;
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

protected:
    void set_energy(double m) {
        e_ = m >= 0.0 ?
            std::sqrt(pt() * pt() + pz_ * pz_ + m * m) :
            std::sqrt(pt() * pt() + pz_ * pz_);
    }
    void set_charge(int q) {
        if (q > 0) {
            q_ = Charge::Positive;
        } else if (q < 0) {
            q_ = Charge::Negative;
        } else {
            q_ = Charge::Neutral;
        }
    }

public:
    Visible() { }
    Visible(double pt, double phi, double eta, double m)
        : Particle(pt, phi), eta_(eta), m_(m), pz_(pt * std::sinh(eta)) {
        set_energy(m);
    }
    Visible(double pt, double phi, double eta, double m, int ntrk)
        : Particle(pt, phi), eta_(eta), m_(m), pz_(pt * std::sinh(eta)) {
        set_energy(m);
        set_charge(ntrk);
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
    int charge() const {
        switch (q_) {
        case Charge::Positive:
            return 1;
        case Charge::Negative:
            return -1;
        default:
            return 0;
        }
    }

    virtual const std::string show() const = 0;

    bool operator<(const Visible& rhs) const {
        return pt() < rhs.pt();
    }
};

class Photon : public Visible {
public:
    Photon() { }
    Photon(double pt, double phi, double eta, double m)
        : Visible(pt, phi, eta, m) { }
    ~Photon() { }

    const std::string show() const;
};

struct Electron : public Visible {
    Electron() { }
    Electron(double pt, double phi, double eta, double m, int ntrk)
        : Visible(pt, phi, eta, m, ntrk) { }
    ~Electron() { }

    virtual const std::string show() const;
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
    Muon(double pt, double phi, double eta, double m, int ntrk, double hadem)
        : Visible(pt, phi, eta, m, ntrk) {
        set_ptiso_etrat(hadem);
    }
    ~Muon() { }

    double ptiso() const {
        return ptiso_;
    }
    double etrat() const {
        return etrat_;
    }

    virtual const std::string show() const;
};

class Tau : public Visible {
public:
    enum class TauProng {OneProng, ThreeProng};

private:
    TauProng prong_;

protected:
    void set_prong(double ntrk) {
        int prong = static_cast<int>(std::abs(ntrk));
        if (prong < 2) {
            prong_ = TauProng::OneProng;
        } else {
            prong_ = TauProng::ThreeProng;
        }
    }

public:
    Tau() { }
    Tau(double pt, double phi, double eta, double m, int ntrk)
        : Visible(pt, phi, eta, m) {
        ntrk > 0? set_charge(1) : set_charge(-1);
        set_prong(ntrk);
    }
    ~Tau() { }

    int prong() const {
        return prong_ == TauProng::OneProng ? 1 : 3;
    }

    const std::string show() const;
};

class Jet : public Visible {
private:
    int num_track_;

public:
    Jet() { }
    Jet(double pt, double phi, double eta, double m, int ntrk)
        : Visible(pt, phi, eta, m), num_track_(ntrk) { }
    virtual ~Jet() { }

    int num_track() const {
        return num_track_;
    }

    const std::string show() const;
};

class Bjet : public Jet {
public:
    enum class BTag {Loose, Tight};

private:
    BTag btag_ = BTag::Loose;

public:
    Bjet() { }
    Bjet(double pt, double phi, double eta, double m, int ntrk, int btag)
        : Jet(pt, phi, eta, m, ntrk) {
        btag < 1.5 ? btag_ = BTag::Loose : btag_ = BTag::Tight;
    }
    ~Bjet() { }

    int btag() const {
        return btag_ == BTag::Loose ? 1 : 2;
    }

    const std::string show() const;
};
}  // namespace lhco

#endif  // SRC_TYPE_H_
