"""
Make an ACI-encrypted 'GetStatus' request to an OEM-licensed ACI server.
"""
import context as aci

response = aci.client.call(
  encryption_key="REPLACE_WITH_MY_LONG_KEY_STRING",
  hostname="127.0.0.1", 
  port=13000, 
  aci_action="GetStatus"
)
print(response)
