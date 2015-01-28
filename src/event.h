#ifndef SRC_EVENT_H_
#define SRC_EVENT_H_

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "momentum.h"
#include "object.h"

namespace lhco {
class Particle {
private:
    double pt_  = 0.0;
    double phi_ = 0.0;
    double px_  = 0.0;
    double py_  = 0.0;

public:
    Particle() { }
    Particle(const Pt& pt, const Phi& phi)
        : pt_(pt.value), phi_(phi.value),
          px_(pt.value * std::cos(phi.value)),
          py_(pt.value * std::sin(phi.value)) { }
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
    Visible(const Pt& pt, const Eta& eta, const Phi& phi, const Mass& m)
        : Particle(pt, phi), eta_(eta.value), m_(m.value),
          pz_(pt.value * std::sinh(eta.value)) {
        set_energy(m.value);
    }
    Visible(const Pt& pt, const Eta& eta, const Phi& phi, const Mass& m,
            const int& ntrk)
        : Particle(pt, phi), eta_(eta.value), m_(m.value),
          pz_(pt.value * std::sinh(eta.value)) {
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

    virtual const std::string show() const = 0;

    bool operator<(const Visible& rhs) const {
        return pt() < rhs.pt();
    }
};

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

    virtual const std::string show() const;
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
         int ntrk, double hadem)
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

    virtual const std::string show() const;
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
    Tau(const Pt& pt, const Eta& eta, const Phi& phi, const Mass& m, int ntrk)
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
    Jet(const Pt& pt, const Eta& eta, const Phi& phi, const Mass& m, int ntrk)
        : Visible(pt, eta, phi, m), num_track_(ntrk) { }
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
    Bjet(const Pt& pt, const Eta& eta, const Phi& phi, const Mass& m,
         int ntrk, int btag)
        : Jet(pt, eta, phi, m, ntrk) {
        btag < 1.5 ? btag_ = BTag::Loose : btag_ = BTag::Tight;
    }
    ~Bjet() { }

    int btag() const {
        return btag_ == BTag::Loose ? 1 : 2;
    }

    const std::string show() const;
};

class Event {
private:
    EventStatus status_;

    std::vector<Photon>   photons_;
    std::vector<Electron> electrons_;
    std::vector<Muon>     muons_;
    std::vector<Tau>      taus_;
    std::vector<Jet>      jets_;
    std::vector<Bjet>     bjets_;
    Met met_;

public:
    explicit Event(EventStatus s = EventStatus::Empty) : status_(s) { }

    std::vector<Photon> photon() const {
        return photons_;
    }
    void add_photon(const Object& obj) {
        status_ = EventStatus::Fill;
        Photon photon(Pt(obj.pt), Eta(obj.eta), Phi(obj.phi), Mass(obj.jmass));
        photons_.push_back(photon);
    }
    std::vector<Electron> electron() const {
        return electrons_;
    }
    void add_electron(const Object& obj) {
        status_ = EventStatus::Fill;
        Electron elec(Pt(obj.pt), Eta(obj.eta), Phi(obj.phi), Mass(obj.jmass),
                      obj.ntrk);
        electrons_.push_back(elec);
    }
    std::vector<Muon> muon() const {
        return muons_;
    }
    void add_muon(const Object& obj) {
        status_ = EventStatus::Fill;
        Muon muon(Pt(obj.pt), Eta(obj.eta), Phi(obj.phi), Mass(obj.jmass),
                  obj.ntrk, obj.hadem);
        muons_.push_back(muon);
    }
    std::vector<Tau> tau() const {
        return taus_;
    }
    void add_tau(const Object& obj) {
        status_ = EventStatus::Fill;
        Tau tau(Pt(obj.pt), Eta(obj.eta), Phi(obj.phi), Mass(obj.jmass),
                obj.ntrk);
        taus_.push_back(tau);
    }
    std::vector<Jet> jet() const {
        return jets_;
    }
    void add_jet(const Object& obj) {
        status_ = EventStatus::Fill;
        Jet jet(Pt(obj.pt), Eta(obj.eta), Phi(obj.phi), Mass(obj.jmass),
                obj.ntrk);
        jets_.push_back(jet);
    }
    std::vector<Bjet> bjet() const {
        return bjets_;
    }
    void add_bjet(const Object& obj) {
        status_ = EventStatus::Fill;
        Bjet bjet(Pt(obj.pt), Eta(obj.eta), Phi(obj.phi), Mass(obj.jmass),
                  obj.ntrk, obj.btag);
        bjets_.push_back(bjet);
    }
    Met met() const {
        return met_;
    }
    void set_met(const Object& obj) {
        status_ = EventStatus::Fill;
        met_ = Met(Pt(obj.pt), Phi(obj.phi));
    }
    bool empty() const {
        return status_ == EventStatus::Empty;
    }
};
}  // namespace lhco

#endif  // SRC_EVENT_H_
