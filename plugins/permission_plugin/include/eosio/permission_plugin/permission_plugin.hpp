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

namespace permission_apis {
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
}

/**
 *  This is a template plugin, intended to serve as a starting point for making new plugins
 */
class permission_plugin : public appbase::plugin<permission_plugin> {
public:
   permission_plugin();
   virtual ~permission_plugin();
 
   APPBASE_PLUGIN_REQUIRES()
   virtual void set_program_options(options_description&, options_description& cfg) override;
    permission_apis::permission_info get_permission_info_api() const { return permission_apis::permission_info(chain()); }
 
   void plugin_initialize(const variables_map& options);
   void plugin_startup();
   void plugin_shutdown();

    // Only call this after plugin_initialize()!
    controller& chain();
    // Only call this after plugin_initialize()!
    const controller& chain() const;

private:
   std::unique_ptr<class permission_plugin_impl> my;
};

}
FC_REFLECT( eosio::permission_apis::action, (contract_name)(action_name))
FC_REFLECT( eosio::permission_apis::permission, (perm_name)(parent)(required_auth)(link_actions))
FC_REFLECT( eosio::permission_apis::permission_info::get_permission_results,
        (account_name)(permissions))
FC_REFLECT( eosio::permission_apis::permission_info::get_permission_params, (account_name))
