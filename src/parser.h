#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include <string>
#include <vector>
#include "type.h"

namespace lhco {
struct Header {
    int event_number = 0;
    int trigger_word = 0;

    Header() { }
    Header(int _evnum, int _trig)
        : event_number(_evnum), trigger_word(_trig) { }

    const std::string show() const;
    friend std::istream& operator>>(std::istream& is, Header& h);
};

struct Object {
    int    typ   = 0;
    double eta   = 0.0;
    double phi   = 0.0;
    double pt    = 0.0;
    double jmass = 0.0;
    int    ntrk  = 0;
    int    btag  = 0;
    double hadem = 0.0;

    Object() { }
    Object(int _typ, double _eta, double _phi, double _pt, double _jmass,
           int _ntrk, int _btag, double _hadem)
        : typ(_typ), eta(_eta), phi(_phi), pt(_pt), jmass(_jmass),
          ntrk(_ntrk), btag(_btag), hadem(_hadem) { }

    const std::string show() const;
    friend std::istream& operator>>(std::istream& is, Object& obj);
};

using Objects = std::vector<Object>;

class RawEvent {
public:
    enum class EventStatus {Empty, Fill};

private:
    EventStatus status_;
    Header header_;
    std::vector<Object> objects_;

public:
    explicit RawEvent(EventStatus s = EventStatus::Empty) : status_(s) { }
    explicit RawEvent(const Objects& objects)
        : status_(EventStatus::Fill), objects_(objects) { }

    void set_event(const Header& header, const Objects& objects) {
        status_ = EventStatus::Fill;
        header_ = header;
        objects_ = objects;
    }
    Header header() const {
        return header_;
    }
    Objects objects() const {
        return objects_;
    }
    bool empty() const {
        return status_ == EventStatus::Empty;
    }
    void operator()(const EventStatus& s) {
        status_ = s;
    }

    const std::string show() const;
};

RawEvent ParseRawEvent(std::istream *is);
}  // namespace lhco

#endif  // SRC_PARSER_H_
