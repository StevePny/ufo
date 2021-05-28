/*
 * (C) Copyright 2021 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include "ufo/filters/obsfunctions/SunGlintAngle.h"

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "ioda/ObsDataVector.h"
#include "ufo/filters/Variable.h"
#include "ufo/utils/Constants.h"

namespace ufo {

static ObsFunctionMaker<SunGlintAngle> makerSunGlintAngle_("SunGlintAngle");

SunGlintAngle::SunGlintAngle(const eckit::LocalConfiguration & conf)
  : invars_() {
  // Include list of required data from ObsSpace
  invars_ += Variable("solar_zenith_angle@MetaData");
  invars_ += Variable("solar_azimuth_angle@MetaData");
  invars_ += Variable("sensor_zenith_angle@MetaData");
  invars_ += Variable("sensor_azimuth_angle@MetaData");
}

// -----------------------------------------------------------------------------

SunGlintAngle::~SunGlintAngle() {}

// -----------------------------------------------------------------------------

void SunGlintAngle::compute(const ObsFilterData & in,
                                    ioda::ObsDataVector<float> & out) const {
  // Get dimension
  const size_t nlocs = in.nlocs();

  // This is taken from AMSR2's Sun_glint_angle calculation in GSI's subroutine "setuprad.f90".
  std::vector<float> &sun_glint = out[0];
  std::vector<float> sun_zenith(nlocs), sun_azimuth(nlocs);
  std::vector<float> sat_zenith(nlocs), sat_azimuth(nlocs);

  in.get(Variable("solar_zenith_angle@MetaData"), sun_zenith);
  in.get(Variable("solar_azimuth_angle@MetaData"), sun_azimuth);
  in.get(Variable("sensor_zenith_angle@MetaData"), sat_zenith);
  in.get(Variable("sensor_azimuth_angle@MetaData"), sat_azimuth);
  for (size_t iloc = 0; iloc < nlocs; ++iloc) {
    sun_zenith[iloc]  *= Constants::deg2rad;
    sun_azimuth[iloc] *= Constants::deg2rad;
    sat_zenith[iloc]  *= Constants::deg2rad;
    sat_azimuth[iloc] *= Constants::deg2rad;
    float cosza  = cos(sat_zenith[iloc]);
    float bearaz = sun_azimuth[iloc] - sat_azimuth[iloc] + M_PI;
    sun_glint[iloc] = acos(cos(sun_zenith[iloc])*cosza + sin(sun_zenith[iloc])
                            *sin(sat_zenith[iloc])*cos(bearaz))*Constants::rad2deg;
  }
}

// -----------------------------------------------------------------------------

const ufo::Variables & SunGlintAngle::requiredVariables() const {
  return invars_;
}

// -----------------------------------------------------------------------------

}  // namespace ufo
