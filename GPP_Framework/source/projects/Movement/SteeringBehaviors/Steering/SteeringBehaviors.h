/*=============================================================================*/
// Copyright 2021-2022 Elite Engine
// Authors: Matthieu Delaere, Thomas Goussaert
/*=============================================================================*/
// SteeringBehaviors.h: SteeringBehaviors interface and different implementations
/*=============================================================================*/
#ifndef ELITE_STEERINGBEHAVIORS
#define ELITE_STEERINGBEHAVIORS

//-----------------------------------------------------------------
// Includes & Forward Declarations
//-----------------------------------------------------------------
#include "../SteeringHelpers.h"
#include "framework\EliteMath\EMatrix2x3.h"

class SteeringAgent;
class Obstacle;

#pragma region **ISTEERINGBEHAVIOR** (BASE)
class ISteeringBehavior
{
public:
	ISteeringBehavior() = default;
	virtual ~ISteeringBehavior() = default;

	virtual SteeringOutput CalculateSteering(float deltaT, SteeringAgent* pAgent) = 0;

	//Seek Functions
	void SetTarget(const TargetData& target) { m_Target = target; }

	template<class T, typename std::enable_if<std::is_base_of<ISteeringBehavior, T>::value>::type* = nullptr>
	T* As()
	{
		return static_cast<T*>(this);
	}

protected:
	TargetData m_Target;
};
#pragma endregion

///////////////////////////////////////
//SEEK
//****
class Seek : public ISteeringBehavior
{
public:
	Seek() = default;
	virtual ~Seek() = default;

	//Seek Behaviour
	SteeringOutput CalculateSteering(float deltaT, SteeringAgent* pAgent) override;
};

///////////////////////////////////////
//CONTEXTSTEERING
//****
class ContextSteering : public Seek
{
public:
	ContextSteering() = default;
	virtual ~ContextSteering() = default;

	SteeringOutput CalculateSteering(float deltaT, SteeringAgent* pAgent) override;
	void AddObstacle(Obstacle* obstacle) { m_pObstacles.push_back(obstacle); };
	void SetArraySize(int size = 8);

private:
	bool IsArrowInObstacle(const Elite::Vector2& start, const Elite::Vector2& dir, Obstacle* pObstacle);

	bool m_InterpolateDangers = true;

	std::vector<Obstacle*> m_pObstacles{};
	size_t m_ArraySize = 16;
	float m_LookAheadRange = 10.f; // Default 5

	// Only here for sparing out memory allocation each frame;
	std::vector<Elite::Vector2> m_Directions;
	std::vector<float> m_Interests;
	std::vector<float> m_Dangers;
	std::vector<Elite::Color> m_Colors;
};
#endif


