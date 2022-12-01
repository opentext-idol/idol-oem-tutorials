"""
Collect files from Dropbox using an ACI-encrypted 'Fetch' request to 
an OEM-licensed IDOL Dropbox Connector.
"""
import context as aci
import json

file_ids = [
  "PGlkIHQ9IkZpbGUiIHM9Ik1ZVEFTSzEiIHI9ImRiaWQ6QUFBNjNieWNEckh5NG1ERUpCSEpoalZya0YxM0xONEVCX3c6L2RvY3VtZW50cy9kcm9wYm94Y29ubmVjdG9yXzEyLjEyX2FkbWluX2VuLnBkZiI+PHAgbj0iUEFUSCIgdj0iL2RvY3VtZW50cy9kcm9wYm94Y29ubmVjdG9yXzEyLjEyX2FkbWluX2VuLnBkZiIvPjxwIG49IlVJRCIgdj0iZGJpZDpBQUE2M2J5Y0RySHk0bURFSkJISmhqVnJrRjEzTE40RUJfdyIvPjwvaWQ+"
]

response = aci.client.call(
  encryption_key="<REPLACE_WITH_MY_LONG_KEY_STRING>",
  hostname="127.0.0.1",
  port=7030,
  aci_action="Fetch",
  aci_params = {
    "FetchAction": "Delete",
    "Identifiers": ",".join(file_ids),
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
  