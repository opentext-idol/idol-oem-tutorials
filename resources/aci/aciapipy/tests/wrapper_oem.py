"""
Make an ACI-encrypted 'GetStatus' request to an OEM-licensed ACI server.
"""
import context as aci

# 0. Initialize
client = aci.wrapper.AciClient()
client.create("REPLACE_WITH_MY_LONG_KEY_STRING")
client.printVersion()

# 1. Create the connection object
connection = aci.wrapper.AciConnection("127.0.0.1", 13000)
connection.create(client)
client.printToScreen(connection)

# 2. Create the command object
command = aci.wrapper.AciCommand("GetStatus")
command.create(client)
client.printToScreen(command)

# 3. Execute action
request = aci.wrapper.AciRequest(connection, command)
response = request.call(client)
print(response)
