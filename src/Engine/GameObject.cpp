#include "GameObject.h"

#include "Engine.h"

namespace Biendeo::GameOff2016::Engine {

	GameObject::GameObject(Engine* engine) {
		this->engine = engine;
		active = true;
		initialized = false;

		AddComponent(new Components::Transform(this));

		transform = GetComponent<Components::Transform>();
	}

	GameObject::~GameObject() {

	}

	bool GameObject::AddComponent(Component* c) {
		components.push_back(std::shared_ptr<Component>(c));
		return true;
	}

	void GameObject::Destroy() {
		// TODO: Figure out what needs to be done first.
		typedef std::map<uint64_t, std::weak_ptr<GameObject>>::iterator iterator;

		for (iterator it = children.begin(); it != children.end(); it++) {
			//auto s = it->second;
			std::shared_ptr<GameObject> p = std::shared_ptr<GameObject>(it->second);
			p->Destroy();
			//Sleep(1);
		}
		engine->RemoveGameObject(*this);
	}

	Components::Transform& GameObject::Transform() {
		return *std::shared_ptr<Components::Transform>(transform);
	}

	Components::Transform GameObject::GlobalTransform() {
		// TODO
		return Components::Transform(this);
	}

	std::string GameObject::Name() {
		return name;
	}

	std::string GameObject::Name(std::string newName) {
		this->name = newName;
		return name;
	}

	uint64_t GameObject::ID() {
		return id;
	}

	uint64_t GameObject::ID(uint64_t newId) {
		this->id = newId;
		return id;
	}

	std::shared_ptr<GameObject> GameObject::Parent() {
		return std::shared_ptr<GameObject>(parent);
	}

	std::shared_ptr<GameObject> GameObject::Parent(std::shared_ptr<GameObject> newParent) {
		// TODO: Additional things for unsetting the previous parent such as repositioning, etc.
		if (newParent->GetChildDepth() >= MAXIMUM_CHILD_DEPTH) {
			std::string message = newParent->Name() + " is at the maximum child depth of " + std::to_string(MAXIMUM_CHILD_DEPTH) + ", cannot set parent.";
			throw std::exception(message.data());
		}

		if (!parent.expired()) {
			std::shared_ptr<GameObject> oldParentPtr = std::shared_ptr<GameObject>(parent);
			if (oldParentPtr != nullptr && oldParentPtr->children.find(ID()) != oldParentPtr->children.end()) {
				oldParentPtr->children.erase(ID());
			}
		}

		this->parent = newParent;

		if (newParent != nullptr) {
			newParent->children.insert(std::pair<uint64_t, std::weak_ptr<GameObject>>(ID(), std::weak_ptr<GameObject>(GetPointer())));
		}

		return newParent;
	}

	std::map<uint64_t, std::shared_ptr<GameObject>> GameObject::Children() {
		typedef std::map<uint64_t, std::weak_ptr<GameObject>>::iterator iterator;
		std::map<uint64_t, std::shared_ptr<GameObject>> childrenMap;
		for (iterator it = children.begin(); it != children.end(); it++) {
			auto childPtr = std::shared_ptr<GameObject>(it->second);
			childrenMap.insert(std::make_pair(childPtr->ID(), childPtr));
		}
		return childrenMap;
	}

	std::shared_ptr<GameObject> GameObject::GetPointer() {
		return engine->GetGameObjectPointer(*this);
	}

	uint16_t GameObject::GetChildDepth() {
		if (parent.expired()) {
			return 0;
		}

		auto ptr = std::shared_ptr<GameObject>(parent);
		if (ptr != nullptr) {
			return ptr->GetChildDepth() + 1;
		} else {
			return 0;
		}
	}

	void GameObject::Draw() {
		glPushMatrix();

		glTranslatef(Transform().Translate().x, Transform().Translate().y, Transform().Translate().z);
		glRotatef(Transform().Rotate().z, 0.0f, 0.0f, 1.0f);
		glRotatef(Transform().Rotate().y, 0.0f, 1.0f, 0.0f);
		glRotatef(Transform().Rotate().x, 1.0f, 0.0f, 0.0f);
		glScalef(Transform().Scale().x, Transform().Scale().y, Transform().Scale().z);

		DrawSelf();
		for (auto& child : children) {
			std::shared_ptr<GameObject>(child.second)->Draw();
		}

		glPopMatrix();
	}

	void GameObject::DrawSelf() {

	}

	bool GameObject::Active() {
		return active;
	}

	bool GameObject::Active(bool activeState) {
		this->active = activeState;
		return active;
	}

	bool GameObject::ToggleActive() {
		this->active = !active;
		return active;
	}

	void GameObject::Awake() {
		for (auto& c : components) {
			std::shared_ptr<Component>(c)->Awake();
		}

		for (auto& child : children) {
			std::shared_ptr<GameObject>(child.second)->Awake();
		}
		this->initialized = true;
	}

	void GameObject::LateUpdate(float deltaTime) {
		for (auto& c : components) {
			std::shared_ptr<Component>(c)->LateUpdate(deltaTime);
		}

		for (auto& child : children) {
			std::shared_ptr<GameObject>(child.second)->LateUpdate(deltaTime);
		}
	}

	void GameObject::OnActive() {
		for (auto& c : components) {
			std::shared_ptr<Component>(c)->OnActive();
		}

		for (auto& child : children) {
			std::shared_ptr<GameObject>(child.second)->OnActive();
		}
	}

	void GameObject::OnDestroy() {
		for (auto& c : components) {
			std::shared_ptr<Component>(c)->OnDestroy();
		}

		for (auto& child : children) {
			std::shared_ptr<GameObject>(child.second)->OnDestroy();
		}
	}

	void GameObject::OnDisable() {
		for (auto& c : components) {
			std::shared_ptr<Component>(c)->OnDisable();
		}

		for (auto& child : children) {
			std::shared_ptr<GameObject>(child.second)->OnDisable();
		}
	}

	void GameObject::Start() {
		for (auto& c : components) {
			std::shared_ptr<Component>(c)->Start();
		}

		for (auto& child : children) {
			std::shared_ptr<GameObject>(child.second)->Start();
		}
	}

	void GameObject::Update(float deltaTime) {
		for (auto& c : components) {
			std::shared_ptr<Component>(c)->Update(deltaTime);
		}

		for (auto& child : children) {
			std::shared_ptr<GameObject>(child.second)->Update(deltaTime);
		}
	}
}