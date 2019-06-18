# permission_plugin

permission_plugin is designed to get permssion detail of account. comparing with chain_api_plugin, the permission plugin can get the link action of each permission.

# how to add the permission plugin

1.download the permission plugin code

```
cd eos/plugin;
git clone git@github.com:tokenbankteam/permission_plugin.git

```
 
2.modify eos/plugins/CMakeLists.txt

```
add_subdirectory(permission_plugin)

```

3.modify eos/programs/nodeos/CMakeLists.txt

```
target_link_libraries( ${NODE_EXECUTABLE_NAME} PRIVATE -Wl,${whole_archive_flag} permission_plugin -Wl,${no_whole_archive_flag} )
```

# how to test the permission plugin

/v1/permission/get_permission

```
curl -X POST --url http://127.0.0.1:8888/v1/permission/get_permission -d '{"account_name":"huoyantest11"}'
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

 