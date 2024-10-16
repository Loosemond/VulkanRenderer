//
//  Scene.cpp
//
#include "Scene.h"
#include "Physics/Contact.h"
#include "Physics/Intersections.h"
#include "Physics/Broadphase.h"

/*
========================================================================================================

Scene

========================================================================================================
*/

/*
====================================================
Scene::~Scene
====================================================
*/
Scene::~Scene() {
	for ( int i = 0; i < m_bodies.size(); i++ ) {
		delete m_bodies[ i ].m_shape;
	}
	m_bodies.clear();
}

/*
====================================================
Scene::Reset
====================================================
*/
void Scene::Reset() {
	for ( int i = 0; i < m_bodies.size(); i++ ) {
		delete m_bodies[ i ].m_shape;
	}
	m_bodies.clear();

	Initialize();
}

/*
====================================================
Scene::Initialize
====================================================
*/
void Scene::Initialize() {
	Body body;
	body.m_id = 0;
	body.m_type = Body::BODY_DYNAMIC;
	body.m_position = Vec3( 0, 0, 1 );
	body.m_orientation = Quat( 0, 0, 0, 1 );
	body.m_shape = new ShapeSphere( 1.0f );
	body.m_radius = 1.0f;
	body.m_invMass = 1/10.0f;
	m_bodies.push_back( body );

	body.m_id = 1;
	body.m_type = Body::BODY_DYNAMIC;
	body.m_position = Vec3( 0, 0, -101 );
	body.m_orientation = Quat( 0, 0, 0, 1 );
	body.m_shape = new ShapeSphere( 100.0f );
	body.m_radius = 100.0f;
	body.m_invMass = 0.0f;
	m_bodies.push_back( body );

	body.m_id = 2;
	body.m_type = Body::BODY_DYNAMIC;
	body.m_position = Vec3(0, 0, 4);
	body.m_orientation = Quat(0, 0, 0, 1);
	body.m_shape = new ShapeSphere(1.0f);
	body.m_radius = 1.0f;
	body.m_invMass = 1 / 10.0f;
	m_bodies.push_back(body);

	// TODO: Add code
}

/*
====================================================
Scene::Update
====================================================
*/
void Scene::Update( const float dt_sec ) {
	// TODO: Add code
	for (auto& body : m_bodies)
	{
		if (body.m_type != Body::BODY_FIXED)
		{
			// Gravity is an impulse
			// I = dp, F = dp/dt => dp = f * dp => I = F * dt
			// F = mgs
			Vec3 impulseGravity = Vec3(0, 0, -10) * 1/body.m_invMass * dt_sec;
			body.ApplyImpulseLinear(impulseGravity);
			for (auto& contact_body : m_bodies)
			{
				if (body.m_id != contact_body.m_id) 
				{
					body.CollisionCheck(contact_body);
				}
			}
			body.m_position += body.m_linearVelocity * dt_sec;
		}
	}
}