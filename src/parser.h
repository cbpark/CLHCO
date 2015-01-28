#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include "object.h"

namespace lhco {
RawEvent ParseRawEvent(std::istream *is);
}  // namespace lhco

#endif  // SRC_PARSER_H_
