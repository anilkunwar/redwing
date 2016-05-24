[GlobalParams]
  k = 1e2
[]

[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 10
  ny = 10
  nz = 10
[]

[Variables]
  [./Ax]
    family = LAGRANGE
    order = FIRST 
  [../]
  [./Ay]
    family = LAGRANGE
    order = FIRST
  [../]
  [./Az]
    family = LAGRANGE
    order = FIRST
  [../]
[]

[Kernels]
  [./VectorPotentialAx]
    type = VectorPotentialA
    variable = Ax
    component = 0
  [../]
  [./VectorPotentialAy]
    type = VectorPotentialA
    variable = Ay
    component = 1
  [../]
  [./VectorPotentialAz]
    type = VectorPotentialA
    variable = Az
    component = 2
  [../]
[]

[Materials]
  [./muMat]
    type = MuMaterial
    block = 0
    Ax = Ax
    Ay = Ay
    Az = Az
    mu = 1.2566e-6 #H/m
    output_properties = 'B'
    outputs = out
  [../]
[]

[BCs]
  active = 'noFluxX noFluxY noFluxZ topFluxX topFluxY topFluxZ bottomFluxX bottomFluxY bottomFluxZ'
  [./naturalx]
    type = VectorPotentialABC
    boundary = 'left right front back top bottom'
    variable = Ax
  [../]
  [./naturaly]
    type = VectorPotentialABC
    boundary = 'left right front back top bottom'
    variable = Ay
  [../]
  [./naturalz]
    type = VectorPotentialABC
    boundary = 'left right front back top bottom'
    variable = Az
  [../]
  [./noFluxX]
    type = VectorPotentialABBC
    variable = Ax
    component = 0
    boundary = 'left right front back'
    b = 0
    Ax = Ax
    Ay = Ay
    Az = Az
  [../]
  [./noFluxY]
    type = VectorPotentialABBC
    variable = Ay
    component = 1
    boundary = 'left right front back'
    b = 0
    Ax = Ax
    Ay = Ay
    Az = Az
  [../]
  [./noFluxZ]
    type = VectorPotentialABBC
    variable = Az
    component = 2
    boundary = 'left right front back'
    b = 0
    Ax = Ax
    Ay = Ay
    Az = Az
  [../]
  [./topFluxX]
    type = VectorPotentialABBC
    variable = Ax
    component = 0
    boundary = top
    b = 1000
    Ax = Ax
    Ay = Ay
    Az = Az
  [../]
  [./topFluxY]
    type = VectorPotentialABBC
    variable = Ay
    component = 1
    boundary = top
    b = 1000
    Ax = Ax
    Ay = Ay
    Az = Az
  [../]
  [./topFluxZ]
    type = VectorPotentialABBC
    variable = Az
    component = 2
    boundary = top
    b = 1000
    Ax = Ax
    Ay = Ay
    Az = Az
  [../]
  [./bottomFluxX]
    type = VectorPotentialABBC
    variable = Ax
    component = 0
    boundary = bottom
    b = -1000
    Ax = Ax
    Ay = Ay
    Az = Az
  [../]
  [./bottomFluxY]
    type = VectorPotentialABBC
    variable = Ay
    component = 1
    boundary = bottom
    b = -1000
    Ax = Ax
    Ay = Ay
    Az = Az
  [../]
  [./bottomFluxZ]
    type = VectorPotentialABBC
    variable = Az
    component = 2
    boundary = bottom
    b = -1000
    Ax = Ax
    Ay = Ay
    Az = Az
  [../]
[]

[Preconditioning]
  active = 'debug'
  [./debug]
    type = FDP
  [../]
  [./my_prec]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Steady
  solve_type = 'PJFNK'
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  nl_rel_step_tol = 1e-5
  l_max_its = 25
[]

[Outputs]
  execute_on = 'INITIAL LINEAR NONLINEAR TIMESTEP_END FAILED'
  [./out]
    type = Exodus
  [../]
[]
