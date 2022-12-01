"""
Capture the ACI server name and version from an ACI-encrypted 
'GetVersion' request to an OEM-licensed IDOL ACI Server.
"""
import context as aci
import xml.etree.ElementTree as ET

response = aci.client.call(
  encryption_key="<REPLACE_WITH_MY_LONG_KEY_STRING>",
  hostname="127.0.0.1",
  port="<REPLACE_WITH_ACI_PORT>",
  aci_action="GetVersion"
)
# print(response)

root = ET.fromstring(response)
namespaces = {'autn': 'http://schemas.autonomy.com/aci/'}
name = root.find(".//autn:commonname", namespaces).text
version = root.find(".//autn:version", namespaces).text
print(f'{name} v{version}')
