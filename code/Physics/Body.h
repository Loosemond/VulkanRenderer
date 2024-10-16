//
//	Body.h
//
#pragma once
#include "../Math/Vector.h"
#include "../Math/Quat.h"
#include "../Math/Matrix.h"
#include "../Math/Bounds.h"
#include "Shapes.h"
#include <random>


#include "../Renderer/model.h"
#include "../Renderer/shader.h"
#include <string>

/*
====================================================
Body
====================================================
*/


class Body {


public:
	Body();

	enum body_t
	{
		BODY_FIXED,
		BODY_DYNAMIC
	};

	body_t		m_type;
	Vec3		m_position;
	Quat		m_orientation;
	Vec3		m_linearVelocity;
	float		m_invMass;
	Shape *		m_shape;
	float		m_radius;
	float		m_id;

	void ApplyImpulseLinear(const Vec3& impulse)
	{
		if (0.0f != m_invMass)
		{
			// p = mv
			// dp = m dv = J
			// => dv = J / m
			m_linearVelocity += impulse * m_invMass;
		}
	}

	Vec3 DistanceTo(Vec3 targetObject)
	{
		if (m_position.GetLengthSqr() > targetObject.GetLengthSqr()) 
		{
			return m_position - targetObject;
		}
		else {
			return targetObject - m_position;
		}
	}

	void CollisionCheck(Body targetBody) 
	{

		if (targetBody.m_shape->GetType() == Shape::SHAPE_SPHERE)
		{
			 printf("Body %f Distance to %f: %f\n", m_id, targetBody.m_id, (DistanceTo(targetBody.m_position).GetLengthSqr()));
			if ((DistanceTo(targetBody.m_position).GetLengthSqr() ) < ((m_radius + targetBody.m_radius)* (m_radius + targetBody.m_radius)))
			{
				m_linearVelocity = Vec3{ 0,0,0 };
			}
		}
	}

};

