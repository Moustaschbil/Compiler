#ifndef _PASSE_H_
#define _PASSE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "defs.h"
#include "utils/mips_inst.h"
#include "utils/context.h"
#include "utils/env.h"
#include "utils/registers.h"


bool echelon;

void afficher_noeud(node_t noeud);
void passe_uno(node_t root);
void create_print_inst(node_t root);
int get_load(node_t root);
void passe_dos(node_t root);

#endif
