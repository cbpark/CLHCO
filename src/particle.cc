#include "particle.h"

namespace lhco {
double PseudoRapidity(const double& x, const double& y, const double& z) {
    double ptot = std::sqrt(x * x + y * y + z * z);
    double cos_theta = ptot == 0.0 ? 1.0 : z / ptot;
    if (cos_theta * cos_theta < 1) {
        return -0.5 * std::log((1.0 - cos_theta) / (1.0 + cos_theta));
    }
    if (z == 0) {
        return 0.0;
    } else if (z > 0) {
        return 10.0e+10;
    } else {
        return -10.0e+10;
    }
}

const std::string Met::show() const {
    return "Met {pt=" + std::to_string(pt())
        + ",phi=" + std::to_string(phi()) + "}";
}

double InvariantMass(const Energy& e,
                     const Px& px, const Py& py, const Pz& pz) {
    return std::sqrt(e.value * e.value - px.value * px.value
                     - py.value * py.value - pz.value * pz.value);
}

const std::string show_pt_eta_phi(const Visible& p) {
    return "pt=" + std::to_string(p.pt())
        + ",eta=" + std::to_string(p.eta())
        + ",phi=" + std::to_string(p.phi());
}

const std::string show_pt_eta_phi_m(const Visible& p) {
    return show_pt_eta_phi(p) + ",mass=" + std::to_string(p.mass());
}

const std::string show_e_px_py_pz(const Visible& p) {
    return "e=" + std::to_string(p.energy())
        + ",px=" + std::to_string(p.px())
        + ",py=" + std::to_string(p.py())
        + ",pz=" + std::to_string(p.pz());
}

const std::string Visible::show() const {
    return "Visible {" + show_pt_eta_phi_m(*this)
        + "," + show_e_px_py_pz(*this) + "}";
}

Visible& Visible::operator+=(const Visible& rhs) {
    Energy e(this->energy() + rhs.energy());
    Px px(this->px() + rhs.px());
    Py py(this->py() + rhs.py());
    Pz pz(this->pz() + rhs.pz());
    *this = Visible(e, px, py, pz);
    return *this;
}

const std::string Photon::show() const {
    return "Photon {" + show_pt_eta_phi(*this) + "}";
}

const std::string Electron::show() const {
    return "Electron {" + show_pt_eta_phi(*this)
        + ",charge=" + std::to_string(charge()) + "}";
}

const std::string Muon::show() const {
    return "Muon {" + show_pt_eta_phi_m(*this)
        + ",charge=" + std::to_string(charge())
        + ",ptiso="  + std::to_string(ptiso())
        + ",etrat="  + std::to_string(etrat()) + "}";
}

const std::string Tau::show() const {
    return "Tau {" + show_pt_eta_phi_m(*this)
        + ",charge=" + std::to_string(charge())
        + ",prong="  + std::to_string(prong()) + "}";
}

const std::string Jet::show() const {
    return "Jet {" + show_pt_eta_phi_m(*this)
        + ",ntrk=" + std::to_string(num_track()) + "}";
}

const std::string Bjet::show() const {
    return "Bjet {" + show_pt_eta_phi_m(*this)
        + ",ntrk=" + std::to_string(num_track())
        + ",btag=" + std::to_string(btag()) + "}";
}
}  // namespace lhco
