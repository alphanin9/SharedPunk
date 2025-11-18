#include <Shared/Raw/Ink/InkSystem.hpp>
#include <Shared/Raw/Quest/NodeFuncs.hpp>

using namespace Red;
using namespace shared::raw;

Ink::SyntheticInputBuffer::~SyntheticInputBuffer()
{
}

DynArray<Ink::RawInputData>& Ink::SyntheticInputBuffer::GetInputs()
{
    return inputs;
}

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

void Ink::InkSystem::InjectSyntheticInput(RawInputBuffer& aInputBuffer) noexcept
{
    float a2 = 0.f;

    ProcessInputEvents(this, &a2, aInputBuffer);
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