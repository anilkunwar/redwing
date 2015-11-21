#ifndef REDWINGAPP_H
#define REDWINGAPP_H

#include "MooseApp.h"

class RedwingApp;

template<>
InputParameters validParams<RedwingApp>();

class RedwingApp : public MooseApp
{
public:
  RedwingApp(InputParameters parameters);
  virtual ~RedwingApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* REDWINGAPP_H */
