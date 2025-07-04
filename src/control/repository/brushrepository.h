#ifndef BRUSHREPOSITORY_H
#define BRUSHREPOSITORY_H
#include <memory>
#include <qobject.h>

#include "blendrepository.h"
#include "repository.h"
#include "../tools/brushes/brush.h"

namespace PIPKA::CONTROL::TOOLS
{

using BrushStorage = std::vector<std::shared_ptr<BRUSH::Brush>>;

class BrushRepository : public Repository<BrushRepository, BrushStorage>
{
    Q_OBJECT

public:
    BrushRepository();
    ~BrushRepository() override;

    template <class Brush>
    void addBrush(IMAGE::COLOR::Blend *blendMode = BlendRepository::instance()->getBlend<IMAGE::COLOR::NormalBlend>())
    {
        const auto newBrush = std::make_shared<Brush>(
            blendMode,
            0xFFFF0000);
        m_storage.push_back(newBrush);
        selectBrush(m_storage.size() - 1);
        emit brushAdded(m_storage.size() - 1);
    }

    std::shared_ptr<BRUSH::Brush> activeBrush() {return m_activeBrush;}
    void selectBrush(int index);;

signals:
    void brushSelected();
    void brushAdded(int index);

private:
    std::shared_ptr<BRUSH::Brush> m_activeBrush;
};

}

#endif //BRUSHREPOSITORY_H
