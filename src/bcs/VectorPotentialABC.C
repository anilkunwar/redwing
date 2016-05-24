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

#include "VectorPotentialABC.h"

template<>
InputParameters validParams<VectorPotentialABC>()
{
  InputParameters params = validParams<IntegratedBC>();
  return params;
};

VectorPotentialABC::VectorPotentialABC(const InputParameters & parameters) :
  IntegratedBC(parameters),
  _mu(getMaterialProperty<Real>("mu"))
{
}

Real
VectorPotentialABC::computeQpResidual()
{
  return _test[_i][_qp]*1/_mu[_qp]*_grad_u[_qp]*_normals[_qp];
}

Real
VectorPotentialABC::computeQpJacobian()
{
  return _test[_i][_qp]*1/_mu[_qp]*_grad_phi[_j][_qp]*_normals[_qp];
}
