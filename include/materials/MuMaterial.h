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

#ifndef MUMATERIAL_H
#define MUMATERIAL_H

#include "Material.h"

class MuMaterial;

template<>
InputParameters validParams<MuMaterial>();

class MuMaterial : public Material
{
public:
  MuMaterial(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

private:
  Real _mu_param;
  MaterialProperty<Real> & _mu;
  MaterialProperty<RealVectorValue> & _B;
  VariableGradient & _grad_ax;
  VariableGradient & _grad_ay;
  VariableGradient & _grad_az;
};

#endif // MUMATERIAL_H
