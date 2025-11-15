#ifdef WIN32
	#include <windows.h>
#endif
	
#include "Header/Head.h"


////////////////////////////////////////////////////

////////////////////////////////////////////////////

////////////////////////////////////////////////////

////////////////////////////////////////////////////

////////////////////////////////////////////////////



//--------------------------------Fonctions générales-----------------------------------//

bool IsModeEdition(){if(ProgOff.Mode == Edition) {return(true);}else{return(false);}}
void InscrireNomFichier(char *Filename) 
	{PtrM.PtrEspace3D->ListSave->NomString = Filename;PtrM.PtrEspace3D->ListSave->NomChar = Filename;}
bool VerifNomFichier() {if(PtrM.PtrEspace3D->ListSave->NomChar != NULL){return(true);}else{return(false);}}

void EnregistrerEspace3D(){EnrEnregistrerEspace3D(PtrM.PtrEspace3D);}
void ViderEspace3D(){EnrViderEspace3D(PtrM.PtrEspace3D);}
void OuvrirEspace3D(){EnrOuvrirEspace3D(PtrM.PtrEspace3D);}
void InfoCam(int &Largeur, int &Hauteur, float &Angle, float &Pres, float &Loin) 
	{	Largeur = PtrM.PtrEspace3D->ListMenu->Screen.Largeur; 
		Hauteur = PtrM.PtrEspace3D->ListMenu->Screen.Hauteur;
		Angle = PtrM.PtrEspace3D->NouvCam->AngleOuverture;
		Pres = PtrM.PtrEspace3D->NouvCam->Pres;
		Loin = PtrM.PtrEspace3D->NouvCam->Loin;}
void GetActivMenu(Menu *&PtrMen) {PtrMen = PtrM.PtrEspace3D->ListMenu;}
void GetActivCam(Camera *&PtrCam) {PtrCam = PtrM.PtrEspace3D->NouvCam;}
void GiveActivCam(Camera *PtrCam) {PtrM.PtrEspace3D->NouvCam = PtrCam;}

void setHits(int Hits, int NbObj, SelObj *ObjSel) 
{
	PtrM.PtrEspace3D->SelecActive->Hits = Hits; 
	PtrM.PtrEspace3D->SelecActive->NbObj = NbObj; 
	PtrM.PtrEspace3D->SelecActive->TeteObjSel = ObjSel;
};

void setHits(int Hits, int NbPt, SelPt *PtSel) 
{
	PtrM.PtrEspace3D->SelecActive->Hits = Hits; 
	PtrM.PtrEspace3D->SelecActive->NbPt = NbPt; 
	PtrM.PtrEspace3D->SelecActive->TetePtSel = PtSel;
};	


void getSelectionObject(int &Hits) {Hits = PtrM.PtrEspace3D->SelecActive->Hits;};
void getSelectionType(unsigned char &VectorSel, bool &Add_Ret, int &SelType) 
{	VectorSel = PtrM.PtrEspace3D->SelecActive->VectorSel;
	Add_Ret = PtrM.PtrEspace3D->SelecActive->Add_Ret;
	SelType = PtrM.PtrEspace3D->SelecActive->Type;};
void SwitchSelectionTypeVS() 
{
	if(PtrM.PtrEspace3D->SelecActive->VectorSel == SUPERFICIELLE)
	{
		PtrM.PtrEspace3D->SelecActive->VectorSel = PERFORANTE;
	}
	else
	{
		PtrM.PtrEspace3D->SelecActive->VectorSel = SUPERFICIELLE;
	}
};
void getSelOff(Select *&PtrSelOff) {PtrSelOff = ProgOff.SelectOff;};
void ResetSelOff() {ProgOff.SelectOff->Refresh();};
void ActiverAnimation(void) {PtrM.PtrEspace3D->ListAnim->Animations_Activee = true;};
void DesactiverAnimation(void) {PtrM.PtrEspace3D->ListAnim->Animations_Activee = false;};
void GetTypeAff(int &TypeAff) {TypeAff = PtrM.PtrEspace3D->Affichage->TypeAffichage;};
void ChangTypeAff(int TypeAff) {PtrM.PtrEspace3D->Affichage->TypeAffichage = TypeAff;};
void GetTeteObjet(Objet *&TeteObjet) {TeteObjet = PtrM.PtrEspace3D->TeteObjet;};
void giveTeteObjet(Objet *TeteObjet) {PtrM.PtrEspace3D->TeteObjet = TeteObjet;};
void giveQueueObjet(Objet *PtrObjet) {PtrM.PtrEspace3D->NouvObjet = PtrObjet;};
void GetEvent(Event *&PtrEvent) {PtrEvent = PtrM.PtrEspace3D->ListEvenement;};
void GetPtrEspace3D(Environnement *&PtrEspace3D) {PtrEspace3D = PtrM.PtrEspace3D;};
void GetCam(Camera *&PtrCam) {PtrCam = PtrM.PtrEspace3D->NouvCam;};
void GetPtrVueUseCam(Camera *&PtrCam) 
{
	if(PtrM.PtrEspace3D->ListMenu->PtrVuesUse != NULL)
	{
		PtrCam = PtrM.PtrEspace3D->ListMenu->PtrVuesUse->PtrCam;
	}
	else
	{
		GetCam(PtrCam);
	}
};
void GetSelOff(Select *&PtrSelOff) {PtrSelOff = ProgOff.SelectOff;};
void GetLargeur_Ecran(int &Largeur_Ecran) {Largeur_Ecran = PtrM.PtrEspace3D->ListMenu->Screen.Largeur;};
void GetHauteur_Ecran(int &Hauteur_Ecran) {Hauteur_Ecran = PtrM.PtrEspace3D->ListMenu->Screen.Hauteur;};
void getSauvProp(Sauvegarde *&SauvProp) {SauvProp = PtrM.PtrEspace3D->ListSave;};
void GetEcran(Ecran &Ecran) {Ecran = PtrM.PtrEspace3D->ListMenu->Screen;};
void getPlacerPointMode(int &Mode) {Mode = PtrM.PtrEspace3D->ListMenu->PlacerPointMode;};
void setPlacerPointMode(int Mode) {PtrM.PtrEspace3D->ListMenu->PlacerPointMode = Mode;};
void setCam() 
{
	PtrM.PtrEspace3D->NouvCam->Cam_Change_Shape(
		(PtrM.PtrEspace3D->ListMenu->Screen.Largeur-PtrM.PtrEspace3D->ListMenu->Epais*3)/2,
		(PtrM.PtrEspace3D->ListMenu->Screen.Hauteur-PtrM.PtrEspace3D->ListMenu->Epais*3)/2);
}
void DeleteHeadObjet(void) { PtrM.PtrEspace3D->EffacerTeteObjet();};
void GiveNewObjet(Objet *NouvObjet) { PtrM.PtrEspace3D->NouvObjet = NouvObjet;};
void getPtrVueBefore(Vues *&PtrVues) {PtrVues = PtrM.PtrEvent->PtrCamBefore;};
void getNewPoint(Point *&NouvPoint) { NouvPoint = PtrM.PtrEspace3D->NouvObjet->NouvForme->NouvPoint;};
void GiveNewCam(Camera *NouvCam) { PtrM.PtrEspace3D->NouvCam = NouvCam;};
void AddNewPoint(Coord3D Pt, Forme *PtrForme){PtrM.PtrEspace3D->NewFacePoint(Pt, ProgOff.SelectOff, PtrForme);};
void ErasePoint(Point *PtrPoint){PtrM.PtrEspace3D->EraseFacePoint(PtrM.PtrEspace3D->ListEvenement->FreePt, ProgOff.SelectOff);};
void GetVectPerp(Vecteur3D &VectPerp) {VectPerp = PtrM.PtrMenu->PlanPerp->VectNor;};
void SwitchProgMode() {if(ProgOff.Mode == Console){ProgOff.Mode = Edition;}else{ProgOff.Mode = Console;}cout<<"ModeConsole"<<endl;};
void getProgMode(int &Mode) {Mode = ProgOff.Mode;};
void giveProgMode(int Mode) {ProgOff.Mode = Mode;};

void GetMatFromSelector(ColorMaterial &ColMat) 
{
	if(ProgOff.SelectOff != NULL)
	{
		SelObj *PtrObjSel = ProgOff.SelectOff->TeteObjSel;
		
		if(PtrObjSel != NULL)
		{
			if(PtrObjSel->PtrObj != NULL)
			{
				ColMat = PtrObjSel->PtrObj->Materiel;
			}
		}
	}
};

void GiveMatToSelector(ColorMaterial ColMat)
{
	if(ProgOff.SelectOff != NULL)
	{
		SelObj *PtrObjSel = ProgOff.SelectOff->TeteObjSel;
		
		while(PtrObjSel != NULL)
		{
			if(PtrObjSel->PtrObj != NULL)
			{
				PtrObjSel->PtrObj->Materiel = ColMat;
			}
			PtrObjSel = PtrObjSel->NxSel;
		}
	}
};

void SaidFileSelectorActive(bool Activity){PtrM.PtrEspace3D->ListMenu->FileSelectorActive = Activity;};


void InitOrtho2D(Ecran Screen)
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D(0, Screen.Largeur, 0, Screen.Hauteur);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();
}

void InitPerspective(Ecran Screen, Camera *Cam)
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(Cam->AngleOuverture, (float) Screen.Largeur/Screen.Hauteur, Cam->Pres, Cam->Loin);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();
}



//--------------------------------Fin des déclarations----------------------------------//

/*
void Init (void)
{
	Colorf BackCol = PtrM.PtrEspace3D->ListMenu->BackColor;
	glClearColor (BackCol.r, BackCol.v, BackCol.b, 0.0);

	InitLights();
	InitFrameTimer();
}
*/

void ResetView()
{
	switch(PtrM.PtrEspace3D->Affichage->TypeAffichage)
	{
	case ORTHOVIEW:
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		break;
	case PERSPECTIVE:
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		gluPerspective(PtrM.PtrEspace3D->NouvCam->AngleOuverture, (float) PtrM.PtrEspace3D->ListMenu->Screen.Largeur/(float) PtrM.PtrEspace3D->ListMenu->Screen.Hauteur, PtrM.PtrEspace3D->NouvCam->Pres, PtrM.PtrEspace3D->NouvCam->Loin);
		glMatrixMode(GL_MODELVIEW);
		break;
	default:
		break;
	}	
}



void ActionFunction(void)
{/*
	switch(*Espace3D.ListEvenement)
	{
	default:
		break;
	}*/
}

void TerminerFonctionPlacerPoint()
{
	switch(PtrM.PtrEspace3D->NouvObjet->Type)
	{
	case Squeleton:
	case FormeTriangulaire:
	case J_Triangles:
	case J_Faces:
	case J_Points:
	case J_Lines:
		break;
	default:
		PtrM.PtrObjet->NouvForme->getCenter();
		break;
	}

	PtrM.PtrObjet->ToComplete();
	PtrM.PtrEvent->ErasePointFreePt();
	PtrM.PtrEvent->TerminerPoint();
	PtrM.PtrEspace3D->CL.Back(false);
}


void FonctionAjoutPoint(void)
{	
	PtrM.PtrEvent = PtrM.PtrEspace3D->ListEvenement;
	PtrM.PtrObjet = PtrM.PtrEspace3D->NouvObjet;
	PtrM.PtrForme = PtrM.PtrEspace3D->NouvObjet->NouvForme;
	
	if(PtrM.PtrEspace3D->NouvObjet != NULL)
	{
		if(PtrM.PtrEvent->Func != Fonction_Terminee)
		{
			PtrM.PtrEvent->CalculTemps();
	
			PtrM.PtrEvent->TestLeftAction();
	
			if(PtrM.PtrEvent->IsFonctionOver() || PtrM.PtrEvent->TerminerFonction)
			{	
				TerminerFonctionPlacerPoint();
				PtrM.PtrEvent->TerminerFonction = false;
				PtrM.PtrEvent->Func = Fonction_Terminee;
				PtrM.PtrEvent->NettoyerSourie();
			}
			else
			{
				if(PtrM.PtrEvent->AddPoint)
				{
					switch(PtrM.PtrEspace3D->NouvObjet->Type)
					{
					case J_Triangles:
					case J_Faces:
						if(PtrM.PtrForme->nbPt >=3)
						{
							PtrM.PtrObjet->AjouterForme();
						}
						PtrM.PtrForme = PtrM.PtrEspace3D->NouvObjet->NouvForme;
					case FormeTriangulaire:
					case J_Points:
					case J_Lines:
						AddNewPoint(PtrM.PtrEvent->FreePt, PtrM.PtrForme);
						break;
					default:
						PtrM.PtrObjet->AjouterPoint(PtrM.PtrEvent->FreePt);
						break;
					}

					PtrM.PtrEvent->TerminerPoint();
				}
			
				if(PtrM.PtrForme->TetePoints != NULL)
				{
					switch(PtrM.PtrEspace3D->NouvObjet->Type)
					{
					case J_Triangles:
					case J_Faces:
					case FormeTriangulaire:
					case J_Points:
					case J_Lines:
						if(PtrM.PtrEspace3D->NouvPoint != NULL)
						{
							PtrM.PtrEspace3D->NouvPoint->Pt3D = PtrM.PtrEvent->FreePt;
						}
						break;
					default:
						PtrM.PtrForme->NouvPoint->Pt3D = PtrM.PtrEvent->FreePt;
						break;
					}
				}
			}
		}
	}
}


void AcMovCam(Camera *PtrCam)
{
	switch(PtrCam->Cam_Mov_Mode)
	{
	case RotSurCam:
		AcMovCam_Mod0(PtrCam, PtrM.PtrEspace3D->ListEvenement);
		break;
	case RotSurCamClic:
		AcMovCam_Mod1(PtrCam, PtrM.PtrEspace3D->ListEvenement);
		break;
	case RotSurCible:
		AcMovCam_Mod2(PtrCam, PtrM.PtrEspace3D->ListEvenement);
		break;
	case RotSurCibleClic:
		AcMovCam_Mod3(PtrCam, PtrM.PtrEspace3D->ListEvenement);
		break;
	default:
		break;
	}

	setCam();
}



////////////////////////////////////////////////////

////////////////////////////////////////////////////

////////////////////////////////////////////////////

////////////////////////////////////////////////////

////////////////////////////////////////////////////






void AskCodeName(int &NewName)
{
}


/*
void ForEachInt_DoThis(Class_List_Int Int_List, string Command)
{
	Class_List_Int *PtrInt;

	if(Int_List.TeteInt!=NULL)
	{
		PtrInt = Int_List.TeteInt;
		while(PtrInt->NouvInt != NULL)
		{
			//	Do this
			PtrInt = PtrInt->NxInt;
		}
	}
}
*/


void InitMain()
{
}

void InitTextBitmap()
{
	glShadeModel (GL_FLAT);
	makeRasterFont();
//	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho (0.0, w, 0.0, h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}


bool GetCommand(Command *&MemCommand, string Name)
{
	CommandControler *PtrCmd = MainProgram.TeteCom;
	bool GetOut = false;
	while(PtrCmd!=NULL && !GetOut)
	{
		if(PtrCmd->ListCommand->Name == Name)
		{
			MemCommand = PtrCmd->ListCommand;
			GetOut = true;
			return(true);
		}
		PtrCmd = PtrCmd->NxCom;
	}
	return(false);
}



void AddTab(fstream *FicOut)
{
	char C;
	C = '\t';
	for (int i = 0; i<Tab; i++)
	{
		FicOut->write((char *) &C, sizeof(C));
	}
}

void WriteChar(fstream *FicOut, char C)
{
	FicOut->write((char *) &C, sizeof(C));
	if(C == '\n')
	{AddTab(FicOut);}
}

void WriteString(fstream *FicOut, int IntVal)
{
	FicOut->write((char *) &IntVal, sizeof(IntVal));
}

void WriteString(fstream *FicOut, string Writer)
{
	int n = strlen(Writer.c_str());
	char W;
	if(Writer == "}")
	{Tab--;	WriteChar(FicOut, '\n');}
	for(int i = 0; i<n; i++)
	{
		W = Writer[i];
		FicOut->write((char *) &W, sizeof(W));
	}
	if(Writer == "{")
	{Tab++;}
}

void WriteFloat(fstream *FicOut, float Number)
{
	FicOut->write((char *) &Number, sizeof(Number));
}

puInput *CPPTextBoxCl = NULL;
puInput *CPPTextBox = NULL;
puInput *CPPTextBox2 = NULL;
puInput *CPPFloatBox = NULL;
puInput *CPPTextBoxTypeList = NULL;
puInput *CPPTextBoxTypeSpec = NULL;
puText* CPPTextMessage;

string LasVarType, LastListType, ControlMode;


char *CPPComboBoxItems[] =
{
	"None","Liste","bool","*bool","char","*char","int","*int","float","*float","double","*double","string","Bloc","*Bloc","Specifie",
		NULL 
};

void CPPComboBox_CB( puObject *pWidget )
{
	LasVarType = pWidget->getStringValue();

	ListClass->NouvVar->GetStringType(LasVarType);
	if(LasVarType == "None") {ListClass->NouvVar->GetType(0); goto EndCombobox_CB;}
	if(LasVarType == "Liste") {ListClass->NouvVar->GetType(Var_Liste); goto EndCombobox_CB;}
	if(LasVarType == "bool") {ListClass->NouvVar->GetType(Var_bool); goto EndCombobox_CB;}
	if(LasVarType == "*bool") {ListClass->NouvVar->GetType(Var_star_bool); goto EndCombobox_CB;}
	if(LasVarType == "char") {ListClass->NouvVar->GetType(Var_star_char); goto EndCombobox_CB;}
	if(LasVarType == "*char") {ListClass->NouvVar->GetType(Var_star_char); goto EndCombobox_CB;}
	if(LasVarType == "int") {ListClass->NouvVar->GetType(Var_int); goto EndCombobox_CB;}
	if(LasVarType == "*int") {ListClass->NouvVar->GetType(Var_star_int); goto EndCombobox_CB;}
	if(LasVarType == "float") {ListClass->NouvVar->GetType(Var_float); goto EndCombobox_CB;}
	if(LasVarType == "*float") {ListClass->NouvVar->GetType(Var_star_float); goto EndCombobox_CB;}
	if(LasVarType == "double") {ListClass->NouvVar->GetType(Var_double); goto EndCombobox_CB;}
	if(LasVarType == "*double") {ListClass->NouvVar->GetType(Var_star_double); goto EndCombobox_CB;}
	if(LasVarType == "string") {ListClass->NouvVar->GetType(Var_string); goto EndCombobox_CB;}
	if(LasVarType == "Bloc") {ListClass->NouvVar->GetType(Var_bloc); goto EndCombobox_CB;}
	if(LasVarType == "*Bloc") {ListClass->NouvVar->GetType(Var_star_bloc);}
	if(LasVarType == "Specifie") {ListClass->NouvVar->GetType(Var_Specifiee);}
EndCombobox_CB:;
}

char *CPPComboBoxItems_List[] =
{
	"Lineaire",	"Ramification",
		NULL 
};

void CPPComboBox_CB_List( puObject *pWidget )
{
	LastListType = pWidget->getStringValue();

	if(LastListType == "Lineaire") {ListClass->NouvVar->GetStructList(1); goto EndCombobox_CB_List;}
	if(LastListType == "Ramification") {ListClass->NouvVar->GetStructList(2);}
EndCombobox_CB_List:;
}

void CPPText_CB( puObject *pWidget )
{
	ListClass->SetName(pWidget->getStringValue());
}

void CPPText_CB2( puObject *pWidget )
{
	ListClass->NouvVar->SetName(pWidget->getStringValue());
	string ControlerName = "";
	ControlerName += ListClass->NouvVar->Name;
	ControlerName += "Controler";
	ListClass->NouvVar->GetControlName(ControlerName);
}

void CPPFloat_CB( puObject *pWidget )
{
	float dVal; 
	pWidget->getValue(&dVal); 

	ListClass->NouvVar->GetValInit(dVal);
}

void CPPButton_Callback_NCl( puObject *pWidget )
{
	ListClass->KillClass();
}

void CPPButton_Callback_CFH( puObject *pWidget )
{
	if(ListClass->Name == "")
	{
		CPPTextMessage->setLabel("Attention!!! Cette classe n'a pas de nom !!!");
	}
	else
	{
		string Filename;
		Filename = ListClass->Name;
		Filename += ".h";
		FabriquerClass(Filename, ListClass);
		CPPTextMessage->setLabel("Classe transcrite");
	}
}

void CPPTextCB_TypeSpec( puObject *pWidget )
{
	LasVarType = pWidget->getStringValue();
	int n = strlen(LasVarType.c_str());
	if(n > 0)
	{
		if(LasVarType[0] == '*')
		{
			string NewString = "";

			for(int i = 0;  i<(n-1); i++)
			{
				NewString += LasVarType[i+1];
			}
			
//			NewString += '*';
			LasVarType = NewString;
		}
	}
	ListClass->NouvVar->GetStringType(LasVarType);
}

char *CPPComboBoxItems_ListControl[] =
{
	"Indirect",	"Direct",
		NULL 
};

void CPPComboBox_CB_ListControl( puObject *pWidget )
{
	ControlMode = pWidget->getStringValue();

	if(ControlMode == "Indirect") {ListClass->NouvVar->GetControlMode(ControleurIndirect); goto EndCombobox_CB_ListControl;}
	if(ControlMode == "Direct") {ListClass->NouvVar->GetControlMode(ControleurDirect);}
EndCombobox_CB_ListControl:;
}


void CPPTextCB_TypeList( puObject *pWidget )
{
	LastListType = pWidget->getStringValue();
	int n = strlen(LastListType.c_str());
	if(n > 0)
	{
		if(LastListType[0] == '*')
		{
			string NewString = "";

			for(int i = 0;  i<(n-1); i++)
			{
				NewString += LastListType[i+1];
			}
			
			NewString += '*';
			LastListType = NewString;
		}
	}
	ListClass->NouvVar->GetTypeListe(LastListType);
}


char *CPPIsClickClassBoxItems[] =
{
	"Faux", "Vrai",
		NULL 
};

void CPPIsClickClassBox_CB( puObject *pWidget )
{
	string Tool = pWidget->getStringValue();

	if(Tool == "Vrai")
	{
		ListClass->GetIfClickClass(false);
	}
}

char *CPPIsClickVariableBoxItems[] =
{
	"Faux", "Vrai",
		NULL 
};

void CPPIsClickVariableBox_CB( puObject *pWidget )
{
	string Tool = pWidget->getStringValue();

	if(Tool == "Vrai" || ListClass->NouvVar != NULL)
	{
		ListClass->NouvVar->GetIfClickVariable(false);
	}
}

void CPPButton_Callback_AddVar( puObject *pWidget )
{
	VarMem *PtrVar = ListClass->TeteVar, *PtrVarNouv = ListClass->NouvVar;
	
	if(PtrVar != PtrVarNouv && PtrVar != NULL && PtrVarNouv != NULL)
	{
		while(PtrVar->NxVar !=NULL)
		{
			switch(PtrVarNouv->TypeVar)
			{
			case Var_Liste:
				if((PtrVar->TypeVar == Var_Liste) && (PtrVar->NomSpecDuControleur == PtrVarNouv->NomSpecDuControleur))
				{
					CPPTextMessage->setLabel("Attention!!! Deux controleurs sont identiques !!! Changer le nom de variable");
					goto End_Button_Callback_AddVar;
				}
				break;
			default:
				if((PtrVar->Name == PtrVarNouv->Name) && (PtrVar != PtrVarNouv))
				{
					CPPTextMessage->setLabel("Attention!!! Deux noms de variables sont identiques !!!");
					goto End_Button_Callback_AddVar;
				}
				break;
			}

			PtrVar = PtrVar->NxVar;
		}
	}

	if(PtrVarNouv != NULL)
	{
		switch(PtrVarNouv->TypeVar)
		{
		case 0:
				CPPTextMessage->setLabel("Attention!!! Aucun type de variable n'est selectionne !!!");
				goto End_Button_Callback_AddVar;
		case Var_Liste:
			if(PtrVarNouv->Name == "" ||
				PtrVarNouv->TypeListe == "" || 
				PtrVarNouv->StructListe == 0)	
			{
				CPPTextMessage->setLabel("Attention!!! Cases incompletes pour ce type de variable !!!");
				goto End_Button_Callback_AddVar;
			}
			else
			{
				if(PtrVarNouv->NomSpecDuControleur == "")
				{
					CPPTextMessage->setLabel("Attention!!! Cette variable n'a pas de nom !!! ");
					goto End_Button_Callback_AddVar;
				}
			}
			break;
		case Var_Specifiee:
			if(PtrVarNouv->Name == "" ||
				PtrVarNouv->StringType == "")	
			{
				CPPTextMessage->setLabel("Attention!!! Cases incompletes pour ce type de variable !!!");
				goto End_Button_Callback_AddVar;
			}
			break;
		default:
			if(PtrVarNouv->Name == "")
			{
				CPPTextMessage->setLabel("Attention!!! Cette variable n'a pas de nom !!!");
				goto End_Button_Callback_AddVar;
			}
			break;
		}
	}

	CPPTextMessage->setLabel("Message");

	ListClass->AddVar();

End_Button_Callback_AddVar:;
}

int HauteurVariablesBoxHaut = 465;
int HauteurVariablesBoxBas = 440;
int HauteurLigne = 50;

void PasserAutreLigne()
{
	HauteurVariablesBoxHaut -= HauteurLigne;
	HauteurVariablesBoxBas -= HauteurLigne;
}

void InitUI()
{
	puSetDefaultStyle ( PUSTYLE_SMALL_SHADED ) ;
	puSetDefaultColourScheme( 0.3f, 0.7f, 0.9f );

	puText* HeadText = new puText( 10, 460 );
	HeadText->setLabel("Class Creator");

	puText* TextCl = new puText( 130, HauteurVariablesBoxBas );
	TextCl->setLabel("Nom de la classe : ");
	CPPTextBoxCl = new puInput(270, HauteurVariablesBoxBas, 620, HauteurVariablesBoxHaut );
	CPPTextBoxCl->setLabel("");
	CPPTextBoxCl->setCallback(CPPText_CB);

	PasserAutreLigne();
	
	puOneShot *NewCL = new puOneShot( 140, HauteurVariablesBoxBas, 340, HauteurVariablesBoxHaut );
	NewCL -> setLegend   ( "Nouvelle Classe" );
	NewCL -> setCallback ( CPPButton_Callback_NCl );

	puOneShot *CreateFileH = new puOneShot( 360, HauteurVariablesBoxBas, 560, HauteurVariablesBoxHaut );
	CreateFileH -> setLegend   ( "Creer le fichier .h" );
	CreateFileH -> setCallback ( CPPButton_Callback_CFH );

	PasserAutreLigne();

	puText* Text1 = new puText( 25, HauteurVariablesBoxHaut );
	Text1->setLabel("Type");
	puComboBox *box = new puComboBox( 25, HauteurVariablesBoxBas, 125, HauteurVariablesBoxHaut, CPPComboBoxItems, FALSE );
	box->setCallback(CPPComboBox_CB); 

	puText* Text2 = new puText( 135, HauteurVariablesBoxHaut );
	Text2->setLabel("Nom de la variable");
	CPPTextBox2 = new puInput( 135, HauteurVariablesBoxBas, 390, HauteurVariablesBoxHaut );
	CPPTextBox2->setLabel("");
	CPPTextBox2->setCallback(CPPText_CB2);

	puText* Text3 = new puText( 400, HauteurVariablesBoxHaut );
	Text3->setLabel("Valeur initiale");
	CPPFloatBox = new puInput( 400, HauteurVariablesBoxBas, 580, HauteurVariablesBoxHaut );
	CPPFloatBox->setLabel("");
	CPPFloatBox->setCallback(CPPFloat_CB);
	
	PasserAutreLigne();

	puText* TextTypeSpec = new puText( 25, HauteurVariablesBoxHaut );
	TextTypeSpec->setLabel("Type specifie de la variable");
	CPPTextBoxTypeSpec = new puInput( 25, HauteurVariablesBoxBas, 185, HauteurVariablesBoxHaut );
	CPPTextBoxTypeSpec->setLabel("");
	CPPTextBoxTypeSpec->setCallback(CPPTextCB_TypeSpec);

	PasserAutreLigne();

	puText* TextTypeList = new puText( 25, HauteurVariablesBoxHaut );
	TextTypeList->setLabel("Type de la liste");
	CPPTextBoxTypeList = new puInput( 25, HauteurVariablesBoxBas, 185, HauteurVariablesBoxHaut );
	CPPTextBoxTypeList->setLabel("");
	CPPTextBoxTypeList->setCallback(CPPTextCB_TypeList);

	puText* TextList = new puText( 195, HauteurVariablesBoxHaut );
	TextList->setLabel("List's Struct");
	puComboBox *boxlist = new puComboBox( 195, HauteurVariablesBoxBas, 340, HauteurVariablesBoxHaut, CPPComboBoxItems_List, FALSE );
	boxlist->setCallback(CPPComboBox_CB_List); 

	puText* TextListControl = new puText( 350, HauteurVariablesBoxHaut );
	TextListControl->setLabel("Type de Controleur");
	puComboBox *boxlistControl = new puComboBox( 350, HauteurVariablesBoxBas, 480, HauteurVariablesBoxHaut, CPPComboBoxItems_ListControl, FALSE );
	boxlistControl->setCallback(CPPComboBox_CB_ListControl); 

	PasserAutreLigne();

	puText* EstClickClass = new puText( 25, HauteurVariablesBoxHaut );
	EstClickClass->setLabel("Is a clikable class ?");
	puComboBox *ClickClass = new puComboBox( 25, HauteurVariablesBoxBas, 125, HauteurVariablesBoxHaut, CPPIsClickClassBoxItems, FALSE );
	ClickClass->setCallback(CPPIsClickClassBox_CB); 

	puText* EstClickVariable = new puText( 225, HauteurVariablesBoxHaut );
	EstClickVariable->setLabel("Is a clikable variable ?");
	puComboBox *ClickVariable = new puComboBox( 225, HauteurVariablesBoxBas, 350, HauteurVariablesBoxHaut, CPPIsClickVariableBoxItems, FALSE );
	ClickVariable->setCallback(CPPIsClickVariableBox_CB); 

	puOneShot *b = new puOneShot( 450, HauteurVariablesBoxBas, 600, HauteurVariablesBoxHaut );
	b -> setLegend   ( "Add Variable" );
	b -> setCallback ( CPPButton_Callback_AddVar );

	PasserAutreLigne();

	CPPTextMessage = new puText( 10, 5 );
	CPPTextMessage->setLabel("Message");
}

/* custom OpenGL Initialisation */

GLvoid Reshape(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport
}

int Init()
{
	glClearColor(0.2f,0.5f,0.9f,0);

	return (true);
}







void CalculerPositionPourNouveauPoint()
{
	Event *PtrEvent = PtrM.PtrEspace3D->ListEvenement;
	Menu *PtrMen = PtrM.PtrEspace3D->ListMenu;

	if(PtrMen->Aimant)
	{
		SelPt *PtrSelPoint = PtrM.PtrEspace3D->SelecPassive->TetePtSel;

		if(PtrSelPoint != NULL)
		{
			if(PtrSelPoint->PtrPt != NULL && PtrM.PtrEspace3D->NouvObjet->NouvForme->NouvPoint != NULL)
			{
				if(PtrSelPoint->PtrForme->HaveCenter)
				{
					PtrEvent->FreePt.getCoord(
						PtrSelPoint->PtrPt->Pt3D.x + PtrSelPoint->PtrForme->Center.Pt3D.x,
						PtrSelPoint->PtrPt->Pt3D.y + PtrSelPoint->PtrForme->Center.Pt3D.y,
						PtrSelPoint->PtrPt->Pt3D.z + PtrSelPoint->PtrForme->Center.Pt3D.z);
				}
				else
				{
					PtrEvent->FreePt = PtrSelPoint->PtrPt->Pt3D;
				}
				AllowedNewPoint(PtrM.PtrEspace3D);
			}
			else
			{
				goto PointSansAimant;
			}
		}
		else
		{
			goto PointSansAimant;
		}
	}
	else
	{
PointSansAimant:;
		if(PtrM.PtrEspace3D->NouvObjet != NULL)
		{
			switch(PtrM.PtrEspace3D->NouvObjet->Type)
			{
			case Geometrie:
				PlacerUnPointNormalement(PtrM.PtrEspace3D);
				break;
			case CameraShape:
				PlacerPoint_CameraShape(PtrM.PtrEspace3D);
				break;
			case J_Points:
			case J_Lines:
			case J_Triangles:
			case J_Faces:
			case FormeTriangulaire:
				PlacerPoint_FormeTriangulaire(PtrM.PtrEspace3D);
				break;
			case Spot:
				PlacerPoint_Spot(PtrM.PtrEspace3D);
				break;
			case Help_Plan:
				PlacerPoint_Help_Plan(PtrM.PtrEspace3D);
				break;
			case Help_Point:
				PlacerPoint_Help_Point(PtrM.PtrEspace3D);
				break;
			case Help_Compat:
				PlacerPoint_Help_Compat(PtrM.PtrEspace3D);
				break;
			case Help_Ligne_Proj:
				PlacerPoint_Help_Ligne_Proj(PtrM.PtrEspace3D);
				break;
			case Vecteur:
				PlacerPoint_Vecteur(PtrM.PtrEspace3D);
				break;
			case Globe:
				PlacerPoint_Globe(PtrM.PtrEspace3D);
				break;
			case Quadrilatere:
				PlacerPoint_Quadrilatere(PtrM.PtrEspace3D);
				break;
			case Cylindre:
				PlacerPoint_Cylindre(PtrM.PtrEspace3D);
				break;
			case Tube:
				PlacerPoint_Tuyau(PtrM.PtrEspace3D);
				break;
			case FlecheDep_X:
				PlacerPoint_FlecheDep_X(PtrM.PtrEspace3D);
				break;
			case FlecheDep_Y:
				PlacerPoint_FlecheDep_Y(PtrM.PtrEspace3D);
				break;
			case FlecheDep_Z:
				PlacerPoint_FlecheDep_Z(PtrM.PtrEspace3D);
				break;
			case PlanDep_XY:
				PlacerPoint_PlanDep_XY(PtrM.PtrEspace3D);
				break;
			case PlanDep_XZ:
				PlacerPoint_PlanDep_XZ(PtrM.PtrEspace3D);
				break;
			case PlanDep_YZ:
				PlacerPoint_PlanDep_YZ(PtrM.PtrEspace3D);
				break;
			case CercleRotation:
				PlacerPoint_CercleRotation(PtrM.PtrEspace3D);
				break;
			case Scale:
				PlacerPoint_Scale(PtrM.PtrEspace3D);
				break;
			case DirectionTranslation: 
				PlacerDirectionTranslation(PtrM.PtrEspace3D);
				break;
			case Squeleton:
				PlacerSqueleton(PtrM.PtrEspace3D);
				break;
			default:
				break;
			}
	
			if(PtrM.PtrEspace3D->ListMenu->Ortho)
			{
				Coord3D Pt = PtrEvent->FreePt;
				
/*				Pt.getCoord(
					(int)(Pt.x+PtrMen->VarOrtho/2)/PtrMen->VarOrtho*PtrMen->VarOrtho, 
					(int)(Pt.y+PtrMen->VarOrtho/2)/PtrMen->VarOrtho*PtrMen->VarOrtho, 
					(int)(Pt.z+PtrMen->VarOrtho/2)/PtrMen->VarOrtho*PtrMen->VarOrtho);
*/
				if(Pt.x < 0)
				{Pt.x = (int)(Pt.x-PtrMen->VarOrtho/2)/PtrMen->VarOrtho*PtrMen->VarOrtho;}
				else
				{Pt.x = (int)(Pt.x+PtrMen->VarOrtho/2)/PtrMen->VarOrtho*PtrMen->VarOrtho;}

				if(Pt.y < 0)
				{Pt.y = (int)(Pt.y-PtrMen->VarOrtho/2)/PtrMen->VarOrtho*PtrMen->VarOrtho;}
				else
				{Pt.y = (int)(Pt.y+PtrMen->VarOrtho/2)/PtrMen->VarOrtho*PtrMen->VarOrtho;}

				if(Pt.z < 0)
				{Pt.z = (int)(Pt.z-PtrMen->VarOrtho/2)/PtrMen->VarOrtho*PtrMen->VarOrtho;}
				else
				{Pt.z = (int)(Pt.z+PtrMen->VarOrtho/2)/PtrMen->VarOrtho*PtrMen->VarOrtho;}

				PtrEvent->FreePt = Pt;
			}
		}
	}
		
	PtrEvent->NewMouse->Coord_Plan = PtrEvent->FreePt;
	FonctionAjoutPoint();
}



#define BUFSIZE 512

void Selection(int Type)
{
	PtrM.PtrEvent = PtrM.PtrEspace3D->ListEvenement;
	PtrM.PtrEvent->GetSelecType(Type);

	Sourie *PtrSourie = PtrM.PtrEvent->NewMouse;

	Vues *PtrVues = PtrM.PtrEvent->NewMouse->PtrVues;

	int x = PtrSourie->PosEv.x, y = PtrSourie->PosEv.y;
	GLuint selectBuf[BUFSIZE];
	GLint Hits;
	GLint viewport[4];

	PtrVues->Viewport(PtrM.PtrEspace3D->ListMenu->WideOpen);

	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(BUFSIZE, selectBuf);
	(void) glRenderMode(GL_SELECT);

	glInitNames();
	glPushName(0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glPushMatrix();


	int LargCadre, HautCadre, Xcentre, Ycentre;

	if((PtrM.PtrEvent->PtrCamBefore == PtrM.PtrEvent->PtrCamAfter)
		&& PtrM.PtrEvent->PtrCamBefore != NULL)
	{
		LargCadre = abs(PtrM.PtrEvent->PosAfter.x - PtrM.PtrEvent->PosBefore.x);
		HautCadre = abs(PtrM.PtrEvent->PosAfter.y - PtrM.PtrEvent->PosBefore.y);
		Xcentre = (PtrM.PtrEvent->PosAfter.x + PtrM.PtrEvent->PosBefore.x)/2;
		Ycentre = (PtrM.PtrEvent->PosAfter.y + PtrM.PtrEvent->PosBefore.y)/2;

		if(LargCadre == 0)
		{
			LargCadre = 1;
		}
		if(HautCadre == 0)
		{
			HautCadre = 1;
		}

		gluPickMatrix((GLdouble) Xcentre, (GLdouble) (viewport[3] - Ycentre), LargCadre, HautCadre, viewport);

		PtrM.PtrEvent->Aff_Select = true;
	}
	else
	{
		switch(PtrM.PtrEspace3D->SelecActive->Type)
		{
		case (SelObjet):

			if(PtrM.PtrEspace3D->ListMenu->Aimant)
			{
				float VarAimant = PtrM.PtrEspace3D->ListMenu->VarAimant;
				gluPickMatrix((GLdouble) x, (GLdouble) (viewport[3] - y), VarAimant, VarAimant, viewport);
			}
			else
			{
				gluPickMatrix((GLdouble) x, (GLdouble) (viewport[3] - y), 5.0, 5.0, viewport);
			}
			break;
		case (SelPoint):
			gluPickMatrix((GLdouble) x, (GLdouble) (viewport[3] - y), 20.0, 20.0, viewport);
			break;
		default:
			break; 
		}
	}

	PtrVues->AfficherVues(Type, PtrM.PtrEspace3D->ListMenu->WideOpen);

	glPopMatrix();
	glFlush();

	Hits = glRenderMode(GL_RENDER);
	PtrM.PtrEspace3D->SelecActive->Hits = Hits;

	ResetView();
	
	ColorMaterial ColMat;

	switch(Type)
	{
	case Active:
		FabriquerTraiterSelection(Hits, selectBuf, PtrM.PtrEspace3D->SelecActive, ProgOff.SelectOff);
		GetMatFromSelector(ColMat);
		PtrM.PtrEspace3D->ListMenu->MatColor.getMaterial(ColMat);
		break;
	case Passive:
		PtrM.PtrEspace3D->SelecPassive->Refresh();
		FabriquerTraiterSelection(Hits, selectBuf, PtrM.PtrEspace3D->SelecActive, PtrM.PtrEspace3D->SelecPassive);
		break;
	case Independent:
		break;
	default:
		break;
	}
}



//-------------------------------------------------Evenements------------------------------------------------//

int n;

void Evenements(int button, int state, int x, int y, bool MsMove, bool ClavierActive, int Event)
{
	PtrM.PtrEvent = PtrM.PtrEspace3D->ListEvenement;

	bool ClickSel = ProgOff.SelectOff->ClickSurSel;

	Camera *PtrCam;
	PtrCam = PtrM.PtrEspace3D->NouvCam;
	Keys *PtrKeys = PtrM.PtrEvent->Clavier;

	PtrM.PtrEvent->NewMouse->Pos2D.getCoord(x, PtrM.PtrEspace3D->ListMenu->Screen.Hauteur-y);

	PtrM.PtrEvent->NewMouse->PosEv.getCoord(x, y);
	PtrM.PtrEvent->NewMouse->getPosScreen(x, y, PtrM.PtrEspace3D->ListMenu->Screen.Hauteur);
	PtrM.PtrEvent->NewMouse->MsMove = MsMove;
	PtrM.PtrEvent->EtatEvenement = PtrM.PtrEvent->NewMouse->EtatSourie = Event;
	PtrM.PtrEvent->Clavier->ClavierActif = ClavierActive;
	PtrM.PtrMenu = PtrM.PtrEspace3D->ListMenu;

	Vues *PtrVues;
	GetPtrVues(PtrM.PtrEspace3D->ListMenu->TeteVues, PtrVues, PtrM.PtrEvent->NewMouse->Pos2D);
	PtrVues->GetPos(x, y, PtrM.PtrEspace3D->ListMenu->WideOpen);

	PtrM.PtrEvent->NewMouse->PtrVues = PtrVues;

	if(!ClavierActive)
	{
		PtrM.PtrEvent->NewMouse->BtPress = state;

		PtrM.PtrEvent->ClicUpAndDown();
		if(!(Event == DeplacerSourie
			|| Event == ClickDeplacerSourie))
		{
			PtrM.PtrEvent->WitchActive();
			PtrM.PtrEvent->NewMouse->BtType = button;
		}
		PtrM.PtrEvent->getMove(x, y);
	}

	float Nx, Ny, Nz;

	if(PtrM.PtrEspace3D->ListMenu->SourieSurMenu(PtrM.PtrEspace3D->ListEvenement))
	{
		ProgOff.Mode = Edition;
	}
	else
	{
		ProgOff.Mode = Edition;
	}

	if(ProgOff.Mode == Edition)
	{
		switch(PtrVues->PtrCam->Type)
		{
		case Devant:
			Nx = (float) PtrVues->Pos.x/PtrVues->DimCam.w*PtrVues->PtrCam->AngleOuverture*2.0 + PtrVues->PtrCam->Pos.x;
			Ny = (float) PtrVues->Pos.y/PtrVues->DimCam.h*PtrVues->PtrCam->AngleOuverture*2.0*PtrVues->DimCam.h/PtrVues->DimCam.w - PtrVues->PtrCam->Pos.y;
			Nz = (float) PtrM.PtrEspace3D->Grille->PosInit.z;

			PtrM.PtrEvent->getMove(
			Contact_Droite_Plan(
				CalculerDroite( EcrirePoint(Nx, Ny, Nz), PtrVues->PtrCam->Lc),
				CalculerPlan(EcrirePoint(0,0,0), EcrireVector(0,0,1))
								)
							);
			PtrM.PtrMenu->PlanPerp->NouvPlan(PtrM.PtrEvent->Pt1_3D, EcrireVector(0,0,1));
			break;
		case Derriere:
			Nx = (float) -PtrVues->Pos.x/PtrVues->DimCam.w*PtrVues->PtrCam->AngleOuverture*2.0 + PtrVues->PtrCam->Pos.x;
			Ny = (float) PtrVues->Pos.y/PtrVues->DimCam.h*PtrVues->PtrCam->AngleOuverture*2.0*PtrVues->DimCam.h/PtrVues->DimCam.w - PtrVues->PtrCam->Pos.y;
			Nz = (float) PtrM.PtrEspace3D->Grille->PosInit.z;

			PtrM.PtrEvent->getMove(
			Contact_Droite_Plan(
				CalculerDroite( EcrirePoint(Nx, Ny, Nz), PtrVues->PtrCam->Lc),
				CalculerPlan(EcrirePoint(0,0,0), EcrireVector(0,0,-1))
								)
							);
			PtrM.PtrMenu->PlanPerp->NouvPlan(PtrM.PtrEvent->Pt1_3D, EcrireVector(0,0,-1));
			break;
		case Droite:
			Nx = (float) PtrM.PtrEspace3D->Grille->PosInit.x;
			Ny = (float) PtrVues->Pos.y/PtrVues->DimCam.h*PtrVues->PtrCam->AngleOuverture*2.0*PtrVues->DimCam.h/PtrVues->DimCam.w - PtrVues->PtrCam->Pos.y;
			Nz = (float) PtrVues->Pos.x/PtrVues->DimCam.w*PtrVues->PtrCam->AngleOuverture*2.0 + PtrVues->PtrCam->Pos.z;
			
			PtrM.PtrEvent->getMove(
			Contact_Droite_Plan(
				CalculerDroite( EcrirePoint(Nx, Ny, Nz), PtrVues->PtrCam->Lc),
				CalculerPlan(EcrirePoint(0,0,0), EcrireVector(1,0,0))
								)
							);
			PtrM.PtrMenu->PlanPerp->NouvPlan(PtrM.PtrEvent->Pt1_3D, EcrireVector(1,0,0));
			break;
		case Gauche:
			Nx = (float) PtrM.PtrEspace3D->Grille->PosInit.x;
			Ny = (float) PtrVues->Pos.y/PtrVues->DimCam.h*PtrVues->PtrCam->AngleOuverture*2.0*PtrVues->DimCam.h/PtrVues->DimCam.w - PtrVues->PtrCam->Pos.y;
			Nz = (float) -PtrVues->Pos.x/PtrVues->DimCam.w*PtrVues->PtrCam->AngleOuverture*2.0 + PtrVues->PtrCam->Pos.z;
			
			PtrM.PtrEvent->getMove(
			Contact_Droite_Plan(
				CalculerDroite( EcrirePoint(Nx, Ny, Nz), PtrVues->PtrCam->Lc),
				CalculerPlan(EcrirePoint(0,0,0), EcrireVector(-1,0,0))
								)
							);
			PtrM.PtrMenu->PlanPerp->NouvPlan(PtrM.PtrEvent->Pt1_3D, EcrireVector(-1,0,0));
			break;
		case Haut:
			Nx = (float) PtrVues->Pos.x/PtrVues->DimCam.w*PtrVues->PtrCam->AngleOuverture*2.0 + PtrVues->PtrCam->Pos.x;
			Ny = (float) PtrM.PtrEspace3D->Grille->PosInit.y;
			Nz = (float) -PtrVues->Pos.y/PtrVues->DimCam.h*PtrVues->PtrCam->AngleOuverture*2.0*PtrVues->DimCam.h/PtrVues->DimCam.w - PtrVues->PtrCam->Pos.z;

			PtrM.PtrEvent->getMove(
			Contact_Droite_Plan(
				CalculerDroite( EcrirePoint(Nx, Ny, Nz), PtrVues->PtrCam->Lc),
				*PtrM.PtrEspace3D->Grille));
			PtrM.PtrMenu->PlanPerp->NouvPlan(PtrM.PtrEvent->Pt1_3D, EcrireVector(0,1,0));
			break;
		case Bas:
			Nx = (float) PtrVues->Pos.x/PtrVues->DimCam.w*PtrVues->PtrCam->AngleOuverture*2.0 + PtrVues->PtrCam->Pos.x;
			Ny = (float) PtrM.PtrEspace3D->Grille->PosInit.y;
			Nz = (float) PtrVues->Pos.y/PtrVues->DimCam.h*PtrVues->PtrCam->AngleOuverture*2.0*PtrVues->DimCam.h/PtrVues->DimCam.w - PtrVues->PtrCam->Pos.z;

			PtrM.PtrEvent->getMove(
			Contact_Droite_Plan(
				CalculerDroite( EcrirePoint(Nx, Ny, Nz), PtrVues->PtrCam->Lc),
				*PtrM.PtrEspace3D->Grille));
			PtrM.PtrMenu->PlanPerp->NouvPlan(PtrM.PtrEvent->Pt1_3D, EcrireVector(0,-1,0));
			break;
		case Perspective:
			PtrM.PtrEvent->getMove(
			Croisement_Pt2D_Plan(
				PtrVues->Pos,
				PtrM.PtrEspace3D->Grille, 
				PtrM.PtrEspace3D->NouvCam
								)
							);

			*PtrM.PtrMenu->PlanPerp = *PtrM.PtrEspace3D->Grille;
			break;
		case Parallele:
			break;
		case Mode2D:
			break;
		default:
			break;
		}

		if( !ClickSel )
		{
			if(PtrM.PtrEvent->Func == 0)
			{
				if(button == GLUT_LEFT_BUTTON
				&& PtrM.PtrEvent->ButGoingDown)
				{
					PtrM.PtrEvent->PtrCamBefore = PtrVues;
		
					if(!PtrM.PtrEspace3D->ListMenu->WideOpen)
					{
						PtrM.PtrEspace3D->ListMenu->PtrVuesUse = PtrVues;
					}
					
					PtrM.PtrEvent->PosBefore = PtrM.PtrEvent->NewMouse->PosEv;
					PtrM.PtrEvent->PosBeforeScreen = PtrM.PtrEvent->NewMouse->PosScreen;
					PtrM.PtrEvent->PtrCamAfter = NULL;
				}
			}
			else
			{
				PtrM.PtrEvent->PtrCamBefore = NULL;
			}
		}
		


/*
		switch(Event)
		{
		case Rien:
			break;
		case TaperClavier:
			break;
		case SourieEnfoncee:
			break;
		case SourieLevee:
			break;
		case ClickDeplacerSourie:
			break;
		case DeplacerSourie:
			Selection(Temporaire);
			break;
		default:
			break;
		}

#define Rien					0
#define TaperClavier			1
#define SourieEnfoncee			2
#define SourieLevee				3
#define ClickDeplacerSourie		4
#define DeplacerSourie			5
	Vues *PtrCamBefore, *PtrCamAfter;
		*/


//******************Fonctions de sourie*****************//

/*
		if(Event == DeplacerSourie)
		{
			Selection(Passive);
		}

		if(	PtrM.PtrEvent->Func == 0
			&& !ClavierActive
			&& button == GLUT_LEFT_BUTTON
			&& PtrM.PtrEvent->ButGoingDown
			&& !ClickSel)
		{
			Selection(Active);
		}
		else
		{
			if(	
				Event == ClickDeplacerSourie 
				&& PtrM.PtrEvent->Left
				&& ClickSel
				)
			{
				ProgOff.SelectOff->Translation(PtrM.PtrEvent);
			}
		}

		if(!ClickSel
			&& PtrM.PtrEvent->Func == 0
			&& !PtrM.PtrEspace3D->NouvCam->MovCam)
		{
			if(PtrM.PtrEvent->Left && MsMove)
			{
				PtrM.PtrEvent->PtrCamAfter = PtrVues;
				PtrM.PtrEvent->PosAfter = PtrM.PtrEvent->NewMouse->PosEv;
				PtrM.PtrEvent->PosAfterScreen = PtrM.PtrEvent->NewMouse->PosScreen;
				Selection(Passive);
				PtrM.PtrEvent->PtrCamAfter = NULL;
			}

			if(button == GLUT_LEFT_BUTTON
				&& PtrM.PtrEvent->ButGoingUp
				&& PtrM.PtrEvent->Func == 0
				&& PtrM.PtrEvent->PtrCamBefore != NULL)
			{
				PtrM.PtrEvent->PtrCamAfter = PtrVues;
				PtrM.PtrEvent->PosAfter = PtrM.PtrEvent->NewMouse->PosEv;
				PtrM.PtrEvent->PosAfterScreen = PtrM.PtrEvent->NewMouse->PosScreen;
				Selection(Active);
				PtrM.PtrEvent->PtrCamBefore = PtrM.PtrEvent->PtrCamAfter = NULL;
			}
		}

/*	if(PtrM.PtrEspace3D->ListCam->MovCam 
		&& PtrM.PtrEvent->Left
		&& PtrM.PtrEvent->Right
		&& PtrM.PtrEvent->Middle)
	{
//		ActiveMovingCamera(Av_Rec_Sur_Cible);
	}
*//////////	
		if(PtrM.PtrEspace3D->NouvCam->MovCam 
			&& PtrM.PtrEvent->Left
			&& MsMove)
		{
			if(!PtrKeys->v
				&& PtrKeys->n
				&& !PtrKeys->b)
				ActiveMovingCamera(Av_Rec_Sur_Ptr);
	
			if(!PtrKeys->v
				&& !PtrKeys->n
				&& !PtrKeys->b)
				ActiveMovingCamera(Av_Rec_Sur_Cible);

			if(PtrKeys->v
				&& PtrKeys->n
				&& !PtrKeys->b)
				ActiveMovingCamera(Rot_Sur_Cible);

			if(!PtrKeys->v
				&& !PtrKeys->n
				&& PtrKeys->b)
				ActiveMovingCamera(Rot_Sur_Cam);

			if(PtrKeys->v
				&& !PtrKeys->n
				&& !PtrKeys->b)
				ActiveMovingCamera(Changer_Focalisation);

			if(!PtrKeys->v
				&& PtrKeys->n
				&& PtrKeys->b)
				ActiveMovingCamera(Sur_Vertical);

			if(PtrKeys->v
				&& !PtrKeys->n
				&& PtrKeys->b)
				ActiveMovingCamera(Sur_U_V);

			if(PtrKeys->v
				&& PtrKeys->n
				&& PtrKeys->b)
				ActiveMovingCamera(Sur_X_Y);
		}

		if(	state == GLUT_UP &&
			button == GLUT_LEFT_BUTTON)
		{
			ProgOff.SelectOff->ClickSurSel = false;
		}

		if(PtrM.PtrEvent->Func != 0)
		{
			CalculerPositionPourNouveauPoint();
		}
	}
	else
	{
		//	Alors c'est en mode console		//
	}

	if(PtrM.PtrEvent->Mouse->BtPress != PtrM.PtrEvent->NewMouse->BtPress)
	{
		PtrM.PtrEvent->BufferingMouse();
	}

/*
	if(!ClavierActive)
	{
		if(Event == SourieEnfoncee || Event == SourieLevee)
		{
			puMouse(button,state,x,y);
		}
		else
		{
			puMouse(x,y);
		}
	}
*/
	glutPostRedisplay();
}



//-----Evenements du clavier------//

/* called when the mouse moves */
void SpecialKeyBoard(int key,int x,int y)
{
	puKeyboard(key+PU_KEY_GLUT_SPECIAL_OFFSET,PU_DOWN);
	glutPostRedisplay();
}

void KeyBoard(unsigned char key, int x, int y)
{	
	if(key == KEY_ESCAPE)
	{exit(0);}
	puKeyboard(key,PU_DOWN);

	PtrM.PtrEspace3D->ListEvenement->Clavier->KeyPressed(key);

	ActionTaperClavier(
		key, 
		x, y, 
		PtrM.PtrEspace3D, 
		true);
	Evenements(-1, -1, x, y, false, true, TaperClavier);
}

void KeyBoardUp(unsigned char key, int x, int y)
{	
	PtrM.PtrEspace3D->ListEvenement->Clavier->KeyReleased(key);
	
	ActionTaperClavier(
		key, 
		x, y, 
		PtrM.PtrEspace3D, 
		false);
//	Evenements(0, 0, x, y, false, true, TaperClavier);
}


	//-----Clic de sourie seulement-----//

void MouseButton(int button, int state, int x, int y)
{
	puMouse(button,state,x,y);

	if(state == GLUT_DOWN)
	{
		Evenements(button, state, x, y, false, false, SourieEnfoncee);
	}
	else
	{
		Evenements(button, state, x, y, false, false, SourieLevee);
	}

	if(button == 1)
	{
//		Exit(PtrM.PtrEspace3D->ListMenu);
	}
}

	//-----Sourie qui bouge avec clic -----//

void MouseMove(int x, int y)
{
	puMouse(x,y);
	Evenements(-1, GLUT_DOWN, x, y, true, false, ClickDeplacerSourie);
}

	//-----Sourie qui bouge sans clic -----//

void MousePassive(int x, int y)			
{	
	Evenements(-1, GLUT_UP, x, y, true, false, DeplacerSourie);
}



/* The display function - called when redraw is needed */
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	DisplayTextBitmap();

	/* display the user interface */
	puDisplay();

	glutSwapBuffers();
}


void main(int argc,char** argv)
{

	PtrM.PtrEspace3D = ProgOff.Espace3D;

	PtrM.PtrEspace3D->ListMenu->Screen.setPosSize(0,400, 1400, 600);

	setCam();
	PtrM.PtrEspace3D->ListEvenement->PtrPlan = PtrM.PtrEspace3D->Grille;

/*	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 

	glutInitWindowSize (PtrM.PtrEspace3D->ListMenu->Screen.Largeur, PtrM.PtrEspace3D->ListMenu->Screen.Hauteur);
	glutInitWindowPosition (PtrM.PtrEspace3D->ListMenu->Screen.PosX, PtrM.PtrEspace3D->ListMenu->Screen.PosY);
	glutCreateWindow ("Menu1");

	/*PtrM.PtrEspace3D->ListMenu->Screen.GameMode.c_str()*/

	glutGameModeString("1400x1050:32@60") ;
/*
	//		glutWarpPointer();
	//		glutFullScreen();
	//		glutSetCursor(GLUT_CURSOR_NONE);

	if (glutGameModeGet(GLUT_GAME_MODE_WIDTH) != -1)  // if the width is different to -1
	{

//		glutEnterGameMode();		// enter full screen mode
*/






	InitMain();

	ListClass = NULL;
	ListClass = new NClass;
	ListClass->AddVar();

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(300,400);
	glutCreateWindow("Class - List - Creator");
	InitTextBitmap();

	glutReshapeFunc(reshape);
	glutDisplayFunc(Display);

	glutPassiveMotionFunc(MousePassive);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMove);
	glutKeyboardFunc(KeyBoard);
	glutKeyboardUpFunc(KeyBoardUp);
	glutSpecialFunc(SpecialKeyBoard);

	puInit();
	Init();
	InitUI();
	PtrM.PtrEspace3D->ListMenu->MenuInit();
	PtrM.PtrEspace3D->CL.Init();

	glutMainLoop();

}


/*

void init(void)
{
glShadeModel (GL_FLAT);
makeRasterFont();
}
int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize(300, 100);
glutInitWindowPosition (100, 100);
glutCreateWindow(argv[0]);

glutReshapeFunc(reshape);
glutKeyboardFunc(KeyBoard);
glutDisplayFunc(Display);
glutMainLoop();
return 0;
}
*/