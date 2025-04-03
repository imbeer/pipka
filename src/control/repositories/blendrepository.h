#ifndef BLENDREPOSITORY_H
#define BLENDREPOSITORY_H
#include <qobject.h>
#include <typeindex>

#include "repository.h"
#include "../../image/color/blend.h"

namespace PIPKA::CONTROL::TOOLS
{

/// cool af magic (key ~= type)
using BlendStorage = std::map<std::type_index, std::unique_ptr<IMAGE::COLOR::Blend>>;

class BlendRepository : public Repository<BlendRepository, BlendStorage>
{
    Q_OBJECT

public:
    BlendRepository();
    ~BlendRepository() override;

    template<class BlendType>
    IMAGE::COLOR::Blend *getBlend() const
    {
        return m_storage.at(std::type_index(typeid(BlendType))).get();
    }

private:
    template<class BlendType>
    void add(std::unique_ptr<BlendType> obj)
    {
        m_storage[std::type_index(typeid(BlendType))] = std::move(obj);
    }

};


}

#endif //BLENDREPOSITORY_H
