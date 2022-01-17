//Precompiled Header [ALWAYS ON TOP IN CPP]
#include "stdafx.h"

//Includes
#include "SteeringBehaviors.h"
#include "../SteeringAgent.h"
#include "../Obstacle.h"
#include "framework\EliteMath\EMatrix2x3.h"

using namespace Elite;

//SEEK
//****
SteeringOutput Seek::CalculateSteering(float deltaT, SteeringAgent* pAgent)
{
	SteeringOutput steering = {};

	pAgent->SetAutoOrient(true);

	const float arrivalRadius{ 1.f };

	steering.LinearVelocity = m_Target.Position - pAgent->GetPosition();
	steering.LinearVelocity.Normalize();
	steering.LinearVelocity *= pAgent->GetMaxLinearSpeed();

	const float distance = steering.LinearVelocity.Magnitude();

	steering.LinearVelocity *= pAgent->GetMaxLinearSpeed();
	if (distance < arrivalRadius) steering.LinearVelocity = ZeroVector2;

	if (pAgent->CanRenderBehavior()) DEBUGRENDERER2D->DrawDirection(pAgent->GetPosition(), steering.LinearVelocity, 5.f, {0,1,0,1});

	return steering;
}

//FLEE
//****
SteeringOutput Flee::CalculateSteering(float deltaT, SteeringAgent* pAgent)
{
	SteeringOutput steering = {};

	pAgent->SetAutoOrient(true);


	//Variables
	const float exitRadius{ 20.f };
	const float slowRadius{ 15.f };

	steering.LinearVelocity = pAgent->GetPosition() - m_Target.Position;
	const float distance = steering.LinearVelocity.Magnitude();
	steering.LinearVelocity.Normalize();
	steering.LinearVelocity *= pAgent->GetMaxLinearSpeed();


	if (distance > exitRadius) steering.LinearVelocity = ZeroVector2;
	else if (distance > exitRadius - slowRadius) steering.LinearVelocity *= pAgent->GetMaxLinearSpeed() * distance / slowRadius;
	else steering.LinearVelocity *= pAgent->GetMaxLinearSpeed();

	if (pAgent->CanRenderBehavior()) DEBUGRENDERER2D->DrawDirection(pAgent->GetPosition(), steering.LinearVelocity, 5.f, { 0,1,0,1 });

	return steering;
}

//ARRIVE
//****
SteeringOutput Arrive::CalculateSteering(float deltaT, SteeringAgent* pAgent)
{
	SteeringOutput steering = {};

	pAgent->SetAutoOrient(true);

	//Variables
	const float arrivalRadius{ 15.f };
	const float slowRadius{ 30.f };

	steering.LinearVelocity = m_Target.Position - pAgent->GetPosition();

	float distance = steering.LinearVelocity.Magnitude();

	steering.LinearVelocity.Normalize();
	steering.LinearVelocity *= pAgent->GetMaxLinearSpeed();

	if (distance < slowRadius) steering.LinearVelocity *= pAgent->GetMaxLinearSpeed() * distance / (slowRadius - arrivalRadius);
	else steering.LinearVelocity *= pAgent->GetMaxLinearSpeed();

	if (distance < arrivalRadius) steering.LinearVelocity = ZeroVector2;

	if (pAgent->CanRenderBehavior()) DEBUGRENDERER2D->DrawDirection(pAgent->GetPosition(), steering.LinearVelocity, 5.f, { 0,1,0,1 });

	return steering;
}

//FACE
//****
SteeringOutput Face::CalculateSteering(float deltaT, SteeringAgent* pAgent)
{
	SteeringOutput steering = {};

	pAgent->SetAutoOrient(false);

	Vector2 toTarget = m_Target.Position - pAgent->GetPosition();
	float angle = std::atan2f(toTarget.y, toTarget.x);
	float currAngle = pAgent->GetRotation();
	
	float diffAngle = angle - currAngle;

	//Offset
	diffAngle += b2_pi/2;

	// Variables 
	float rotateSpeed{ 10000.f };
	float rangeToStopCheckking{ 0.1f };

	steering.LinearVelocity = ZeroVector2;
	if (diffAngle > 0 + rangeToStopCheckking) steering.AngularVelocity = deltaT * rotateSpeed;
	else if (diffAngle < 0 - rangeToStopCheckking) steering.AngularVelocity = deltaT * -rotateSpeed;

	if (pAgent->CanRenderBehavior()) DEBUGRENDERER2D->DrawDirection(pAgent->GetPosition(), steering.LinearVelocity, 5.f, { 0,1,0,1 });

	return steering;
}

//WANDER
//****
SteeringOutput Wander::CalculateSteering(float deltaT, SteeringAgent* pAgent)
{
	SteeringOutput steering = {};

	pAgent->SetAutoOrient(true);

	// Set Target To Different Target
	// Vars
	const float offsetDistance{ 6.0f };
	const float radius{ 4.0f };
	constexpr float maxAngleChange{ ToRadians(45.0f) };
	const float wanderAngle{ 0.0f };

	Vector2 circleCenter{ pAgent->GetPosition() + (pAgent->GetLinearVelocity().GetNormalized() * offsetDistance) };








	// Move towards target
	const float arrivalRadius{ 1.f };

	steering.LinearVelocity = m_Target.Position - pAgent->GetPosition();
	steering.LinearVelocity.Normalize();
	steering.LinearVelocity *= pAgent->GetMaxLinearSpeed();

	const float distance = steering.LinearVelocity.Magnitude();

	steering.LinearVelocity *= pAgent->GetMaxLinearSpeed();
	if (distance < arrivalRadius) steering.LinearVelocity = ZeroVector2;

	if (pAgent->CanRenderBehavior()) DEBUGRENDERER2D->DrawDirection(pAgent->GetPosition(), steering.LinearVelocity, 5.f, { 0,1,0,1 });

	return steering;
}


//EVADE
//****
SteeringOutput Evade::CalculateSteering(float deltaT, SteeringAgent* pAgent)
{
	SteeringOutput steering = {};

	//ToDo: Implement Evade

	return steering;
}

//PURSUIT
//****
SteeringOutput Pursuit::CalculateSteering(float deltaT, SteeringAgent* pAgent)
{
	SteeringOutput steering = {};

	//ToDo: Implement Pursuit

	return steering;
}

