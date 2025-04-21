#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <memory>
#include <QObject>

namespace PIPKA::CONTROL::TOOLS
{
template<class DerivedRepository, class Storage>
class Repository : public QObject
{
    // Q_OBJECT
private:
    Repository(const Repository&) = delete;
    Repository& operator=(const Repository&) = delete;
    Repository(Repository&&) = delete;
    Repository& operator=(Repository&&) = delete;

protected:
    explicit Repository(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~Repository() = default;

public:
    static DerivedRepository *instance() {
        if (!m_instance) {
            m_instance.reset(new DerivedRepository());
        }
        return m_instance.get();
    }

    static void cleanup() {
        m_instance.reset();
    }

    Storage storage() { return m_storage; }

protected:
    static std::unique_ptr<DerivedRepository> m_instance;
    Storage m_storage;
};

}

#endif //REPOSITORY_H
