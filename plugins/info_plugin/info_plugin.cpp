/**
 *  @file
 *  @copyright defined in eos/LICENSE
 */
#include <eosio/info_plugin/info_plugin.hpp>
#include <eosio/http_plugin/http_plugin.hpp>
#include <eosio/chain_plugin/chain_plugin.hpp>
#include <eosio/chain/permission_object.hpp>
#include <eosio/chain/permission_link_object.hpp>
#include <fc/io/json.hpp>
namespace eosio {
   using namespace info_apis;
   using namespace  chain;
   static appbase::abstract_plugin& _info_plugin = app().register_plugin<info_plugin>();

class info_plugin_impl {
   public:
    chain_plugin *chain_plug;
    fc::microseconds                 abi_serializer_max_time_ms;
};

info_plugin::info_plugin():my(new info_plugin_impl()){}
info_plugin::~info_plugin(){}

void info_plugin::set_program_options(options_description&, options_description& cfg) {
   //cfg.add_options()
     //  ("abi-serializer-max-time-ms", bpo::value<uint32_t>()->default_value(config::default_abi_serializer_max_time_ms),
      //  "Override default maximum ABI serialization time allowed in ms")
      //   ;
}

controller& info_plugin::chain() { return my->chain_plug->chain();}
const controller& info_plugin::chain() const { return my->chain_plug->chain();}

namespace info_apis {
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

template<typename Api>
struct resolver_factory {
    static auto make(const Api* api, const fc::microseconds& max_serialization_time) {
        return [api, max_serialization_time](const account_name &name) -> optional<abi_serializer> {
            const auto* accnt = api->db.db().template find<account_object, by_name>(name);
            if (accnt != nullptr) {
                abi_def abi;
                if (abi_serializer::to_abi(accnt->abi, abi)) {
                    return abi_serializer(abi, max_serialization_time);
                }
            }

            return optional<abi_serializer>();
        };
    }
};

template<typename Api>
auto make_resolver(const Api* api, const fc::microseconds& max_serialization_time) {
    return resolver_factory<Api>::make(api, max_serialization_time);
}

template<typename I>
std::string itoh(I n, size_t hlen = sizeof(I)<<1) {
    static const char* digits = "0123456789abcdef";
    std::string r(hlen, '0');
    for(size_t i = 0, j = (hlen - 1) * 4 ; i < hlen; ++i, j -= 4)
        r[i] = digits[(n>>j) & 0x0f];
    return r;
}

fc::variant block_info::get_block(string block_num_or_id) const {
    signed_block_ptr block;
    optional<uint64_t> block_num;

    EOS_ASSERT( !block_num_or_id.empty() && block_num_or_id.size() <= 64,
                chain::block_id_type_exception,
                "Invalid Block number or ID, must be greater than 0 and less than 64 characters"
    );

    try {
        block_num = fc::to_uint64(block_num_or_id);
    } catch( ... ) {}

    if( block_num.valid() ) {
        block = db.fetch_block_by_number( *block_num );
    } else {
        try {
            block = db.fetch_block_by_id( fc::variant(block_num_or_id).as<block_id_type>() );
        } EOS_RETHROW_EXCEPTIONS(chain::block_id_type_exception, "Invalid block ID: ${block_num_or_id}", ("block_num_or_id", block_num_or_id))
    }

    EOS_ASSERT( block, unknown_block_exception, "Could not find block: ${block}", ("block", block_num_or_id));

    fc::variant pretty_output;
    abi_serializer::to_variant(*block, pretty_output, make_resolver(this, abi_serializer_max_time), abi_serializer_max_time);

    uint32_t ref_block_prefix = block->id()._hash[1];

    return fc::mutable_variant_object(pretty_output.get_object())
            ("id", block->id())
            ("block_num",block->block_num())
            ("ref_block_prefix", ref_block_prefix);
}

info_apis::get_block_info_results block_info::get_block_info(const block_info::get_block_info_params&) const {
    const auto& rm = db.get_resource_limits_manager();
    return {
            itoh(static_cast<uint32_t>(app().version())),
            db.get_chain_id(),
            db.head_block_num(),
            db.last_irreversible_block_num(),
            db.last_irreversible_block_id(),
            db.head_block_id(),
            db.head_block_time(),
            db.head_block_producer(),
            rm.get_virtual_block_cpu_limit(),
            rm.get_virtual_block_net_limit(),
            rm.get_block_cpu_limit(),
            rm.get_block_net_limit(),
            //std::bitset<64>(db.get_dynamic_global_properties().recent_slots_filled).to_string(),
            //__builtin_popcountll(db.get_dynamic_global_properties().recent_slots_filled) / 64.0,
            app().version_string(),
            db.fork_db_pending_head_block_num(),
            db.fork_db_pending_head_block_id(),
            get_block(fc::to_string(db.last_irreversible_block_num())),
    };
}
}

fc::microseconds info_plugin::get_abi_serializer_max_time() const {
    return my->abi_serializer_max_time_ms;
}

void info_plugin::plugin_initialize(const variables_map& options) {
   try {
       //if(options.count("abi-serializer-max-time-ms")){
           //my->abi_serializer_max_time_ms = fc::microseconds(options.at("abi-serializer-max-time-ms").as<uint32_t>() * 1000);
       //}
       my->abi_serializer_max_time_ms = fc::microseconds(2000*1000);

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

#define PERMISSION_CALL(call_name,http_response_code) CALL(info, permission_api, permission_info, call_name, http_response_code)
#define BLOCK_CALL(call_name,http_response_code) CALL(info, block_api, block_info, call_name, http_response_code)

void info_plugin::plugin_startup() {
   // Make the magic happen
    auto permission_api = get_permission_info_api();
    auto block_api = get_block_info_api();

    ilog( "starting info_plugin" );
    app().get_plugin<http_plugin>().add_api({
         PERMISSION_CALL(get_permission, 200),
         BLOCK_CALL(get_block_info,200)
    });
}

void info_plugin::plugin_shutdown() {
   // OK, that's enough magic
}

}
