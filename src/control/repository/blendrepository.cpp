#include "blendrepository.h"

namespace PIPKA::CONTROL::TOOLS
{

template<>
std::unique_ptr<BlendRepository> Repository<BlendRepository, BlendStorage>::m_instance = nullptr;

BlendRepository::BlendRepository()
{
    using namespace PIPKA::IMAGE::COLOR;

    add(std::make_unique<NormalBlend>());
    add(std::make_unique<ReplaceBlend>());
    add(std::make_unique<MultiplyBlend>());
    add(std::make_unique<OverlayBlend>());
    add(std::make_unique<ScreenBlend>());
}

BlendRepository::~BlendRepository()
{
}

}
