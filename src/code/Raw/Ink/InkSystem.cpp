#include <Raw/Ink/InkSystem.hpp>
#include <Raw/Quest/NodeFuncs.hpp>

using namespace Red;
using namespace shared::raw;

Ink::InkSystem* Ink::InkSystem::Get() noexcept
{
    return InkSystemInstance;
}

Ink::InkLayerManager* Ink::InkSystem::GetLayerManager() noexcept
{
    return m_layerManagers[0].instance;
}

Handle<ink::LoadingLayer> Ink::InkLayerManager::GetLoadingLayer() noexcept
{
    for (auto& layer : layers)
    {
        if (auto& asLoadingLayer = Cast<ink::LoadingLayer>(layer))
        {
            return asLoadingLayer;
        }
    }

    return {};
}

void Ink::InkSystem::SetInitialLoadingScreenTDBID(TweakDBID aId) noexcept
{
    auto loadingLayer = GetLayerManager()->GetLoadingLayer();

    if (!loadingLayer)
    {
        return;
    }

    auto nodeDefinition = MakeHandle<quest::SetSaveDataLoadingScreen_NodeType>();

    nodeDefinition->selectedLoading = aId;

    Quest::SetNextLoadingScreen::Execute(nodeDefinition);
    Ink::LoadingScreen::SetUnknownVarInInitialLoadingScreen(loadingLayer, 2u);
}

Ink::SessionData::Data::Data() noexcept
    : m_unk(ESessionUnkEnum::Unk1)
    , m_sessionName("Session")
{
}

Ink::SessionData::Data::~Data() noexcept
{
    Dtor(this);
}