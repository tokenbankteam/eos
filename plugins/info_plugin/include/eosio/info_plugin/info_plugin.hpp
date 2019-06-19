/**
 *  @file
 *  @copyright defined in eos/LICENSE
 */
#pragma once
#include <appbase/application.hpp>
#include <eosio/chain/authority.hpp>
#include <eosio/chain/account_object.hpp>
#include <eosio/chain/block.hpp>
#include <eosio/chain/controller.hpp>
#include <eosio/chain/contract_table_objects.hpp>

#include <eosio/chain/types.hpp>

#include <boost/container/flat_set.hpp>
#include <boost/multiprecision/cpp_int.hpp>

#include <fc/static_variant.hpp>
namespace eosio {
    using chain::controller;
    using std::unique_ptr;
    using std::pair;
    using namespace appbase;
    using chain::name;
    using chain::uint128_t;
    using chain::public_key_type;
    using fc::optional;
    using boost::container::flat_set;


    using chain::authority;
    using chain::account_name;
    using chain::action_name;

namespace info_apis {
    struct empty{};
    struct action {
        name contract_name;
        name action_name;
    };

    struct permission {
        name              perm_name;
        name              parent;
        authority         required_auth;
        vector<action>    link_actions;
    };

    template<typename>
    struct resolver_factory;

    class permission_info {
        const controller& db;

        public:
        static const string KEYi64;
        permission_info(const controller& db)
                : db(db) {}

        struct get_permission_results {
            name                       account_name;
            vector<permission>         permissions;
        };

        struct get_permission_params {
            name             account_name;
        };
        get_permission_results get_permission( const get_permission_params& params )const;

    };

    struct get_block_info_results {
        fc::time_point          head_block_time;
        uint32_t                last_irreversible_block_num = 0;
        uint64_t                ref_block_prefix = 0;
    };

    class block_info {
        const controller& db;
        const fc::microseconds abi_serializer_max_time;
        public:
        block_info(const controller& db,const fc::microseconds& abi_serializer_max_time)
                : db(db),abi_serializer_max_time(abi_serializer_max_time) {}
        using get_block_info_params = empty;
        uint64_t get_ref_block_prefix(string block_num_or_id) const;
        get_block_info_results get_block_info(const get_block_info_params&) const;

        friend struct resolver_factory<block_info>;
    };
}

/**
 *  This is a template plugin, intended to serve as a starting point for making new plugins
 */
class info_plugin : public appbase::plugin<info_plugin> {
public:
   info_plugin();
   virtual ~info_plugin();
 
   APPBASE_PLUGIN_REQUIRES();
   virtual void set_program_options(options_description&, options_description& cfg) override;
    info_apis::permission_info get_permission_info_api() const { return info_apis::permission_info(chain()); }
    info_apis::block_info get_block_info_api() const { return info_apis::block_info(chain(),get_abi_serializer_max_time()); }
 
   void plugin_initialize(const variables_map& options);
   void plugin_startup();
   void plugin_shutdown();

    // Only call this after plugin_initialize()!
    controller& chain();
    // Only call this after plugin_initialize()!
    const controller& chain() const;

    fc::microseconds get_abi_serializer_max_time() const;

private:
   std::unique_ptr<class info_plugin_impl> my;
};

}
FC_REFLECT( eosio::info_apis::action, (contract_name)(action_name))
FC_REFLECT( eosio::info_apis::permission, (perm_name)(parent)(required_auth)(link_actions))
FC_REFLECT( eosio::info_apis::permission_info::get_permission_results,
        (account_name)(permissions))
FC_REFLECT( eosio::info_apis::permission_info::get_permission_params, (account_name))

FC_REFLECT(eosio::info_apis::empty, )
FC_REFLECT(eosio::info_apis::get_block_info_results,
(head_block_time)(last_irreversible_block_num)(ref_block_prefix))
