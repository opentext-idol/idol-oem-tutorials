from . import wrapper

def call(hostname, port, aci_action, aci_params={}, encryption_key=None):

  # 0. Initialize
  client = wrapper.AciClient()
  client.create(encryption_key)

  # 1. Create the connection object
  connection = wrapper.AciConnection(hostname, port)
  connection.create(client)

  # 2. Create the command object
  command = wrapper.AciCommand(aci_action, aci_params)
  command.create(client)

  # 3. Execute action
  request = wrapper.AciRequest(connection, command)
  response = request.call(client)
  return response
