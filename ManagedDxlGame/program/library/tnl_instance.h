#pragma once

#include <unordered_map>
#include <functional>
#include <any>
#include <string>
#include "tnl_using.h"
#include "tnl_shared_factory.h"

namespace tnl {

    /*
    
    ・ゲーム個別で特定箇所の処理をどのように実装したか
     ( 実装過程で苦労したポイントをどのように工夫したか )
    ・メモリ管理はどうしているか
    ・ゲーム全体の設計で工夫したポイントはどういった所か
    ・制作したゲームの面白いと思う( 売りになる )ポイントはどこか
    ・完成度はどのくらいか ( 考えられる残作業と優先度はどう考えているか )

    
    */


    TNL_SHARED_FACTORY_CLASS(Instance, tnl::SharedFactory<Instance>)
    public:
        template<class T>
        static Shared<T> Generate() { return Instance::Create<T>() ; }
        template<class T>
        static Shared<Instance> GenerateAccompDesc(const std::any& desc) { return Instance::Create<T>(desc); }

        static Shared<Instance> Generate(const std::string& class_name) {
            auto it = generator_register_->find(class_name);
            if (it == generator_register_->end()) return nullptr;
            return it->second();
        }
        static Shared<Instance> GenerateAccompDesc(const std::string& class_name, const std::any& desc) {
            auto it = generator_desc_register_->find(class_name);
            if (it == generator_desc_register_->end()) return nullptr;
            return it->second(desc);
        }
        const int static Regist(const std::string& name, const std::function<Shared<Instance>()>& generator) {
            static std::unordered_map<std::string, std::function<Shared<Instance>()>> generator_register ;
            generator_register_ = &generator_register;
            generator_register_->try_emplace(name, generator);
            return 0;
        }
        const int static RegistAccompDesc(const std::string& name, const std::function<Shared<Instance>(const std::any& desc)>& generator) {
            static std::unordered_map<std::string, std::function<Shared<Instance>(const std::any&)>> generator_desc_register;
            generator_desc_register_ = &generator_desc_register;
            generator_desc_register_->try_emplace(name, generator);
            return 0;
        }

    private:
        static std::unordered_map<std::string, std::function<Shared<Instance>()>>* generator_register_;
        static std::unordered_map<std::string, std::function<Shared<Instance>(const std::any&)>>* generator_desc_register_;
    };

#define TNL_INSTANCE_GENERATE_REGISTER( type )                                                                                          \
const int gme_temp_regist_##type = tnl::Instance::Regist(typeid(type).name(), tnl::Instance::Generate<type>);                           \

#define TNL_INSTANCE_ACCOMP_DESC_GENERATE_REGISTER( type )                                                                              \
const int gme_temp_regist_desc_##type = tnl::Instance::RegistAccompDesc(typeid(type).name(), tnl::Instance::GenerateAccompDesc<type>);  \
    
}
