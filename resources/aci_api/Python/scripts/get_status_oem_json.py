"""
Capture the ACI server status from an ACI-encrypted 
'GetStatus' request to an OEM-licensed IDOL ACI Server, receiving JSON.
"""
import context as aci
import json

response = aci.client.call(
  encryption_key="<REPLACE_WITH_MY_LONG_KEY_STRING>",
  hostname="127.0.0.1",
  port="<REPLACE_WITH_ACI_PORT>",
  aci_action="GetStatus",
  aci_params = {
    "ResponseFormat": "simplejson"
  }
)
# print(response)

try:
  data = json.loads(response)
  action = data["autnresponse"]["action"]
  status = data["autnresponse"]["response"]
  print(f'{action}: {status}')

except json.decoder.JSONDecodeError:
  print("ERROR: Response does not contain valid JSON.")
  print(response)
