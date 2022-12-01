"""
Insert a file into Dropbox using an ACI-encrypted 'Fetch' request to 
an OEM-licensed IDOL Dropbox Connector.
"""
import context as aci
import json, os, sys

try:
  source_path = os.path.normpath(
    os.path.join(os.getcwd(), sys.argv[1])
  )

except IndexError:
  print("File name not provided. This script should be run as follows:\npython insert_file.py my_file.ext")

# Build XML options
file_name = os.path.split(source_path)[1]
target_folder = "/".join(["Documents"])
target_path = "/".join(["", target_folder, file_name])
insert_xml = f"""<insertXML>
  <insert>
    <property name="PATH" value="{target_path}"/>
    <file>
      <type>file</type>
      <content>{source_path}</content>
    </file>
  </insert>
</insertXML>"""

# Run the action
response = aci.client.call(
  encryption_key="<REPLACE_WITH_MY_LONG_KEY_STRING>",
  hostname="127.0.0.1",
  port=7030,
  aci_action="Fetch",
  aci_params = {
    "FetchAction": "Insert",
    "ConfigSection": "MyTask1",
    "InsertXML": insert_xml,
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
