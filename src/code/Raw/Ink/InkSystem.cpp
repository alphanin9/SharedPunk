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

void Ink::SyntheticInputBuffer::Unk10()
{
}

void Ink::SyntheticInputBuffer::Unk18()
{
}

void Ink::SyntheticInputBuffer::Unk20()
{
}

void Ink::SyntheticInputBuffer::Unk28()
{
}

void Ink::SyntheticInputBuffer::Unk30()
{
}

void Ink::SyntheticInputBuffer::Unk38()
{
}

void Ink::SyntheticInputBuffer::Unk40()
{
}

void Ink::SyntheticInputBuffer::Unk48()
{
}

void Ink::SyntheticInputBuffer::Unk50()
{
}

void Ink::SyntheticInputBuffer::Unk58()
{
}

void Ink::SyntheticInputBuffer::Unk60()
{
}

void Ink::SyntheticInputBuffer::Unk68()
{
}

void Ink::SyntheticInputBuffer::Unk70()
{
}

void Ink::SyntheticInputBuffer::Unk78()
{
}

void Ink::SyntheticInputBuffer::Unk80()
{
}

void Ink::SyntheticInputBuffer::Unk88()
{
}

int Ink::SyntheticInputBuffer::Unk90()
{
    return 0;
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

#ifdef __APPLE__
    // The loading-screen node's Execute and the loading layer setter have no macOS entry yet. Without them the game
    // shows its default loading screen; the session itself is unaffected.
    if (!Quest::SetNextLoadingScreen::Execute.IsAvailable() ||
        !Ink::LoadingScreen::SetUnknownVarInInitialLoadingScreen.IsAvailable())
    {
        return;
    }
#endif
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
#ifdef __APPLE__
    // The game's SessionData destructor is inlined on macOS. Its callers release the argument array with 0x3f0e794
    // (as the game does right after StartSession) and the CString member destructor handles the name.
    using ReleaseArgumentsFn = void (*)(void*);
    reinterpret_cast<ReleaseArgumentsFn>(ngplus_mac_image_base() + 0x3f0e794)(&m_arguments);
#else
    Dtor(this);
#endif
}