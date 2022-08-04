"""
Capture the ACI server name and version from an ACI-encrypted 'GetVersion' request 
to an OEM-licensed IDOL Eduction Server, receiving JSON.
"""
import context as aci
import json

response = aci.client.call(
  encryption_key="REPLACE_WITH_MY_LONG_KEY_STRING",
  hostname="127.0.0.1", 
  port=13000, 
  aci_action="GetVersion",
  aci_params = {
    "ResponseFormat": "simplejson"
  }
)
# print(response)
try:
  data = json.loads(response)

  name = data["autnresponse"]["responsedata"]["productname"]
  version = data["autnresponse"]["responsedata"]["version"]
  print(f'{name} v{version}')

except json.decoder.JSONDecodeError:
  print("ERROR: Response does not contain valid JSON.")
  print(response)
