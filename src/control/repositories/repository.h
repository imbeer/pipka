#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <memory>

namespace PIPKA::CONTROL::TOOLS
{
template<class DerivedRepository>
class Repository : protected QObject
{
    // Q_OBJECT
private:
    Repository(const Repository&) = delete;
    Repository& operator=(const Repository&) = delete;
    Repository(Repository&&) = delete;
    Repository& operator=(Repository&&) = delete;

public:
    static DerivedRepository* instance() {
        if (!m_instance) {
            m_instance.reset(new DerivedRepository());
        }
        return m_instance.get();
    }

    static void cleanup() {
        m_instance.reset();
    }

protected:
    explicit Repository(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~Repository() = default;

private:
    static std::unique_ptr<DerivedRepository> m_instance;
};

}

#endif //REPOSITORY_H
