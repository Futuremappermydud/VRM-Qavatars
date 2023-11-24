#include "TPoseHelper.hpp"

#include "UnityEngine/HumanPoseHandler.hpp"

#include "json.hpp"

namespace VRMQavatars
{
    std::vector<TransData> TPoseHelper::originalPositions;

    void TPoseHelper::SavePose(UnityEngine::Transform* root)
    {
        originalPositions.clear();
        originalPositions.push_back({root, root->get_position(), root->get_localEulerAngles(), root->get_localScale()});

        auto allTrans = root->GetComponentsInChildren<UnityEngine::Transform*>(true);
        for(const auto trans : allTrans)
        {
            originalPositions.push_back({trans, trans->get_position(), trans->get_localEulerAngles(), trans->get_localScale()});
        }
    }

    void TPoseHelper::LoadPose()
    {
        for(const auto transData : originalPositions)
        {
            if(auto trans = transData.trans)
            {
                trans.ptr()->set_position(transData.position);
                trans.ptr()->set_localEulerAngles(transData.eulerRotation);
                trans.ptr()->set_localScale(transData.localScale);
            }
        }
    }
}
