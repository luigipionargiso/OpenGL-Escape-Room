#include "World.h"
#include "engine/physics/Physics.h"

#include <iostream>

void World::Populate(Shader& shader)
{
    objects_["floor"] = new GameObject(Model("res/models/floor/floor.fbx"), nullptr, nullptr);
    objects_["floor"]->CorrectOrientation();

    objects_["armadio"] = new GameObject(Model("res/models/armadio/armadio.fbx"), nullptr, nullptr);
    objects_["armadio"]->CorrectOrientation();
    objects_["armadio"]->SetPosition(glm::vec3(-1.91336, 1.36503, 0.88));
    auto ptr = objects_["armadio"];

    //std::cout << ptr->GetBBHalfExtents().x << " " << ptr->GetBBHalfExtents().y << " " << ptr->GetBBHalfExtents().z << '\n';

    Physics::AddRigidBody(ptr, ptr->GetPosition(), ptr->GetRotationEulerXYZ(), 0, BOX, ptr->GetBBHalfExtents());

    objects_["cassettiera"] = new GameObject(Model("res/models/cassettiera/cassettiera.fbx"), nullptr, nullptr);
    objects_["cassettiera"]->CorrectOrientation();
    objects_["cassettiera"]->SetPosition(glm::vec3(0.690669, -1.71948, 0.405));
    ptr = objects_["cassettiera"];
    Physics::AddRigidBody(ptr, ptr->GetPosition(), ptr->GetRotationEulerXYZ(), 0, BOX, ptr->GetBBHalfExtents());



    objects_["comodino"] = new GameObject(Model("res/models/comodino/comodino.fbx"), nullptr, nullptr);
    objects_["comodino"]->CorrectOrientation();
    objects_["comodino"]->SetPosition(glm::vec3(-0.639844, -1.78922, 0.498333));
    ptr = objects_["comodino"];
    Physics::AddRigidBody(ptr, ptr->GetPosition(), ptr->GetRotationEulerXYZ(), 0, BOX, ptr->GetBBHalfExtents());


    objects_["telaio_letto"] = new GameObject(Model("res/models/letto/telaio.fbx"), nullptr, nullptr);
    objects_["telaio_letto"]->CorrectOrientation();
    objects_["telaio_letto"]->SetPosition(glm::vec3(-1.53501, -0.948316, 0.357138));

    for (auto& obj : objects_)
        obj.second->SetShader(&shader);
}

void World::Draw(Shader& shader)
{
    for (auto& obj : objects_)
        obj.second->Draw();
}
