// Copyright 2018, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef PFAEDLE_DEF_H_
#define PFAEDLE_DEF_H_

#include <unistd.h>
#include <string>
#include "util/log/Log.h"
#include "util/Misc.h"
#include "util/geo/Geo.h"
#include "util/geo/PolyLine.h"

#define __str_a(s) __str_b(s)
#define __str_b(s) #s
#define __str_c(s) s ## 1
#define __str_d(s) __str_c(s)

#if !defined(PFDL_PREC) || (__str_d(PFDL_PREC) == 1)
#undef PFDL_PREC
#define PFDL_PREC double
#endif

#define PFDL_PREC_STR __str_a(PFDL_PREC)

#define POINT util::geo::Point<PFDL_PREC>
#define LINE util::geo::Line<PFDL_PREC>
#define BOX util::geo::Box<PFDL_PREC>
#define POLYLINE util::geo::PolyLine<PFDL_PREC>

#define BOX_PADDING 2500

namespace pfaedle {

// _____________________________________________________________________________
inline std::string getTmpFName(std::string dir, std::string postf) {
  if (postf.size()) postf = "-" + postf;
  if (!dir.size()) dir = util::getTmpDir();
  if (dir.size() && dir.back() != '/') dir = dir + "/";

  std::string f = dir + ".pfaedle-tmp" + postf;

  size_t c = 0;

  while (access(f.c_str(), F_OK) != -1) {
    c++;
    if (c > 10000) {
      // giving up...
      LOG(ERROR) << "Could not find temporary file name!";
      exit(1);
    }
    std::stringstream ss;
    ss << dir << ".pfaedle-tmp" << postf << "-" << std::rand();
    f = ss.str().c_str();
  }

  return f;
}

}  // namespace pfaedle

#endif  // PFAEDLE_DEF_H_
