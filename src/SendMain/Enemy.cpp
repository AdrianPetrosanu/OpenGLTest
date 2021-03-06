#include "Enemy.h"
#include <stdlib.h>

Enemy::Enemy(Shader* s, float dim, int t)
{
	hd = dim / 2.0f;

	Vertex verts[] = {
		Vertex(glm::vec3(hd, hd, 0), glm::vec2(1, 1)),
		Vertex(glm::vec3(hd, -hd, 0), glm::vec2(1, 0)),
		Vertex(glm::vec3(-hd, -hd, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(-hd, hd, 0), glm::vec2(0, 1))
	};

	
	m_type = t;
	m_file = m_type == 0 ? std::string("../data/Textures/Enemy1.png") : std::string("../data/Textures/Enemy2.png");
	
	m_sprite = new Sprite(verts, sizeof(verts) / sizeof(verts[0]), m_file.c_str());

	m_asc = 1;
	m_fps = 0.0f;

	m_shader = s;
	m_transform = new Transform;

	float x, y, z;
	x = (rand() % 100 - 50) / 50.0f;
	y = (rand() % 100 - 20) / 100.0f;
	z = 0;

	m_transform->SetPos(glm::vec3(x, y, z));
	m_shader->Update(*m_transform);
	hp = 100;
}

void Enemy::Draw()
{
	m_shader->Update(*m_transform);
	m_sprite->Draw();
}

void Enemy::Update()
{
	float speed = 0.01f;
	float limit = 0.85f;
	float x, y, z;
	x = m_transform->GetPos()->x;
	y = m_transform->GetPos()->y;
	z = m_transform->GetPos()->z;

	if (m_type == 1)
	{
		if (y + sinf(m_fps) / 200 < limit)
		{
			float inc = sinf(m_fps) / 200;
			y += inc;
		}
		m_fps += speed;
	}

	x += m_asc * speed;

	if (fabs(x) < limit)
	{
		m_transform->SetPos(glm::vec3(x, y, z));
	}
	else
	{
		m_transform->SetPos(glm::vec3(x < 0 ? -limit : limit, y, z));
		m_asc *= -1;
	}

	///2 nu face parte din algoritm, dar arata mai realist asa
	xm = m_transform->GetPos()->x - hd / 2;
	xM = m_transform->GetPos()->x + hd / 2;
	ym = m_transform->GetPos()->y - hd / 2;
	yM = m_transform->GetPos()->y + hd / 2;
}

void Enemy::TakeDamage()
{
	hp -= 40;
	if (m_file == std::string("../data/Textures/Enemy1.png"))
		m_file = std::string("../data/Textures/Enemy1d1.png");
	else if (m_file == std::string("../data/Textures/Enemy1d1.png"))
		m_file = std::string("../data/Textures/Enemy1d2.png");
	else if (m_file == std::string("../data/Textures/Enemy2.png"))
		m_file = std::string("../data/Textures/Enemy2d1.png");
	else if (m_file == std::string("../data/Textures/Enemy2d1.png"))
		m_file = std::string("../data/Textures/Enemy2d2.png");

	Vertex verts[] = {
		Vertex(glm::vec3(hd, hd, 0), glm::vec2(1, 1)),
		Vertex(glm::vec3(hd, -hd, 0), glm::vec2(1, 0)),
		Vertex(glm::vec3(-hd, -hd, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(-hd, hd, 0), glm::vec2(0, 1))
	};

	m_sprite = new Sprite(verts, sizeof(verts) / sizeof(verts[0]), m_file.c_str());
}

Enemy::~Enemy()
{
	delete m_sprite;
	delete m_transform;
}
