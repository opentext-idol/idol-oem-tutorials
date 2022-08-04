"""
Make a 'GetStatus' request to an ACI server.
"""
import context as aci

# 0. Initialize
client = aci.wrapper.AciClient()
client.create()
client.printVersion()

# 1. Create the connection object
connection = aci.wrapper.AciConnection("127.0.0.1", 14000)
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
