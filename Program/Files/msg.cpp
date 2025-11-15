
#include "msg.h"


msg::msg(string newContent) : m_content(newContent)
{
}

msg::msg()
{
}


msg::~msg()
{
}

void msg::changeTo(string newContent)
{
	m_content = newContent;
}