#include "event.h"

namespace lhco {
const std::string Met::show() const {
    return "Met {pt=" + std::to_string(pt())
        + ",phi=" + std::to_string(phi()) + "}";
}

const std::string show_pt_eta_phi(const Visible& p) {
    return "pt=" + std::to_string(p.pt())
        + ",eta=" + std::to_string(p.eta())
        + ",phi=" + std::to_string(p.phi());
}

const std::string Photon::show() const {
    return "Photon {" + show_pt_eta_phi(*this) + "}";
}

const std::string Electron::show() const {
    return "Electron {" + show_pt_eta_phi(*this)
        + ",charge=" + std::to_string(charge()) + "}";
}

const std::string Muon::show() const {
    return "Muon {" + show_pt_eta_phi(*this)
        + ",charge=" + std::to_string(charge())
        + ",ptiso="  + std::to_string(ptiso())
        + ",etrat="  + std::to_string(etrat()) + "}";
}

const std::string Tau::show() const {
    return "Tau {" + show_pt_eta_phi(*this)
        + ",charge=" + std::to_string(charge())
        + ",prong="  + std::to_string(prong()) + "}";
}

const std::string Jet::show() const {
    return "Jet {" + show_pt_eta_phi(*this)
        + ",ntrk=" + std::to_string(num_track()) + "}";
}

const std::string Bjet::show() const {
    return "Bjet {" + show_pt_eta_phi(*this)
        + ",ntrk=" + std::to_string(num_track())
        + ",btag=" + std::to_string(btag()) + "}";
}

template<typename T>
const std::string show_all(const std::vector<T>& ps) {
    std::string str = "";
    if (!ps.empty()) {
        str += "[";
        for (const auto& p : ps) {
            str += p.show() + ",";
        }
        str.pop_back();
        str += "],";
    }
    return str;
}

const std::string Event::show() const {
    std::string str = "Event {";
    str += show_all(photons_) + show_all(electrons_) + show_all(muons_);
    str += show_all(jets_) + show_all(bjets_);
    str += met_.show() + "}";
    return str;
}
}  // namespace lhco
