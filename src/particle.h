#ifndef SRC_PARTICLE_H_
#define SRC_PARTICLE_H_

#include <cmath>
#include <string>
#include <vector>

namespace lhco {
struct Px {
    double value;
    explicit Px(double v) : value(v) { }
};

struct Py {
    double value;
    explicit Py(double v) : value(v) { }
};

struct Pz {
    double value;
    explicit Pz(double v) : value(v) { }
};

struct Energy {
    double value;
    explicit Energy(double v) : value(v) { }
};

struct Pt {
    double value;
    explicit Pt(double v) : value(v) { }
    Pt(const Px& px, const Py& py)  {
        value = std::sqrt(px.value * px.value + py.value * py.value);
    }
};

double PseudoRapidity(const double& x, const double& y, const double& z);

struct Eta {
    double value;
    explicit Eta(double v) : value(v) { }
    Eta(const Px& px, const Py& py, const Pz& pz)
        : value(PseudoRapidity(px.value, py.value, pz.value)) { }
};

struct Phi {
    double value;
    explicit Phi(double v) : value(v) { }
    Phi(const Px& px, const Py& py) {
        if (px.value == 0.0 && py.value == 0.0) {
            value = 0.0;
        } else {
            value = std::atan2(py.value, px.value);
        }
    }
};

struct Mass {
    double value;
    explicit Mass(double v) : value(v) { }
};

class Particle {
private:
    double pt_  = 0.0;
    double phi_ = 0.0;
    double px_  = 0.0;
    double py_  = 0.0;

public:
    Particle() { }
    Particle(const Pt& pt, const Phi& phi)
        : pt_(pt.value), phi_(phi.value) {
        px_ = pt.value * std::cos(phi.value);
        py_ = pt.value * std::sin(phi.value);
    }
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
    Met(const Pt& pt, const Phi& phi) : Particle(pt, phi) { }
    ~Met() { }

    const std::string show() const;
};

double InvariantMass(const Energy& e, const Px& px, const Py& py, const Pz& pz);

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
        if (m >= 0.0) {
            e_ = std::sqrt(pt() * pt() + pz_ * pz_ + m * m);
        } else {
            e_ = std::sqrt(pt() * pt() + pz_ * pz_);
        }
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
    Visible(const Pt& pt, const Eta& eta, const Phi& phi, const Mass& m)
        : Particle(pt, phi), eta_(eta.value), m_(m.value) {
        pz_ = pt.value * std::sinh(eta.value);
        set_energy(m.value);
    }
    Visible(const Energy& e, const Px& px, const Py& py, const Pz& pz)
        : Particle(Pt(px, py), Phi(px, py)), pz_(pz.value), e_(e.value) {
        Eta eta(px, py, pz);
        eta_ = eta.value;
        m_ = InvariantMass(e, px, py, pz);
    }
    Visible(const Pt& pt, const Eta& eta, const Phi& phi, const Mass& m,
            const int& ntrk)
        : Particle(pt, phi), eta_(eta.value), m_(m.value) {
        pz_ = pt.value * std::sinh(eta.value);
        set_energy(m.value);
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

    virtual const std::string show() const;
    bool operator<(const Visible& rhs) const {
        return pt() < rhs.pt();
    }
    bool operator>(const Visible& rhs) const {
        return pt() > rhs.pt();
    }
    Visible& operator+=(const Visible& rhs);
    friend Visible operator+(Visible lhs, const Visible& rhs) {
        return lhs += rhs;
    }
};

using Visibles = std::vector<Visible>;

class Photon : public Visible {
public:
    Photon() { }
    Photon(const Pt& pt, const Eta& eta, const Phi& phi, const Mass& m)
        : Visible(pt, eta, phi, m) { }
    ~Photon() { }

    const std::string show() const;
};

struct Electron : public Visible {
    Electron() { }
    Electron(const Pt& pt, const Eta& eta, const Phi& phi, const Mass& m,
             int ntrk)
        : Visible(pt, eta, phi, m, ntrk) { }
    ~Electron() { }

    const std::string show() const;
};

class Muon : public Visible {
private:
    double ptiso_;
    double etrat_;

protected:
    void set_ptiso_etrat(double hadem) {
        ptiso_ = std::trunc(hadem);
        etrat_ = hadem - ptiso_;
    }

public:
    Muon() { }
    Muon(const Pt& pt, const Eta& eta, const Phi& phi, const Mass& m,
         const int& ntrk, const double& hadem)
        : Visible(pt, eta, phi, m, ntrk) {
        set_ptiso_etrat(hadem);
    }
    ~Muon() { }

    double ptiso() const {
        return ptiso_;
    }
    double etrat() const {
        return etrat_;
    }

    const std::string show() const;
};

class Tau : public Visible {
public:
    enum class TauProng {OneProng, ThreeProng};

private:
    TauProng prong_;

protected:
    void set_prong(int ntrk) {
        if (ntrk < 2) {
            prong_ = TauProng::OneProng;
        } else {
            prong_ = TauProng::ThreeProng;
        }
    }

public:
    Tau() { }
    Tau(const Pt& pt, const Eta& eta, const Phi& phi, const Mass& m,
        const int& ntrk)
        : Visible(pt, eta, phi, m) {
        ntrk > 0 ? set_charge(1) : set_charge(-1);
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
    Jet(const Pt& pt, const Eta& eta, const Phi& phi, const Mass& m,
        const int& ntrk)
        : Visible(pt, eta, phi, m), num_track_(ntrk) { }
    virtual ~Jet() { }

    int num_track() const {
        return num_track_;
    }

    virtual const std::string show() const;
};

class Bjet : public Jet {
public:
    enum class BTag {Loose, Tight};

private:
    BTag btag_ = BTag::Loose;

public:
    Bjet() { }
    Bjet(const Pt& pt, const Eta& eta, const Phi& phi, const Mass& m,
         const int& ntrk, const int& btag)
        : Jet(pt, eta, phi, m, ntrk) {
        btag < 1.5 ? btag_ = BTag::Loose : btag_ = BTag::Tight;
    }
    ~Bjet() { }

    int btag() const {
        return btag_ == BTag::Loose ? 1 : 2;
    }

    const std::string show() const;
};
}  // namespace lhco

#endif  // SRC_PARTICLE_H_
