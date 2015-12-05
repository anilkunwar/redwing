/* -------------------------------------------------------------------------------
    redwing - a finite element solver for electromagnetic problems
    Copyright (C) 2015 Adam Lange

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
----------------------------------------------------------------------------- */

#include "VectorPotentialAJ0.h"

template<>
InputParameters validParams<VectorPotentialAJ0>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<unsigned>("component","component");
  return params;
}

VectorPotentialAJ0::VectorPotentialAJ0(const InputParameters & parameters) :
  Kernel(parameters),
  _j0(getMaterialProperty<RealVectorValue>("j0")),
  _component(getParam<unsigned>("component"))
{
}

Real
VectorPotentialAJ0::computeQpResidual()
{
  return -_test[_i][_qp]*_j0[_qp](_component);
}

Real
VectorPotentialAJ0::computeQpJacobian()
{
  return 0;
}
