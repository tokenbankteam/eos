# info_plugin

info_plugin is designed to get information of blockchain ,such as account permission(including link action),block information,etc

# how to add the permission plugin

1.download the info plugin code

```
cd eos/plugin;
git clone git@github.com:tokenbankteam/info_plugin.git

```
 
2.modify eos/plugins/CMakeLists.txt

```
add_subdirectory(info_plugin)

```

3.modify eos/programs/nodeos/CMakeLists.txt

```
target_link_libraries( ${NODE_EXECUTABLE_NAME} PRIVATE -Wl,${whole_archive_flag} info_plugin -Wl,${no_whole_archive_flag} )
```

# how to test the info plugin

## get permission

/v1/info/get_permission

```
curl -X POST --url http://127.0.0.1:8888/v1/info/get_permission -d '{"account_name":"huoyantest11"}'
```

Response

```
{
	"account_name": "huoyantest11",
	"permissions": [{
		"perm_name": "active",
		"parent": "owner",
		"required_auth": {
			"threshold": 1,
			"keys": [{
				"key": "EOS8Nx6YqWuKfadEV4nNh2hZRmBzR3kar1UqRz6KbrUCmVVcRwwKS",
				"weight": 1
			}],
			"accounts": [],
			"waits": []
		},
		"link_actions": []
	}, {
		"perm_name": "buyram",
		"parent": "active",
		"required_auth": {
			"threshold": 1,
			"keys": [{
				"key": "EOS5nhwQpHdwczn3fmBp28zxiVzLqTpsfhB2JRtRBxY6dzHjW1x44",
				"weight": 1
			}],
			"accounts": [],
			"waits": []
		},
		"link_actions": [{
			"contract_name": "eosio",
			"action_name": "buyram"
		}, {
			"contract_name": "eosio",
			"action_name": "buyrambytes"
		}]
	}, {
		"perm_name": "owner",
		"parent": "",
		"required_auth": {
			"threshold": 1,
			"keys": [{
				"key": "EOS8Nx6YqWuKfadEV4nNh2hZRmBzR3kar1UqRz6KbrUCmVVcRwwKS",
				"weight": 1
			}],
			"accounts": [],
			"waits": []
		},
		"link_actions": []
	}]
}

```

## get block information

/v1/info/get_block_info

```
curl -X POST --url http://127.0.0.1:8888/v1/info/get_block_info

```

Response

```
{
	"server_version": "d4da0bbc",
	"chain_id": "e70aaab8997e1dfce58fbfac80cbbb8fecec7b99cf982a9444273cbc64c41473",
	"head_block_num": 34501025,
	"last_irreversible_block_num": 34500702,
	"last_irreversible_block_id": "020e705e93c96cf46049aa477cc7d682871944871733a58420af935efa709f49",
	"head_block_id": "020e71a17d125e4bbfc17da1727959bac8971b5e35cc70f1f4a0d36bdb70aee2",
	"head_block_time": "2019-06-18T01:51:24.000",
	"head_block_producer": "blocksmithio",
	"virtual_block_cpu_limit": 200000000,
	"virtual_block_net_limit": 524288000,
	"block_cpu_limit": 200000,
	"block_net_limit": 524288,
	"server_version_string": "v1.8.0-rc2-dirty",
	"fork_db_head_block_num": 34501025,
	"fork_db_head_block_id": "020e71a17d125e4bbfc17da1727959bac8971b5e35cc70f1f4a0d36bdb70aee2",
	"last_irreversible_block": {
		"timestamp": "2019-06-18T01:48:41.500",
		"producer": "mosquitometa",
		"confirmed": 0,
		"previous": "020e705d9a3850550a569794b45941a3a7b53c272ce18e3e26841caa3ebb570b",
		"transaction_mroot": "f38d5b8bee3eed7cc34cdcdc80ad46343937b66907dfd71a1e02e216a4293771",
		"action_mroot": "369bb8d6c57459015728501bea24319dbe538df6a83bb7b8f9d8c0a668520c82",
		"schedule_version": 211,
		"new_producers": null,
		"header_extensions": [],
		"producer_signature": "SIG_K1_JwKXBzrSJcohdvfgE1w19UopH3gDecUPLb7pXVdwoJgAGqHwxhWd2zxe2eXWCS5PV57Wha7S5jo8PABJD7HJwayXtiGVe9",
		"transactions": [{
			"status": "executed",
			"cpu_usage_us": 100,
			"net_usage_words": 17,
			"trx": "35f2b45ab7818aff6afdfafe8c29afdc1b3e9716275c84d918d6440eb4d2cb88"
		}, {
			"status": "executed",
			"cpu_usage_us": 579,
			"net_usage_words": 51,
			"trx": {
				"id": "8887738f409f4e9f8566e0050683363589607f85968d38b749e43e07815f2bb2",
				"signatures": ["SIG_K1_JwDqng9ghjPtQMx8ngog1ByiFXgM8D9KEekLjAiNP4j1ZCKRm9DdEDcxjoRxtn9653so4f2hQjYaFYed3As3JNDhfUBDDD", "SIG_K1_KdBGcySEMnCv6rm1urm9jjv9fNp9CccyPHQZMQBGQL4hJM8e5e6AgNkzRQyjZ6ng2L5q1gKsJdS5E5srp7qKDbXgNBUX56", "SIG_K1_KjfdQN7NsuvozvbWmET3onPih839e3EWkV9d3di3daKNefuQTWLWtFtmTpoxXjfTTdaBTZic3Y6RWoMoTJ3gDNs2pG6Luu", "SIG_K1_Kct2VKQ3akKzApf2Kcf49AmYyP5XStj27UYbVP8PW85V2hzcyWiXwRNafJc4o2pMvuqHNU8BNnptgrPQnwUxY9c4ZSsasQ"],
				"compression": "none",
				"packed_context_free_data": "",
				"context_free_data": [],
				"packed_trx": "3343085d106f89c2723f000000000400a6823403ea3055000000572d3ccdcd0110c274321955cd6500000000a8ed32322110c274321955cd65104280d31c55cd65e80300000000000004454f53000000000000a6823403ea3055000000572d3ccdcd01104280d31c55cd6500000000a8ed323221104280d31c55cd6510d2d44b5d55cd651e0000000000000004454f53000000000000a6823403ea3055000000572d3ccdcd0110d2d44b5d55cd6500000000a8ed32323310d2d44b5d55cd65705572db2555cd651e0000000000000004454f5300000000124469766964656e64207472616e736665722e00a6823403ea3055000000572d3ccdcd01705572db2555cd6500000000a8ed323233705572db2555cd65a0f054b52b55cd65040000000000000004454f5300000000124f7065726174696e6720657870656e73652e00",
				"transaction": {
					"expiration": "2019-06-18T01:49:39",
					"ref_block_num": 28432,
					"ref_block_prefix": 1064485513,
					"max_net_usage_words": 0,
					"max_cpu_usage_ms": 0,
					"delay_sec": 0,
					"context_free_actions": [],
					"actions": [{
						"account": "eosio.token",
						"name": "transfer",
						"authorization": [{
							"actor": "grapeadmin11",
							"permission": "active"
						}],
						"data": {
							"from": "grapeadmin11",
							"to": "grapebank111",
							"quantity": "0.1000 EOS",
							"memo": ""
						},
						"hex_data": "10c274321955cd65104280d31c55cd65e80300000000000004454f530000000000"
					}, {
						"account": "eosio.token",
						"name": "transfer",
						"authorization": [{
							"actor": "grapebank111",
							"permission": "active"
						}],
						"data": {
							"from": "grapebank111",
							"to": "graperefund1",
							"quantity": "0.0030 EOS",
							"memo": ""
						},
						"hex_data": "104280d31c55cd6510d2d44b5d55cd651e0000000000000004454f530000000000"
					}, {
						"account": "eosio.token",
						"name": "transfer",
						"authorization": [{
							"actor": "graperefund1",
							"permission": "active"
						}],
						"data": {
							"from": "graperefund1",
							"to": "grapedivider",
							"quantity": "0.0030 EOS",
							"memo": "Dividend transfer."
						},
						"hex_data": "10d2d44b5d55cd65705572db2555cd651e0000000000000004454f5300000000124469766964656e64207472616e736665722e"
					}, {
						"account": "eosio.token",
						"name": "transfer",
						"authorization": [{
							"actor": "grapedivider",
							"permission": "active"
						}],
						"data": {
							"from": "grapedivider",
							"to": "grapeexpense",
							"quantity": "0.0004 EOS",
							"memo": "Operating expense."
						},
						"hex_data": "705572db2555cd65a0f054b52b55cd65040000000000000004454f5300000000124f7065726174696e6720657870656e73652e"
					}],
					"transaction_extensions": []
				}
			}
		}, {
			"status": "executed",
			"cpu_usage_us": 139,
			"net_usage_words": 21,
			"trx": {
				"id": "d5e53e9ecfdb010fe5c79eb091194cfdaf58d31b7823a71fd1881e0f825d2805",
				"signatures": ["SIG_K1_KXkKrHNrByRpZYgek3ifmN65K4adHUzHRw7wUoScwVCFERYrFNAN6bW4VfW2fbooiEt2nwX8zg29N71mCxkrpNrAJAgLjs"],
				"compression": "none",
				"packed_context_free_data": "",
				"context_free_data": [],
				"packed_trx": "3243085d106f89c2723f000000000100a6823403ea3055000000572d3ccdcd0190b1ca982a3fa7c600000000a8ed32324590b1ca982a3fa7c610c274321955cd65423d01000000000004454f530000000024454f534752414e44202d3e204752414e442044494345203a3a207b22526f6c6c223a327d00",
				"transaction": {
					"expiration": "2019-06-18T01:49:38",
					"ref_block_num": 28432,
					"ref_block_prefix": 1064485513,
					"max_net_usage_words": 0,
					"max_cpu_usage_ms": 0,
					"delay_sec": 0,
					"context_free_actions": [],
					"actions": [{
						"account": "eosio.token",
						"name": "transfer",
						"authorization": [{
							"actor": "sunnyeostest",
							"permission": "active"
						}],
						"data": {
							"from": "sunnyeostest",
							"to": "grapeadmin11",
							"quantity": "8.1218 EOS",
							"memo": "EOSGRAND -> GRAND DICE :: {\"Roll\":2}"
						},
						"hex_data": "90b1ca982a3fa7c610c274321955cd65423d01000000000004454f530000000024454f534752414e44202d3e204752414e442044494345203a3a207b22526f6c6c223a327d"
					}],
					"transaction_extensions": []
				}
			}
		}, {
			"status": "executed",
			"cpu_usage_us": 242,
			"net_usage_words": 43,
			"trx": {
				"id": "3f291545f3b2eda25a81d8b0579ce4245b1194dfb3308b86e8b67b3151bfba3d",
				"signatures": ["SIG_K1_Kiqv9zcqpWwkcGQgDAmYwJ8m3T9q5PpnWuDT41S95Qp5jvfcMURHCehUdCNJgVmK8UB24zA3kVRtq4ouU7cW1SBuJEbw7M"],
				"compression": "none",
				"packed_context_free_data": "",
				"context_free_data": [],
				"packed_trx": "3443085d106f89c2723f000000000310c254906655cd650000000000a531760110aed2183b55cd6500000000a8ed32323e10aed2183b55cd6560e31600000000000447524400000000254d616b6520746f6b656e20736f6d657468696e6720666f722079656c6c6f776b6969696e6710c254906655cd65000000572d3ccdcd0110aed2183b55cd6500000000a8ed32323010aed2183b55cd65c0a6730e721aa3f2804f12000000000004475244000000000f5452414e5346455220544f4b454e2e10c254906655cd65000000572d3ccdcd0110aed2183b55cd6500000000a8ed32324810aed2183b55cd6510c254683a55cd65e0930400000000000447524400000000274765742061205465616d20496e63656e746976652066726f6d2079656c6c6f776b6969696e672e00",
				"transaction": {
					"expiration": "2019-06-18T01:49:40",
					"ref_block_num": 28432,
					"ref_block_prefix": 1064485513,
					"max_net_usage_words": 0,
					"max_cpu_usage_ms": 0,
					"delay_sec": 0,
					"context_free_actions": [],
					"actions": [{
						"account": "grapetoken11",
						"name": "issue",
						"authorization": [{
							"actor": "grapeissuer1",
							"permission": "active"
						}],
						"data": {
							"to": "grapeissuer1",
							"quantity": "150.0000 GRD",
							"memo": "Make token something for yellowkiiing"
						},
						"hex_data": "10aed2183b55cd6560e31600000000000447524400000000254d616b6520746f6b656e20736f6d657468696e6720666f722079656c6c6f776b6969696e67"
					}, {
						"account": "grapetoken11",
						"name": "transfer",
						"authorization": [{
							"actor": "grapeissuer1",
							"permission": "active"
						}],
						"data": {
							"from": "grapeissuer1",
							"to": "yellowkiiing",
							"quantity": "120.0000 GRD",
							"memo": "TRANSFER TOKEN."
						},
						"hex_data": "10aed2183b55cd65c0a6730e721aa3f2804f12000000000004475244000000000f5452414e5346455220544f4b454e2e"
					}, {
						"account": "grapetoken11",
						"name": "transfer",
						"authorization": [{
							"actor": "grapeissuer1",
							"permission": "active"
						}],
						"data": {
							"from": "grapeissuer1",
							"to": "grapeincen11",
							"quantity": "30.0000 GRD",
							"memo": "Get a Team Incentive from yellowkiiing."
						},
						"hex_data": "10aed2183b55cd6510c254683a55cd65e0930400000000000447524400000000274765742061205465616d20496e63656e746976652066726f6d2079656c6c6f776b6969696e672e"
					}],
					"transaction_extensions": []
				}
			}
		}],
		"block_extensions": [],
		"id": "020e705e93c96cf46049aa477cc7d682871944871733a58420af935efa709f49",
		"block_num": 34500702,
		"ref_block_prefix": 1202342240
	}
}

```
 