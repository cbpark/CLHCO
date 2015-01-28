#include "lhco.h"
#include <cmath>
#include <vector>

namespace lhco {
template<typename T>
int NumOfParticles(const Pt& pt, const Eta& eta, const std::vector<T>& ps) {
    int count = 0;
    for (const auto& p : ps) {
        if (p.pt() > pt.value && std::abs(p.eta()) < eta.value) {
            ++count;
        }
    }
    return count;
}

int NumPhoton(const Event& ev) {
    return ev.photon().size();
}

int NumPhoton(const Pt& pt, const Eta& eta, const Event& ev) {
    return NumOfParticles(pt, eta, ev.photon());
}

int NumElectron(const Event& ev) {
    return ev.electron().size();
}

int NumElectron(const Pt& pt, const Eta& eta, const Event& ev) {
    return NumOfParticles(pt, eta, ev.electron());
}

int NumMuon(const Event& ev) {
    return ev.muon().size();
}

int NumMuon(const Pt& pt, const Eta& eta, const Event& ev) {
    return NumOfParticles(pt, eta, ev.muon());
}

int NumTau(const Event& ev) {
    return ev.tau().size();
}

int NumTau(const Pt& pt, const Eta& eta, const Event& ev) {
    return NumOfParticles(pt, eta, ev.tau());
}

int NumNormalJet(const Event& ev) {
    return ev.jet().size();
}

int NumNormalJet(const Pt& pt, const Eta& eta, const Event& ev) {
    return NumOfParticles(pt, eta, ev.jet());
}

int NumBjet(const Event& ev) {
    return ev.bjet().size();
}

int NumBjet(const Pt& pt, const Eta& eta, const Event& ev) {
    return NumOfParticles(pt, eta, ev.bjet());
}

int NumAllJet(const Event& ev) {
    return NumNormalJet(ev) + NumBjet(ev);
}

int NumAllJet(const Pt& pt, const Eta& eta, const Event& ev) {
    return NumNormalJet(pt, eta, ev) + NumBjet(pt, eta, ev);
}
}  // namespace lhco
