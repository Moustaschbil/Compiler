#include "passe.h"

static node_t* list;
int op1, op2;
node_type type_noeud;
bool fin = false;
void passe_uno(node_t root)
{
        if(root == NULL)
                EXIT_SUCCESS;
        afficher_noeud(root);

        switch(root->nature)
        {
                case NODE_PROGRAM: push_global_context();
                                        break;
                case NODE_IDENT: if(strcmp(root->ident, "main") != 0)
                                {
                                        node_t res = (node_t)get_decl_node(root->ident);
                                        if (res == NULL)
                                        {
                                                printf("Variable '%s' non defini", root->ident);
                                                return;
                                        }
                                        else
                                        {
                                                root->type = res->type;
                                                root-> decl_node = res;
                                        }
                                }
                                else
                                {
                                        if(root->type != TYPE_VOID)
                                        {
                                                printf("On entre dans le \"main\" \n");
                                        }
                                }//root->type = root->opr[0]->type; get_d
                                break;
                case NODE_BLOCK: push_context();
                                        break;
                case NODE_DECL: if(env_add_element(root->opr[0]->ident, root, 4) < 0)
                                {
                                        root->opr[0]->offset = env_add_element(root->opr[0]->ident, root, 4);
                                        if(root->opr[0]->offset < 0)
                                        {
                                                printf("Erreur ligne %d: Variable défini plusieurs fois\n", root->lineno);
                                                EXIT_FAILURE;
                                        }
                                        else if(root->opr[0]->type != root->opr[1]->type)
                                        {
                                                printf("Erreur ligne %d: Initialisation d'une variable de mauvais type\n", root->lineno);
                                                EXIT_FAILURE;
                                        }
                                        else
                                                root->opr[0]->decl_node = NULL;
                                }
                                else
                                {
                                        printf("Variable deja déclarée\n");
                                }

                                break;

                case NODE_DECLS: if(root->opr[0]->type == TYPE_VOID)
                                {
                                        printf("Erreur ligne %d: Variable de type void\n", root->lineno);
                                        EXIT_FAILURE;
                                };
                                break;

                case NODE_STRINGVAL: root->offset = add_string(root->str);
		                     root->type = TYPE_STRING;
		                     break;

                case NODE_TYPE: type_noeud = root->type;
                                break;

                case NODE_INTVAL: root->type = TYPE_INT;
                                        break;

                case NODE_BOOLVAL: root->type = TYPE_BOOL;
                                        break;
                case NODE_AFFECT: if(root->opr[0] == NULL || root->opr[1] == NULL)
                                        break;
                                if(root->opr[0]->type == root->opr[1]->type)
                                        root->type = root->opr[0]->type;
                                if(root->opr[0]->type != root->opr[1]->type)
                                {
                                        printf("Erreur ligne %d: Les variable doivent être de même types différents\n", root->lineno);
                                        EXIT_FAILURE;
                                }
                                break;
                case NODE_FUNC: echelon=false;//A changer
                                reset_env_current_offset();
                                reset_temporary_max_offset();
                                set_max_registers(DEFAULT_MAX_REGS);
                                break;

                case NODE_PLUS:
		case NODE_MINUS:
		case NODE_MUL:
		case NODE_DIV:
		case NODE_MOD:
                case NODE_BAND:
		case NODE_SRL:
		case NODE_SRA:
		case NODE_SLL:
		case NODE_BOR:
		case NODE_BXOR: if(root->opr[0]->type != TYPE_INT || root->opr[1]->type != TYPE_INT)
                                {
                                        printf("Erreur ligne %d: les opérateurs doivent être des entiers\n", root->lineno);
                                        EXIT_FAILURE;
                                }
                                else
                                        root->type = TYPE_INT;
                                break;

		case NODE_LT:
		case NODE_GT:
		case NODE_LE:
		case NODE_GE: if(root->opr[0]->type == TYPE_INT || root->opr[1]->type == TYPE_INT)
                                {
                                        printf("Erreur ligne %d: les opérateurs doivent être des booléeans\n", root->lineno);
                                        EXIT_FAILURE;
                                }
                                else
                                        root->type = TYPE_BOOL;
                                break;

		case NODE_EQ:
		case NODE_NE: if(root->opr[0]->type != root->opr[1]->type)
                                {
                                        printf("Erreur ligne %d: les opérateurs doivent être de même type\n", root->lineno);
                                        EXIT_FAILURE;
                                }
                                else
                                        root->type = TYPE_BOOL;
                                break;
		case NODE_AND:
		case NODE_OR: if(root->opr[0]->type != TYPE_BOOL || root->opr[1]->type != TYPE_BOOL)
                                {
                                        printf("Erreur ligne %d: les opérateurs doivent être des booléens\n", root->lineno);
                                        EXIT_FAILURE;
                                }
                                else
                                        root->type = TYPE_BOOL;
                                break;


                case NODE_NOT:if(root->opr[0]->type != TYPE_BOOL)
                                {
                                        printf("Erreur ligne %d: Opérateur doit être de type booléen\n", root->lineno);
                                        EXIT_FAILURE;
                                }
                                else
                                        root->type = TYPE_BOOL;
                                break;

                case NODE_BNOT:
                case NODE_UMINUS: if(root->opr[0]->type!= TYPE_INT)
                                        printf("Erreur ligne %d: Opérateur doit être de type entier\n", root->lineno);
                                else
                                        root->type = TYPE_INT;
                                break;

                case NODE_WHILE:
                case NODE_IF: if(root->opr[0]->type != TYPE_BOOL)
                                {
                                        printf("Erreur ligne %d: Condition doit être un booléen\n", root->lineno);
                                        EXIT_FAILURE;
                                }
                                break;

                case NODE_DOWHILE:
                case NODE_FOR:if(root->opr[1]->type != TYPE_BOOL)
                                {
                                        printf("Erreur ligne %d: Condition doit être un booléen\n", root->lineno);
                                        EXIT_FAILURE;
                                }
                                break;
                case NODE_LIST: break;
                case NONE: return;
                                break;
                default: printf("défault passe 1.....%d\n", root->nature);
                        break;
        }

        for(int i = 0; i < root->nops; i++)
        {
                if(root->opr[i])
                {
                        passe_uno(root->opr[i]);
                }

        }
}

void afficher_noeud(node_t noeud)
{
        switch (noeud->nature)
        {
                case NODE_PROGRAM: printf("NODE_PROGRAM\n");
                                break;

                case NODE_IDENT: printf("NODE_IDENT\n");
                                break;

                case NODE_BLOCK: printf("NODE_BLOCK\n");
                                break;

                case NODE_LIST: printf("NODE_LIST\n");
                                break;

                case NODE_DECL: printf("NODE_DECL\n");
                                break;

                case NODE_DECLS: printf("NODE_DECLS\n");
                                break;

                case NODE_STRINGVAL: printf("NODE_STRINGVAL\n");
                                break;

                case NODE_INTVAL: printf("NODE_INTVAL\n");
                                break;

                case NODE_BOOLVAL: printf("NODE_BOOLVAL\n");
                                break;

                case NODE_AFFECT: printf("NODE_AFFECT\n");
                                break;
                case NODE_FUNC: printf("NODE_FUNC\n");
                                break;

                case NODE_PLUS: printf("NODE_PLUS\n");
                                break;

                case NODE_MINUS: printf("NODE_MINUS\n");
                                break;

                case NODE_MUL: printf("NODE_MUL\n");
                                break;

                case NODE_DIV: printf("NODE_DIV\n");
                                break;

                case NODE_MOD: printf("NODE_MOD\n");
                                break;

                case NODE_BAND: printf("NODE_BAND\n");
                                break;

                case NODE_TYPE: printf("NODE_TYPE\n");
                                break;

                case NODE_SRL: printf("NODE_SRL\n");
                                break;

                case NODE_SRA: printf("NODE_SRA\n");
                                break;

                case NODE_SLL: printf("NODE_SLL\n");
                                break;

                case NODE_BOR: printf("NODE_BOR\n");
                                break;

                case NODE_BXOR: printf("NODE_BXOR\n");
                                break;

                case NODE_LT: printf("NODE_LT\n");
                                break;

                case NODE_GT: printf("NODE_GT\n");
                                break;

                case NODE_LE: printf("NODE_LE\n");
                                break;

                case NODE_GE: printf("NODE_GE\n");
                                break;

                case NODE_EQ: printf("NODE_EQ\n");
                                break;

                case NODE_NE: printf("NODE_NE\n");
                                break;

                case NODE_AND:printf("NODE_AND\n");
                                break;

                case NODE_OR: printf("NODE_OR\n");
                                break;

                case NODE_NOT:printf("NODE_NOT\n");
                                break;

                case NODE_BNOT: printf("NODE_BNOT\n");
                                break;

                case NODE_WHILE: printf("NODE_WHILE\n");
                                break;

                case NODE_IF: printf("NODE_IF\n");
                                break;

                case NODE_DOWHILE: printf("NODE_DOWHILE\n");
                                break;

                case NODE_FOR:printf("NODE_FOR\n");
                                break;

                default:
                                break;
        }
}

int get_load(node_t root)
{
        if(root == NULL)
        {
                //printf("Erreur chargement de registre...VIDE\n");
                return get_current_reg();
        }
        if(root->nature == NODE_INTVAL || root->nature == NODE_BOOLVAL)
                create_ori_inst(get_current_reg(), 0, root->value);
        else if(root->nature == NODE_IDENT)
        {
                if(!root->global_decl)
                        create_lw_inst(get_current_reg(), root->offset, stack_reg);
                else
                {
                        create_lui_inst(get_current_reg(),data_start);
                        create_lw_inst(get_current_reg(), root->offset, get_current_reg());
                }
        }
        else
        {
                passe_dos(root);
        }
        return get_current_reg();
}

void passe_dos(node_t root)
{
        int32_t label0, label1;
        Liste* list_global_decl;
        if(fin)
        {
                printf("ALLLLLLLLLLLLLLLLLo\n");
                return;
        }

        switch(root->nature)
        {
                case NONE:
                          break;
                case NODE_PROGRAM: create_data_sec_inst();
                                if(root->opr[0] != NULL)
                                        passe_dos(root->opr[0]);
                                while(list_global_decl != NULL)
                                {
                                        create_asciiz_inst(NULL, list_global_decl->root->str);
                                        list_global_decl = list_global_decl->suiv;
                                }
                                create_text_sec_inst();
                                passe_dos(root->opr[1]);
                                break;
                case NODE_IDENT: if(root->decl_node) //OK
                                {
			                     if(root->decl_node->global_decl)
                                             {
                                                     create_lui_inst(4, data_start);
				                     create_lw_inst(4, root->decl_node->offset, 4);
			                     }
			                     else
                                                     create_lw_inst(4, root->decl_node->offset, stack_reg);
		                }
		                else
			                     create_lw_inst(4, root->offset, stack_reg);
                                break;
                /*case NODE_BLOCK:
                                break;
                case NODE_DECLS:
                                break;*/

                case NODE_DECL: if(root->opr[1])
                                        create_word_inst(root->opr[0]->ident, root->opr[1]->value);
		                else
                                        create_word_inst(root->opr[0]->ident, 0);
                                root->opr[0]->global_decl = true;
                                break;




                                // if(root->opr[0]->global_decl) // NOT OK
                                // {
                                //         if(root->opr[1] != NULL)
                                //                 create_word_inst(root->opr[0]->ident, root->opr[1]->value);
                                //         else
                                //                 create_word_inst(root->opr[0]->ident, 0);
                                //         break;
                                // }
                                // else
                                // {
                                //         if(root->opr[1] != NULL)
                                //         {
                                //                 if(root->opr[1]->nature == NODE_IDENT)
                                //                 {
                                //                         create_lui_inst(get_current_reg(), data_start);
                                //                         create_lw_inst(get_current_reg(), root->opr[1]->decl_node->offset, get_current_reg());
                                //                         create_sw_inst(get_current_reg(), root->opr[0]->decl_node->offset, stack_reg);
                                //                 }
                                //                 else if(root->opr[1]->nature == NODE_BOOLVAL || root->opr[1]->nature == NODE_INTVAL)
                                //                 {
                                //                         create_ori_inst(get_current_reg(), 0, root->opr[1]->value );
                                //                         create_sw_inst(get_current_reg(), root->opr[0]->offset, stack_reg);
                                //                 }
                                //         }
                                //         else
                                //         {
                                //                 create_sw_inst(stack_reg, root->opr[0]->offset, stack_reg);
                                //         }
                                // }
                                break;

                case NODE_STRINGVAL: create_lui_inst(4, data_start); //OK jusqu'à case default
                                        create_ori_inst(4,4,root->offset);
                                        create_ori_inst(2,0,4);
                                        create_syscall_inst();
                                        break;

                case NODE_BLOCK:
                case NODE_LIST:
                case NODE_DECLS:
                case NODE_TYPE: break;

                case NODE_INTVAL:
                case NODE_BOOLVAL: create_ori_inst(get_current_reg(), 0, root->value);
                                        break;


                case NODE_AFFECT: passe_dos(root->opr[1]);
                                create_sw_inst(get_current_reg(), root->opr[0]->offset, stack_reg);
                                break;

                case NODE_FUNC: create_label_str_inst(root->opr[1]->ident);
                                create_addiu_inst(stack_reg, stack_reg, -root->offset);
                                passe_dos(root->opr[2]);
                                create_ori_inst(2, 0, 10);
                        	create_syscall_inst();
                                printf("FIN DU PROGRAMME !!\n");
                                //fin=true;
                                break;

                case NODE_PLUS: op1 = get_load(root->opr[0]);
                                passe_dos(root->opr[1]);
                                create_addu_inst(get_current_reg(), op1,get_current_reg());
                                break;
                case NODE_MINUS:op1 = get_load(root->opr[0]);
                                passe_dos(root->opr[1]);
                                create_subu_inst(get_current_reg(), op1, get_current_reg());
                                break;
                case NODE_MUL: op1 = get_load(root->opr[0]);
                                passe_dos(root->opr[1]);
                                create_mult_inst(op1, get_current_reg());
                                create_mflo_inst(get_current_reg());
                                break;
                case NODE_DIV: op1 = get_load(root->opr[0]);
                                passe_dos(root->opr[1]);
                                create_div_inst(op1, get_current_reg());
                                create_mflo_inst(get_current_reg());
                                break;
                case NODE_MOD: op1 = get_load(root->opr[0]);
                                passe_dos(root->opr[1]);
                                create_div_inst(op1, get_current_reg());
                                create_mfhi_inst(get_current_reg());
                                break;

                case NODE_BAND: op1 = get_load(root->opr[0]);
                                passe_dos(root->opr[1]);
                                create_and_inst(get_current_reg(),op1,get_current_reg());
                                break;

                case NODE_SRL: op1 = get_load(root->opr[0]);
                                passe_dos(root->opr[1]);
                                create_srlv_inst(get_current_reg(),op1,get_current_reg());
                                break;

                case NODE_SRA: op1 = get_load(root->opr[0]);
                                passe_dos(root->opr[1]);
                                create_srav_inst(get_current_reg(),op1,get_current_reg());
                                break;

                case NODE_SLL: op1 = get_load(root->opr[0]);
                                passe_dos(root->opr[1]);
                                create_sllv_inst(get_current_reg(),op1,get_current_reg());
                                break;

                case NODE_BOR: op1 = get_load(root->opr[0]);
                                passe_dos(root->opr[1]);
                                create_or_inst(get_current_reg(),op1,get_current_reg());
                                break;
                case NODE_BXOR: op1 = get_load(root->opr[0]);
                                passe_dos(root->opr[1]);
                                create_xor_inst(get_current_reg(), op1, get_current_reg());
                                break;

                case NODE_LT: op1 = get_load(root->opr[0]);
                                passe_dos(root->opr[1]);
                                create_slt_inst(get_current_reg(), op1, get_current_reg());
                                break;
		case NODE_GT: op1 = get_load(root->opr[0]);
                                passe_dos(root->opr[1]);
                                create_slt_inst(get_current_reg(), get_current_reg(), op1);
                                break;
		case NODE_LE: op1 = get_load(root->opr[0]);
                                passe_dos(root->opr[1]);
                                create_slt_inst(get_current_reg(), op1, get_current_reg());
                                create_xori_inst(get_current_reg(),get_current_reg(),1);
                                break;
		case NODE_GE: op1 = get_load(root->opr[0]);
                                op2 = get_load(root->opr[1]);
                                create_slt_inst(op1,op1,op2);
                                create_xori_inst(get_current_reg(),op1,1);
                                break;

		case NODE_EQ: op1 = get_load(root->opr[0]);
                                op2 = get_load(root->opr[1]);
                                create_slt_inst(get_current_reg(),op1,op2);
                                create_slt_inst(op1,op2,op1);
                                create_or_inst(op1,get_current_reg(),op1);
                                create_xori_inst(get_current_reg(),op1,1);
                                break;

		case NODE_NE: op1 = get_load(root->opr[0]);
                                op2 = get_load(root->opr[1]);
                                create_slt_inst(get_current_reg(),op1,op2);
                                create_slt_inst(op1,op2,op1);
                                create_or_inst(get_current_reg(),get_current_reg(),op1);
                                break;

        	case NODE_AND: op1 = get_load(root->opr[0]);
                                passe_dos(root->opr[1]);
                                create_and_inst(get_current_reg(),op1,get_current_reg());
                                break;

        	case NODE_OR: op1 = get_load(root->opr[0]);
                                passe_dos(root->opr[1]);
                                create_or_inst(get_current_reg(),op1,get_current_reg());
                                break;

                case NODE_NOT: passe_dos(root->opr[0]);
                                create_xori_inst(get_current_reg(), get_current_reg(), 1);
                                break;

                case NODE_BNOT: passe_dos(root->opr[0]);
                                create_nor_inst(get_current_reg(),get_current_reg(),0);
                                break;
                case NODE_UMINUS: passe_dos(root->opr[0]);
                                create_subu_inst(get_current_reg(),0,get_current_reg());
                                break;

                case NODE_WHILE: label0 = get_new_label();
                                label1 = get_new_label();
                                create_label_inst(label0);
                                passe_dos(root->opr[0]);
                                create_beq_inst(get_current_reg(), 0, label1);
                                passe_dos(root->opr[1]);
                                create_j_inst(label0);
                                create_label_inst(label1);
                                break;

                case NODE_IF: label0 = get_new_label();
                                passe_dos(root->opr[0]);
                                create_beq_inst(get_current_reg(), 0, label0);
                                passe_dos(root->opr[1]);
                                if (root->nops == 3)
                                {
                                        label1 = get_new_label();
                                        create_j_inst(label1);
                                        create_label_inst(label0);
                                        passe_dos(root->opr[2]);
                                        create_label_inst(label1);
                                }
                                else
                                        create_label_inst(label0);
                                break;

                case NODE_DOWHILE:label0 = get_new_label();
                                create_label_inst(label0);
                                passe_dos(root->opr[0]);
                                passe_dos(root->opr[1]);
                                create_bne_inst(get_current_reg(), 0, label0);
                                break;
                case NODE_FOR: label0 = get_new_label();
		              label1 = get_new_label();
                              passe_dos(root->opr[0]);
                              create_label_inst(label0);
                              passe_dos(root->opr[1]);
                              create_beq_inst(get_current_reg(), 0, label1);
                              passe_dos(root->opr[3]);
                              passe_dos(root->opr[2]);
                              create_j_inst(label0);
                              create_label_inst(label1);
                              break;
                case NODE_PRINT: if(root->nature == NODE_IDENT)
                                {
                                        if(root->global_decl)
                                        {
                                                create_lui_inst(4,data_start);
                                                create_lw_inst(4, root->offset, 4);
                                        }
                                        else
                                                create_lw_inst(4, root->offset, stack_reg);
                                        create_addiu_inst(2,0,1);
                                        create_syscall_inst();
                                }
                                else if(root->nature == NODE_STRINGVAL)
                                {
                                        create_lui_inst(4, data_start);
                                        create_addiu_inst(4,4,root->offset);
                                        create_ori_inst(2,0,4);
                                        create_syscall_inst();
                                }
                                else
                                {
                                        /*for(int i = 0; i < root->nops; i++)
                                        {
                                                create_print_inst(root->opr[i]);
                                        }*/
                                }
                                break;
                default: printf("Oupsi je suis dans le default de passe_dos()..........%d\n", root->nature);
                        /*for(int i = 0; i < root->nops; i++)
                                if(root->opr[i] != NULL)
                                        passe_dos(root->opr[i]);*/
                        break;
        }
        for(int i = 0; i < root->nops; i++)
        {
                if(root->opr[i])
                {
                        passe_dos(root->opr[i]);
                }

        }
}
