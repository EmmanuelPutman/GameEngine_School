#include "EP_Engine_PCH.h"
#include "Transform.h"

void ep::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
