"""
Capture the ACI server name and version from a 'GetVersion' 
request to a non-OEM licensed IDOL ACI Server.
"""
import context as aci
import xml.etree.ElementTree as ET

response = aci.client.call(
  hostname="127.0.0.1",
  port="<REPLACE_WITH_ACI_PORT>",
  aci_action="GetVersion"
)
# print(response)
root = ET.fromstring(response)

namespaces = {'autn': 'http://schemas.autonomy.com/aci/'}
name = root.find(".//autn:productname", namespaces).text
version = root.find(".//autn:version", namespaces).text
print(f'{name} v{version}')
