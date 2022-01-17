//Precompiled Header [ALWAYS ON TOP IN CPP]
#include "stdafx.h"

//Includes
#include "SteeringBehaviors.h"
#include "../SteeringAgent.h"
#include "../Obstacle.h"
#include "framework\EliteMath\EMatrix2x3.h"

using namespace Elite;
class Color;

//SEEK
//****
SteeringOutput Seek::CalculateSteering(float deltaT, SteeringAgent* pAgent)
{
	SteeringOutput steering = {};

	steering.LinearVelocity = (m_Target).Position - pAgent->GetPosition(); //Desired Velocity
	steering.LinearVelocity.Normalize(); //Normalize Desired Velocity
	steering.LinearVelocity *= pAgent->GetMaxLinearSpeed(); //Rescale to Max Speed

	//DEBUG RENDERING
	if (pAgent->CanRenderBehavior())
		DEBUGRENDERER2D->DrawDirection(pAgent->GetPosition(), steering.LinearVelocity, 5, { 0,1,0 }, 0.4f);

	return steering;
}

// CONTEXT STEERING
//****
SteeringOutput ContextSteering::CalculateSteering(float deltaT, SteeringAgent* pAgent)
{
	#pragma region Initialize
	// Agent info
	Vector2 agentPos = pAgent->GetPosition();
	float agentAngle = pAgent->GetOrientation();
	#pragma endregion

	#pragma region RotateDirections
	for (size_t i{}; i < m_ArraySize; i++)
	{
		float angle = (int)i * (2 * (float)M_PI / m_ArraySize);
		Vector2 RotatedVector{};
		Vector2 rightVector{ 1,0 };

		RotatedVector.x = rightVector.x * cos(agentAngle + angle) - rightVector.y * sin(agentAngle + angle);
		RotatedVector.y = rightVector.x * sin(agentAngle + angle) - rightVector.y * cos(agentAngle + angle);

		RotatedVector = RotatedVector.GetNormalized();
		RotatedVector *= m_LookAheadRange;
		m_Directions[i] = RotatedVector;
	}
	#pragma endregion

	#pragma region CalculateInterests
	Vector2 desired{ m_Target.Position - pAgent->GetPosition() };
	desired = desired.GetNormalized();

	for (size_t i{}; i < m_ArraySize; i++)
	{
		float dot = m_Directions[i].GetNormalized().Dot(desired);
		if (dot <= 0.f)
		{
			m_Interests[i] = 0;
		}
		else
		{
			m_Interests[i] = dot;
		}
	}
	#pragma endregion

	#pragma region CalculateDangers

	for (size_t i{}; i < m_ArraySize; i++)
	{
		bool active{};
		for (size_t j{}; j < m_pObstacles.size(); j++)
		{
			
			if (IsArrowInObstacle(agentPos, m_Directions[i], m_pObstacles[j]))
			{
				if (m_InterpolateDangers) 
				{
					// Danger value = normalized(max range - actual range)
					float distance = Elite::Distance(agentPos, m_pObstacles[j]->GetCenter());
					distance -= m_pObstacles[j]->GetRadius();

					//m_Dangers[i] = (m_LookAheadRange - distance); // Will avoid sooner, but a bit too soon 
					m_Dangers[i] = (m_LookAheadRange - distance) / m_LookAheadRange;
				}
				else
				{
					m_Dangers[i] = 1;
				}
				active = true;
				m_Colors[i] = Elite::Color(m_Dangers[i],1 - m_Dangers[i],0);
			}
			else if (!active)
			{
				m_Dangers[i] = 0.f;
				m_Colors[i] = Elite::Color(0,1,0);
			}
		}

	}
	#pragma endregion

	// Render all arrows
	if (pAgent->CanRenderBehavior())
	{
		for (size_t i{}; i < m_ArraySize; i++)
		{
			DEBUGRENDERER2D->DrawDirection(pAgent->GetPosition(), m_Directions[i] * m_Interests[i], (m_Directions[i] * m_Interests[i]).Magnitude(), m_Colors[i], 0.4f);
		}
	}

	// Subtract dangers from interests
	for (size_t i{}; i < m_ArraySize; i++)
	{
		m_Interests[i] -= m_Dangers[i];
	}

	// Calculate final direction
	Elite::Vector2 finalDirection{};
	for (size_t i{}; i < m_ArraySize; i++)
	{
		finalDirection += m_Directions[i] * m_Interests[i];
	}
	finalDirection = finalDirection.GetNormalized();
	finalDirection *= pAgent->GetMaxLinearSpeed();

	// Draw Debug Direction
	if (pAgent->CanRenderBehavior())
		DEBUGRENDERER2D->DrawDirection(pAgent->GetPosition(), finalDirection, finalDirection.Magnitude(), { 0,0,1, 1.f }, 0.4f);

	// Output
	auto output = SteeringOutput();
	output.AngularVelocity = 0.0f;
	output.LinearVelocity = finalDirection;
	output.IsValid = true;
	return output;
}

void ContextSteering::SetArraySize(int size)
{
	m_ArraySize = size;
	m_Dangers.resize(m_ArraySize);
	m_Interests.resize(m_ArraySize);
	m_Colors.resize(m_ArraySize);
	m_Directions.resize(m_ArraySize);
}

bool ContextSteering::IsArrowInObstacle(const Elite::Vector2& start, const Elite::Vector2& dir, Obstacle* pObstacle)
{
	Vector2 closestPoint = ProjectOnLineSegment(start, start + dir, pObstacle->GetCenter());
	float distanceToCircleCenter = Elite::Distance(pObstacle->GetCenter(), closestPoint);

	if (distanceToCircleCenter <= pObstacle->GetRadius())
	{
		return  true;
	}

	return false;
}
