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

	//body.m_id = 2;
	//body.m_type = Body::BODY_DYNAMIC;
	//body.m_position = Vec3(0, 0, 4);
	//body.m_orientation = Quat(0, 0, 0, 1);
	//body.m_shape = new ShapeSphere(1.0f);
	//body.m_radius = 1.0f;
	//body.m_invMass = 1 / 10.0f;
	//m_bodies.push_back(body);

	// TODO: Add code
}

/*
====================================================
Scene::Update
====================================================
*/
void Scene::Update( const float dt_sec ) {
	// TODO: Add code
	int collision_count{ 0 };
	for (auto& body : m_bodies)
	{
		if (body.m_type != Body::BODY_FIXED)
		{
			// Gravity is an impulse
			// I = dp, F = dp/dt => dp = f * dp => I = F * dt
			// F = mgs
			Vec3 impulseGravity = Vec3(0, 0, -10000) * 1/body.m_invMass * dt_sec;
			body.ApplyImpulseLinear(impulseGravity);
			for (auto& contact_body : m_bodies)
			{
				if ((body.m_id != contact_body.m_id) && (body.m_invMass != 0.0f) && (body.m_linearVelocity != Vec3(0,0,0)))
				{
					//body.CollisionCheck(contact_body);
					//collision_count++;
				}
			}


		}
	}

	for (int i = 0; i < m_bodies.size(); i++)
	{
		for (int j = 0; j < m_bodies.size(); j++)
		{
			Body* bodyA = &m_bodies[i];
			Body* bodyB = &m_bodies[j];

			if ((bodyA->m_id != bodyB->m_id) && (bodyA->m_invMass != 0.0f) && (bodyA->m_linearVelocity != Vec3(0, 0, 0)))
			//if ((bodyA->m_invMass != 0.0f))
			{
				//body.CollisionCheck(contact_body);
				contact_t contact;
				if (Intersect(bodyA, bodyB, contact))
				{
					ResolveContact(contact);
				}
				collision_count++;
			}
		}


	}
	for (auto& body : m_bodies)
	{
		body.m_position += body.m_linearVelocity * dt_sec;
	}



	printf("Collisions: %d\n", collision_count);
}