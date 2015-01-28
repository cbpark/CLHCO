#include "event.h"
#include <algorithm>
#include <functional>

namespace lhco {
const std::string RawEvent::show() const {
    std::string str = "RawEvent {" + header_.show() + ",[";
    for (const auto& o : objects_) {
        str += o.show() + ",";
    }
    str.pop_back();
    str += "]}";
    return str;
}

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
const std::string ShowAll(const std::vector<T>& ps) {
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
    str += ShowAll(photons_) + ShowAll(electrons_) + ShowAll(muons_);
    str += ShowAll(taus_) + ShowAll(jets_) + ShowAll(bjets_);
    str += met_.show() + "}";
    return str;
}

template<typename T>
void SortByPt(std::vector<T> *ps) {
    if (!ps->empty()) {
        std::sort(ps->begin(), ps->end(), std::greater<T>());
    }
}

void Event::sort_particles() {
    SortByPt(&photons_);
    SortByPt(&electrons_);
    SortByPt(&muons_);
    SortByPt(&taus_);
    SortByPt(&jets_);
    SortByPt(&bjets_);
}
}  // namespace lhco
