import ctypes, enum, os
from dotenv import load_dotenv

load_dotenv()

# 
# NULL Pointers
# 
class AciObject(ctypes.c_void_p): pass

# 
# Enums
# 
class CtypesEnum(enum.IntEnum):
  @classmethod
  def from_param(cls, obj):
    return int(obj)

class AciObjectType(CtypesEnum):
  ACI_CONNECTION = 1
  ACI_COMMAND = 2
  ACI_DATA = 3
  ACI_DATA_ELEMENT = 4	
  ACI_DATA_TEXT = 5

# 
# Objects
# 
class AciClient():
  """
  A class to represent an ACI Client.
  """
  variables = {}

  def __init__(self):
    """
    Load the ACI API C library and header file for definitions.
    """
    lib_path = os.getenv("ACI_LIB_PATH", os.getcwd())
    self._lib = ctypes.CDLL(os.path.join(lib_path, "aciclient"))
    self._header_path = os.path.join(lib_path, "client.h")
    self._captureDefinedVariables()
    
  def __del__(self):
    self._lib.aciShutDown()

  def _captureDefinedVariables(self):
    """
    #define		ACI_CONN_RETRIES				"ACIO RETRIES"
    """
    with open(self._header_path, "r") as header:
      for line in header.readlines():
        if not line.strip().startswith("#define"): continue
        if -1 == line.find('"'): continue
        property = line.replace("#define", "").strip().split("\t")[0]
        self.variables[property] = line.strip().split("\t")[-1].strip('"')

  def getErrorDescription(self, error_code):
    """
    Return the error message.
    """
    acioGetErrorDescription = self._lib.acioGetErrorDescription
    acioGetErrorDescription.restype = ctypes.c_char_p
    return acioGetErrorDescription(error_code).decode()

  def raiseException(self, error_code):
    """
    Throw error from C library.
    """
    error_description = self.getErrorDescription(error_code)
    raise Exception(f"ACI API [{error_code}]: {error_description}")

  def create(self, encryption_keys=None):
    """
    Call this function to set up optional ACI encryption.
    Provide the long key shipped with your OEM `licensekey.dat`.
    """
    self.init()
    if not encryption_keys is None:
      self.initEncryption(encryption_keys)
    
  def createConnection(self):
    connection = AciObject()
    sc = self._lib.aciObjectCreate(ctypes.byref(connection), AciObjectType.ACI_CONNECTION)
    if sc==0: 
      return connection
    else:
      self.raiseException(sc)

  def createCommand(self):
    command = AciObject()
    sc = self._lib.aciObjectCreate(ctypes.byref(command), AciObjectType.ACI_COMMAND)
    if sc==0: 
      return command
    else:
      self.raiseException(sc)

  def executeToString(self, connection, command):
    response = ctypes.c_char_p()
    response_length = ctypes.c_int()

    sc = self._lib.aciObjectExecuteToString(
      connection.getAciObject(),
      command.getAciObject(),
      ctypes.byref(response),
      ctypes.byref(response_length),
      None
    )
    if sc==0: 
      # print(response_length)
      return response.value.decode("utf-8")
    else:
      self.raiseException(sc)

  def getVersion(self):
    """
    Return the version string of the ACI client.
    """
    aciGetVersion = self._lib.aciObjectGetVersion
    aciGetVersion.restype = ctypes.c_char_p
    return aciGetVersion().decode()

  def init(self):
    self._lib.aciInit()

  def initEncryption(self, encryption_keys, oem_licensed=True, encryption_type="TEA"):
    self._lib.aciInitEncryption(oem_licensed, encryption_type.encode("utf-8"), encryption_keys.encode("utf-8"))

  def namedParamSetValue(self, connection, var_name, param_value):
    if type(param_value) is int:
      sc = self._lib.aciObjectParamSetInt(connection, var_name.encode("utf-8"), param_value)

    elif type(param_value) is bool:
      sc = self._lib.aciObjectParamSetBool(connection, var_name.encode("utf-8"), param_value)

    else:
      sc = self._lib.aciObjectParamSetString(connection, var_name.encode("utf-8"), param_value.encode("utf-8"))
    
    if not sc==0: self.raiseException(sc)

  def paramSetValue(self, connection, param_name, param_value):
    var_name = self.variables[param_name]
    self.namedParamSetValue(connection, var_name, param_value)

  def printVersion(self):
    print(self.getVersion())

  def printToScreen(self, aci_base_instance):
    aci_object = aci_base_instance.getAciObject()
    aciObjectToString = self._lib.aciObjectToString
    return aciObjectToString(aci_object)

class AciBase():
  def create(self): pass
  def getAciObject(self): pass

class AciConnection(AciBase):
  """
  A class to represent an ACI Connection.
  """
  def __init__(self, host, port, num_retries=1):
    self.host = host
    self.port = port
    self.num_retries = num_retries

  def create(self, client):
    self.connection = client.createConnection()
    client.paramSetValue(self.connection, "ACI_HOSTNAME", self.host)
    client.paramSetValue(self.connection, "ACI_PORTNUMBER", self.port)
    client.paramSetValue(self.connection, "ACI_CONN_RETRIES", self.num_retries)

  def getAciObject(self):
    return self.connection

class AciCommand(AciBase):
  """
  A class to represent an ACI Command.
  NOTE: Multi-part form data is not supported with ACI Encryption,
  however, enabling post does allow for longer* query strings.
  * Details of which TBC
  """
  def __init__(self, action, params={}, post=True):
    self.action = action
    self.params = params
    self.post = post

  def create(self, client):
    self.command = client.createCommand()
    client.paramSetValue(self.command, "ACI_COM_USE_POST", self.post)
    client.paramSetValue(self.command, "ACI_COM_COMMAND", self.action)
    for param_name in self.params.keys():
      client.namedParamSetValue(self.command, param_name, self.params[param_name])

  def getAciObject(self):
    return self.command

class AciRequest():
  """
  A class to represent an ACI Request.
  """
  def __init__(self, connection, command):
    self.connection = connection
    self.command = command

  def call(self, client):
    return client.executeToString(self.connection, self.command)

# 
# Main Execution
# 
if __name__ == "__main__":

  # 0. Initialize
  client = AciClient()
  client.create("REPLACE_WITH_MY_LONG_KEY_STRING")
  client.printVersion()

  # 1. Create the connection object
  connection = AciConnection("127.0.0.1", 13000)
  connection.create(client)
  client.printToScreen(connection)

  # 2. Create the command object
  command = AciCommand("GetStatus")
  command.create(client)
  client.printToScreen(command)

  # 3. Execute action
  request = AciRequest(connection, command)
  response = request.call(client)
  print(response)
