// Copyright 2023 DeepMind Technologies Limited
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef MUJOCO_PLUGIN_ELASTICITY_MEMBRANE_H_
#define MUJOCO_PLUGIN_ELASTICITY_MEMBRANE_H_

#include <optional>
#include <utility>
#include <vector>

#include <mujoco/mjdata.h>
#include <mujoco/mjmodel.h>
#include <mujoco/mjtnum.h>
#include "elasticity.h"


namespace mujoco::plugin::elasticity {

class Membrane {
 public:
  // Returns a new Membrane instance or nullopt on failure.
  static std::optional<Membrane> Create(const mjModel* m, mjData* d,
                                     int instance);
  Membrane(Membrane&&) = default;

  Membrane& operator=(Membrane&& other) = default;

  void Compute(const mjModel* m, mjData* d, int instance);

  static void RegisterPlugin();

  int f0;  // index of corresponding flex
  int i0;  // index of first body
  int nc;  // number of quads in the grid
  int nv;  // number of vertices (bodies) in the Membrane
  int ne;  // number of edges in the Membrane

  // precomputed quantities
  std::vector<mjtNum> prev;                 // previous-step lengths  (ne x 1)
  std::vector<mjtNum> elongation;           // edge elongation        (ne x 1)
  std::vector<mjtNum> force;                // force at all vertices  (nv x 3)

  mjtNum damping;

 private:
  Membrane(const mjModel* m, mjData* d, int instance, mjtNum damp);
};

}  // namespace mujoco::plugin::elasticity

#endif  // MUJOCO_PLUGIN_ELASTICITY_MEMBRANE_H_
