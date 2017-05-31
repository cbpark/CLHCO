/* Copyright (c) 2015, 2017, Chan Beom Park <cbpark@gmail.com> */

#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include "event.h"

namespace lhco {
RawEvent parseRawEvent(std::istream *is);

Event parseEvent(std::istream *is);
}  // namespace lhco

#endif  // SRC_PARSER_H_
