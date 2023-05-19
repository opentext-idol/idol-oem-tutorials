#!/bin/sh

ACI_API_HOME=../../../../../../IDOLCSDK_23.2.0_LINUX_X86_64
ACI_API_LIB=$ACI_API_HOME

LD_LIBRARY_PATH=$ACI_API_HOME
export LD_LIBRARY_PATH

# Replace the values for the following parameters for your environment
# The TOKEN value will be returned from a=fetch or similar
ACI_HOST=localhost
ACI_PORT=7010
QUEUE_NAME=ingest
#TOKEN=MTI3LjAuMS4xOjcwMDA6SU5HRVNUOjE2NTk5ODI1NTIwMDY2ODAxNjEyNjk3MjAz
TOKEN=

ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY=REPLACE_WITH_MY_LONG_KEY_STRING
export ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY

./queueInfo_getStatus.exe $ACI_HOST $ACI_PORT $QUEUE_NAME $TOKEN

