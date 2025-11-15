
#include "KeyControl.h"





_Key::_Key(int _newKey2Bind0, int _newKey2Bind1, MouseState _MS2use, ButtonState _BS2Use) : _keyslot0(_newKey2Bind0), _keyslot1(_newKey2Bind1), m_mousestat(_MS2use), m_bs_for_activation(_BS2Use)
{

};

_Key::_Key() : _keyslot0(0), _keyslot1(0), m_mousestat(m_anything), m_bs_for_activation(b_steady), m_bs_old(b_steady)
{
}

_Key::~_Key() {

};

bool _Key::IsDoubleClicked(int _tick)
{
	return (false);
};

bool _Key::IsActivated(GLFWwindow* window)
{
	//	cout << isActivated << "\t"<< oldActivation << endl;
	//	Check if its a release //	It was activated but its not anymore, that means, its just got released!!
	if (isActivated && (_keyslot0 != 0 && glfwGetKey(window, _keyslot0) == GLFW_RELEASE) || (_keyslot1 != 0 &&glfwGetKey(window, _keyslot1) == GLFW_RELEASE))
		{
			//	Its a release!!
			isActivated = false;
			_justReleased = true;

			return false;
		}

	//	So we can only see those that are pressed, not when release. If its not pressed, but was pressed before, then its a release.
	if (m_bs_for_activation == b_pressed &&
		(_keyslot0 != 0 && glfwGetKey(window, _keyslot0) == GLFW_PRESS || (_keyslot1 != 0 && glfwGetKey(window, _keyslot1) == GLFW_PRESS)))
	{
		m_bs_old = m_bs_for_activation;

		isActivated = true;
		if (oldActivation != isActivated)
		{
			recentlyActivated = true;
			oldActivation = true;
		}
		else
		{
			recentlyActivated = false;
		}

		_justReleased = false;
		return true;
	}

	return (false);
};

bool _Key::IsJustReleased()
{
	if (_justReleased)
	{
		_justReleased = false;
		oldActivation = false;
		return true;
	}

	return false;
}

KeyControl::KeyControl() {

};


KeyControl::~KeyControl() {

};

void KeyControl::KeyActivated(int _time, MouseState _NewMouseState) {

};

bool KeyControl::DoesExist(int _Key2Check) {
	for (_key_it = m_KeyList.begin(); _key_it != m_KeyList.end(); _key_it++)
	{
		if (_key_it->second._keyslot0 == _Key2Check || _key_it->second._keyslot1 == _Key2Check)
		{
			//	Bon on l'� trouv�!!
			return true;
		}
	}

	return false;
}

msg KeyControl::AssignNewKeyBinding(int functionLevel, int newKeybinding, int posBinding)
{
	if (functionLevel < m_KeyList.size() - 1)
	{
		for (size_t i = 0; i < m_KeyList.size(); i++)
		{
			if (functionLevel == i)
			{
				if (posBinding == 0)
					m_KeyList[i]._keyslot0 = newKeybinding;
				else
					m_KeyList[i]._keyslot1 = newKeybinding;

				return msg("New key binding is complete");
			}
		}
		return msg("New key binding completed");
	}
	else
		return msg("KeyList is empty");
}

bool KeyControl::IsDoubleclicked(int _newKeyUsed)
{
	return false;
}

void KeyControl::InitiateFunctionBinding()
{	//	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)


	//enum MouseState {
	//	m_steady,
	//	m_justmove,
	//	m_move,
	//	m_juststop
	//};

	//enum ButtonState {
	//	b_steady,
	//	b_pressed,
	//	b_hold,
	//	b_released,
	//	b_double_clicked
	//};



}

void KeyControl::KeyContent(int _KeyToReturn)
{
	_key_it = m_KeyList.find(_KeyToReturn);
}

bool KeyControl::IsActivated(GLFWwindow* window, int _KeyToCheck)
{
	_Key KeyUsed;
	KeyContent(_KeyToCheck);

	return(_key_it->second.IsActivated(window));
}

bool KeyControl::IsRecentlyActivated(int _KeyToCheck)
{
	_Key KeyUsed;
	KeyContent(_KeyToCheck);

	return(_key_it->second.recentlyActivated);
}

bool KeyControl::IsJustReleased(int _KeyToCheck)
{
	_Key KeyUsed;
	KeyContent(_KeyToCheck);

	return(_key_it->second.IsJustReleased());
}
