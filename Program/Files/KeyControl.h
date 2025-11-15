#pragma once

//#include "GraphicCard.h"
#include <functional>
using ActionCallback = std::function<void()>;

#include "Shader.h"
#include "structures.h"
#include "msg.h"
#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <string>

//	Ici, on liste donc les fonctions qu'on veut en fonction des touche de clavier/sourie qu'on doit appuyer pour lancer ces fonctions.


#define _KeyConfig_Up					0
#define _KeyConfig_Down					1
#define _KeyConfig_Right				2
#define _KeyConfig_Left					3
#define _KeyConfig_ChangeGridUpper		4
#define _KeyConfig_ChangeGridLower		5
#define _KeyConfig_ChangeColorMap		6
#define _KeyConfig_ChangeOrthoMod		7
#define _KeyConfig_LeftControl			8
#define _KeyConfig_LeftShift			9
#define _KeyConfig_Space				10
#define _KeyConfig_Exit					11
#define _KeyConfig_NavRotateTarget		12
#define _KeyConfig_NavRotateCamera		13
#define _KeyConfig_Etire				14
#define _KeyConfig_Rotation				15
#define _KeyConfig_Translation			16
#define _KeyConfig_SpecifierPapilleHaut	17
#define _KeyConfig_SpecifierCreteHaut	18
#define _KeyConfig_SpecifierCentreBas	19
#define _KeyConfig_SpecifierCretesBas	20
#define _KeyConfig_ContourCrete			21
#define _KeyConfig_EpaisseurLiner		22
#define _KeyConfig_EpaisseurBoudin		23
#define _KeyConfig_EpaiseureGencive		24
#define _KeyConfig_CreerReperes			25
#define _KeyConfig_LancerReperes		26
#define _KeyConfig_Cachee				27
#define _KeyConfig_FonctionOpposee		28
#define _KeyConfig_NavCenterOnSelected	29
#define _KeyConfig_NavCenterOnAll		30
#define _KeyConfig_ToggleShowGrid		31





// Include GLFW
#include <GLFW/glfw3.h>

#include <functional>
using ActionCallback = std::function<void()>;

using namespace std;



enum MouseState {
	m_anything,
	m_steady,
	m_justmove,
	m_move,
	m_juststop
};

enum ButtonState {
	b_steady,
	b_pressed,
	b_hold,
	b_released,
	b_double_clicked
};


class _Key
{
public:

	int lastTimePressed = 0;

	int _keyslot0 = 0, _keyslot1 = 0;

	ButtonState m_bs_for_activation, m_bs_old;
	MouseState m_mousestat;

	bool oldActivation = false;
	bool recentlyActivated = false;
	bool isActivated = false;
	bool _justReleased = false;

public:
	_Key(int, int, MouseState, ButtonState);
	_Key();
	~_Key();

	bool IsActivated(GLFWwindow*);
	bool IsJustReleased();
	bool IsDoubleClicked(int);
};


class KeyControl
{
public:
	map<int, _Key> m_KeyList;
	map<int, _Key>::iterator _key_it;

	_Key Mouse_Right, Mouse_Left, Mouse_Middle;

	float doublicktime = 0.5;

	KeyControl();
	~KeyControl();

	void KeyActivated(int, MouseState);
	bool DoesExist(int);
	msg AssignNewKeyBinding(int, int, int);
	bool IsDoubleclicked(int);
	void InitiateFunctionBinding();
	void KeyContent(int _KeyToReturn);
	bool IsActivated(GLFWwindow*, int);
	bool IsRecentlyActivated(int _KeyToCheck);
	bool IsJustReleased(int _key2check);
};
