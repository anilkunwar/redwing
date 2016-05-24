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

#include "MuMaterial.h"

template<>
InputParameters validParams<MuMaterial>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredParam<Real>("mu","magnetic magnetic permeability");
  params.addRequiredCoupledVar("Ax","Magnetic vector potential x component");
  params.addRequiredCoupledVar("Ay","Magnetic vector potential y component");
  params.addRequiredCoupledVar("Az","Magnetic vector potential z component");
  return params;
}

MuMaterial::MuMaterial(const InputParameters & parameters) :
  Material(parameters),
  _mu_param(getParam<Real>("mu")),
  _mu(declareProperty<Real>("mu")),
  _B(declareProperty<RealVectorValue>("B")),
  _grad_ax(coupledGradient("Ax")),
  _grad_ay(coupledGradient("Ay")),
  _grad_az(coupledGradient("Az"))
{
}

void
MuMaterial::computeQpProperties()
{
  _mu[_qp] = _mu_param;
  //_B[_qp] = RealVectorValue(1,1,1);
  _B[_qp](0) = ( _grad_az[_qp](1) - _grad_ay[_qp](2) );
  _B[_qp](1) = ( _grad_ax[_qp](2) - _grad_az[_qp](0) );
  _B[_qp](2) = ( _grad_ay[_qp](0) - _grad_ax[_qp](1) );

}
