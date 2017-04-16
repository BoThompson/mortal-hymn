#pragma once
#ifndef __SCRIPTS_H
#define __SCRIPTS_H

#ifdef _DEBUG
#undef _DEBUG
#include <python.h>
#define _DEBUG
#else
#include <python.h>
#endif
#include <map>
#include "shader.h"

int setup_python();
void shutdown_python();
PyObject *loadPyModule(const char * const module_name);
PyObject *NewAI(const char *const fsm_name);

#endif