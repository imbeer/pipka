#ifndef BRUSHREPOSITORY_H
#define BRUSHREPOSITORY_H
#include <memory>
#include <qvariant.h>
#include <vector>

#include "repository.h"
#include "../tools/brushes/brush.h"

namespace PIPKA::CONTROL::TOOLS
{

class BrushRepository : public Repository<BrushRepository>
{
    Q_OBJECT

public:
    BrushRepository();
    ~BrushRepository() override;

    void addBrush();
    void setColor(Color color) const;
    void selectBrush(int index);
    std::shared_ptr<BRUSH::Brush> activeBrush() {return m_activeBrush;};
    std::vector<std::shared_ptr<BRUSH::Brush>> brushes() {return m_brushes;};

signals:
    void brushSelected();

private:
    friend class Repository<BrushRepository>;
    std::shared_ptr<BRUSH::Brush> m_activeBrush;
    std::vector<std::shared_ptr<BRUSH::Brush>> m_brushes;
};

}

#endif //BRUSHREPOSITORY_H
