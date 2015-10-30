#include "KinematicUnitManager.h"
#include "AddKinematicUnitNearPlayerMessage.h"

KinematicUnitManager::KinematicUnitManager()
{

}

KinematicUnitManager::~KinematicUnitManager()
{
	clear();
}

void KinematicUnitManager::addKinematicUnit(KinematicUnit *kunit)
{
	m_units.push_back(kunit);
}

void KinematicUnitManager::removeKinematicUnit(std::string id)
{
	for (size_t i = 0; i < m_units.size(); i++)
	{
		if (id == m_units[i]->getID())
		{
			delete m_units[i];
			m_units.erase(m_units.begin() + i);
			//return;
		}
	}
}

void KinematicUnitManager::removeKinematicUnit(KinematicUnit *kunit)
{
	for (size_t i = 0; i < m_units.size(); i++)
	{
		if (kunit == m_units[i])
		{
			std::cout << "Implement me.\n";
		}
	}
}

void KinematicUnitManager::removeRandomKinematicUnit()
{
	if (m_units.size() == 1)
		return;

	srand(time(0));

	int rand_index;
	do
	{
		rand_index = rand() % m_units.size();
	} while (m_units[rand_index]->getID() == "player");

	delete m_units[rand_index];
	m_units.erase(m_units.begin() + rand_index);
}

void KinematicUnitManager::removeAllBoids()
{
	for (size_t i = 0; i < m_units.size(); i++)
	{
		if (m_units[i]->getID() == "player")
			continue;

		delete m_units[i];
		m_units.erase(m_units.begin() + i);
	}
}

KinematicUnit* KinematicUnitManager::getKinematicUnit(std::string id)
{
	for (size_t i = 0; i < m_units.size(); i++)
	{
		if (id == m_units[i]->getID())
		{
			return m_units[i];
		}
	}
	return NULL;
}

int KinematicUnitManager::getNumKinematicUnits()
{
	return m_units.size();
}

void KinematicUnitManager::update(float dTime)
{
	for (size_t i = 0; i < m_units.size(); i++)
	{
		//std::cout << "Updating: " << m_units[i]->getID() << std::endl;
		m_units[i]->update(dTime);
	}

	displayUnitCount();
}

void KinematicUnitManager::draw()
{
	for (size_t i = 0; i < m_units.size(); i++)
	{
		m_units[i]->draw(GRAPHICS_SYSTEM->getBackBuffer());
	}
}

void KinematicUnitManager::clear()
{
	for (size_t i = 0; i < m_units.size(); i++)
	{
		delete m_units[i];
	}
	m_units.clear();
}

void KinematicUnitManager::displayUnitCount()
{
	std::stringstream displayStream;
	displayStream << "[UNITS ON SCREEN]: [" << m_units.size() << "]";
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 0, 0), 0, 0, ALLEGRO_ALIGN_LEFT, displayStream.str().c_str());
}