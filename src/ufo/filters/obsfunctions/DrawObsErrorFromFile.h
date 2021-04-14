/*
 * (C) Copyright 2021 Met Office UK
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef UFO_FILTERS_OBSFUNCTIONS_DRAWOBSERRORFROMFILE_H_
#define UFO_FILTERS_OBSFUNCTIONS_DRAWOBSERRORFROMFILE_H_

#include <string>

#include "ufo/filters/obsfunctions/DrawValueFromFile.h"
#include "ufo/filters/obsfunctions/ObsFunctionBase.h"

namespace ufo {

/// \brief Derive observation error from a file representing the variance or the covariance
/// matrix.
/// \details See NetCDFInterpolator for details on the format of this file.
///
/// ### example configurations: ###
///
/// \code{.yaml}
///     - Filter: Perform Action
///       filter variables:
///       - name: air_temperature
///       action:
///         name: assign error
///         error function:
///           name: DrawObsErrorFromFile@ObsFunction
///           options:
///             file: <filepath>
///             interpolation:
///             - name: channel_number@MetaData
///               method: exact
///             - name: satellite_id@MetaData
///               method: exact
///             - name: processing_center@MetaData
///               method: exact
///             - name: air_pressure@MetaData
///               method: linear
/// \endcode
///
class DrawObsErrorFromFile : public ObsFunctionBase {
 public:
  static const std::string classname() {return "DrawObsErrorFromFile";}

  explicit DrawObsErrorFromFile(const eckit::LocalConfiguration &);

  void compute(const ObsFilterData &, ioda::ObsDataVector<float> &) const;
  const ufo::Variables & requiredVariables() const;

 private:
  DrawValueFromFile drawValueFromFile_;
};

}  // namespace ufo

#endif  // UFO_FILTERS_OBSFUNCTIONS_DRAWOBSERRORFROMFILE_H_
