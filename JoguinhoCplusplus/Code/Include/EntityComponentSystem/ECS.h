#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <bitset>
#include <array>

class Component;
class GameManager;
class Entity;

using ComponentId = std::size_t;
using Group = std::size_t;

inline ComponentId getNewComponentTypeId() {
    static ComponentId lastId = 0;
    return lastId++;
}

template <typename T>
inline ComponentId getComponentTypeId() noexcept {
    static_assert(std::is_base_of<Component, T>::value, "");
    static ComponentId typeId = getNewComponentTypeId();
    return typeId;
}

enum GROUP_LABELS : size_t {
    kmap_group,
    kplayer_group,
    kenemy_group,
    kcolliders_group
};

constexpr ComponentId maxComponents = 64;
constexpr Group maxGroups = 64;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component *, maxComponents>;

class Component {
  public:
    Entity *entity_ = nullptr;

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    virtual ~Component() = default;
};

class Entity {
  private:
    GameManager *manager_;

    bool isActive_ = true;

    std::vector<std::unique_ptr<Component>> components_;
    ComponentArray componentArr_;
    ComponentBitSet componentBitSet_;
    GroupBitSet groupBitSet_;

  public:
    Entity(GameManager *manager) {
        this->manager_ = manager;
    }

    ~Entity() {
        std::cout << "destrutor de Entidade Chamado\n";
        this->isActive_ = false;
    }

    void update() {
        for (auto &component : this->components_) {
            component->update();
        }
    }

    void draw() {
        for (auto &component : this->components_) {
            component->draw();
        }
    }

    void destroy() {
        this->isActive_ = false;
    }

    template <typename T, typename... TArgs>
    T &addComponent(TArgs &&... mArgs) {
        T *component(new T(std::forward<TArgs>(mArgs)...));
        component->entity_ = this;

        std::unique_ptr<Component> temp(component);
        this->components_.push_back(std::move(temp));

        this->componentArr_[getComponentTypeId<T>()] = component;
        this->componentBitSet_[getComponentTypeId<T>()] = true;

        component->init();

        return *component;
    }

    /* tem que ser declarada no .cpp, pois usa uma função da classe GameManager
       que ainda n foi implementada.
    */
    void addGroup(const Group &group);

    void removeGroup(const Group &group) {
        this->groupBitSet_[group] = false;
    }

    template <typename T>
    const bool hasComponent() const {
        return this->componentBitSet_[getComponentTypeId<T>()];
    }

    const bool hasGroup(const Group &group) const {
        return this->groupBitSet_[group];
    }

    template <typename T>
    T *getComponent() {
        auto ptr(this->componentArr_[getComponentTypeId<T>()]);
        return static_cast<T *>(ptr);
    }

    bool isActive() const {
        return this->isActive_;
    }

    ComponentArray getComponentArray() {
        return this->componentArr_;
    }

    ComponentBitSet getComponentBitSet() {
        return this->componentBitSet_;
    }
};

class GameManager {
  private:
    std::vector<std::unique_ptr<Entity>> entities_;
    std::array<std::vector<Entity *>, maxGroups> groupedEntities_;

  public:
    GameManager() = default;

    ~GameManager() {
        std::cout << "destrutor do GameManager chamado\n";
    }

    void update() {
        for (auto &entity : this->entities_) {
            entity->update();
        }
    }

    void draw() {
        for (auto &entity : this->entities_) {
            entity->draw();
        }
    }

    Entity *addEntity() {
        Entity *entity = new Entity(this);

        std::unique_ptr<Entity> temp(entity);
        this->entities_.push_back(std::move(temp));

        return entity;
    }

    void addToGroup(Entity *entity, Group group) {
        this->groupedEntities_[group].push_back(entity);
    }

    std::vector<Entity *> &getGroup(Group group) {
        return this->groupedEntities_[group];
    }

    void refresh() {
        for (size_t i = 0; i < maxGroups; ++i) {
            auto &v(this->groupedEntities_[i]);

            v.erase(std::remove_if(std::begin(v), std::end(v),
                                   [i](const Entity *entity) {
                                       return !entity->isActive() || !entity->hasGroup(i);
                                   }),
                    std::end(v));
        }

        this->entities_.erase(std::remove_if(std::begin(this->entities_),
                                             std::end(this->entities_),
                                             [](const std::unique_ptr<Entity> &entity) {
                                                 return !entity->isActive();
                                             }),
                              std::end(this->entities_));
    }
};