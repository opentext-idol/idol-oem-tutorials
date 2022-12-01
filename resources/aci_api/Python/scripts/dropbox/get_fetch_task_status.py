"""
Capture the ACI server status from an ACI-encrypted 
'Fetch Task Status' request to an OEM-licensed IDOL Dropbox Connector.
"""
import context as aci
import json, sys

try:
  token_file = sys.argv[1]

except IndexError:
  print("Token file not provided. This script should be run as follows:\npython get_fetch_task_status.py token.txt")

try:
  with open(token_file) as t:
    token = t.read().rstrip()

except FileNotFoundError:
  print(f'Token file "{token_file}" not found.')

response = aci.client.call(
  encryption_key="<REPLACE_WITH_MY_LONG_KEY_STRING>",
  hostname="127.0.0.1",
  port=7030,
  aci_action="QueueInfo",
  aci_params = {
    "QueueAction": "GetStatus",
    "QueueName": "Fetch",
    "token": token,
    "ResponseFormat": "simplejson"
  }
)
# print(response)

try:
  data = json.loads(response)
  # token = data["autnresponse"]["responsedata"]["token"]
  print(json.dumps(data, indent=2))

except json.decoder.JSONDecodeError:
  print("ERROR: Response does not contain valid JSON.")
  print(response)