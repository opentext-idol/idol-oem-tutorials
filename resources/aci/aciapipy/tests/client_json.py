"""
Make a 'GetStatus' request to an ACI server, receiving JSON.
"""
import context as aci

response = aci.client.call(
  hostname="127.0.0.1", 
  port=14000, 
  aci_action="GetStatus",
  aci_params = {
    "ResponseFormat": "simplejson"
  }
)
print(response)
