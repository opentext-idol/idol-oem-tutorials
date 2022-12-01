"""
Capture the ACI server status from an ACI-encrypted 
'Fetch Identifiers' request to an OEM-licensed IDOL Dropbox Connector.
"""
import context as aci
import json

response = aci.client.call(
  encryption_key="<REPLACE_WITH_MY_LONG_KEY_STRING>",
  hostname="127.0.0.1",
  port=7030,
  aci_action="Fetch",
  aci_params = {
    "FetchAction": "Identifiers",
    "MaxDepth": 0,
    "ConfigSection": "MyTask1",
    "ResponseFormat": "simplejson"
  }
)
# print(response)

try:
  data = json.loads(response)
  token = data["autnresponse"]["responsedata"]["token"]
  print(token)

except json.decoder.JSONDecodeError:
  print("ERROR: Response does not contain valid JSON.")
  print(response)