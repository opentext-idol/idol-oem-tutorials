"""
Capture entity matches from text you submit to an OEM-licensed IDOL Eduction Server:
$ python educe_from_text_oem.py > matches.csv

NOTE: Configure IDOL Eduction Server with 'ResourceFiles=grammars/internet.ecr'.
"""
import context as aci
import xml.etree.ElementTree as ET

response = aci.client.call(
  encryption_key="<REPLACE_WITH_MY_LONG_KEY_STRING>",
  hostname="127.0.0.1", 
  port=13000, 
  aci_action="EduceFromText",
  aci_params = {
    "Text": "Simon received email from christopher.blanks@opentext.com and chris.blanks@opentext.com today.",
    "Entities": "internet/addr_email"
  }
)
# print(response)

root = ET.fromstring(response)
namespaces = {'autn': 'http://schemas.autonomy.com/aci/'}

print(",".join(["offset", "match", "score"]))

for hit in root.findall(".//autn:hit", namespaces):
  match = hit.find(".//normalized_text").text
  offset = int(hit.find(".//offset").text)
  score = float(hit.find(".//score").text)

  print(",".join([str(offset), match, f'{score:.1f}']))
