#include "AvatarManager.hpp"

#include <functional>
#include <HandController.hpp>

#include "customTypes/BlendShape/BlendShapeController.hpp"

namespace VRMQavatars {
    AssetLib::Structure::VRM::VRMModelContext* AvatarManager::currentContext;
    RootMotion::FinalIK::VRIK* AvatarManager::_vrik;
    TargetManager* AvatarManager::_targetManager;
    WristTwistFix* AvatarManager::_wristTwistFix;
    CP_SDK::Utils::Event<> AvatarManager::OnLoad;

    void AvatarManager::SetContext(AssetLib::Structure::VRM::VRMModelContext* context)
    {
        getLogger().info("x1");
        if(currentContext != nullptr)
        {
            UnityEngine::GameObject::Destroy(currentContext->rootGameObject);
            delete currentContext;
        }
        getLogger().info("x2");
        currentContext = context;
        const auto root = currentContext->rootGameObject;
        getLogger().info("x3");
        _vrik = root->GetComponent<RootMotion::FinalIK::VRIK*>();
        getLogger().info("x4");
        _targetManager = root->GetComponent<TargetManager*>();
        _wristTwistFix = root->GetComponent<WristTwistFix*>();
        getLogger().info("x5");
        auto blendShapeMaster = root->GetComponent<BlendShape::BlendShapeController*>();
        getLogger().info("x6");
        blendShapeMaster->Init();
        getLogger().info("x7");
        blendShapeMaster->SetBlendshape(AssetLib::Structure::VRM::Blink_L, 100.0f);
        getLogger().info("x8");

        OnLoad();
    }

    void AvatarManager::SetLegSwivel(const float value)
    {
        if(_vrik == nullptr) return;
        _vrik->solver->leftLeg->swivelOffset = value;
        _vrik->solver->rightLeg->swivelOffset = value;
    }

    void AvatarManager::SetArmSwivel(const float value)
    {
        if(_vrik == nullptr) return;
        _vrik->solver->leftArm->swivelOffset = value;
        _vrik->solver->rightArm->swivelOffset = value;
    }

    void AvatarManager::SetHandOffset(const Structs::OffsetPose& pose)
    {
        if(_targetManager == nullptr) return;
        _targetManager->offset = pose;
    }

    void AvatarManager::SetBodyStiffness(float value)
    {
        if(_vrik == nullptr) return;
        _vrik->solver->spine->bodyPosStiffness = value;
    }

    void AvatarManager::SetShoulderRotation(float value)
    {
        if(_vrik == nullptr) return;
        _vrik->solver->leftArm->shoulderRotationWeight = value;
        _vrik->solver->rightArm->shoulderRotationWeight = value;
    }

    void AvatarManager::SetShoulderFixWeight(float value)
    {
        if(_wristTwistFix == nullptr) return;
        _wristTwistFix->shoulderWeight = value;
    }

    void AvatarManager::SetWristFixWeight(float value)
    {
        if(_wristTwistFix == nullptr) return;
        _wristTwistFix->wristWeight = value;
    }

    void AvatarManager::SetFootDist(float value)
    {
        if(_vrik == nullptr) return;
        _vrik->solver->locomotion->footDistance = value;
    }

    void AvatarManager::SetStepThreshold(float value)
    {
        if(_vrik == nullptr) return;
        _vrik->solver->locomotion->stepThreshold = value;
    }

    void AvatarManager::SetStepHeight(float value)
    {
    }

    void AvatarManager::SetStepOffsetZ(float value)
    {
        if(_vrik == nullptr) return;
        _vrik->solver->locomotion->offset = {0.0f, 0.0f, value};
    }

    void AvatarManager::SetFingerPose(std::string value)
    {
        if(_vrik == nullptr) return;
        HandController::ApplyHandPose(_vrik->animator, value);
    }
}
