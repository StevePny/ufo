/*
 * (C) Copyright 2018-2019 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef UFO_UTILS_INTSETPARSER_H_
#define UFO_UTILS_INTSETPARSER_H_

#include <set>
#include <string>

namespace ufo {
  std::set<int> parseIntSet(const std::string &);

  template<typename TT>
  bool contains(std::set<TT> & set, const TT & elem) {
    return set.find(elem) != set.end();
  }

  void splitVarGroup(const std::string &, std::string &, std::string &);
}  // namespace ufo

#endif  // UFO_UTILS_INTSETPARSER_H_
