//Precompiled Header [ALWAYS ON TOP IN CPP]
#include "stdafx.h"

//Includes
#include "App_Sandbox.h"
#include "SandboxAgent.h"

using namespace Elite;

//Destructor
App_Sandbox::~App_Sandbox()
{
	SAFE_DELETE(m_pAgent);
}

//Functions
void App_Sandbox::Start()
{
	m_pAgent = new SandboxAgent{ };
}

void App_Sandbox::Update(float deltaTime)
{
	m_pAgent->Update(deltaTime);

	if (INPUTMANAGER->IsMouseButtonUp(InputMouseButton::eLeft)) 
	{
		auto const mouseData = INPUTMANAGER->GetMouseData(InputType::eMouseButton, InputMouseButton::eLeft);
		m_pAgent->SetTarget(DEBUGRENDERER2D->GetActiveCamera()->ConvertScreenToWorld(Vector2{(float)mouseData.X, (float)mouseData.Y }));
	}
}

void App_Sandbox::Render(float deltaTime) const
{
	m_pAgent->Render(deltaTime);
}