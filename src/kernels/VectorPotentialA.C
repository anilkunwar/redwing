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

#include "VectorPotentialA.h"

template<>
InputParameters validParams<VectorPotentialA>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<unsigned>("component","component");
  return params;
}

VectorPotentialA::VectorPotentialA(const InputParameters &parameters):
  Kernel(parameters),
  //_component(getParameter<unsigned>("component")),
  _mu(getMaterialPropertyByName<Real>("mu"))
{
}

Real
VectorPotentialA::computeQpResidual()
{
  return _grad_test[_i][_qp] * _grad_u[_qp] / _mu[_qp];
}

Real
VectorPotentialA::computeQpJacobian()
{
  return _grad_test[_i][_qp] * _grad_phi[_i][_qp] / _mu[_qp];
}
