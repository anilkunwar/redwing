#include "RedwingApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

#include "VectorPotentialA.h"
#include "VectorPotentialAJ0.h"
#include "VectorPotentialABBC.h"
#include "MuMaterial.h"
#include "VectorPotentialABC.h"

template<>
InputParameters validParams<RedwingApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_output_syntax") = false;

  return params;
}

RedwingApp::RedwingApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  RedwingApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  RedwingApp::associateSyntax(_syntax, _action_factory);
}

RedwingApp::~RedwingApp()
{
}

// External entry point for dynamic application loading
extern "C" void RedwingApp__registerApps() { RedwingApp::registerApps(); }
void
RedwingApp::registerApps()
{
  registerApp(RedwingApp);
}

// External entry point for dynamic object registration
extern "C" void RedwingApp__registerObjects(Factory & factory) { RedwingApp::registerObjects(factory); }
void
RedwingApp::registerObjects(Factory & factory)
{
  registerKernel(VectorPotentialA);
  registerKernel(VectorPotentialAJ0);
  registerBoundaryCondition(VectorPotentialABBC);
  registerMaterial(MuMaterial);
  registerBoundaryCondition(VectorPotentialABC);
}

// External entry point for dynamic syntax association
extern "C" void RedwingApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { RedwingApp::associateSyntax(syntax, action_factory); }
void
RedwingApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
