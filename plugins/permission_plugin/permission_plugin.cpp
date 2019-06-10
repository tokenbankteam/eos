/**
 *  @file
 *  @copyright defined in eos/LICENSE
 */
#include <eosio/permission_plugin/permission_plugin.hpp>
#include <eosio/http_plugin/http_plugin.hpp>
#include <eosio/chain_plugin/chain_plugin.hpp>
#include <eosio/chain/permission_object.hpp>
#include <eosio/chain/permission_link_object.hpp>
#include <fc/io/json.hpp>
namespace eosio {
   using namespace permission_apis;
   using namespace  chain;
   static appbase::abstract_plugin& _permission_plugin = app().register_plugin<permission_plugin>();

class permission_plugin_impl {
   public:
    chain_plugin *chain_plug;
};

permission_plugin::permission_plugin():my(new permission_plugin_impl()){}
permission_plugin::~permission_plugin(){}

void permission_plugin::set_program_options(options_description&, options_description& cfg) {
   cfg.add_options()
         ("option-name", bpo::value<string>()->default_value("default value"),
          "Option Description")
         ;
}

controller& permission_plugin::chain() { return my->chain_plug->chain();}
const controller& permission_plugin::chain() const { return my->chain_plug->chain();}

//namespace permission_apis {
permission_info::get_permission_results permission_info::get_permission( const get_permission_params& params )const {
       get_permission_results result;
       result.account_name = params.account_name;

       const auto& d = db.db();
       const auto& permissions = d.get_index<permission_index,by_owner>();
       auto perm = permissions.lower_bound( boost::make_tuple( params.account_name ) );

       while( perm != permissions.end() && perm->owner == params.account_name ) {
          /// TODO: lookup perm->parent name
          name parent;

          // Don't lookup parent if null
          if( perm->parent._id ) {
             const auto* p = d.find<permission_object,by_id>( perm->parent );
             if( p ) {
                EOS_ASSERT(perm->owner == p->owner, invalid_parent_permission, "Invalid parent permission");
                parent = p->name;
             }
          }
          vector<action> actions;
         const auto& permission_links = d.get_index<permission_link_index, by_permission_name>();
         auto link = permission_links.lower_bound(boost::make_tuple(perm->owner));
         action act;
         if (link == permission_links.end()) {
            elog("link is empty");
         }

         while(link != permission_links.end()) {
            if(link->account != perm->owner){
               break;
            }
            if (link->required_permission != perm->name) {
               ++link;
               continue;
            }

            elog("contract name: ${e}",("e",link->code));
            elog("action name: ${e}",("e",link->message_type));
            act.contract_name = link->code;
            act.action_name = link->message_type;
            actions.push_back(act);
            ++link;
         }

          elog("actions: ${e}",("e",actions));
          result.permissions.push_back( permission{ perm->name, parent, perm->auth.to_authority(), actions} );
          elog("result.permissions: ${e}",("e",result.permissions));
          ++perm;
       }
       return result;
}
//}
void permission_plugin::plugin_initialize(const variables_map& options) {
   try {
      if( options.count( "option-name" )) {
         // Handle the option
      }
   }catch(...){

   }
    my->chain_plug = app().find_plugin<chain_plugin>();
    EOS_ASSERT(my->chain_plug, chain::missing_chain_plugin_exception, "");

   //FC_LOG_AND_RETHROW();
}

#define CALL(api_name, api_handle, api_namespace, call_name, http_response_code) \
{std::string("/v1/" #api_name "/" #call_name), \
   [api_handle](string, string body, url_response_callback cb) mutable { \
          try { \
             if (body.empty()) body = "{}"; \
             fc::variant result( api_handle.call_name(fc::json::from_string(body).as<api_namespace::call_name ## _params>()) ); \
             cb(http_response_code, std::move(result)); \
          } catch (...) { \
             http_plugin::handle_exception(#api_name, #call_name, body, cb); \
          } \
       }}

#define PERMISSION_CALL(call_name,http_response_code) CALL(permission, ro_api, permission_info, call_name, http_response_code)

void permission_plugin::plugin_startup() {
   // Make the magic happen
    auto ro_api = get_permission_info_api();

    ilog( "starting permission_plugin" );
    app().get_plugin<http_plugin>().add_api({
         PERMISSION_CALL(get_permission, 200)
    });
}

void permission_plugin::plugin_shutdown() {
   // OK, that's enough magic
}

}
