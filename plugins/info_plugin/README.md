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
	"head_block_time": "2019-06-19T03:50:10.500",
	"last_irreversible_block_num": 34686352,
	"ref_block_prefix": 3859383589
}

```
 