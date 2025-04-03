#ifndef BRUSHREPOSITORY_H
#define BRUSHREPOSITORY_H
#include <memory>
#include <qobject.h>

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

    void addBrush();
    void selectBrush(int index);
    std::shared_ptr<BRUSH::Brush> activeBrush() {return m_activeBrush;};

signals:
    void brushSelected();

private:
    std::shared_ptr<BRUSH::Brush> m_activeBrush;
};

}

#endif //BRUSHREPOSITORY_H
