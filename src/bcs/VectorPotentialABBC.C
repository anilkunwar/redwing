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

#include "VectorPotentialABBC.h"

template<>
InputParameters validParams<VectorPotentialABBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<Real>("b","outward boundary flux density");
  params.addRequiredCoupledVar("Ax","Magnetic vector potential x component");
  params.addRequiredCoupledVar("Ay","Magnetic vector potential y componetnt");
  params.addRequiredCoupledVar("Az","Magnetic vector potential z componetnt");
  return params;
}

VectorPotentialABBC::VectorPotentialABBC(const InputParameters & parameters) :
  IntegratedBC(parameters),
  _ax_var(coupled("Ax")),
  _ay_var(coupled("Ay")),
  _az_var(coupled("Az")),
  _grad_ax(coupledGradient("Ax")),
  _grad_ay(coupledGradient("Ay")),
  _grad_az(coupledGradient("Az")),
  _b(getParam<Real>("b"))
{
}

Real
VectorPotentialABBC::computeQpResidual()
{
  return _test[_i][_qp] * ( - _b + 
     ( _grad_az[_qp](1) - _grad_ay[_qp](2) ) * _normals[_qp](0)
    +( _grad_ax[_qp](2) - _grad_az[_qp](0) ) * _normals[_qp](1)
    +( _grad_ay[_qp](0) - _grad_ax[_qp](1) ) * _normals[_qp](2)
    );
}

Real
VectorPotentialABBC::computeQpJacobian()
{
  return computeQpOffDiagJacobian(_j);
}

Real
VectorPotentialABBC::computeQpOffDiagJacobian(unsigned jvar)
{
  if ( jvar == _ax_var )
  {
    return _test[_i][_qp] * (
      _grad_phi[jvar][_qp](2) * _normals[_qp](1)
    - _grad_phi[jvar][_qp](1) * _normals[_qp](2)
    );
  }
  else if ( jvar == _ay_var )
  {
    return _test[_i][_qp] * (
      -_grad_phi[jvar][_qp](2) * _normals[_qp](0)
      +_grad_phi[jvar][_qp](0) * _normals[_qp](2)
    );
  }
  else //if ( jvar == _az_var )
  {
    return _test[_i][_qp] * (
      _grad_phi[jvar][_qp](1) * _normals[_qp](0)
     -_grad_phi[jvar][_qp](0) * _normals[_qp](1)
    );
  }
  //else
  //{
  //raise
  //}
}
